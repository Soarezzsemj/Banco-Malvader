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
        return OK;
    } else {
        // se nao tiver \n nao teve espaço para armazenar toda a string
        return ERR_INPUT_MUITO_LONG;
    }
}

int encontrar_conta_por_numero(const Conta contas[], int num_conta, int quant_atual) {
    int i;
    /* a funcao pega o numero da conta,verifica se a conta existe,
    e se for retorna O INDICE DA CONTA, por isso atencao ao uso dela*/

    for (i = 0; i < quant_atual; i++) { /*quantidade de contas*/
        if (contas[i].numero == num_conta) {
            return i;
        }
    }
    return ERR_CONTA_INEXISTENTE;
}

int valida_conta_ativa(Conta contas[], int indice_conta) {
    //sempre garantam que essa funcao receba um indice valido ou seja
    //indice >= 0 && indice < quant_atual
    if (contas[indice_conta].status == ENCERRADA) {
        return ERR_CONTA_INATIVA;
    }
    return OK;
}

int verifica_digitos(char INFO[]) {
    int i, tamanho = strlen(INFO);

    for (i = 0; i < tamanho; i++) {
        if (!isdigit(INFO[i])) { /* se a posição atual da string NAO FOR um digito
                                         mande um codigo de erro */
            return ERR_LETRA_EM_NUMERO; // codigo de erro
        }
    }
    return OK;
}

int verifica_digitos_saldo(char SALDO[]) {
    for (int i = 0; SALDO[i] != '\0'; i++) {
        if (!isdigit(SALDO[i]) && SALDO[i] != '.') {
            return ERR_LETRA_EM_NUMERO;
        }
    }
    return OK;
}

int verifica_letras(char INFO[]) {
    int i, tamanho = strlen(INFO);

    for (i = 0; i < tamanho; i++) {
        if (isdigit(INFO[i])) { /* se a posição atual da string FOR um digito
                                         mande um codigo de erro */
            return ERR_DIGIT_EM_NOME; // codigo de erro
        }
    }
    return OK;
}

int coletar_numero_conta(void) { //coleta o numero de uma conta de forma segura e retorna um int
    int entrada_valida = 0, num_conta_digito;
    char num_conta[5];

    do {
        printf("Informe o numero da conta: ");
        fgets(num_conta, sizeof(num_conta), stdin);

        entrada_valida = verifica_fgets(num_conta);

        if (entrada_valida == ERR_INPUT_MUITO_LONG) {
            printf("\nErro: Informe apenas o numero da conta!\n");
            limpa_buffer();
            continue;
        }

        entrada_valida = verifica_digitos(num_conta);

        if (entrada_valida == ERR_LETRA_EM_NUMERO) {
            printf("\nErro: Informe somente numeros!\n");
            continue; //return para dar a possibilidade do usuario criar uma conta caso nao tenha
        }

        num_conta_digito = atoi(num_conta); //transforma a string ja verificada em um int

        return num_conta_digito;

    }while (entrada_valida != OK);

    return ERR_PARA_COMPILADOR; //funcao nao chega aqui, so para o compilador nao reclamar
}
