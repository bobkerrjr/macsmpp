# Software Requirements Document (SRD)

**Projeto:** macsmpp  
**Repositório:** [https://github.com/bobkerrjr/macsmpp](https://github.com/bobkerrjr/macsmpp)  
**Versão do documento:** 1.0  
**Data:** 2026-09-01  
**Fonte:** código-fonte existente (commit `210008f`, “Primeira versão”) e descrição do repositório (“My personal SMPP gateway.”)

Este documento descreve **o que** o sistema deve fazer. Mudanças de requisito, decisão de produto ou comportamento observado devem ser refletidas aqui na mesma sessão em que forem ditas ou implementadas. Ver [AGENTS.md](../AGENTS.md).

---

## 1. Propósito

macsmpp é um **gateway SMPP pessoal**: um software local (macOS, com intenção de portabilidade) capaz de falar o protocolo Short Message Peer-to-Peer (SMPP) com um SMSC, para enviar, receber, consultar, substituir e cancelar mensagens SMS.

O código atual cobre principalmente a **camada de codec de PDUs** (decode, validação, inspeção e encode parcial) e um **harness de testes** com PDUs de exemplo. A sessão TCP, o ciclo de vida de bind e o roteamento de mensagens ainda não estão implementados como gateway.

## 2. Escopo

### 2.1 Em escopo (produto)

| ID | Requisito de produto |
| --- | --- |
| P-01 | Operar como cliente SMPP (ESME) contra um SMSC |
| P-02 | Codificar e decodificar PDUs SMPP 3.3, 3.4 e 5.0 |
| P-03 | Autenticar via `bind_transmitter`, `bind_receiver` e `bind_transceiver` |
| P-04 | Enviar SMS (`submit_sm`, `submit_multi`, `data_sm`) |
| P-05 | Receber SMS e receipts (`deliver_sm`, `alert_notification`) |
| P-06 | Consultar, substituir e cancelar mensagens |
| P-07 | Manter o enlace (`enquire_link` / `enquire_link_resp`) |
| P-08 | Interpretar `command_status` e `generic_nack` |
| P-09 | Suportar parâmetros opcionais TLV conforme a versão do protocolo |

### 2.2 Implementado hoje (baseline)

| ID | Capacidade presente no código |
| --- | --- |
| B-01 | Decode de header SMPP de 16 octetos (big-endian) |
| B-02 | Factory de body por `command_id` |
| B-03 | Decode de PDUs listados na seção 5 |
| B-04 | Detecção de versão 3.3 / 3.4 / 5.0 (`0x33`, `0x34`, `0x50`) |
| B-05 | Validação básica (`isValid`, `numOfByteErrors`) |
| B-06 | Impressão diagnóstica de header, body e TLVs |
| B-07 | Encode do header; encode do body ainda não está ligado |
| B-08 | Harness em `main.cpp` que percorre 28 PDUs concatenados de exemplo |

### 2.3 Fora de escopo atual

- Interface gráfica de usuário
- Persistência de mensagens / banco de dados
- Cluster, alta disponibilidade ou billing
- Protocolos que não sejam SMPP (HTTP, CIMD, UCP)
- SMSC completo (o papel atual é ESME / codec, não o kernel do SMSC)

## 3. Definições

| Termo | Significado |
| --- | --- |
| **SMPP** | Short Message Peer-to-Peer, protocolo binário sobre TCP |
| **PDU** | Protocol Data Unit: header (16 bytes) + body + TLVs opcionais |
| **ESME** | External Short Message Entity — o cliente (este software) |
| **SMSC** | Short Message Service Center — o servidor remoto |
| **TLV** | Tag-Length-Value, parâmetro opcional no body |
| **TON / NPI** | Type of Number / Numbering Plan Indicator |
| **Bind** | Autenticação e modo da sessão (TX, RX ou TRX) |

## 4. Atores

- **Operador / dono do gateway:** configura host, porta, `system_id`, senha e modo de bind.
- **SMSC remoto:** parceiro SMPP.
- **Desenvolvedor / agente de IA:** evolui codec, gateway e documentação.

## 5. Requisitos funcionais

Prioridade: **M** must, **S** should, **C** could.  
Status: **feito**, **parcial**, **não feito**.

### 5.1 Codec de protocolo

| ID | Descrição | Pri | Status |
| --- | --- | --- | --- |
| FR-01 | Decodificar `command_length`, `command_id`, `command_status`, `sequence_number` em big-endian | M | feito |
| FR-02 | Instanciar o body correto a partir de `command_id` | M | feito |
| FR-03 | PDUs só-header (`enquire_link`, `unbind`, `generic_nack` e respostas equivalentes) não devem alocar body | M | feito |
| FR-04 | `command_id` desconhecido marca a PDU como inválida | M | feito |
| FR-05 | Imprimir nome curto e nome completo de `command_id` e `command_status` | S | feito |
| FR-06 | Codificar PDU completa (header + body + TLVs) | M | parcial (só header) |
| FR-07 | Round-trip decode → encode deve reproduzir a PDU original quando válida | S | não feito |
| FR-08 | Respeitar limites de campo de `SmppUtilities.h` (system_id, password, short_message, etc.) | M | parcial |

### 5.2 PDUs obrigatórias (versões 3.3, 3.4 e 5.0)

Decode implementado, salvo indicação.

| command_id | PDU | Notas |
| --- | --- | --- |
| `0x00000001` / `0x80000001` | bind_receiver / resp | Body compartilhado (`BindDummy` / `BindRespDummy`) |
| `0x00000002` / `0x80000002` | bind_transmitter / resp | Idem |
| `0x00000009` / `0x80000009` | bind_transceiver / resp | 3.4 e 5.0 |
| `0x00000006` / `0x80000006` | unbind / resp | Só header |
| `0x00000004` / `0x80000004` | submit_sm / resp | Campos obrigatórios + TLVs 3.4/5.0 |
| `0x00000005` / `0x80000005` | deliver_sm / resp | Inclui short_message longa nos exemplos |
| `0x00000021` / `0x80000021` | submit_multi / resp | Destinos SME e distribution list |
| `0x00000003` / `0x80000003` | query_sm / resp | |
| `0x00000007` / `0x80000007` | replace_sm / resp | resp só header |
| `0x00000008` / `0x80000008` | cancel_sm / resp | resp só header |
| `0x00000015` / `0x80000015` | enquire_link / resp | Só header |
| `0x80000000` | generic_nack | Só header |
| `0x0000000B` | outbind | 3.4 e 5.0 |
| `0x00000102` | alert_notification | 3.4 e 5.0 |
| `0x00000103` / `0x80000103` | data_sm / resp | 3.4 e 5.0 |

### 5.3 PDUs específicas de versão

| command_id | PDU | Versão | Status decode |
| --- | --- | --- | --- |
| `0x00000022` / `0x80000022` | param_retrieve / resp | 3.3 | feito |
| `0x00000023` / `0x80000023` | query_last_msgs / resp | 3.3 | feito |
| `0x00000024` / `0x80000024` | query_msg_details / resp | 3.3 | feito |
| `0x00000111` / `0x80000111` | broadcast_sm / resp | 5.0 | feito |
| `0x00000112` / `0x80000112` | query_broadcast_sm / resp | 5.0 | feito |
| `0x00000113` / `0x80000113` | cancel_broadcast_sm / resp | 5.0 | feito (resp só header) |

### 5.4 Gateway (ainda não implementado)

| ID | Descrição | Pri | Status |
| --- | --- | --- | --- |
| FR-20 | Conectar via TCP a host:porta do SMSC | M | não feito |
| FR-21 | Enviar bind e tratar bind_resp (`system_id`, `sc_interface_version`) | M | não feito |
| FR-22 | Manter `enquire_link` periódico e reagir a timeout | M | não feito |
| FR-23 | Filas de envio e de entrega | S | não feito |
| FR-24 | Correlacionar request/response por `sequence_number` (1..0x7FFFFFFF) | M | não feito |
| FR-25 | Aceitar `outbind` do SMSC | C | não feito |
| FR-26 | Configuração (credenciais, TON/NPI, versão de interface) sem recompilar | S | não feito |
| FR-27 | Log de sessão e de PDU em formato legível | S | parcial (`printPduInfo`) |

### 5.5 Diagnóstico e testes

| ID | Descrição | Pri | Status |
| --- | --- | --- | --- |
| FR-30 | Banco de PDUs de exemplo cobrindo os fluxos principais | S | feito (`examplePDUs` em `main.cpp` / `pduExamples.h`) |
| FR-31 | Percorrer PDUs concatenadas usando `command_length` como stride | M | feito |
| FR-32 | Benchmark de decode (loop 5000×) disponível mas comentado | C | parcial |
| FR-33 | Relatar se a PDU é 3.3, 3.4 e/ou 5.0 | S | feito |

## 6. Requisitos não funcionais

| ID | Descrição | Pri | Status |
| --- | --- | --- | --- |
| NFR-01 | Plataforma primária: macOS (projeto Xcode `macsmpp.xcodeproj`) | M | feito |
| NFR-02 | Linguagem: C++ (com helper C em `numofprocessors.c`) | M | feito |
| NFR-03 | SMPP é big-endian; host little-endian deve fazer swap (`endianSwap`) | M | feito (macOS/Windows; Linux TODO) |
| NFR-04 | Decode de PDU individual deve ser adequado a alto volume (há esboço de microbenchmark) | S | não medido |
| NFR-05 | Não vazar buffers: `init`/`destroy` em cada classe de PDU | M | parcial (padrão presente, encode incompleto) |
| NFR-06 | Sem dependências externas além da libc++ / SDK do sistema | S | feito |
| NFR-07 | Documentação viva: SRD, SDD e AGENTS.md sempre alinhados ao código | M | este documento |

## 7. Regras de protocolo (constantes)

Valores de `macsmpp/protocols/smpp/SmppUtilities.h` — requisitos, não meros detalhes de implementação:

- Header: 16 octetos
- Versões suportadas: `0x33`, `0x34`, `0x50`
- `sequence_number`: `0x00000001` .. `0x7FFFFFFF`
- `system_id` ≤ 16, `password` ≤ 9, `system_type` ≤ 13, `address_range` ≤ 41
- `service_type` ≤ 6
- `source_addr` / `destination_addr` ≤ 21 (data_sm e alert_notification: até 65)
- `short_message` ≤ 254; `message_id` ≤ 9 (3.3) ou 65 (3.4/5.0)
- `number_of_dests` ≤ 254
- Destino em `submit_multi`: flag 1 = SME, flag 2 = distribution list (nome ≤ 21)

## 8. Restrições e premissas

1. O repositório GitHub é a fonte de verdade do código (`origin` = `https://github.com/bobkerrjr/macsmpp.git`, branch `master`).
2. O software é pessoal; não há requisito de multi-tenant.
3. Exemplos de PDU em `main.cpp` contêm strings de teste (números, senhas fictícias). Não são credenciais de produção.
4. `SmppBody::pduEncode` está comentado: o encode completo é dívida técnica explícita (SDD §8).

## 9. Critérios de aceite (codec atual)

Uma PDU de exemplo é considerada processada com sucesso quando:

1. `pduDecode` consome exatamente `command_length` octetos.
2. `getIsValid()` é verdadeiro para PDUs bem formadas do conjunto de exemplos.
3. `printPduInfo()` identifica o `command_id`.
4. `isVersion` distingue 3.3 / 3.4 / 5.0 quando os campos o permitem.

Uma sessão gateway (futuro) será aceita quando bind, submit_sm e enquire_link funcionarem contra um SMSC de teste, com correlação por `sequence_number`.

## 10. Histórico

| Versão | Data | Alteração |
| --- | --- | --- |
| 1.0 | 2026-09-01 | Extraído do código existente e da descrição do GitHub |
