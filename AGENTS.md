# macsmpp — instruções do agente

Este repositório é o gateway SMPP pessoal em [https://github.com/bobkerrjr/macsmpp](https://github.com/bobkerrjr/macsmpp).

Os documentos vivos são:

- [docs/SRD.md](docs/SRD.md) — o que o sistema deve fazer
- [docs/SDD.md](docs/SDD.md) — como o sistema está desenhado
- este arquivo (`AGENTS.md`) — memória operacional para não retrabalhar

## Regra permanente: não deixar os documentos atrasarem

Sempre manter o SRD e o SDD atualizados. Sempre atualizar este agent quando alguma informação pertinente for dita, para evitar retrabalho.

Isso vale para conversa, código, revisão e decisão. Não esperar um pedido explícito de “atualiza o doc”.

### O que é pertinente (atualizar na mesma sessão)

- Novo requisito, restrição, prioridade, ator ou critério de aceite → **SRD**
- Requisito existente que mudou de status (feito / parcial / não feito) → **SRD**
- Classe, fluxo, layout, constante de protocolo, factory de PDU, encode/decode → **SDD**
- Dívida técnica descoberta ou resolvida → **SDD** (tabela da seção 8) e SRD se o status do requisito mudar
- Preferência do dono do repo, convenção, “não faça X”, “o alvo é Y”, credenciais de teste vs produção, SMSC de referência, versão SMPP alvo, plataforma → **AGENTS.md** (seção Memória) **e** SRD/SDD se afetar requisito ou desenho
- Qualquer fato que, se esquecido, faria o agente repetir perguntas ou refazer trabalho → **AGENTS.md**

### Como atualizar

1. Ler SRD, SDD e a seção Memória deste arquivo antes de implementar.
2. Implementar alinhado ao que já está documentado; se o código divergir, o documento é que estava errado — corrija o documento, não ignore o código.
3. Alterar só as seções afetadas; incrementar a versão e a linha no histórico.
4. Se a informação for operacional (como trabalhar neste repo) e não um requisito de produto, ela entra aqui, não no SRD.
5. Não duplicar parágrafos longos entre os três arquivos: o SRD aponta o quê, o SDD o como, o agent o contexto de trabalho.

### O que não fazer

- Não implementar gateway TCP/sessão sem atualizar SRD (FR-20+) e SDD (§10).
- Não assumir que `pduEncode` serializa o body — não serializa (SDD §6 e §8).
- Não tratar o harness `main.cpp` como o produto gateway.
- Não reperguntar o que já está na Memória abaixo.

## Memória (fatos ditos / descobertos)

Atualizar esta lista em vez de redescobrir.

- Remote Git: `origin` → `https://github.com/bobkerrjr/macsmpp.git`. Branch remota: `master`.
- Descrição do produto no GitHub: “My personal SMPP gateway.”
- Autor original: Bob Kerr. Código iniciado em 2011; snapshot público em 2019 (`210008f` Primeira versão).
- Linguagem: C++. Build: Xcode (`macsmpp.xcodeproj`). Host principal: macOS.
- O que existe hoje é codec de PDU SMPP 3.3 / 3.4 / 5.0 + harness de 28 PDUs de exemplo. Não há socket, bind de sessão, fila nem config file.
- Header SMPP: 16 bytes, big-endian. Factory em `SmppPdu::pduDecode`.
- `SmppBody::pduEncode` está comentado; encode atual é só header.
- PDUs de exemplo vivem duplicadas em `macsmpp/main.cpp` e `macsmpp/pduExamples.h`.
- Constantes de tamanho e versão: `macsmpp/protocols/smpp/SmppUtilities.h`.
- Endian swap Linux ainda é TODO.
- Documentos canônicos: `docs/SRD.md`, `docs/SDD.md`, `AGENTS.md`.
