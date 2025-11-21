#include <stdio.h>
#include "banco.h"

int main() {
    Conta vetor_de_contas[MAX_CONTAS];
    int quantidade_atual = 0; // numero de contas criadas
    int num_proxima_conta = 1; // vai ser incrementado depois apos a criação de uma nova conta
    int opcao, sucesso_leitura, resultado_da_conta;
    int ler_int(const char *mensagem);
    double ler_double(const char *mensagem);

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

        switch (opcao) { /* chamar as funções conforme a escolha */


            case 1: {
                if (quantidade_atual >= MAX_CONTAS) {
                    printf("\nErro: Limite de contas atingido!\n");
                    break; // volta para o menu
                }

                char nome_temp[TAM_NOME];
                char cpf_temp[TAM_CPF];
                char agencia_temp[TAM_AGENCIA];
                char telefone_temp[TAM_TELEFONE];

                coletar_dados_abertura_conta(nome_temp, cpf_temp, agencia_temp, telefone_temp); // preenche os dados

                resultado_da_conta = abrir_conta(vetor_de_contas, &quantidade_atual, num_proxima_conta, nome_temp,
                                                 cpf_temp, agencia_temp,
                                                 telefone_temp); //verifica se o CPF ja existe em outra conta

                if (resultado_da_conta == OK) {
                    printf("\nConta criada com sucesso!\n");
                    num_proxima_conta++;
                }
                else { //erro se o cpf da conta for duplicado
                    printf("\nErro: O CPF cadastrado já existe em uma conta ativa.");
                }

                break;
            }


            case 2: {
                int indice, num_conta, verifica_sucesso;
                double valor_deposito;

                num_conta = coletar_numero_conta();

                /* a funcao encontrar_conta_por_numero pega o numero da conta,
                verifica se a conta e valida, e se for retorna O INDICE DA CONTA*/
                indice = encontrar_conta_por_numero(vetor_de_contas, num_conta, quantidade_atual);

                if (indice == ERR_CONTA_INEXISTENTE) {
                    printf("Erro: A conta nao existe!");
                    break;
                }

                valor_deposito = coletar_info_deposito("\nInforme o valor do deposito: ");

                verifica_sucesso = realizar_deposito(vetor_de_contas, indice, valor_deposito);

                if (verifica_sucesso == ERR_VALOR_INVALIDO) {
                    printf("Erro: Informe um valor maior que 0!\n");
                    break;
                }
                if (verifica_sucesso == ERR_CONTA_INATIVA) {
                    printf("Erro: A conta informada esta desativada!\n");
                    break;
                }
                else {
                    printf("\nSucesso no deposito!");
                    break;
                }

                break;
            }

            case 3:
                printf("Voce escolheu sacar seu saldo.");
                // chamada aqui

                break;


            case 4: { // Transferir
                int num_origem = ler_int("Informe o numero da conta de origem: ");
                int num_destino = ler_int("Informe o numero da conta de destino: ");
                double valor_transferencia = ler_double("Informe o valor da transferencia: ");

                int resultado = realizar_transferencia(
                        vetor_de_contas,
                        quantidade_atual,
                        num_origem,
                        num_destino,
                        valor_transferencia
                );

                if (resultado == OK) {
                    printf("\nTransferencia concluida com sucesso!\n");
                } else {
                    printf("\nErro na transferencia! Verifique os dados e tente novamente.\n");
                }

                break;
            }

                case 5:
                break;

                case 6:
                char TELEFONE_TEMP[TAM_TELEFONE], AGENCIA_TEMP[TAM_AGENCIA];
                int sucesso_atualizacao, numero_conta, idx_conta;

                numero_conta = coletar_numero_conta(); //coleta os dados

                idx_conta = encontrar_conta_por_numero(vetor_de_contas, numero_conta, quantidade_atual); //ve se a conta existe

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    printf("\nErro: A conta nao existe!");
                    break;
                }

                sucesso_atualizacao = valida_conta_ativa(vetor_de_contas, idx_conta); //ve se a conta esta ativa

                if (sucesso_atualizacao == ERR_CONTA_INATIVA) {
                    printf("\nErro: A conta esta desativada!");
                    break;
                }

                coletar_novos_dados_tel_agencia(TELEFONE_TEMP, AGENCIA_TEMP); //pega os dados novos

                atualizar_dados_tel_agencia(vetor_de_contas, TELEFONE_TEMP,
                    AGENCIA_TEMP, idx_conta); //atualiza os dados de fato

                break;

                case 7: { // Listar contas
                    int filtro, sucesso_scanf, valida_listar;
                    printf("\n--- Listar Contas ---\n");
                    printf("Qual filtro deseja aplicar?\n");
                    printf(" (1) Somente Encerradas\n");
                    printf(" (2) Somente Ativas\n");
                    printf(" (3) Todas as Contas\n");
                    printf("Escolha: ");
                    sucesso_scanf = scanf("%d", &filtro);

                    if (sucesso_scanf != 1) { // se for uma letra, ele ficou preso na fila, temos que limpa-lo
                        limpa_tela();
                        printf("\nErro: Entrada invalida! Por favor informe somente numeros.\n");
                        limpa_buffer();
                        continue;
                    }

                    limpa_buffer(); //tira /n para proximo fgets

                    // Verifica se o filtro é válido ANTES de chamar a função
                    if (filtro < 1 || filtro > 3) {
                        printf("Erro: Opcao de filtro invalida!\n");
                    }
                    else {
                        // Se o filtro for válido, chama a função
                        valida_listar = listar_contas(vetor_de_contas, quantidade_atual, filtro);

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

                default:
                printf("\nErro: Opcao invalida!");
                break;

            }

        } while (opcao != 9);

        return OK;

    }