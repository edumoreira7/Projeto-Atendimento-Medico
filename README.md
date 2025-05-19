# 🏥 Gerenciador de Atendimento Médico

**Disciplina:** Estrutura de Dados  
**Professor:** Luciano Rossi  

---

##  Objetivo

Este sistema tem como objetivo gerenciar atendimentos em um ambiente médico, utilizando diferentes **estruturas de dados** para organizar e controlar os pacientes, filas de atendimento, filas prioritárias, histórico de operações e armazenamento de dados, garantindo que as informações não se percam mesmo após o encerramento da aplicação.

---

##  Funcionalidades Implementadas

### 1. Cadastro de Pacientes
- Utiliza uma **Lista Encadeada**
- Campos registrados: Nome, Idade, RG e Data de Entrada
- Funcionalidades:
  - Inserir novo paciente
  - Consultar paciente pelo RG
  - Atualizar dados do paciente
  - Remover paciente
  - Listar todos os pacientes cadastrados

### 2. Atendimento Convencional
- Implementado com uma **Fila (Queue)**
- Funcionalidades:
  - Enfileirar paciente
  - Desenfileirar paciente
  - Visualizar fila de atendimento

### 3. Atendimento Prioritário
- Implementado com uma **Heap Máxima** (baseada na idade do paciente)
- Capacidade máxima: 20 pacientes
- Funcionalidades:
  - Enfileirar paciente prioritário
  - Desenfileirar paciente mais idoso
  - Mostrar fila de prioridade

### 4. Pesquisa
- Utiliza uma **Árvore Binária de Busca (ABB)**
- Permite ordenação e visualização dos pacientes por:
  - Ano de entrada
  - Mês de entrada
  - Dia de entrada

### 5. Desfazer Operações
- Implementado com uma **Pilha de operações**
- Registra ações de enfileirar e desenfileirar da fila comum
- Permite desfazer a última operação realizada

### 6. Arquivo
- Salva e carrega automaticamente os dados dos pacientes
- Utiliza arquivos `.txt` para persistência
- Funcionalidades:
  - Carregar dados salvos em execuções anteriores
  - Salvar dados ao encerrar ou manualmente

### 7. Sobre
- Mostra os nomes dos desenvolvedores e dados do curso

---

## Integrantes do Grupo

- **Eduardo Gonçalves Moreira**  
  RA: 22.124.087-2  
- **David Gabriel de Souza Batista**  
  RA: 22.123.056-8
