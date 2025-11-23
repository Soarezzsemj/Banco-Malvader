#include <stdio.h>
#include <string.h>

#include "banco.h"

void coletar_novos_dados_tel_agencia (char tel_temp[], char agencia_temp[]) {
    int entrada_valida = OK;

        do {
            printf("Informe o novo numero de telefone: ");
            fgets(tel_temp, TAM_TELEFONE, stdin);

            entrada_valida = verifica_fgets(tel_temp);

            if (entrada_valida == ERR_INPUT_MUITO_LONG) {
                printf("\nErro: Informe um numero de ate %d digitos!", TAM_TELEFONE - 2);
                limpa_buffer();
                continue;
            }

            entrada_valida = verifica_digitos(tel_temp);

            if (entrada_valida == ERR_LETRA_EM_NUMERO) {
                printf("\nErro: Informe somente numeros!");
                continue;
            }
        }while (entrada_valida != OK);

        do {
            printf("Informe a nova agencia: ");
            fgets(agencia_temp, TAM_AGENCIA, stdin);

            entrada_valida = verifica_fgets(agencia_temp);

            if (entrada_valida == ERR_INPUT_MUITO_LONG) {
                printf("\nErro: Informe um numero de ate %d digitos!", TAM_AGENCIA - 2);
                limpa_buffer();
                continue;
            }

            entrada_valida = verifica_digitos(agencia_temp);

            if (entrada_valida == ERR_LETRA_EM_NUMERO) {
                printf("\nErro: Informe somente numeros!");
                continue;
            }
        }while (entrada_valida != OK);
}

void atualizar_dados_tel_agencia (Conta contas[], char tel_novo[], char agencia_nova[], int indice) {
    strcpy(contas[indice].telefone, tel_novo);
    strcpy(contas[indice].agencia, agencia_nova);

    printf("\nDados alterados com sucesso!\n");
}

