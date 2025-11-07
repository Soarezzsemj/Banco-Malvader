#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 13
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

void limpa_tela(); //por enquanto deixa ai kkkkk achei daora por

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]);

int verifica_fgets(char INFO[], int TAMANHO);

void verifica_dados_conta(Conta contas, int *quant, int *proximo_numero);

int main()
{
    Conta vetor_de_contas[MAX_CONTAS];
    int quantidade_atual = 0; // numero de contas criadas
    int num_proxima_conta = 1; //vai ser incrementado depois apos a criação de uma nova conta
    int opcao, sucesso_leitura, c;

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

        sucesso_leitura= scanf("%d", &opcao); //se ler um numero ele retorna 1

        if (sucesso_leitura != 1) { //se for uma letra, ele ficou preso na fila, temos que limpa-lo
            limpa_tela();
            printf("\nEntrada invalida! Por favor informe somente numeros.\n");
            while (( c= getchar()) != '\n' && c != EOF); /*Limpa o buffer (usa getchar enquanto nao
            nao limpar a fila toda), o buffer que causa o loop*/

            opcao = 0;
            continue;
        }

        while ((c = getchar()) != '\n' && c != EOF); //limpar o buffer para o \n nao ir para o proximo fgets

        if (opcao < 1 || opcao > 9) { //se nao for uma das opcoes pede ao usuario para tentar novamente
            limpa_tela();
            printf("\nOpcao invalida! Digite uma opcao valida por favor.\n");
            continue; // reinicia o loop
        }

        switch (opcao) { /* chamar as funções conforme a escolha */
            case 1:
                if (quantidade_atual >= MAX_CONTAS) {
                    limpa_tela();
                    printf("\nErro: Limite de contas atingido!\n");
                    break; //volta para o menu
                }
                char nome_temp[TAM_NOME];
                char cpf_temp[TAM_CPF];
                char agencia_temp[TAM_AGENCIA];
                char telefone_temp[TAM_TELEFONE];

                coletar_dados_abertura_conta(nome_temp, cpf_temp, agencia_temp, telefone_temp); //preenche os dados
                break;
            case 2:
                printf("Voce escolheu depositar.");
                //chamada aqui
                break;
            case 3:
                printf("Voce escolheu sacar seu saldo.");
                //chamada aqui
                break;
                //...
        }

    } while (opcao != 9);

    return 0;
}

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]) {
    printf("\n------ABERTURA DE CONTA NOVA------\n");

    int entrada_valida, i, c;

    do {
        printf("\nDigite o seu nome completo: ");
        fgets(NOME_temp, TAM_NOME, stdin);

        entrada_valida = verifica_fgets(NOME_temp, TAM_NOME); //funcao verifica se ultrapassou o limite
        if (entrada_valida != 0) {
            printf("\nErro: Nome muito longo! O limite de caracteres eh %d.", TAM_NOME - 2);
            while ((c = getchar()) != '\n' && c != EOF); //limpando o string
        }
    }while (entrada_valida == -1);

    do {
        printf("\nDigite o seu cpf completo (apenas numeros): ");
        fgets(CPF_temp, TAM_CPF, stdin);

        entrada_valida = verifica_fgets(CPF_temp, TAM_CPF);
        if (entrada_valida == -1) {
            printf("Erro: CPF muito longo!");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        for (i = 0; i < strlen(CPF_temp); i++) {
            c = CPF_temp[i];

            if (!isdigit(c)) {
                while ((c = getchar()) != '\n' && c != EOF);
                entrada_valida = -1;
                printf("\nErro: Informe somente numeros!");
                break;
            }
        }
    }while (entrada_valida == -1);


    printf("Informe sua agencia: ");
    fgets(AGENCIA_temp, TAM_AGENCIA, stdin);

    printf("Informe seu telefone (apenas numeros): ");
    fgets(TELEFONE_temp, TAM_AGENCIA, stdin);

    //limpar o \n que o fgets deixa
    CPF_temp[strcspn(CPF_temp, "\n")] = '\0';
    AGENCIA_temp[strcspn(AGENCIA_temp, "\n")] = '\0';
    TELEFONE_temp[strcspn(TELEFONE_temp, "\n")] = '\0';
}

void limpa_tela() {
    int i;
    for (i = 0; i < 40; i++) //da 40 espaços
        printf("\n");
}

int verifica_fgets(char INFO[], int TAMANHO) {
    char *ponteiro_enter;
    ponteiro_enter = strchr(INFO, '\n'); //procura o /n na string, se tiver o limite de char foi respeitado

    if (ponteiro_enter != NULL) {
        *ponteiro_enter = '\0';
        return 0;
    }
    else { //se nao tiver \n nao teve espaço para armazenar toda a string
        return -1;
    }
}