#  Gerenciador de Atendimento Médico

 **Estrutura de Dados** 
**Prof. Luciano Rossi**

---

##  Objetivo

O sistema tem como objetivo gerenciar atendimentos em um ambiente médico, utilizando diferentes estruturas de dados para organizar e controlar os pacientes, filas de atendimento, filas prioritárias, histórico de operações e
armanezar os dados, de forma que os mesmos não se percam.

---

##  Funcionalidades Implementadas

### 1. Cadastro de Pacientes
- Registro com nome, idade, RG e data de entrada
- Lista encadeada dinâmica
- Operações:
  - Inserir novo paciente
  - Consultar paciente
  - Atualizar dados
  - Remover paciente
  - Listar todos os pacientes

### 2. Atendimento Convencional
- Implementado com Fila (Queue)
- Operações:
  - Enfileirar paciente
  - Desenfileirar paciente
  - Visualizar fila

### 3. Atendimento Prioritário 
- Implementado com Heap Máxima por idade
- Capacidade máxima de 20 pacientes
- Operações:
  - Enfileirar paciente prioritário
  - Desenfileirar
  - Mostrar heap

### 4. Pesquisa 
- Previsto uso de Árvore Binária de Busca (ABB)
- Ordenações por:
  - Ano, mês ou dia da entrada
  - Idade do paciente

### 5. Desfazer Operações 
- Pilha de operações
- Desfaz a última ação realizada sobre a fila comum

### 6. Arquivo
- XXXXX

### 7. Sobre
- Mostra dados dos desenvolvedores e informações do curso

---

##  Integrantes do Grupo

- **Eduardo Gonçalves Moreira** 
- RA:22.124.087-2 
- **David Gabriel de Souza Batista** 
- RA:22.123.056-8

