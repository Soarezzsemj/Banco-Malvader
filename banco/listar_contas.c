// Puxa as nossas structs (Conta) e os defines (ATIVA, etc) do .h
#include "banco.h"
// Puxa o printf
#include <stdio.h>

void listar_contas(const Conta contas[], int qtd, int filtro_status) {

    // Variavel pra saber se a gente achou alguma conta pra imprimir
    int encontrou_alguma = 0;

    // Vou usar 2 pra ser "TODAS", ja que 1 é ATIVA e 0 é ENCERRADA
    const int FILTRO_TODAS = 2;

    printf("\n--- Lista de Contas ---\n");

    // Se nao tem conta nenhuma, so avisa e sai
    if (qtd == 0) {
        printf("Nenhuma conta cadastrada no sistema.\n");
        return;
    }

    // Loop principal, passa por todas as contas
    for (int i = 0; i < qtd; i++) {
        // Pega a conta atual pra ficar mais facil
        const Conta c = contas[i];

        // Flag pra decidir se imprime essa conta especifica
        int imprimir = 0;

        // Lógica dos filtros
        // O trabalho pede filtros por status

        // Se o filtro for 2 (TODAS), imprime sempre
        if (filtro_status == FILTRO_TODAS) {
            imprimir = 1;

            // Se o filtro for 1 (ATIVA) e a conta ta ATIVA
        } else if (filtro_status == ATIVA && c.status == ATIVA) {
            imprimir = 1;

            // Se o filtro for 0 (ENCERRADA) e a conta ta ENCERRADA
        } else if (filtro_status == ENCERRADA && c.status == ENCERRADA) {
            imprimir = 1;
        }

        // Se a flag 'imprimir' for 1, entao mostra os dados
        if (imprimir) {
            // O trabalho pede pra usar a 'mostrar_dados'
            // (assumindo que o colega já fez ela)
            mostrar_dados(&c);
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