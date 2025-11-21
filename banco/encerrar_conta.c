#include <stdio.h>
#include "banco.h"

int encerrar_conta(Conta contas[], int idx_conta, int quant_atual) {

    contas[idx_conta].status = ENCERRADA;
    return OK;
}