#include <stdio.h>
#include "banco.h"

// Função para coletar os dados (Conta e Valor)
void coletar_info_saque (int *num_conta, double *valor_saque) {
    int opcao_valida = 0;

    // --- Parte 1: Coletar Número da Conta ---
    do {
        printf("Informe o numero da conta que voce deseja fazer o saque: ");
        opcao_valida = scanf("%d", &*num_conta);

        if (opcao_valida != 1) {
            limpa_buffer();
            printf("\nErro: Informe somente numeros!\n");
            continue;
        }
        if (*num_conta < 1) {
            printf("\nErro: Informe uma conta valida!\n");
            opcao_valida = -1;
        }
        limpa_buffer();
    } while (opcao_valida != 1);

    // --- Parte 2: Coletar Valor do Saque ---
    do {
        printf("Informe o valor do saque: ");
        opcao_valida = scanf("%lf", &*valor_saque);

        if (opcao_valida != 1) {
            printf("\nErro: Informe somente numeros!");
            limpa_buffer();
            continue;
        }

        if (*valor_saque <= 0) {
            printf("Informe um numero positivo maior que zero!\n");
            opcao_valida = -1;
            continue;
        }



        limpa_buffer();
    } while (opcao_valida != 1);
}

// Função lógica que efetiva a subtração do saldo
int realizar_saque(Conta contas[], int indice_conta, double valor_saque) {
    // Validação 1: Valor positivo
    if (valor_saque <= 0) {
        printf("Erro: Informe um valor maior que 0!\n");
        return -1;
    }

    // Validação 2: Conta ativa
    if (contas[indice_conta].status == ENCERRADA) {
        printf("Erro: A conta informada esta desativada!\n");
        return -1;
    }

    // Validação 3: Saldo suficiente (EXCLUSIVO DO SAQUE)
    if (contas[indice_conta].saldo < valor_saque) {
        printf("Erro: Saldo insuficiente para realizar o saque!\n");
        printf("Saldo atual: %.2lf\n", contas[indice_conta].saldo);
        return -1;
    }

    // Operação de saque
    contas[indice_conta].saldo -= valor_saque;

    return 0; // Sucesso
}