#include <stdio.h>
#include <math.h>
#include "banco.h"

int encerrar_conta(Conta contas[], int idx_conta, int quant_atual) {

    if (idx_conta < 0 || idx_conta >= quant_atual) {
        return ERR_CONTA_INEXISTENTE;
    }

    if (valida_conta_ativa(contas, idx_conta) == ERR_CONTA_INATIVA) {
        return ERR_CONTA_INATIVA;
    }
    const double EPS = 1e-9; //para comparacao
    if (fabs(contas[idx_conta].saldo) > EPS) { // se o saldo nao for (praticamente) zero, usado para precisao em doubles
        return ERR_SALDO_NAO_ZERO;
    }

    contas[idx_conta].status = ENCERRADA;
    return OK;
}