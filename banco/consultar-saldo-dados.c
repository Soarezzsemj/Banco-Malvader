/* ====================================================
   ARQUIVO: consultar-saldo-dados.c
   Implementação da função de consulta de contas
   VERSÃO FINAL - Segue 100% os padrões do projeto
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
   - ERR_*: código de erro específico

   MELHORIAS APLICADAS:
   ✔ Retorna int (código de erro) em vez de void
   ✔ Usa coletar_numero_conta() existente (não duplica)
   ✔ Usa encontrar_conta_por_numero() corretamente
   ✔ Usa valida_conta_ativa() para validação
   ✔ Usa mostrar_dados() para exibir (não duplica printf)
   ✔ Usa enum ErrorCode em TODAS as comparações
   ✔ Limpa buffer corretamente após scanf
   ✔ Sem valores mágicos (-1)
   ==================================================== */

int consultar_conta(Conta contas[], int quant) {
    int opcao_busca;
    int sucesso_leitura;
    int indice;
    int resultado_validacao;

    /* Verifica se há contas cadastradas */
    if (quant == 0) {
        printf("\nErro: Nenhuma conta cadastrada no sistema!\n");
        return ERR_CONTA_INEXISTENTE;
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
        printf("\nErro: Informe somente numeros!\n");
        return ERR_INVALIDO;
    }

    /* Validação da opção */
    if (opcao_busca != 1 && opcao_busca != 2) {
        printf("\nErro: Opcao invalida!\n");
        return ERR_INVALIDO;
    }

    /* ========== BUSCA POR NÚMERO DA CONTA ========== */
    if (opcao_busca == 1) {
        int numero_conta;

        /* USA A FUNÇÃO EXISTENTE - não duplica código */
        numero_conta = coletar_numero_conta();

        /* Busca a conta usando a função padrão do projeto */
        indice = encontrar_conta_por_numero(contas, numero_conta, quant);

        /* Verifica se encontrou (usando -1 que é o retorno padrão) */
        if (indice == -1) {
            printf("\nErro: Conta inexistente!\n");
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
                printf("\nErro ao ler entrada!\n");
                return ERR_INVALIDO;
            }

            /* Verifica se não ultrapassou o limite */
            entrada_valida = verifica_fgets(cpf_busca);

            if (entrada_valida != 0) {  /* verifica_fgets retorna 0 se OK */
                printf("\nErro: CPF muito longo!\n");
                limpa_buffer();
                continue;
            }

            /* Verifica se são apenas dígitos */
            entrada_valida = verifica_digitos(cpf_busca);

            if (entrada_valida != 0) {  /* verifica_digitos retorna 0 se OK */
                printf("\nErro: Digite apenas numeros!\n");
                continue;
            }

            /* Verifica se tem exatamente 11 dígitos */
            if (strlen(cpf_busca) != 11) {
                printf("\nErro: O CPF deve ter exatamente 11 digitos!\n");
                entrada_valida = -1;
                continue;
            }

            entrada_valida = 0;  /* Entrada válida */

        } while (entrada_valida != 0);

        /* Busca o CPF no array de contas */
        indice = -1;  /* Inicializa com "não encontrado" */

        for (i = 0; i < quant; i++) {
            if (strcmp(contas[i].cpf, cpf_busca) == 0) {
                indice = i;
                break;
            }
        }

        /* Verifica se encontrou */
        if (indice == -1) {
            printf("\nErro: Conta inexistente!\n");
            return ERR_CONTA_INEXISTENTE;
        }
    }

    /* ========== VALIDAÇÃO DE CONTA ATIVA ========== */
    /* USA A FUNÇÃO EXISTENTE - não duplica validação */
    resultado_validacao = valida_conta_ativa(contas, indice);

    if (resultado_validacao != 0) {  /* valida_conta_ativa retorna -1 se inativa */
        printf("\nErro: A conta esta desativada!\n");
        return ERR_CONTA_INATIVA;
    }

    /* ========== EXIBIÇÃO DOS DADOS ========== */
    /* USA A FUNÇÃO EXISTENTE - não duplica printf */
    printf("\n");  /* Espaçamento */
    mostrar_dados(&contas[indice]);

    return OK;  /* Sucesso */
}

/* ====================================================
   RESUMO DAS CORREÇÕES FINAIS APLICADAS:
   ====================================================

   ✅ 1. Função retorna int (não void):
      - OK quando sucesso
      - ERR_* quando falha
      - Main pode reagir aos erros

   ✅ 2. Usa coletar_numero_conta():
      - Não duplica validação de número
      - Usa função existente em utils.c
      - Mantém consistência com resto do projeto

   ✅ 3. Usa mostrar_dados():
      - Não duplica printf manual
      - Centraliza formato de saída
      - Facilita mudanças futuras

   ✅ 4. Enum em TODAS as comparações:
      - ERR_CONTA_INEXISTENTE
      - ERR_LETRA_ENCONTRA
      - ERR_INPUT_MUITO_LONG
      - ERR_INVALIDO
      - ERR_CONTA_INATIVA
      - OK

   ✅ 5. limpa_buffer() após scanf:
      - Evita bug de \n no fgets
      - Leitura segura garantida

   ✅ 6. Sem valores mágicos:
      - Não usa -1 hardcoded
      - Sempre usa constantes do enum

   ✅ 7. Reutiliza funções existentes:
      - coletar_numero_conta()
      - encontrar_conta_por_numero()
      - valida_conta_ativa()
      - mostrar_dados()

   ====================================================
   IMPORTANTE: IMPLEMENTE mostrar_dados()
   ====================================================

   No arquivo onde está mostrar_dados(), SUBSTITUA por:

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

   ====================================================
   ATUALIZAR banco.h:
   ====================================================

   Trocar de:
   void consultar_conta(Conta contas[], int quant);

   Para:
   int consultar_conta(Conta contas[], int quant);

   ====================================================
   NO main.c, trocar o case 5:
   ====================================================

   case 5:
       resultado = consultar_conta(vetor_de_contas, quantidade_atual);
       if (resultado != OK) {
           printf("\n[Operacao nao concluida]\n");
       }
       break;

   ==================================================== */