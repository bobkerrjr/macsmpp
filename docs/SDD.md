# Software Design Document (SDD)

**Projeto:** macsmpp  
**Repositório:** [https://github.com/bobkerrjr/macsmpp](https://github.com/bobkerrjr/macsmpp)  
**Versão do documento:** 1.0  
**Data:** 2026-09-01  
**SRD correspondente:** [SRD.md](SRD.md)

Este documento descreve **como** o sistema está organizado. Toda mudança estrutural, de fluxo, de classe ou de dívida técnica relevante deve atualizar este SDD na mesma sessão. Ver [AGENTS.md](../AGENTS.md).

---

## 1. Visão da arquitetura

Hoje o binário é um **codec SMPP + harness**, não um daemon de gateway. A arquitetura-alvo do produto (SRD P-01) é um ESME TCP; a arquitetura implementada é uma biblioteca de PDUs acionada por `main.cpp`.

```
┌─────────────────────────────────────────────────────────┐
│  main.cpp  (harness: 28 PDUs concatenadas)              │
└───────────────────────────┬─────────────────────────────┘
                            │ pduDecode / pduEncode / printPduInfo
┌───────────────────────────▼─────────────────────────────┐
│  SmppPdu                                                │
│    ├── SmppHeader  (16 octetos, big-endian)             │
│    └── SmppBody*   (factory por command_id)             │
│          ├── BindDummy / BindRespDummy                  │
│          ├── SubmitSm, DeliverSm, DataSm, …             │
│          └── TagLengthValue[]  (opcionais)              │
└─────────────────────────────────────────────────────────┘
         │                        │
         ▼                        ▼
   types/                    utilities/
   UnsignedInteger           endianSwap
   UnsignedByte              numOfProcessors
```

Não existe ainda camada de transporte, configuração ou sessão.

## 2. Layout do repositório

```
macsmpp/
  main.cpp                          Harness de decode/encode
  pduExamples.h                     PDUs de exemplo (também inline em main.cpp)
  protocols/smpp/                   Codec SMPP
  types/                            Inteiros com swap de endian
  utilities/                        endianSwap, numOfProcessors
macsmpp.xcodeproj/                  Projeto Xcode (macOS)
docs/
  SRD.md
  SDD.md
AGENTS.md
```

Plataforma de build: Xcode. Não há Makefile/CMake no repositório.

## 3. Princípios de desenho

1. **Uma classe por PDU (ou família).** PDUs de bind compartilham `BindDummy`; respostas de bind compartilham `BindRespDummy`.
2. **Header separado do body.** Header sempre existe; body é opcional.
3. **Factory no decode.** `SmppPdu::pduDecode` faz `switch (command_id)` e instancia a subclasse.
4. **Ciclo de vida explícito.** `init()` / `destroy()` em vez de depender só do construtor, para reutilizar a mesma instância no loop do harness.
5. **Versão como bitmask.** `myPossibleVersion` (ex.: `0x07` = 3.3+3.4+5.0) e `isVersion(0x33|0x34|0x50)`.
6. **Tipos nomeados.** `CommandId`, `CommandStatus`, `TypeOfNumber`, `NumberingPlanIndicator`, `EsmClass` herdam de `UnsignedInteger` ou `UnsignedByte` e carregam strings diagnósticas.

## 4. Camadas

### 4.1 Tipos (`macsmpp/types`)

| Classe | Papel |
| --- | --- |
| `UnsignedInteger` | `uint32_t` + `endianSwap()` |
| `UnsignedByte` | `uint8_t` + impressão |

`CommandId` e `CommandStatus` especializam `UnsignedInteger` com tabelas de nome curto e nome longo (espelhando o spec SMPP).

### 4.2 Utilitários (`macsmpp/utilities`)

| Unidade | Papel |
| --- | --- |
| `endianSwap` | Troca 16/32/64 bits em MACOS e WINDOWS; LINUX marcado TODO (`cpu_to_be32`) |
| `numOfProcessors` | Detecta número de CPUs (C + header C++); ainda não usado pelo codec |

Constantes de protocolo ficam em `SmppUtilities.h` (não em um `.cpp` de rede).

### 4.3 Header (`SmppHeader`)

Quatro campos, nesta ordem, 4 octetos cada, **big-endian na fiação**:

1. `command_length` — tamanho total da PDU, inclusive estes 16 bytes
2. `command_id`
3. `command_status`
4. `sequence_number`

`pduDecode` lê `uint32_t*` e chama `endianSwap` em cada campo. `pduEncode` faz o caminho inverso só para o header.

### 4.4 Body (`SmppBody` e subclasses)

Interface:

- `init()`, `destroy()`
- `pduDecode(char*, uint32_t commandLength)`
- `printPduInfo()`
- `isVersion(uint8_t)`, `getIsValid()`, `getNumOfByteErrors()`

`pduEncode` no body está **comentado** na classe base. Encode de body não faz parte do desenho ativo.

Subclasses notáveis:

| Classe | Uso |
| --- | --- |
| `BindDummy` | Campos comuns de bind: `system_id`, `password`, `system_type`, `interface_version`, TON/NPI, `address_range` |
| `BindReceiver` / `BindTransmitter` / `BindTransceiver` | Herdam `BindDummy`; só ajustam `myPossibleVersion` |
| `BindRespDummy` | `system_id` + TLV `sc_interface_version` |
| `SubmitSm` / `DeliverSm` / `DataSm` | Campos de mensagem + dezenas de ponteiros TLV |
| `SubmitMulti` | Lista de `SmeAddress` / `DistributionListAddress` via `SmeOrDlAddress` |
| `TagLengthValue` | tag `uint16`, length `uint16`, value; nome via `optionalParameterTagDef.h` |

### 4.5 Agregado (`SmppPdu`)

Responsável por:

1. Destruir header/body anteriores (`destroy`)
2. Decodificar header
3. Se `command_length > 16`, despachar o body
4. PDUs só-header: `body = NULL`
5. `command_id` default: `isValid = false`
6. `getIsValid()` = flag do PDU **e** do body
7. `isVersion()` = header **e** body (se existir)

## 5. Fluxo de decode

```
buffer ──► SmppPdu::pduDecode
              │
              ├─► new SmppHeader(buffer)     // 16 bytes, endian swap
              │
              └─► switch(command_id)
                    ├─ known + has body  → new ConcreteBody(buffer, length)
                    ├─ known header-only → body = NULL
                    └─ unknown           → body = NULL, isValid = false
```

O harness avança o ponteiro com `temp += header->getCommandLength()` para a próxima PDU concatenada.

## 6. Fluxo de encode (estado atual)

```
SmppPdu::pduEncode
    → aloca command_length bytes
    → SmppHeader::pduEncode(buffer)
    → NÃO serializa o body
    → retorna o buffer (o chamador dá delete)
```

Isso atende FR-06 apenas em parte. Completar o encode implica:

1. Restaurar `SmppBody::pduEncode` como virtual
2. Implementar em cada subclass
3. Recalcular `command_length` depois dos TLVs

## 7. Versões SMPP

`SMPP_SUPPORTED_VERSION(X)` aceita `0x33`, `0x34`, `0x50`.

Cada body define `myPossibleVersion` (bitmask). Exemplo: `BindReceiver::init` usa `0x07` (as três versões). PDUs 3.3-only (`param_retrieve`, `query_last_msgs`, `query_msg_details`) e 5.0-only (`broadcast_sm` e família) restringem a máscara.

`interface_version` no bind é um octeto no wire (`0x34` nos exemplos = SMPP 3.4).

## 8. Dívida técnica conhecida

Registrar aqui evita redescobrir o mesmo gap:

| Item | Evidência | Impacto |
| --- | --- | --- |
| Encode de body desligado | `SmppBody.h` linha comentada; `pduEncode` só chama o header | Round-trip incompleto |
| Sem camada TCP/sessão | Nenhum socket no código | Gateway (P-01) inexistente |
| Linux endian TODO | `endianSwap.h` | Portabilidade |
| `dynamic_cast` desnecessário | `SmppPdu.cpp` após `new Concrete` | Ruído, não bug |
| PDUs de exemplo duplicadas | `main.cpp` e `pduExamples.h` | Manutenção dupla |
| Harness não usa `pduExamples.h` | `examplePDUs` está em `main.cpp` | Header órfão |
| Sem testes automatizados | Só loop em `main` | Regressão manual |
| `xcuserdata` commitado | `macsmpp.xcodeproj/xcuserdata` | Ruído de IDE |
| Cancel/replace/unbind resp sem body | Intencional (spec) | Não é bug |

## 9. Harness (`main.cpp`)

1. Cria um `SmppPdu` reutilizado.
2. Itera 28 PDUs no buffer `examplePDUs`.
3. Para cada uma: decode, `printPduInfo`, checa versões, checa validade, encode do header, imprime hex, avança `command_length`.
4. Bloco de benchmark (5000 voltas × 27 PDUs) está comentado.

Conjunto coberto pelos exemplos: alert_notification, binds (RX/TX/TRX) e resps, outbind, cancel_sm, data_sm, deliver_sm, enquire_link, generic_nack, query_sm, replace_sm, submit_sm, submit_multi, unbind.

## 10. Desenho futuro do gateway

Não implementar nesta sessão; registrar a direção para não retrabalhar o codec:

```
Config ──► Session (TCP)
              ├── SequenceNumber allocator
              ├── Bind state machine (unbound / bound_tx / bound_rx / bound_trx)
              ├── EnquireLink timer
              └── Codec (SmppPdu)  ← já existe
```

O codec deve permanecer independente de I/O: `char*` in, `uint8_t*` out. A sessão futura consome essa API, não o contrário.

## 11. Mapa SRD → código

| SRD | Unidade de código |
| --- | --- |
| FR-01 | `SmppHeader.cpp` |
| FR-02 | `SmppPdu::pduDecode` |
| FR-03, FR-04 | mesmo switch, ramos header-only e `default` |
| FR-05 | `CommandId`, `CommandStatus` |
| FR-06 | `SmppPdu::pduEncode` + gap no body |
| FR-08, §7 | `SmppUtilities.h` |
| FR-30..33 | `main.cpp`, `pduExamples.h` |
| NFR-03 | `endianSwap`, `UnsignedInteger::endianSwap` |
| P-01, FR-20..26 | inexistente — sessão TCP |

## 12. Histórico

| Versão | Data | Alteração |
| --- | --- | --- |
| 1.0 | 2026-09-01 | Desenho extraído do código em `origin/master` |
