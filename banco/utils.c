/* Implementação das funções "ajudantes" (limpeza de tela, buffer, etc.) */

#include "banco.h" // 1. Inclui o "contrato"
#include <stdio.h> // 2. Inclui as bibliotecas que ESTAS funções usam
#include <string.h>

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

/*
 * Função para exibir o menu principal 
 */
void exibir_menu() {
    printf("\n------Menu------\n");
    printf("1. Abrir conta\n");
    printf("2. Depositar\n");
    printf("3. Sacar\n");
    printf("4. Transferir\n");
    printf("5. Consultar saldo e dados\n");
    printf("6. Atualizar telefone e agencia\n");
    printf("7. Listar contas\n");
    printf("8. Encerrar conta\n");
    printf("9. Sair\n");
    printf("Escolha: ");
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
