/* Implementação das funções "ajudantes" (limpeza de tela, buffer, etc.) */

#include "banco.h" // 1. Inclui o "contrato"
#include <stdio.h> // 2. Inclui as bibliotecas que ESTAS funções usam
#include <string.h>

/* Limpa a tela */
void limpa_tela() {
    for (int i = 0; i < 40; i++)
        printf("\n");
}

/* Limpa o buffer do teclado */
void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Verifica se o fgets respeitou o limite de caracteres */
int verifica_fgets(char INFO[]) {
    char *ponteiro_enter = strchr(INFO, '\n');
    if (ponteiro_enter != NULL) {
        *ponteiro_enter = '\0';
        return 0;
    } else {
        return -1;
    }
}

/* Lê um inteiro com validação */
int ler_int(const char *mensagem) {
    int valor;
    char c;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
            return valor;
        } else {
            printf("Entrada invalida! Digite um numero.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

/* Lê um double com validação */
double ler_double(const char *mensagem) {
    double valor;
    char c;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%lf", &valor) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
            return valor;
        } else {
            printf("Entrada invalida! Digite um numero.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}