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
            printf("\nEntrada invalida! Por favor informe somente numeros.\n");
            limpa_buffer();
            opcao = 0;
            continue;
        }

        limpa_buffer(); // limpar o buffer para o \n nao ir para o proximo fgets

        if (opcao < 1 || opcao > 9) { // se nao for uma das opcoes pede ao usuario para tentar novamente
            limpa_tela();
            printf("\nOpcao invalida! Digite uma opcao valida por favor.\n");
            continue; // reinicia o loop
        }

        switch (opcao) { /* chamar as funções conforme a escolha */

            // CHAVE ADICIONADA AQUI
            case 1: {
                if (quantidade_atual >= MAX_CONTAS) {
                    limpa_tela();
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

                if (resultado_da_conta == 0) {
                    printf("Conta criada com sucesso!\n");
                    num_proxima_conta++;
                }

                break;
            } // CHAVE ADICIONADA AQUI

                // CHAVE ADICIONADA AQUI
            case 2: {
                int num_conta, indice, sucesso_deposito;
                double valor_deposito;

                coletar_info_deposito(&num_conta, &valor_deposito);

                indice = encontrar_conta_por_numero(vetor_de_contas, &num_conta, quantidade_atual);

                if (indice == -1) {
                    printf("\nErro: Conta inexistente!");
                    break;
                }

                sucesso_deposito = realizar_deposito(vetor_de_contas, indice, valor_deposito);
                if (sucesso_deposito == -1) {
                    break;
                } else {
                    printf("\nSucesso no deposito!");
                }
                break;
            } // CHAVE ADICIONADA AQUI

            case 3:
                printf("Voce escolheu sacar seu saldo.");
                // chamada aqui

                break;

            case 6:
                char TELEFONE_TEMP[TAM_TELEFONE], AGENCIA_TEMP[TAM_AGENCIA];
                int sucesso_atualizacao, numero_conta;

                numero_conta = coletar_numero_conta(vetor_de_contas); //coleta os dados

                sucesso_atualizacao = encontrar_conta_por_numero(vetor_de_contas, &numero_conta, quantidade_atual); //ve se a conta existe

                if (sucesso_atualizacao == -1) {
                    printf("\nErro: A conta nao existe!");
                    break;
                }

                sucesso_atualizacao = valida_conta_ativa(vetor_de_contas, numero_conta); //ve se a conta esta ativa

                if (sucesso_atualizacao == -1) {
                    printf("\nErro: A conta esta desativada!");
                    break;
                }

                coletar_novos_dados_tel_agencia(TELEFONE_TEMP, AGENCIA_TEMP); //pega os dados novos

                atualizar_dados_tel_agencia(vetor_de_contas, TELEFONE_TEMP, AGENCIA_TEMP, numero_conta); //atualiza os dados de fato

                break;

            default:
                printf("\nErro: Opcao invalida!");
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7: { // Listar contas
                    int filtro;
                    printf("\n--- Listar Contas ---\n");
                    printf("Qual filtro deseja aplicar?\n");
                    printf(" (1) Somente Encerradas\n");
                    printf(" (2) Somente Ativas\n");
                    printf(" (3) Todas as Contas\n");
                    printf("Escolha: ");
                    scanf("%d", &filtro);

                    limpa_buffer();

                    // Verifica se o filtro é válido ANTES de chamar a função
                    if (filtro < 1 || filtro > 3) {
                        printf("Erro: Opcao de filtro invalida!\n");
                    } else {
                        // Se o filtro for válido, chama a função
                        listar_contas(vetor_de_contas, quantidade_atual, filtro);
                    }

                    break;
                }

        }

    } while (opcao != 9);

    return 0;

}