/* * O "Contrato" do Projeto.
* Define todas as estruturas de dados e "promete"
 * quais funções existem.
 */

#ifndef BANCO_MALVADER_BANCO_H // "Trava" para evitar importação duplicada
#define BANCO_MALVADER_BANCO_H

// --- 1. DEFINIÇÕES GLOBAIS ---
// Qualquer .c que incluir "banco.h" saberá o que são essas constantes.
#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 13
#define TAM_AGENCIA 11
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0
#define VALOR_MAX_DEPOSITO 1000000000.0 //valor maximo para um deposito, 10 milhoes

// --- 2. ESTRUTURAS DE DADOS (O Molde) ---
typedef struct {
    int numero; /* número único da conta */
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status; /* ATIVA ou ENCERRADA */
} Conta;

// --- 3. PROTÓTIPOS DE FUNÇÃO (As "Promessas") ---
// Dizemos ao 'main.c' que essas funções existem em algum lugar...

/* Funções do utils.c */
void limpa_tela();

void limpa_buffer();

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]);

int verifica_fgets(char INFO[]);

int abrir_conta(Conta contas[], int *quant, int num_conta, const char *nome,
        const char *cpf, const char *agencia, const char *telefone);

void coletar_info_deposito (int *num_conta, double *valor_deposito);

/* Funções dos seus amigos (eles adicionarão aqui depois) */
// void depositar(Conta contas[], int quant);
// void sacar(Conta contas[], int quant);


#endif //FIM DA TRAVA