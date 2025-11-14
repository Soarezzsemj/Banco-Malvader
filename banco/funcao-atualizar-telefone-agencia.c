#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "banco.h"

int coletar_dados_att_telefone_agencia (Conta contas[], int contas_ativas, int num_conta);

int obter_conta_valida(const Conta contas[], int quant_atual) {
    int entrada_valida = 0;
    char num_conta[2]; // 1 espaço para numero e outro para o \n da verificao do fgets

    do {
        printf("Informe o numero da conta: ");
        fgets(num_conta, strlen(num_conta), stdin);

        entrada_valida = verifica_fgets(num_conta);

        if (entrada_valida == -1) {
            printf("\nErro: Informe apenas o numero da conta!");
            continue;
        }

        int num_conta_digito = atoi(num_conta); //transforma a string ja verificada em um int

        entrada_valida = encontrar_conta_por_numero(contas, quant_atual, num_conta_digito);

        if (entrada_valida == -1) {
            printf("\nErro: A conta informada nao existe!");
            continue;
        }

        entrada_valida = valida_conta_ativa(contas, num_conta_digito);

        if (entrada_valida == -1) {
            printf("Erro: A conta informada esta desativada!\n");
        }
        return num_conta_digito;

    }while (entrada_valida == -1);


}