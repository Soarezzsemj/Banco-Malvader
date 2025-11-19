
#include "banco.h"
#include <stdio.h>

void listar_contas(const Conta contas[], int qtd, int filtro_status) {

    // Variavel pra saber se a gente achou alguma conta pra imprimir
    int encontrou_alguma = 0;

    // Mudei os filtros pra bater com o menu novo
    const int FILTRO_ENCERRADAS = 1;
    const int FILTRO_ATIVAS = 2;
    const int FILTRO_TODAS = 3;

    printf("\n--- Lista de Contas ---\n");

    // Se nao tem conta nenhuma, so avisa e sai
    if (qtd == 0) {
        printf("Nenhuma conta cadastrada no sistema.\n");
        return;
    }

    // Loop principal, passa por todas as contas
    for (int i = 0; i < qtd; i++) {

        // Flag pra decidir se imprime essa conta especifica
        int imprimir = 0;

        // Se o filtro for 3 (TODAS), imprime sempre
        if (filtro_status == FILTRO_TODAS) {
            imprimir = 1;
        }
            // Se o filtro for 2 (ATIVAS) e a conta ta ATIVA
        else if (filtro_status == FILTRO_ATIVAS && contas[i].status == ATIVA) {
            imprimir = 1;
        }
            // Se o filtro for 1 (ENCERRADA) e a conta ta ENCERRADA
        else if (filtro_status == FILTRO_ENCERRADAS && contas[i].status == ENCERRADA) {
            imprimir = 1;
        }

        // Se a flag 'imprimir' for 1, entao mostra os dados
        if (imprimir) {
            mostrar_dados(&contas[i]);
            printf("-------------------------\n");

            // Avisa que a gente achou pelo menos uma
            encontrou_alguma = 1;
        }
    }

    // Se o loop terminou e 'encontrou_alguma' ainda é 0,
    // é porque ninguem passou no filtro
    if (encontrou_alguma == 0) {
        printf("Nenhuma conta encontrada para este filtro.\n");
    }
}