# Sistema Bancário Básico em C

![Status](https://img.shields.io/badge/status-concluído-brightgreen)


Este projeto é um trabalho prático da disciplina de Algoritmos e Programação em C. O objetivo é desenvolver um sistema bancário simples para cadastro e manutenção de contas correntes.

## 🎯 Sobre o Projeto

O sistema deve permitir a realização de operações bancárias básicas, como abertura de conta, depósitos, saques, transferências e consultas. Todos os dados são mantidos apenas em memória durante a execução do programa.

## 📋 Escopo e Restrições

Conforme os requisitos do trabalho, o projeto deve seguir as seguintes regras:

* **Uso obrigatório** de `structs` e funções.
* Os dados devem ser armazenados em **vetores** com tamanhos máximos definidos por constantes (ex: `MAX_CONTAS`).
* Os dados **não são persistidos**; eles existem apenas enquanto o programa está em execução.
* O sistema deve operar através de um **menu interativo** que se repete até que o usuário escolha a opção "Sair".

## ⚙️ Funcionalidades Obrigatórias

O menu principal deve permitir o acesso às seguintes operações:

1.  **Abrir conta:** Cria uma nova conta com número sequencial, dados do cliente e saldo inicial zero.
    * *Regra:* Deve recusar se o CPF já existir em uma conta ativa ou se o vetor de contas estiver cheio.
2.  **Depositar:** Soma um valor ao saldo da conta.
    * *Regra:* Deve recusar valores menores ou iguais a zero e não operar em contas encerradas.
3.  **Sacar:** Subtrai um valor do saldo da conta.
    * *Regra:* Deve recusar valores inválidos, valores superiores ao saldo e não operar em contas encerradas.
4.  **Transferir:** Debita um valor da conta de origem e credita na conta de destino.
    * *Regra:* Deve conferir a existência e o status de ambas as contas, além do saldo da origem.
5.  **Consultar saldo e dados:** Exibe todos os dados de uma conta específica.
    * *Regra:* Deve permitir a busca por número da conta ou por CPF.
6.  **Atualizar dados do cliente:** Permite alterar o telefone e a agência.
    * *Regra:* Nome e CPF não podem ser alterados.
7.  **Listar contas:** Exibe todas as contas, com filtros (ativas, encerradas ou todas).
8.  **Encerrar conta:** Altera o status da conta para "encerrada".
    * *Regra:* A conta não é removida do vetor. O encerramento só é permitido se o saldo for zero.
9.  **Sair:** Encerra o programa após confirmação.

## 🏗️ Estrutura de Dados Principal

A gestão das contas é feita usando a seguinte `struct`:

```c
#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_AGENCIA 10
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0

typedef struct {
    int numero;                 /* número único da conta */
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status;                 /* ATIVA ou ENCERRADA */
} Conta;
```

O controle é feito por um vetor principal de `Conta` e uma variável que armazena a quantidade atual de contas válidas.

## 📈 Critérios de Avaliação do Trabalho

A avaliação deste projeto será baseada nos seguintes critérios:

| Critério | Peso |
| :--- | :--- |
| Funcionalidades obrigatórias implementadas e corretas | 40% |
| Uso adequado de structs, vetores e funções (divisão de responsabilidades) | 25% |
| Validações e tratamento de erros (entradas do usuário, regras de negócio) | 15% |
| Clareza do código, nomes, comentários e organização | 15% |
| Relatório curto explicando decisões e testes apresentados | 5% |

## 🚀 Como Rodar o Projeto

Este projeto foi estruturado utilizando **CMake** para gerenciamento de build, garantindo portabilidade e organização.

### Pré-requisitos
* Compilador C (GCC, MinGW ou Clang).
* [CMake](https://cmake.org/download/) (opcional, mas recomendado).

### Opção 1: Usando CMake (Recomendado)

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/Soarezzsemj/Banco-Malvader.git](https://github.com/Soarezzsemj/Banco-Malvader.git)
    cd Banco-Malvader
    ```

2.  **Gere os arquivos de build:**
    ```bash
    cmake -B build
    ```

3.  **Compile o projeto:**
    ```bash
    cmake --build build
    ```

4.  **Execute o programa:**
    * **No Windows:**
        ```bash
        .\build\banco.exe
        ```
    * **No Linux/Mac:**
        ```bash
        ./build/banco
        ```

---

### Opção 2: Compilação Manual (GCC)

Se você não tiver o CMake instalado, pode compilar manualmente rodando este comando na raiz do projeto:

```bash
gcc banco/main.c banco/utils.c banco/funcoes_abrir_conta.c banco/listar_contas.c banco/deposito.c banco/saque.c banco/atualizar-telefone-agencia.c banco/mostrar_dados.c banco/encerrar_conta.c banco/funcao-transferir.c banco/ui.c -o banco
