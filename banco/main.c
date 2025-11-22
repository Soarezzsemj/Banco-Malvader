#include <stdio.h>
#include "banco.h"

int main() {
    Conta vetor_de_contas[MAX_CONTAS];
    int quantidade_atual = 0; // numero de contas criadas
    int num_proxima_conta = 1; // vai ser incrementado depois apos a criação de uma nova conta
    int opcao, sucesso_leitura, resultado_da_conta;

    do {
        // imprime na tela todas as opções do sistema bancário
        exibir_menu();

        sucesso_leitura = scanf("%d", &opcao); // se ler um numero ele retorna 1

        if (sucesso_leitura != 1) { // se for uma letra, ele ficou preso na fila, temos que limpa-lo
            limpa_tela();
            printf("\nErro: Entrada invalida! Por favor informe somente numeros.\n");
            limpa_buffer();
            opcao = 0;
            continue;
        }

        limpa_buffer(); // limpar o buffer para o \n nao ir para o proximo fgets

        if (opcao < 1 || opcao > 9) { // se nao for uma das opcoes pede ao usuario para tentar novamente
            limpa_tela();
            printf("\nErro: Opcao invalida! Digite uma opcao valida por favor.\n");
            continue; // reinicia o loop
        }

        switch (opcao) {

            case 1: {
                limpa_tela();

                if (quantidade_atual >= MAX_CONTAS) {
                    printf("\nErro: Limite de contas atingido!\n");
                    break; // volta para o menu
                }

                char nome_temp[TAM_NOME];
                char cpf_temp[TAM_CPF];
                char agencia_temp[TAM_AGENCIA];
                char telefone_temp[TAM_TELEFONE];

                coletar_dados_abertura_conta(nome_temp, cpf_temp, agencia_temp, telefone_temp); // preenche os dados

                resultado_da_conta = abrir_conta(
                    vetor_de_contas, &quantidade_atual, num_proxima_conta,
                    nome_temp, cpf_temp, agencia_temp, telefone_temp
                ); //verifica se o CPF ja existe em outra conta

                if (resultado_da_conta == OK) {
                    printf("\nConta criada com sucesso! Numero da conta: %d\n", num_proxima_conta);
                    num_proxima_conta++;
                }
                else { //erro se o cpf da conta for duplicado
                    printf("\nErro: O CPF cadastrado já existe em uma conta ativa.");
                }

                break;
            }

            case 2: {
                int idx_conta, num_conta, verifica_sucesso;
                double valor_deposito;

                limpa_tela();

                printf("\n --- Fazer deposito --- \n");

                num_conta = coletar_numero_conta();

                idx_conta = encontrar_conta_por_numero(
                    vetor_de_contas, num_conta, quantidade_atual
                ); // pega O INDICE DA CONTA

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    printf("Erro: A conta nao existe!");
                    break;
                }

                valor_deposito = coletar_info_deposito("\nInforme o valor do deposito: ");

                verifica_sucesso = realizar_deposito(
                    vetor_de_contas, idx_conta, valor_deposito
                );

                switch (verifica_sucesso) {

                    case ERR_VALOR_INVALIDO: {
                        printf("Erro: Informe um valor maior que 0!\n");
                        break;
                    }

                    case ERR_CONTA_INEXISTENTE: {
                        printf("Erro: A conta informada esta desativada!\n");
                        break;
                    }

                    case OK: {
                        printf("\nSucesso no deposito! Saldo atual: R$ %.2lf\n",
                               vetor_de_contas[idx_conta].saldo);
                        break;
                    }

                    default:
                        printf("\nErro inesperado: código %d\n", verifica_sucesso);
                        break;
                }

                break;
            }

            case 3:
                printf("Voce escolheu sacar seu saldo.");
                // chamada aqui
                break;

            case 4:
                break;

            case 5:
                break;

            case 6: {
                char TELEFONE_TEMP[TAM_TELEFONE], AGENCIA_TEMP[TAM_AGENCIA];
                int sucesso_atualizacao, numero_conta, idx_conta;

                limpa_tela();

                printf("\n --- Atualizar telefone e agencia --- \n");

                numero_conta = coletar_numero_conta(); // coleta os dados

                idx_conta = encontrar_conta_por_numero(
                    vetor_de_contas, numero_conta, quantidade_atual
                );

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    printf("\nErro: A conta nao existe!");
                    break;
                }

                sucesso_atualizacao = valida_conta_ativa(vetor_de_contas, idx_conta);

                if (sucesso_atualizacao == ERR_CONTA_INATIVA) {
                    printf("\nErro: A conta esta desativada!");
                    break;
                }

                coletar_novos_dados_tel_agencia(TELEFONE_TEMP, AGENCIA_TEMP);

                atualizar_dados_tel_agencia(
                    vetor_de_contas, TELEFONE_TEMP, AGENCIA_TEMP, idx_conta
                );

                break;
            }

            case 7: {
                int filtro, sucesso_scanf, valida_listar;

                limpa_tela();

                printf("\n--- Listar Contas ---\n");
                printf("Qual filtro deseja aplicar?\n");
                printf(" (1) Somente Encerradas\n");
                printf(" (2) Somente Ativas\n");
                printf(" (3) Todas as Contas\n");
                printf("Escolha: ");

                sucesso_scanf = scanf("%d", &filtro);

                if (sucesso_scanf != 1) {
                    limpa_tela();
                    printf("\nErro: Entrada invalida! Por favor informe somente numeros.\n");
                    limpa_buffer();
                    continue;
                }

                limpa_buffer();

                if (filtro < 1 || filtro > 3) {
                    printf("Erro: Opcao de filtro invalida!\n");
                }
                else {
                    valida_listar = listar_contas(
                        vetor_de_contas, quantidade_atual, filtro
                    );

                    if (valida_listar == ERR_CONTA_INEXISTENTE) {
                        printf("Erro: Nenhuma conta cadastrada no sistema.\n");
                        break;
                    }

                    if (valida_listar == ERR_NENHUMA_CONTA) {
                        printf("Erro: Nenhuma conta encontrada para este filtro.\n");
                        break;
                    }
                }

                break;
            }

            case 8: {
                int num_conta, idx_conta, verifica_sucesso;

                limpa_tela();

                printf("\n--- Encerrar conta ---\n");

                num_conta = coletar_numero_conta();

                idx_conta = encontrar_conta_por_numero(
                    vetor_de_contas, num_conta, quantidade_atual
                );

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    printf("\nErro: A conta nao existe!\n");
                    break;
                }

                verifica_sucesso = encerrar_conta(
                    vetor_de_contas, idx_conta, quantidade_atual
                );

                switch (verifica_sucesso) {

                    case ERR_CONTA_INEXISTENTE:
                        printf("\nErro: A conta nao existe!\n");
                        break;

                    case ERR_CONTA_INATIVA:
                        printf("\nErro: A conta ja esta desativada!\n");
                        break;

                    case ERR_SALDO_NAO_ZERO:
                        printf("\nErro: Por favor, faca transferencia do saldo da sua conta antes de encerra-la!");
                        printf("\nO saldo da conta deve ser zero antes dela ser encerrada.\n");
                        break;

                    case OK:
                        printf("\nConta encerrada com sucesso!");
                        break;

                    default:
                        printf("\nErro inesperado: código %d\n", verifica_sucesso);
                        break;
                }

                break;
            }

            case 9: {
                printf("\nEncerrando o programa...\n");
                return OK;
            }

            default:
                printf("\nErro: Opcao invalida!");
                break;
        }

    } while (opcao != 9);

    return OK;
}
