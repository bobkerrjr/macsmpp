---
name: keep-srd-sdd-updated
description: Keep macsmpp SRD, SDD, and AGENTS.md in sync with code and conversation. Use whenever requirements, design, protocol facts, or owner decisions appear, or when implementing SMPP/gateway changes, to avoid rework.
---

# Manter SRD, SDD e agent atualizados

Sempre manter o SRD e o SDD atualizados. Sempre atualizar o agent quando alguma informação pertinente for dita, para evitar retrabalho.

## Arquivos

| Papel | Caminho |
| --- | --- |
| Requisitos | [docs/SRD.md](../../../docs/SRD.md) |
| Desenho | [docs/SDD.md](../../../docs/SDD.md) |
| Memória operacional | [AGENTS.md](../../../AGENTS.md) |

## Fluxo

1. Ler os três arquivos antes de mudar código.
2. Classificar o fato novo:
   - **O quê** (requisito, aceite, ator, status feito/parcial/não feito) → SRD
   - **Como** (classe, fluxo, layout, TLV, factory, encode, dívida) → SDD
   - **Contexto de trabalho** (preferência, remote, “não faça X”, SMSC de teste) → AGENTS.md Memória
3. Editar só as seções afetadas. Incrementar versão e histórico.
4. Se o código contradisser o documento, corrigir o documento para o código real (ou implementar o requisito e então marcar status).

## Pertinente o bastante para gravar

Se esquecer o fato faria o agente repetir pergunta, refazer codec, ou implementar sessão TCP sem saber que ela não existe — grave.

## Armadilhas já documentadas

- `pduEncode` não serializa o body
- Não há camada TCP
- Branch remota é `master`, não `main`
