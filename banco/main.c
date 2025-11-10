#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 13
#define TAM_AGENCIA 11
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0

typedef struct {
    int numero; /* número único da conta */
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status; /* ATIVA ou ENCERRADA */
} Conta;

void limpa_tela();

void limpa_buffer();

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]);
int verifica_fgets(char INFO[], int TAMANHO);

int abrir_conta(Conta contas[], int *quant, const char *nome,
        const char *cpf, const char *agencia, const char *telefone);

int encontrar_conta_por_cpf(const Conta contas[], int quant, const char *cpf);

int main() {
    Conta vetor_de_contas[MAX_CONTAS];
    int quantidade_atual = 0; // numero de contas criadas
    int num_proxima_conta = 1; // vai ser incrementado depois apos a criação de uma nova conta
    int opcao, sucesso_leitura, resultado_da_conta;

    do {
        printf("\n------Menu------\n");
        printf("1. Abrir conta\n");
        printf("2. Depositar\n");
        printf("3. Sacar\n");
        printf("4. Transferir\n");
        printf("5. Consultar saldo e dados\n");
        printf("6. Atualizar telefone e agencia\n");
        printf("7. Listar contas\n");
        printf("8. Encerrar conta\n");
        printf("9. Sair\n");
        printf("Escolha: ");

        sucesso_leitura = scanf("%d", &opcao); // se ler um numero ele retorna 1

        if (sucesso_leitura != 1) { // se for uma letra, ele ficou preso na fila, temos que limpa-lo
            limpa_tela();
            printf("\nEntrada invalida! Por favor informe somente numeros.\n");
            limpa_buffer();
            opcao = 0;
            continue;
        }

        limpa_buffer(); // limpar o buffer para o \n nao ir para o proximo fgets

        if (opcao < 1 || opcao > 9) { // se nao for uma das opcoes pede ao usuario para tentar novamente
            limpa_tela();
            printf("\nOpcao invalida! Digite uma opcao valida por favor.\n");
            continue; // reinicia o loop
        }

        switch (opcao) { /* chamar as funções conforme a escolha */
            case 1:
                if (quantidade_atual >= MAX_CONTAS) {
                    limpa_tela();
                    printf("\nErro: Limite de contas atingido!\n");
                    break; // volta para o menu
                }

                char nome_temp[TAM_NOME];
                char cpf_temp[TAM_CPF];
                char agencia_temp[TAM_AGENCIA];
                char telefone_temp[TAM_TELEFONE];

                coletar_dados_abertura_conta(nome_temp, cpf_temp, agencia_temp, telefone_temp); // preenche os dados

                resultado_da_conta = abrir_conta(vetor_de_contas, &quantidade_atual, nome_temp,
                                                 cpf_temp, agencia_temp, telefone_temp); //verifica se o CPF ja existe em outra conta

                if (resultado_da_conta == 0) {
                    printf("Conta criada com sucesso!\n");
                    num_proxima_conta++;
                }
                break;

            case 2:
                printf("Voce escolheu depositar.");
                // chamada aqui
                break;

            case 3:
                printf("Voce escolheu sacar seu saldo.");
                // chamada aqui
                break;

            // ...
            default:
                printf("\nErro: Opcao invalida!");
                break;
        }

    } while (opcao != 9);

    return 0;
}

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]) {
    int entrada_valida, i;

    printf("\n------ABERTURA DE CONTA NOVA------\n");

    do {
        printf("\nDigite o seu nome completo: ");
        fgets(NOME_temp, TAM_NOME, stdin);

        entrada_valida = verifica_fgets(NOME_temp, TAM_NOME); // funcao verifica se ultrapassou o limite

        if (entrada_valida == -1) {
            printf("\nErro: Nome muito longo! O limite de caracteres eh %d caracteres.", TAM_NOME - 2);
            limpa_buffer(); // limpando o string
        }
    } while (entrada_valida == -1);

    do {
        printf("Digite o seu cpf completo (apenas numeros): ");
        fgets(CPF_temp, TAM_CPF, stdin);

        entrada_valida = verifica_fgets(CPF_temp, TAM_CPF);

        if (entrada_valida == -1) {
            printf("Erro: CPF muito longo! O CPF deve ter 11 digitos.");
            limpa_buffer();
            continue;
        }

        for (i = 0; i < strlen(CPF_temp); i++) {
            if (!isdigit(CPF_temp[i])) { /* se a posição atual do cpf NAO FOR um digito
                                            mande um codigo de erro */
                entrada_valida = -1; // codigo de erro
                break;
            }
        }

        if (entrada_valida == -1) {
            printf("\nErro: Digite apenas numeros!");
            continue;
        }

        if (strlen(CPF_temp) != 11) {
            printf("\nErro: O CPF deve ter 11 digitos, voce informou somente %d.", (int)strlen(CPF_temp));
            entrada_valida = -1;
            continue;
        }
    } while (entrada_valida == -1);

    do {
        printf("Informe sua agencia: ");
        fgets(AGENCIA_temp, TAM_AGENCIA, stdin);

        entrada_valida = verifica_fgets(AGENCIA_temp, TAM_AGENCIA);

        if (entrada_valida == -1) {
            printf("\nErro: Nome de agencia muito longo! O limite eh %d caracteres.", TAM_AGENCIA - 2);
            limpa_buffer();
        }
    } while (entrada_valida == -1);

    do {
        printf("Informe seu telefone (apenas numeros): ");
        fgets(TELEFONE_temp, TAM_TELEFONE, stdin);

        entrada_valida = verifica_fgets(TELEFONE_temp, TAM_TELEFONE);

        if (entrada_valida == -1) {
            printf("\nErro: Numero de telefone grande demais! O limite é de %d numeros.", TAM_TELEFONE - 2);
            limpa_buffer();
            continue;
        }

        for (i = 0; i < strlen(TELEFONE_temp); i++) {
            if (!isdigit(TELEFONE_temp[i])) { /* se a posição atual do numero NAO FOR um digito
                                                 mande um codigo de erro */
                entrada_valida = -1; // codigo de erro
                break;
            }
        }

        if (entrada_valida == -1) {
            printf("\nErro: Digite apenas numeros!");
            continue;
        }
    } while (entrada_valida == -1);
}

