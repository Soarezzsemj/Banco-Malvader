#include <stdio.h>
#include <stdlib.h>

#include "banco.h"

double coletar_info_deposito (const char *mensagem) {
    int opcao_valida = 0;
    char valor[50];
    double saldo;

    do {
        printf("%s", mensagem);
        fgets(valor, 50, stdin);

        opcao_valida = verifica_fgets(valor);

        if (opcao_valida == -1) {
            printf("\nErro: Valor muito longo!");
            limpa_buffer();
            continue;
        }

        opcao_valida = verifica_digitos_saldo(valor);

        if (opcao_valida == -1) {
            printf("Informe somente numeros!\n");
            continue;
        }

        saldo = atof(valor);

        if (saldo <= 0) {
            printf("Erro: Informe um valor positivo maior que zero");
            opcao_valida = -1;
            continue;
        }

        if (saldo > VALOR_MAX_DEPOSITO) {
            printf("\nErro: o valor maximo eh %.2lf\n", VALOR_MAX_DEPOSITO);
            opcao_valida = -1;
            continue;
        }

        return saldo;

    }while (opcao_valida == -1);

    return -1; // o codigo nunca vai chegar aqui, mas é so por segurança mesmo
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