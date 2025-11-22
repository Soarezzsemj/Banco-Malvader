/* * Implementação das funções principais de gerenciamento de conta.
 */

#include "banco.h" // 1. Inclui o "contrato"
#include <stdio.h> // 2. Inclui as bibliotecas que ESTAS funções usam
#include <string.h>

int abrir_conta(Conta contas[], int *quant, int num_conta, const char *nome,
                const char *cpf,const char *agencia, const char *telefone) {
    int i;

    for (i = 0; i < *quant; i++) {
        if (strcmp(contas[i].cpf, cpf) == 0 && contas[i].status == ATIVA) { /* Se o CPF da conta de indice
                                                                               *quant for igual a do CPF temp e a conta
                                                                               do indice *temp estiver ativa, entao é
                                                                               uma conta duplicada */
            return ERR_CPF_DUPLICADO; // erro ao criar conta
        }
    }

    // copia os dados das variaveis _temp para a variavel struct Conta
    strcpy(contas[*quant].nome, nome);
    strcpy(contas[*quant].cpf, cpf);
    strcpy(contas[*quant].agencia, agencia);
    strcpy(contas[*quant].telefone, telefone);
    contas[*quant].saldo = 0.0;
    contas[*quant].numero = num_conta;
    contas[*quant].status = ATIVA;

    *quant += 1; // acrescenta 1 no apontado de quantidade_atual no main
    return OK; // sucesso, uma conta foi criada
}

void coletar_dados_abertura_conta(char NOME_temp[], char CPF_temp[], char AGENCIA_temp[], char TELEFONE_temp[]) {
    printf("\n------ABERTURA DE CONTA NOVA------\n");

    int entrada_valida = OK;

    do {
        printf("\nDigite o seu nome completo: ");
        fgets(NOME_temp, TAM_NOME, stdin);

        entrada_valida = verifica_fgets(NOME_temp); // funcao verifica se ultrapassou o limite

        if (entrada_valida == ERR_INPUT_MUITO_LONG) {
            printf("\nErro: Nome muito longo! O limite de caracteres eh %d caracteres.\n", TAM_NOME - 2);
            limpa_buffer();
            continue;
        }

        entrada_valida = verifica_letras(NOME_temp);

        if (entrada_valida == ERR_DIGIT_EM_NOME) {
            printf("\nErro: Informe somente letras!");
            continue;
        }

    } while (entrada_valida != OK);

    do {
        printf("Digite o seu cpf completo (apenas numeros): ");
        fgets(CPF_temp, TAM_CPF, stdin);

        entrada_valida = verifica_fgets(CPF_temp);
        if (entrada_valida == ERR_INPUT_MUITO_LONG) {
            printf("Erro: CPF muito longo! O CPF deve ter 11 digitos.\n");
            limpa_buffer();
            continue;
        }

        entrada_valida = verifica_digitos(CPF_temp);

        if (entrada_valida == ERR_LETRA_EM_NUMERO) {
            printf("\nErro: Digite apenas numeros!\n");
            continue;
        }

        if (strlen(CPF_temp) != 11) {
            printf("\nErro: O CPF deve ter 11 digitos, voce informou somente %d.\n", (int)strlen(CPF_temp));
            entrada_valida = ERR_INVALIDO;
            continue;
        }
    } while (entrada_valida != OK);

    do {
        printf("Informe sua agencia: ");
        fgets(AGENCIA_temp, TAM_AGENCIA, stdin);

        entrada_valida = verifica_fgets(AGENCIA_temp);
        if (entrada_valida == ERR_INPUT_MUITO_LONG) {
            printf("\nErro: Nome de agencia muito longo! O limite eh %d caracteres.\n", TAM_AGENCIA - 2);
            limpa_buffer();
            continue;
        }

        entrada_valida = verifica_digitos(AGENCIA_temp);

        if (entrada_valida == ERR_LETRA_EM_NUMERO) {
            printf("\nErro: Digite apenas numeros!\n");
            continue;
        }
    } while (entrada_valida != OK);

    do {
        printf("Informe seu telefone (apenas numeros): ");
        fgets(TELEFONE_temp, TAM_TELEFONE, stdin);

        entrada_valida = verifica_fgets(TELEFONE_temp);
        if (entrada_valida == ERR_INPUT_MUITO_LONG) {
            printf("\nErro: Numero de telefone grande demais! O limite eh de %d numeros.\n", TAM_TELEFONE - 2);
            limpa_buffer();
            continue;
        }

        entrada_valida = verifica_digitos(TELEFONE_temp);

        if (entrada_valida == ERR_LETRA_EM_NUMERO) {
            printf("\nErro: Digite apenas numeros!\n");
            continue;
        }
    } while (entrada_valida != OK);

}