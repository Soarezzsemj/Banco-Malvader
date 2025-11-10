#include <stdio.h>
#include "banco.h"

void coletar_info_deposito (int *num_conta, double *valor_deposito) {
    int opcao_valida = 0;

    do {
        printf("Informe o numero da conta que você deseja fazer o deposito: ");
        opcao_valida = scanf("%d", &*num_conta);

        limpa_buffer(); //evita \n no fgets

        if (opcao_valida != 1) { //evita que o usuario digite letras
            printf("\nErro: Informe somente numeros!");
            limpa_buffer();
            continue;
        }
        if (*num_conta < 1) {
            printf("\nErro: Informe uma conta valida!");
            opcao_valida = -1;
        }
    }while (opcao_valida != 1);

    do {
        printf("Informe o valor do deposito: ");
        opcao_valida = scanf("%lf", &*valor_deposito);

        limpa_buffer();

        if (opcao_valida != 1) {
            printf("\nErro: Informe somente numeros!");
            limpa_buffer();
            continue;
        }

        if (*valor_deposito <= 0) {
            printf("Informe um numero positivo maior que zero!");
            opcao_valida = -1;
            continue;
        }

        if (*valor_deposito > VALOR_MAX_DEPOSITO) {
            printf("\nErro: o valor maximo de deposito eh %.2lf", VALOR_MAX_DEPOSITO);
            opcao_valida = -1;
        }

    }while (opcao_valida != 1);

}
