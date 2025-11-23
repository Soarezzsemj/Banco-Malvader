#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

double coletar_info_deposito (const char *mensagem) {
    int opcao_valida = OK;
    char valor[50];
    double saldo;

    do {
        printf("%s", mensagem);
        fgets(valor, 50, stdin);

        opcao_valida = verifica_fgets(valor);

        if (opcao_valida == ERR_INPUT_MUITO_LONG) {
            printf("\nErro: Valor muito longo!");
            limpa_buffer();
            continue;
        }

        opcao_valida = verifica_digitos_saldo(valor);

        if (opcao_valida == ERR_LETRA_EM_NUMERO) {
            printf("Informe somente numeros!\n");
            continue;
        }

        saldo = atof(valor);

        if (saldo <= 0) {
            printf("Erro: Informe um valor positivo maior que zero");
            opcao_valida = ERR_INVALIDO;
            continue;
        }

        if (saldo > VALOR_MAX_DEPOSITO) {
            printf("\nErro: o valor maximo eh %.2lf\n", VALOR_MAX_DEPOSITO);
            opcao_valida = ERR_INVALIDO;
            continue;
        }

        return saldo;

    }while (opcao_valida != OK);

    return ERR_PARA_COMPILADOR_D; //por segurança. o codigo nunca vai chegar aqui, mas o compilador reclama se nao tiver
}

int realizar_deposito(Conta contas[], int indice_conta, double valor_deposito) {

    if (valor_deposito <= 0) { //caso o valor venha de outro lugar alem da funcao "coletar_info_deposito
        return ERR_VALOR_INVALIDO;
    }

    if (valida_conta_ativa(contas, indice_conta) == ERR_CONTA_INATIVA) { //valida se conta esta ativa
        return ERR_CONTA_INATIVA;
    }

    contas[indice_conta].saldo += valor_deposito;

    return OK;
}