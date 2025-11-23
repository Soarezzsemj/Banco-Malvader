#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    const double EPS = 1e-9; //EPS = 0.0000000001
    if (saldo_atual < valor_saque - EPS) { //evitar problemas com precisao no double
        return ERR_SALDO_INSUFICIENTE;
    }

    // --- Saque normal --- //
    contas[indice_conta].saldo -= valor_saque;

    // Se ficou com saldo muito próximo de zero, zera (evita -0.00000001) em caso de o usuario digitar um numero menor que EPS
    if (fabs(contas[indice_conta].saldo) < EPS) {
        contas[indice_conta].saldo = 0.0;
    }

    return OK;
}
