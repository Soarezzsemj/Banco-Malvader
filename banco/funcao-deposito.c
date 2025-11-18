#include <stdio.h>
#include "banco.h"

void coletar_info_deposito (int *num_conta, double *valor_deposito) {
    int opcao_valida = 0;

    do {
        printf("Informe o numero da conta que voce deseja fazer o deposito: ");
        opcao_valida = scanf("%d", &*num_conta);

        if (opcao_valida != 1) { //evita que o usuario digite letras
            limpa_buffer();
            printf("\nErro: Informe somente numeros!\n");
            continue;
        }
        if (*num_conta < 1) {
            printf("\nErro: Informe uma conta valida!\n");
            opcao_valida = -1;
        }
        limpa_buffer(); //evitar letras em caso de 22l ele pega o 22 e descarta o l
    }while (opcao_valida != 1);

    do {
        printf("Informe o valor do deposito: ");
        opcao_valida = scanf("%lf", &*valor_deposito);

        if (opcao_valida != 1) {
            printf("\nErro: Informe somente numeros!");
            limpa_buffer();
            continue;
        }

        if (*valor_deposito <= 0) {
            printf("Informe um numero positivo maior que zero!\n");
            opcao_valida = -1;
            continue;
        }

        if (*valor_deposito > VALOR_MAX_DEPOSITO) {
            printf("\nErro: o valor maximo de deposito eh %.2lf\n", VALOR_MAX_DEPOSITO);
            opcao_valida = -1;
        }
    limpa_buffer();
    }while (opcao_valida != 1);
}

int realizar_deposito(Conta contas[], int indice_conta, double valor_deposito) {
    if (valor_deposito <= 0) { //caso o valor venha de outro lugar alem da funcao "coletar_info_deposito
        printf("Erro: Informe um valor maior que 0!\n");
        return -1;
    }

    if (valida_conta_ativa(contas, indice_conta) == -1) { //valida se conta esta ativa
        printf("Erro: A conta informada esta desativada!\n");
        return -1;
    }

    contas[indice_conta].saldo += valor_deposito;

    return 0;
}