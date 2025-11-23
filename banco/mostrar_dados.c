//
// Created by Danillo de Carvalho Montalvão on 16/11/25.
//
#include "banco.h"
#include <stdio.h>

void mostrar_dados(const Conta* c) {
    printf("\n========================================\n");
    printf("         DADOS DA CONTA\n");
    printf("========================================\n");
    printf("Numero da Conta: %d\n", c->numero);
    printf("Nome: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("Agencia: %s\n", c->agencia);
    printf("Telefone: %s\n", c->telefone);
    printf("Saldo: R$ %.2lf\n", c->saldo);

    if (c->status == ATIVA) {
        printf("Status: ATIVA\n");
    } else {
        printf("Status: ENCERRADA\n");
    }

    printf("========================================\n");
}