void limpa_tela() {
    int i;
    for (i = 0; i < 40; i++) // da 40 espaços
        printf("\n");
}

void limpa_buffer() {
    int c;
    /* Essa funcao vai ser usada em dois casos.
       1: no menu quando o usuario digita uma letra e o scanf espera um int,
       entao o comentario no while ja explica.
       2: quando o usuario digitou algo que nao devia tipo letra em um cpf, entao
       é preciso limpar a string para ela armazenar novamente o que o usuario digitar. */

    while ((c = getchar()) != '\n' && c != EOF); /* Limpa o buffer (usa getchar enquanto nao
                                                     nao limpar a fila toda), o buffer que causa o loop */
}

int verifica_fgets(char INFO[], int TAMANHO) {
    char *ponteiro_enter;
    ponteiro_enter = strchr(INFO, '\n'); // procura o /n na string, se tiver o limite de char foi respeitado

    if (ponteiro_enter != NULL) {
        *ponteiro_enter = '\0';
        return 0;
    } else { // se nao tiver \n nao teve espaço para armazenar toda a string
        return -1;
    }
}

int abrir_conta(Conta contas[], int *quant, const char *nome, const char *cpf, const char *agencia, const char *telefone) {
    int i;

    for (i = 0; i < *quant; i++) {
        if (strcmp(contas[i].cpf, cpf) == 0 && contas[i].status == ATIVA) { /* Se o CPF da conta de indice
                                                                               *quant for igual a do CPF temp e a conta
                                                                               do indice *temp estiver ativa, entao é uma conta duplicada */
            printf("\nErro: O CPF cadastrado já existe em uma conta ativa.");
            printf("\nIndice da conta: %d.", *quant);
            return 1; // erro ao criar conta
        }
    }

    // copia os dados das variaveis _temp para a variavel struct Conta
    strcpy(contas[*quant].nome, nome);
    strcpy(contas[*quant].cpf, cpf);
    strcpy(contas[*quant].agencia, agencia);
    strcpy(contas[*quant].telefone, telefone);
    contas[*quant].saldo = 0.0;
    contas[*quant].status = ATIVA;

    *quant += 1; // acrescenta 1 no apontado de quantidade_atual no main
    return 0; // sucesso, uma conta foi criada
}
