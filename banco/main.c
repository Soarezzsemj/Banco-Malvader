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
            ui_msg_erro("Entrada invalida! Por favor informe somente numeros.");
            limpa_buffer();
            opcao = 0;
            continue;
        }

        limpa_buffer(); // limpar o buffer para o \n nao ir para o proximo fgets

        if (opcao < 1 || opcao > 9) { // se nao for uma das opcoes pede ao usuario para tentar novamente
            limpa_tela();
            ui_msg_erro("Opcao invalida! Digite uma opcao valida por favor.");
            continue; // reinicia o loop
        }

        switch (opcao) {
            /* =============================================================
             *                       1. ABRIR CONTA
             * ============================================================= */
            case 1: {
                limpa_tela();

                if (quantidade_atual >= MAX_CONTAS) {
                    ui_msg_erro("Limite de contas atingido!");
                    break; // volta para o menu
                }

                char nome_temp[TAM_NOME];
                char cpf_temp[TAM_CPF];
                char agencia_temp[TAM_AGENCIA];
                char telefone_temp[TAM_TELEFONE];

                ui_titulo("ABERTURA DE CONTA");

                coletar_dados_abertura_conta(nome_temp, cpf_temp, agencia_temp, telefone_temp); // preenche os dados

                resultado_da_conta = abrir_conta(
                    vetor_de_contas, &quantidade_atual, num_proxima_conta,
                    nome_temp, cpf_temp, agencia_temp, telefone_temp
                ); //verifica se o CPF ja existe em outra conta

                if (resultado_da_conta == OK) {
                    char msg[80];
                    sprintf(msg, "Conta criada com sucesso! Numero da conta: %d", num_proxima_conta);
                    ui_msg_ok(msg);
                    num_proxima_conta++;
                }
                else { //erro se o cpf da conta for duplicado
                    ui_msg_erro("O CPF cadastrado ja existe em uma conta ativa.");
                }

                break;
            }

            /* =============================================================
             *                         2. DEPOSITO
             * ============================================================= */
            case 2: {
                limpa_tela();
                ui_titulo("FAZER DEPOSITO");

                int num_conta = coletar_numero_conta();

                int idx_conta = encontrar_conta_por_numero(
                    vetor_de_contas, num_conta, quantidade_atual
                ); // pega O INDICE DA CONTA

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("A conta nao existe!");
                    break;
                }

                double valor_deposito = coletar_info_deposito("Informe o valor do deposito: ");

                int verifica_sucesso = realizar_deposito(
                    vetor_de_contas, idx_conta, valor_deposito
                );

                switch (verifica_sucesso) {

                    case ERR_VALOR_INVALIDO: {
                        ui_msg_erro("Informe um valor maior que 0!");
                        break;
                    }

                    case ERR_CONTA_INATIVA: {
                        ui_msg_erro("A conta informada esta desativada!");
                        break;
                    }

                    case OK: {
                        char msg[80];
                        sprintf(msg, "Sucesso no deposito! Saldo atual: R$ %.2lf",
                                vetor_de_contas[idx_conta].saldo);
                        ui_msg_ok(msg);
                        break;
                    }

                    default:
                        ui_msg_erro("Erro inesperado no deposito.");
                        break;
                }

                break;
            }

            /* =============================================================
             *                           3. SAQUE
             * ============================================================= */
            case 3: {
                limpa_tela();
                ui_titulo("SAQUE");

                int num_conta_saque, indice_saque;
                double valor_saque;

                coletar_info_saque(&num_conta_saque, &valor_saque);

                // Verifica se o número da conta é válido
                if (num_conta_saque <= 0) {
                    ui_msg_erro("Numero da conta invalido!");
                    break;
                }

                indice_saque = encontrar_conta_por_numero(vetor_de_contas,
                                                          num_conta_saque,
                                                          quantidade_atual);

                if (indice_saque == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("Conta inexistente!");
                    break;
                }

                int resultado = realizar_saque(vetor_de_contas, indice_saque, valor_saque);

                switch (resultado) {

                    case OK:
                        ui_msg_ok("Saque realizado com sucesso!");
                        break;

                    case ERR_SALDO_INSUFICIENTE:
                        ui_msg_erro("Saldo insuficiente para saque!");
                        break;

                    case ERR_CONTA_INATIVA:
                        ui_msg_erro("A conta esta encerrada!");
                        break;

                    case ERR_VALOR_INVALIDO:
                        ui_msg_erro("Valor do saque invalido!");
                        break;

                    default:
                        ui_msg_erro("Erro desconhecido ao realizar saque.");
                        break;
                }

                break;
            }

            /* =============================================================
             *                       4. TRANSFERENCIA
             * ============================================================= */
            case 4: {
                limpa_tela();
                ui_titulo("TRANSFERENCIA");

                printf("Numero da conta de origem:\n");
                int num_origem = coletar_numero_conta();
                printf("Numero da conta de destino:\n");
                int num_destino = coletar_numero_conta();
                double valor_transferencia = coletar_info_deposito("Informe o valor da transferencia: ");

                int resultado = realizar_transferencia(
                    vetor_de_contas,
                    quantidade_atual,
                    num_origem,
                    num_destino,
                    valor_transferencia
                );

                switch (resultado) {
                    case OK:
                        ui_msg_ok("Transferencia concluida com sucesso!");
                        break;

                    case ERR_VALOR_INVALIDO:
                        ui_msg_erro("Valor invalido! Deve ser maior que zero e menor que o limite.");
                        break;

                    case ERR_CONTA_INEXISTENTE:
                        ui_msg_erro("Conta inexistente! Verifique os numeros das contas.");
                        break;

                    case ERR_CONTA_INATIVA:
                        ui_msg_erro("Conta inativa! A operacao nao pode ser realizada.");
                        break;

                    case ERR_SALDO_INSUFICIENTE:
                        ui_msg_erro("Saldo insuficiente na conta de origem!");
                        break;

                    default:
                        ui_msg_erro("Erro desconhecido na transferencia.");
                        break;
                }

                break;
            }

            /* =============================================================
             *                    5. CONSULTAR CONTA
             * ============================================================= */
            case 5: {
                limpa_tela();
                ui_titulo("CONSULTAR CONTA");

                int tipo, numero, r, indice;
                char cpf[TAM_CPF];

                printf("(1) Consultar por numero da conta\n");
                printf("(2) Consultar por CPF\n");
                printf("Escolha: ");

                if (scanf("%d", &tipo) != 1) {
                    limpa_buffer();
                    ui_msg_erro("Entrada invalida.");
                    break;
                }
                limpa_buffer();

                if (tipo == 1) {
                    numero = coletar_numero_conta();
                    r = consultar_por_numero(vetor_de_contas, quantidade_atual, numero, &indice);
                }
                else if (tipo == 2) {
                    r = coletar_cpf(cpf);
                    if (r != OK) {
                        ui_msg_erro("CPF invalido.");
                        break;
                    }
                    r = consultar_por_cpf(vetor_de_contas, quantidade_atual, cpf, &indice);
                }
                else {
                    ui_msg_erro("Opcao invalida.");
                    break;
                }

                switch (r) {
                    case OK:
                        mostrar_dados(&vetor_de_contas[indice]);
                        break;

                    case ERR_NENHUMA_CONTA:
                        ui_msg_erro("Nenhuma conta cadastrada.");
                        break;

                    case ERR_CONTA_INEXISTENTE:
                        ui_msg_erro("Conta nao encontrada.");
                        break;

                    case ERR_CONTA_INATIVA:
                        ui_msg_erro("Conta existe, mas esta inativa.");
                        break;

                    case ERR_INVALIDO:
                        ui_msg_erro("Entrada invalida.");
                        break;
                }

                break;
            }

            /* =============================================================
             *        6. ATUALIZAR TELEFONE / AGENCIA
             * ============================================================= */
            case 6: {
                limpa_tela();
                ui_titulo("ATUALIZAR TELEFONE / AGENCIA");

                char TELEFONE_TEMP[TAM_TELEFONE], AGENCIA_TEMP[TAM_AGENCIA];
                int sucesso_atualizacao, numero_conta, idx_conta;

                printf("\n --- Atualizar telefone e agencia --- \n");

                numero_conta = coletar_numero_conta(); // coleta os dados

                idx_conta = encontrar_conta_por_numero(
                    vetor_de_contas, numero_conta, quantidade_atual
                );

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("A conta nao existe!");
                    break;
                }

                sucesso_atualizacao = valida_conta_ativa(vetor_de_contas, idx_conta);

                if (sucesso_atualizacao == ERR_CONTA_INATIVA) {
                    ui_msg_erro("A conta esta desativada!");
                    break;
                }

                coletar_novos_dados_tel_agencia(TELEFONE_TEMP, AGENCIA_TEMP);

                atualizar_dados_tel_agencia(
                    vetor_de_contas, TELEFONE_TEMP, AGENCIA_TEMP, idx_conta
                );

                ui_msg_ok("Dados atualizados com sucesso!");
                break;
            }

            /* =============================================================
             *                       7. LISTAR CONTAS
             * ============================================================= */
            case 7: {
                limpa_tela();
                ui_titulo("LISTAR CONTAS");

                int filtro, sucesso_scanf, valida_listar;

                printf("\n--- Listar Contas ---\n");
                printf("Qual filtro deseja aplicar?\n");
                printf(" (1) Somente Encerradas\n");
                printf(" (2) Somente Ativas\n");
                printf(" (3) Todas as Contas\n");
                printf("Escolha: ");

                sucesso_scanf = scanf("%d", &filtro);

                if (sucesso_scanf != 1) {
                    limpa_tela();
                    ui_msg_erro("Entrada invalida! Por favor informe somente numeros.");
                    limpa_buffer();
                    continue;
                }

                limpa_buffer();

                if (filtro < 1 || filtro > 3) {
                    ui_msg_erro("Opcao de filtro invalida!");
                }
                else {
                    valida_listar = listar_contas(
                        vetor_de_contas, quantidade_atual, filtro
                    );

                    if (valida_listar == ERR_CONTA_INEXISTENTE) {
                        ui_msg_erro("Nenhuma conta cadastrada no sistema.");
                        break;
                    }

                    if (valida_listar == ERR_NENHUMA_CONTA) {
                        ui_msg_erro("Nenhuma conta encontrada para este filtro.");
                        break;
                    }
                }

                break;
            }

            /* =============================================================
             *                        8. ENCERRAR CONTA
             * ============================================================= */
            case 8: {
                limpa_tela();
                ui_titulo("ENCERRAR CONTA");

                int num_conta, idx_conta, verifica_sucesso;

                printf("\n--- Encerrar conta ---\n");

                num_conta = coletar_numero_conta();

                idx_conta = encontrar_conta_por_numero(
                    vetor_de_contas, num_conta, quantidade_atual
                );

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("A conta nao existe!");
                    break;
                }

                verifica_sucesso = encerrar_conta(
                    vetor_de_contas, idx_conta, quantidade_atual
                );

                switch (verifica_sucesso) {

                    case ERR_CONTA_INEXISTENTE:
                        ui_msg_erro("A conta nao existe!");
                        break;

                    case ERR_CONTA_INATIVA:
                        ui_msg_erro("A conta ja esta desativada!");
                        break;

                    case ERR_SALDO_NAO_ZERO:
                        ui_msg_erro("O saldo deve ser zero antes de encerrar a conta!");
                        break;

                    case OK:
                        ui_msg_ok("Conta encerrada com sucesso!");
                        break;

                    default:
                        ui_msg_erro("Erro inesperado ao encerrar conta.");
                        break;
                }

                break;
            }

            /* =============================================================
             *                        9. SAIR
             * ============================================================= */
            case 9: {
                limpa_tela();
                ui_msg_ok("Encerrando o programa...");
                return OK;
            }

            default:
                ui_msg_erro("Opcao invalida!");
                break;
        }

        /* Pequena pausa antes de mostrar o menu novamente */
        printf("\nPressione ENTER para voltar ao menu...");
        getchar();

    } while (opcao != 9);

    return OK;
}
