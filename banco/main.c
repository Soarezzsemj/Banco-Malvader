#include <stdio.h>

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

int main()
{
    Conta vetor_de_contas[MAX_CONTAS];
    int quantidade_atual = 0; // numero de contas criadas
    int num_proxima_conta = 1; //vai ser incrementado depois apos a criação de uma nova conta
    int opcao;

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

        scanf("%d", &opcao);
        if (opcao < 1 || opcao > 9) { //se nao for uma das opcoes pede ao usuario para tentar novamente
            printf("Opcao invalida! Digite uma opcao valida por favor.\n");
            continue; // reinicia o loop
        }

        switch (opcao) { /* chamar as funções conforme a escolha */
            case 1:
                printf("Voce escolheu abrir conta.");
                //chamada aqui
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