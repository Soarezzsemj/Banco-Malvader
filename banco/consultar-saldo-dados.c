/* ====================================================
   ARQUIVO: consultar-saldo-dados.c
   Implementação da função de consulta de contas
   VERSÃO FINAL - 100% nos padrões do projeto
   ==================================================== */

#include <stdio.h>
#include <string.h>
#include "banco.h"

/* ====================================================
   FUNÇÃO PRINCIPAL: consultar_conta

   Descrição:
   - Permite consultar uma conta por número OU por CPF
   - Exibe todos os dados da conta se encontrada
   - Valida se a conta existe e está ativa

   Parâmetros:
   - contas[]: array com todas as contas do sistema
   - quant: quantidade atual de contas cadastradas

   Retorno:
   - OK: operação concluída com sucesso
   - ERR_NENHUMA_CONTA: sistema sem contas
   - ERR_CONTA_INEXISTENTE: conta não encontrada
   - ERR_CONTA_INATIVA: conta existe mas está inativa
   - ERR_INVALIDO: entrada inválida do usuário

   PADRÕES SEGUIDOS:
   ✔ Retorna int (código de erro)
   ✔ NÃO imprime mensagens (main faz isso)
   ✔ Usa enum em TODAS as comparações
   ✔ Usa OK em vez de 0
   ✔ ERR_NENHUMA_CONTA quando quant == 0
   ✔ Reutiliza funções existentes
   ==================================================== */

int consultar_conta(Conta contas[], int quant) {
    int opcao_busca;
    int sucesso_leitura;
    int indice;
    int resultado_validacao;

    /* Verifica se há contas cadastradas */
    if (quant == 0) {
        return ERR_NENHUMA_CONTA;  /* Sistema vazio */
    }

    /* ========== MENU DE ESCOLHA DO TIPO DE BUSCA ========== */
    printf("\n--- CONSULTAR CONTA ---\n");
    printf("Como deseja buscar a conta?\n");
    printf("(1) Por numero da conta\n");
    printf("(2) Por CPF\n");
    printf("Escolha: ");

    /* Validação robusta do scanf */
    sucesso_leitura = scanf("%d", &opcao_busca);
    limpa_buffer();  /* ESSENCIAL: limpa o \n antes do fgets */

    if (sucesso_leitura != 1) {
        return ERR_INVALIDO;  /* Usuário digitou letra */
    }

    /* Validação da opção */
    if (opcao_busca != 1 && opcao_busca != 2) {
        return ERR_INVALIDO;  /* Opção fora do range */
    }

    /* ========== BUSCA POR NÚMERO DA CONTA ========== */
    if (opcao_busca == 1) {
        int numero_conta;

        /* USA A FUNÇÃO EXISTENTE - não duplica código */
        numero_conta = coletar_numero_conta();

        /* Busca a conta usando a função padrão do projeto */
        indice = encontrar_conta_por_numero(contas, numero_conta, quant);

        /* Verifica se encontrou */
        if (indice == ERR_CONTA_INEXISTENTE) {
            return ERR_CONTA_INEXISTENTE;
        }
    }
    /* ========== BUSCA POR CPF ========== */
    else {
        char cpf_busca[TAM_CPF];
        int entrada_valida;
        int i;

        /* Loop para garantir entrada válida */
        do {
            printf("\nDigite o CPF (11 digitos): ");

            if (fgets(cpf_busca, TAM_CPF, stdin) == NULL) {
                return ERR_INVALIDO;
            }

            /* Verifica se não ultrapassou o limite */
            entrada_valida = verifica_fgets(cpf_busca);

            if (entrada_valida != OK) {
                limpa_buffer();
                continue;
            }

            /* Verifica se são apenas dígitos */
            entrada_valida = verifica_digitos(cpf_busca);

            if (entrada_valida != OK) {
                continue;
            }

            /* Verifica se tem exatamente 11 dígitos */
            if (strlen(cpf_busca) != 11) {
                entrada_valida = ERR_INVALIDO;
                continue;
            }

            entrada_valida = OK;  /* Entrada válida */

        } while (entrada_valida != OK);

        /* Busca o CPF no array de contas */
        indice = ERR_CONTA_INEXISTENTE;  /* Inicializa como "não encontrado" */

        for (i = 0; i < quant; i++) {
            if (strcmp(contas[i].cpf, cpf_busca) == 0) {
                indice = i;
                break;
            }
        }

        /* Verifica se encontrou */
        if (indice == ERR_CONTA_INEXISTENTE) {
            return ERR_CONTA_INEXISTENTE;
        }
    }

    /* ========== VALIDAÇÃO DE CONTA ATIVA ========== */
    /* USA A FUNÇÃO EXISTENTE - não duplica validação */
    resultado_validacao = valida_conta_ativa(contas, indice);

    if (resultado_validacao != OK) {
        return ERR_CONTA_INATIVA;
    }

    /* ========== EXIBIÇÃO DOS DADOS ========== */
    /* USA A FUNÇÃO EXISTENTE - não duplica printf */
    printf("\n");  /* Espaçamento */
    mostrar_dados(&contas[indice]);

    return OK;  /* Sucesso */
}

/* ====================================================
   RESUMO FINAL:
   ====================================================

   ✅ Usa enum em TODAS as comparações (não -1 ou 0)
   ✅ Retorna ERR_NENHUMA_CONTA quando quant == 0
   ✅ Compara com != OK (não != 0)
   ✅ NÃO imprime mensagens de erro (main faz isso)
   ✅ Reutiliza funções existentes
   ✅ Código limpo e consistente

   ====================================================
   NO main.c, o case 5 deve ficar:
   ====================================================

   case 5:
       resultado_da_conta = consultar_conta(vetor_de_contas, quantidade_atual);

       switch (resultado_da_conta) {
           case OK:
               printf("\nConsulta realizada com sucesso!\n");
               break;

           case ERR_NENHUMA_CONTA:
               printf("\nErro: Nenhuma conta cadastrada no sistema!\n");
               break;

           case ERR_CONTA_INEXISTENTE:
               printf("\nErro: Conta inexistente!\n");
               break;

           case ERR_CONTA_INATIVA:
               printf("\nErro: A conta esta desativada!\n");
               break;

           case ERR_INVALIDO:
               printf("\nErro: Entrada invalida!\n");
               break;

           default:
               printf("\nErro desconhecido!\n");
               break;
       }
       break;

   ====================================================
   ATUALIZAR banco.h:
   ====================================================

   int consultar_conta(Conta contas[], int quant);

   ====================================================
   IMPLEMENTAR mostrar_dados() (se ainda não tiver):
   ====================================================

   void mostrar_dados(const Conta* c) {
       printf("\n========================================\n");
       printf("         DADOS DA CONTA\n");
       printf("========================================\n");
       printf("Numero da Conta: %d\n", c->numero);
       printf("Nome: %s\n", c->nome);
       printf("CPF: %s\n", c->cpf);
       printf("Agencia: %s\n", c->agencia);
       printf("Telefone: %s\n", c->telefone);
       printf("Saldo: R$ %.2lf\n", c->saldo);

       if (c->status == ATIVA) {
           printf("Status: ATIVA\n");
       } else {
           printf("Status: ENCERRADA\n");
       }

       printf("========================================\n");
   }

   ==================================================== */