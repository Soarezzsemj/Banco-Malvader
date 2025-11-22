#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

void coletar_info_saque(int *num_conta, double *valor_saque) {

    // coleta número da conta usando função padronizada
    *num_conta = coletar_numero_conta();

    // coleta valor do saque usando função padrão de dinheiro
    *valor_saque = coletar_info_deposito("Informe o valor do saque: ");
}


// Função realizar_saque
int realizar_saque(Conta contas[], int indice_conta, double valor_saque) {

    if (valida_conta_ativa(contas, indice_conta) != OK) {
        return ERR_CONTA_INATIVA;
    }

    if (valor_saque <= 0 || valor_saque > VALOR_MAX_SAQUE) {
        return ERR_VALOR_INVALIDO;
    }

    double saldo_atual = contas[indice_conta].saldo;

    // --- Saque parcial --- //
    if (saldo_atual < valor_saque) {
        contas[indice_conta].saldo = 0;
        return SAQUE_PARCIAL;
    }

    // --- Saque normal --- //
    contas[indice_conta].saldo -= valor_saque;
    return OK;
}
