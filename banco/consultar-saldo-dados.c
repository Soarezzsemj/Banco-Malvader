/* ====================================================
   ARQUIVO: consulta.c
   Implementação da função de consulta de contas
   ==================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

/* Remove o '\n' deixado pelo fgets (segurança adicional) */
static void remove_enter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* ====================================================
   FUNÇÃO PRINCIPAL: consultar_conta

   Descrição:
   - Permite consultar uma conta por número OU por CPF
   - Exibe todos os dados da conta se encontrada
   - Valida se a conta existe e está ativa

   Parâmetros:
   - contas[]: array com todas as contas do sistema
   - quant: quantidade atual de contas cadastradas

   Retorno: void (não retorna valor)
   ==================================================== */

void consultar_conta(Conta contas[], int quant) {
    int opcao_busca;
    int encontrou = 0;  // Flag: 0 = não encontrou, 1 = encontrou
    int indice = -1;    // Índice da conta encontrada

    // ========== MENU DE ESCOLHA DO TIPO DE BUSCA ==========
    printf("\n--- CONSULTAR CONTA ---\n");
    printf("Como deseja buscar a conta?\n");
    printf("(1) Por numero da conta\n");
    printf("(2) Por CPF\n");
    printf("Escolha: ");
    scanf("%d", &opcao_busca);


    // ========== VALIDAÇÃO DA OPÇÃO ==========
    if (opcao_busca != 1 && opcao_busca != 2) {
        printf("\nErro: Opcao invalida!\n");
        return;  // Sai da função
    }

    // ========== BUSCA POR NÚMERO DA CONTA ==========
    if (opcao_busca == 1) {
        int numero_conta;
        int entrada_valida = 0;
        char num_temp[10];

        // Loop para garantir entrada válida
        do {
            printf("\nDigite o numero da conta: ");
            fgets(num_temp, 10, stdin);

            // Verifica se não ultrapassou o limite
            entrada_valida = verifica_fgets(num_temp);
            if (entrada_valida == -1) {
                printf("\nErro: Numero muito grande!\n");
                limpa_buffer();
                continue;
            }

            // Verifica se são apenas dígitos
            entrada_valida = verifica_digitos(num_temp);
            if (entrada_valida == -1) {
                printf("\nErro: Digite apenas numeros!\n");
                continue;
            }

            // Converte string para inteiro
            numero_conta = atoi(num_temp);

            // Verifica se é um número válido (maior que 0)
            if (numero_conta < 1) {
                printf("\nErro: Informe um numero de conta valido!\n");
                entrada_valida = -1;
            }

        } while (entrada_valida == -1);

        // Busca a conta no array
        indice = encontrar_conta_por_numero(contas, numero_conta, quant);

        if (indice != -1) {
            encontrou = 1;
        }
    }

    // ========== BUSCA POR CPF ==========
    else if (opcao_busca == 2) {
        char cpf_busca[TAM_CPF];
        int entrada_valida = 0;
        int i;

        // Loop para garantir entrada válida
        do {
            printf("\nDigite o CPF (11 digitos): ");
            fgets(cpf_busca, TAM_CPF, stdin);

            // Verifica se não ultrapassou o limite
            entrada_valida = verifica_fgets(cpf_busca);
            if (entrada_valida == -1) {
                printf("\nErro: CPF muito longo!\n");
                limpa_buffer();
                continue;
            }

            // Verifica se são apenas dígitos
            entrada_valida = verifica_digitos(cpf_busca);
            if (entrada_valida == -1) {
                printf("\nErro: Digite apenas numeros!\n");
                continue;
            }

            // Verifica se tem exatamente 11 dígitos
            if (strlen(cpf_busca) != 11) {
                printf("\nErro: O CPF deve ter exatamente 11 digitos!\n");
                entrada_valida = -1;
            }

        } while (entrada_valida == -1);

        // Busca o CPF no array de contas
        for (i = 0; i < quant; i++) {
            // strcmp retorna 0 quando as strings são IGUAIS
            if (strcmp(contas[i].cpf, cpf_busca) == 0) {
                indice = i;
                encontrou = 1;
                break;  // Sai do loop quando encontrar
            }
        }
    }

    // ========== EXIBIÇÃO DO RESULTADO ==========

    if (!encontrou) {
        // Não encontrou a conta
        printf("\n========================================\n");
        printf("   CONTA NAO ENCONTRADA!\n");
        printf("========================================\n");
        return;
    }

    // Encontrou a conta - exibe os dados
    printf("\n========================================\n");
    printf("         DADOS DA CONTA\n");
    printf("========================================\n");
    printf("Numero da Conta: %d\n", contas[indice].numero);
    printf("Nome: %s\n", contas[indice].nome);
    printf("CPF: %s\n", contas[indice].cpf);
    printf("Agencia: %s\n", contas[indice].agencia);
    printf("Telefone: %s\n", contas[indice].telefone);
    printf("Saldo: R$ %.2lf\n", contas[indice].saldo);

    // Exibe o status da conta
    if (contas[indice].status == ATIVA) {
        printf("Status: ATIVA\n");
    } else {
        printf("Status: ENCERRADA\n");
    }

    printf("========================================\n");
}

/* ====================================================
   EXPLICAÇÃO DETALHADA DO CÓDIGO
   ====================================================

   1. FLUXO GERAL:
      Menu → Escolher tipo de busca → Validar entrada →
      Buscar conta → Exibir resultado

   2. BUSCA POR NÚMERO:
      - Coleta o número da conta com validações
      - Usa a função encontrar_conta_por_numero() já existente
      - Esta função percorre o array e compara os números

   3. BUSCA POR CPF:
      - Coleta o CPF com validações (11 dígitos, só números)
      - Faz um loop manual pelo array de contas
      - Usa strcmp() para comparar strings
      - strcmp(str1, str2) retorna 0 quando são IGUAIS

   4. VALIDAÇÕES IMPLEMENTADAS:
      - Opção de busca válida (1 ou 2)
      - Apenas números nas entradas
      - CPF com exatamente 11 dígitos
      - Número de conta maior que 0
      - Limites de caracteres respeitados

   5. VARIÁVEIS IMPORTANTES:
      - encontrou: flag booleana (0 ou 1)
      - indice: posição da conta no array (-1 = não encontrou)
      - num_temp/cpf_busca: strings temporárias para validação

   6. FUNÇÕES AUXILIARES USADAS:
      - verifica_fgets(): verifica se não ultrapassou limite
      - verifica_digitos(): verifica se só tem números
      - encontrar_conta_por_numero(): busca por número
      - limpa_buffer(): limpa entrada do teclado
      - strcmp(): compara duas strings
      - atoi(): converte string para inteiro

   ====================================================
   COMO ADICIONAR NO SEU PROJETO:
   ====================================================

   1. ADICIONE NO banco.h (na seção de protótipos):
      void consultar_conta(Conta contas[], int quant);

   2. CRIE O ARQUIVO consulta.c com este código

   3. NO main.c, no case 5, substitua a linha:
      consultar_conta(vetor_de_contas, quantidade_atual);

      Ela já está lá! Só precisa compilar junto.

   4. COMPILE TODOS OS ARQUIVOS JUNTOS:
      gcc main.c banco.c utils.c atualizar.c deposito.c consulta.c -o banco

   ====================================================
   EXEMPLO DE USO:
   ====================================================

   BUSCA POR NÚMERO:
   Menu → Opção 5 → Opção 1 → Digite: 1 → Exibe dados

   BUSCA POR CPF:
   Menu → Opção 5 → Opção 2 → Digite: 12345678901 → Exibe dados

   ==================================================== */