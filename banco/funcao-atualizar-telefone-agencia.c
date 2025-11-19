#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "banco.h"

void coletar_novos_dados_tel_agencia (char TEL_TEMP[], char AGENCIA_TEMP[]) {
    int entrada_valida = 0;

        do {
            printf("Informe o novo numero de telefone: ");
            fgets(TEL_TEMP, TAM_TELEFONE, stdin);

            entrada_valida = verifica_fgets(TEL_TEMP);

            if (entrada_valida == -1) {
                printf("\nErro: Informe um numero de ate %d digitos!", TAM_TELEFONE - 2);
                limpa_buffer();
                continue;
            }

            entrada_valida = verifica_digitos(TEL_TEMP);

            if (entrada_valida == -1) {
                printf("\nErro: Informe somente numeros!");
                continue;
            }
        }while (entrada_valida == -1);

        do {
            printf("Informe a nova agencia: ");
            fgets(AGENCIA_TEMP, TAM_AGENCIA, stdin);

            entrada_valida = verifica_fgets(AGENCIA_TEMP);

            if (entrada_valida == -1) {
                printf("\nErro: Informe um numero de ate %d digitos!", TAM_AGENCIA - 2);
                limpa_buffer();
                continue;
            }

            entrada_valida = verifica_digitos(AGENCIA_TEMP);

            if (entrada_valida == -1) {
                printf("\nErro: Informe somente numeros!");
                continue;
            }
        }while (entrada_valida == -1);
}

void atualizar_dados_tel_agencia (Conta contas[], char TEL_NOVO[], char AGENCIA_NOVA[], int indice) {
    strcpy(contas[indice].telefone, TEL_NOVO);
    strcpy(contas[indice].agencia, AGENCIA_NOVA);

    printf("\nDados alterados com sucesso!\n");
}

