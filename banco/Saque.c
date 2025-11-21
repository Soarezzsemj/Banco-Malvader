#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"


  // FUNÇÃO: coletar_info_saque
void coletar_info_saque(int *num_conta, double *valor_saque) {
    char buffer[50];
    int entrada_valida = 0;

    /* --- PARTE 1: COLETA DO NÚMERO DA CONTA --- */
    *num_conta = coletar_numero_conta();  // já validado
    if (*num_conta < 1) {
        printf("\nErro: Numero da conta invalido!\n");
    }

    /* --- PARTE 2: COLETA DO VALOR DO SAQUE --- */
    do {
        printf("Informe o valor do saque: ");
        fgets(buffer, sizeof(buffer), stdin);

        /* Verificação de overflow */
        entrada_valida = verifica_fgets(buffer);
        if (entrada_valida == -1) {
            printf("\nErro: Valor muito grande! Digite novamente.\n");
            continue;
        }

        if (verifica_digitos(buffer) == -1) {
            printf("\nErro: Informe somente numeros!\n");
            continue;
        }

        /* Converte */
        *valor_saque = strtod(buffer, NULL);

        /* Verifica se é maior que 0 */
        if (*valor_saque <= 0) {
            printf("\nErro: Informe um valor maior que zero!\n");
            continue;
        }

        /* Verifica se ultrapassa o limite do sistema */
        if (*valor_saque > VALOR_MAX_SAQUE) {
            printf("\nErro: Limite máximo permitido é %.2lf!\n", VALOR_MAX_SAQUE);
            continue;
        }

        break;

    } while (1);
}


//Funcao realizar_saque
int realizar_saque(Conta contas[], int indice_conta, double valor_saque) {

    /* Verifica se conta está ativa */
    if (valida_conta_ativa(contas, indice_conta) == -1) {
        printf("\nErro: A conta está encerrada!\n");
        return -1;
    }

    /* Verifica valor */
    if (valor_saque <= 0) {
        printf("\nErro: Valor inválido!\n");
        return -1;
    }

    double saldo_atual = contas[indice_conta].saldo;

    /* --- SAQUE PARCIAL --- */
    if (saldo_atual < valor_saque) {
        printf("\nAviso: Saldo insuficiente! Saque limitado ao saldo disponível.\n");
        printf("Saque realizado: %.2lf\n", saldo_atual);

        contas[indice_conta].saldo = 0;  // zera o saldo
        return 1; // código especial → saque parcial
    }

    /* --- SAQUE NORMAL --- */
    contas[indice_conta].saldo -= valor_saque;
    return 0; // sucesso total
}