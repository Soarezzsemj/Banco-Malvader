#include <stdio.h>
#include <string.h>
#include "banco.h"

int consultar_por_numero(Conta contas[], int quant, int numero, int *indice_out) {
    int indice;
    *indice_out = ERR_INVALIDO; //evitando lixo de memoria no return

    if (quant == 0)
        return ERR_NENHUMA_CONTA;

    indice = encontrar_conta_por_numero(contas, numero, quant);

    if (indice < 0)
        return ERR_CONTA_INEXISTENTE;

    int r = valida_conta_ativa(contas, indice);
    if (r != OK)
        return ERR_CONTA_INATIVA;

    *indice_out = indice;
    return OK;
}


//Consultar por CPF

int consultar_por_cpf(Conta contas[], int quant, const char *cpf, int *indice_out) {
    int i;
    *indice_out = ERR_INVALIDO; //evitando lixo de memoria no return

    if (quant == 0)
        return ERR_NENHUMA_CONTA;

    for (i = 0; i < quant; i++) {
        if (strcmp(contas[i].cpf, cpf) == 0) {
            int r = valida_conta_ativa(contas, i);

            if (r != OK)
                return ERR_CONTA_INATIVA;

            *indice_out = i;
            return OK;
        }
    }

    return ERR_CONTA_INEXISTENTE;
}
