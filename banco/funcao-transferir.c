//
// Created by Soarezz on 16/11/2025.
//

#include <stdio.h>
#include "banco.h"

/*
   Função: realizar_transferencia
   Recebe:
       - contas[]: vetor de todas as contas
       - quant_atual: número total de contas cadastradas
       - conta_origem: número da conta que vai transferir
       - conta_destino: número da conta que vai receber
       - valor: valor a ser transferido
*/
int realizar_transferencia(Conta contas[], int quant_atual, int conta_origem, int conta_destino, double valor) {

    // Verifica se o valor é válido
    if (valor <= 0) {
        return ERR_VALOR_INVALIDO;
    }

    // Encontrar índice da conta de origem
    int idx_origem = encontrar_conta_por_numero(contas, conta_origem, quant_atual);
    if (idx_origem == ERR_CONTA_INEXISTENTE) {
        return ERR_CONTA_INEXISTENTE;
    }

    // Encontrar índice da conta de destino
    int idx_destino = encontrar_conta_por_numero(contas, conta_destino, quant_atual);
    if (idx_destino == ERR_CONTA_INEXISTENTE) {
        return ERR_CONTA_INEXISTENTE;
    }

    // Verifica se as contas estão ativas
    if (!valida_conta_ativa(contas, idx_origem)) {
        return ERR_CONTA_INATIVA;
    }

    if (!valida_conta_ativa(contas, idx_destino)) {
        return ERR_CONTA_INATIVA;
    }

    // Verifica se há saldo suficiente
    if (contas[idx_origem].saldo < valor) {
        return ERR_SALDO_INSUFICIENTE;
    }

    // Realiza a transferência
    contas[idx_origem].saldo -= valor;
    contas[idx_destino].saldo += valor;

    printf("Transferencia de %.2f realizada com sucesso!\n", valor);

    return OK; // Sucesso
}