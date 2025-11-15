/* Implementação das funções "ajudantes" (limpeza de tela, buffer, etc.) */

#include "banco.h" // 1. Inclui o "contrato"
#include <stdio.h> // 2. Inclui as bibliotecas que ESTAS funções usam
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpa_tela() {
    int i;
    for (i = 0; i < 40; i++) // da 40 espaços
        printf("\n");
}

void limpa_buffer() {
    int c;
    /* Essa funcao vai ser usada em dois casos.
       1: no menu quando o usuario digita uma letra e o scanf espera um int,
       entao o comentario no while ja explica.
       2: quando o usuario digitou algo que nao devia tipo letra em um cpf, entao
       é preciso limpar a string para ela armazenar novamente o que o usuario digitar. */

    while ((c = getchar()) != '\n' && c != EOF); /* Limpa o buffer (usa getchar enquanto nao
                                                     nao limpar a fila toda), o buffer que causa o loop */
}

int verifica_fgets(char INFO[]) {
    char *ponteiro_enter;
    ponteiro_enter = strchr(INFO, '\n'); // procura o /n na string, se tiver o limite de char foi respeitado

    if (ponteiro_enter != NULL) {
        *ponteiro_enter = '\0';
        return 0;
    } else {
        // se nao tiver \n nao teve espaço para armazenar toda a string
        return -1;
    }
}

int encontrar_conta_por_numero(const Conta contas[], int num_conta, int quant_atual) {
    int i;
    for (i = 0; i < quant_atual; i++) { /*quantidade de contas*/
        if (contas[i].numero == num_conta) {
            return i;
        }
    }
    return -1;
}

int valida_conta_ativa(Conta contas[], int indice_conta) {
    if (contas[indice_conta].status == ENCERRADA) {
        return -1;
    }
    return 0;
}

int verifica_digitos(char INFO[]) {
    int i, tamanho = strlen(INFO);

    for (i = 0; i < tamanho; i++) {
        if (!isdigit(INFO[i])) { /* se a posição atual da string NAO FOR um digito
                                         mande um codigo de erro */
            return -1; // codigo de erro
        }
    }
    return 0;
}

int coletar_numero_conta(Conta contas[]) { //coleta o numero de uma conta de forma segura e retorna um int
    int entrada_valida = 0, num_conta_digito;
    char num_conta[3]; // 1 espaço para numero e outro para o \n da verificao do fgets

    do {
        printf("Informe o numero da conta: ");
        fgets(num_conta, 2, stdin);

        entrada_valida = verifica_fgets(num_conta);

        if (entrada_valida == -1) {
            printf("\nErro: Informe apenas o numero da conta!");
            continue;
        }

        entrada_valida = verifica_digitos(contas);

        if (entrada_valida == -1) {
            printf("\nErro: Informe somente numeros!");
            continue; //return para dar a possibilidade do usuario criar uma conta caso nao tenha
        }

        num_conta_digito = atoi(num_conta); //transforma a string ja verificada em um int

        return num_conta_digito;

    }while (entrada_valida == -1);
}
