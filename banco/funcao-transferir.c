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
   Retorna:
       - OK (1) se a transferência foi concluída com sucesso
       - ERR_* (0 ou códigos de erro) caso algo dê errado
*/
int realizar_transferencia(Conta contas[], int quant_atual, int conta_origem, int conta_destino, double valor) {

    // Verifica se o valor é válido
    if (valor <= 0) {
        printf("Erro: o valor deve ser maior que zero.\n");
        return 0;
    }

    // Encontrar índice da conta de origem
    int idx_origem = encontrar_conta_por_numero(contas, conta_origem, quant_atual);
    if (idx_origem == -1) {
        printf("Erro: conta de origem nao encontrada.\n");
        return 0;
    }

    // Encontrar índice da conta de destino
    int idx_destino = encontrar_conta_por_numero(contas, conta_destino, quant_atual);
    if (idx_destino == -1) {
        printf("Erro: conta de destino nao encontrada.\n");
        return 0;
    }

    // Verifica se as contas estão ativas
    if (contas[idx_origem].status != ATIVA) {
        printf("Erro: conta de origem esta encerrada.\n");
        return 0;
    }

    if (contas[idx_destino].status != ATIVA) {
        printf("Erro: conta de destino esta encerrada.\n");
        return 0;
    }

    // Verifica se há saldo suficiente
    if (contas[idx_origem].saldo < valor) {
        printf("Erro: saldo insuficiente.\n");
        return 0;
    }

    // Realiza a transferência
    contas[idx_origem].saldo -= valor;
    contas[idx_destino].saldo += valor;

    printf("Transferencia de %.2f realizada com sucesso!\n", valor);

    return 1; // Sucesso
}
