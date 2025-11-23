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
#define VALOR_MAX_DEPOSITO (100000000.0) //valor maximo para um deposito, transferencia, saque: 100 milhoes
#define VALOR_MAX_SAQUE (100000000.0) //valor maximo para um deposito, transferencia, saque: 100 milhoes

// 0 = sucesso, <0 = códigos de erro. parenteses pq se nao compilador reclama

typedef enum {

    /* Sucesso */
    OK = 0, // sucesso geral

    /* Erros de conta / operação bancária */
    ERR_CONTA_INEXISTENTE = -1, // conta não encontrada
    ERR_CONTA_INATIVA     = -2, // conta existe mas está encerrada
    ERR_VALOR_INVALIDO    = -3, // valor <= 0 ou fora do limite
    ERR_DIGIT_EM_NOME     = -4, // dígito encontrado onde não deveria (ex: em nome)
    ERR_CPF_DUPLICADO     = -5, // ao criar conta, CPF já cadastrado em conta ativa
    ERR_NENHUMA_CONTA     = -6, // lista vazia / nenhuma conta no sistema
    ERR_SALDO_NAO_ZERO    = -7, //para funcao encerrar conta
    ERR_SALDO_INSUFICIENTE = -8, // saldo na conta insuficiente, p tranferir

    /*  Erros de input / validação */
    ERR_INPUT_MUITO_LONG  = -9, // fgets ultrapassou buffer
    ERR_PARSE_FAIL        = -10, // conversão/parse (atoi/atof) falhou
    ERR_LETRA_EM_NUMERO   = -11, // letra encontrada onde só número é permitido

    /* Erros sentinela / código inútil só pro compilador parar de reclamar */
    ERR_PARA_COMPILADOR   = -12, // usar onde a função não pode alcançar
    ERR_INVALIDO          = -13  // genérico; usar quando nada mais encaixa

} ErrorCode;

#define ERR_PARA_COMPILADOR_D (-100.0) //mesma do normal mas usado para funcoes que retorna double

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

void exibir_menu();

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]);

int verifica_fgets(char INFO[]);

int abrir_conta(Conta contas[], int *quant, int num_conta, const char *nome,
        const char *cpf, const char *agencia, const char *telefone);

double coletar_info_deposito (const char *mensagem);

int encontrar_conta_por_numero(const Conta contas[], int num_conta, int quant_atual);

int realizar_deposito(Conta contas[], int indice_conta, double valor_deposito);

int valida_conta_ativa(Conta contas[], int indice_conta);

int coletar_numero_conta(void);

int verifica_digitos(char INFO[]);

void coletar_novos_dados_tel_agencia (char TEL_TEMP[], char AGENCIA_TEMP[]);

void atualizar_dados_tel_agencia (Conta contas[], char TEL_NOVO[], char AGENCIA_NOVA[], int indice);

int verifica_letras(char INFO[]);

int listar_contas(const Conta contas[], int qtd, int filtro_status);

void mostrar_dados(const Conta* c);

int verifica_digitos_saldo(char SALDO[]);

int coletar_cpf(char cpf_out[]);

int consultar_por_numero(Conta contas[], int quant, int numero, int *indice_out);

int consultar_por_cpf(Conta contas[], int quant, const char *cpf, int *indice_out);

int encerrar_conta(Conta contas[], int idx_conta, int quant_atual);



int realizar_transferencia(Conta contas[],
                           int quant_atual,
                           int conta_origem,
                           int conta_destino,
                           double valor);

void coletar_info_saque(int *num_conta, double *valor_saque);

int realizar_saque(Conta contas[], int indice_conta, double valor_saque);

int ler_int(const char *mensagem);

double ler_double(const char *mensagem);


#endif //FIM DA TRAVA