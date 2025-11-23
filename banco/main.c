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

        if (sucesso_leitura != 1) { // se for uma letra
            limpa_tela();
            ui_msg_erro("Entrada invalida! Por favor informe somente numeros.");
            limpa_buffer();
            opcao = 0;
            continue;
        }

        limpa_buffer(); // limpar o buffer para o \n nao ir para o proximo fgets

        if (opcao < 1 || opcao > 9) { // opção inválida
            limpa_tela();
            ui_msg_erro("Opcao invalida! Digite uma opcao valida por favor.");
            continue;
        }

        switch (opcao) {

            /* =============================================================
             *                       1. ABRIR CONTA
             * ============================================================= */
            case 1: {
                limpa_tela();

                if (quantidade_atual >= MAX_CONTAS) {
                    ui_msg_erro("Limite de contas atingido!");
                    break;
                }

                char nome_temp[TAM_NOME], cpf_temp[TAM_CPF],
                     agencia_temp[TAM_AGENCIA], telefone_temp[TAM_TELEFONE];

                ui_titulo("ABERTURA DE CONTA");

                coletar_dados_abertura_conta(nome_temp, cpf_temp, agencia_temp, telefone_temp);

                resultado_da_conta = abrir_conta(
                    vetor_de_contas, &quantidade_atual, num_proxima_conta,
                    nome_temp, cpf_temp, agencia_temp, telefone_temp
                );

                if (resultado_da_conta == OK) {
                    char msg[80];
                    sprintf(msg, "Conta criada com sucesso! Numero da conta: %d", num_proxima_conta);
                    ui_msg_ok(msg);
                    num_proxima_conta++;
                } else {
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
                );

                if (idx_conta == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("A conta nao existe!");
                    break;
                }

                double valor_deposito = coletar_info_deposito("Informe o valor do deposito: ");
                int r = realizar_deposito(vetor_de_contas, idx_conta, valor_deposito);

                switch (r) {
                    case ERR_VALOR_INVALIDO:
                        ui_msg_erro("Informe um valor maior que 0!");
                        break;

                    case ERR_CONTA_INATIVA:
                        ui_msg_erro("A conta informada esta desativada!");
                        break;

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

                indice_saque = encontrar_conta_por_numero(
                    vetor_de_contas, num_conta_saque, quantidade_atual
                );

                if (indice_saque == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("Conta inexistente!");
                    break;
                }

                int r = realizar_saque(vetor_de_contas, indice_saque, valor_saque);

                switch (r) {
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
                        ui_msg_erro("Valor de saque invalido!");
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
                double valor = coletar_info_deposito("Informe o valor da transferencia: ");

                int r = realizar_transferencia(
                    vetor_de_contas, quantidade_atual,
                    num_origem, num_destino, valor
                );

                switch (r) {
                    case OK:
                        ui_msg_ok("Transferencia concluida com sucesso!");
                        break;

                    case ERR_VALOR_INVALIDO:
                        ui_msg_erro("Valor invalido! Deve ser maior que zero.");
                        break;

                    case ERR_CONTA_INEXISTENTE:
                        ui_msg_erro("Conta inexistente!");
                        break;

                    case ERR_CONTA_INATIVA:
                        ui_msg_erro("Conta inativa!");
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

                int modo, indice = ERR_INVALIDO;
                char cpf[TAM_CPF];
                int numero, r;

                printf("(1) Consultar por numero da conta\n");
                printf("(2) Consultar por CPF\n");
                printf("Escolha: ");

                if (scanf("%d", &modo) != 1) {
                    limpa_buffer();
                    ui_msg_erro("Entrada invalida.");
                    break;
                }
                limpa_buffer();

                if (modo == 1) {
                    numero = coletar_numero_conta();
                    r = consultar_por_numero(vetor_de_contas, quantidade_atual, numero, &indice);
                }
                else if (modo == 2) {
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

                    default:
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

                char telefone_temp[TAM_TELEFONE], agencia_temp[TAM_AGENCIA];
                int numero_conta = coletar_numero_conta();
                int idx = encontrar_conta_por_numero(vetor_de_contas, numero_conta, quantidade_atual);

                if (idx == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("A conta nao existe!");
                    break;
                }

                int r = valida_conta_ativa(vetor_de_contas, idx);
                if (r == ERR_CONTA_INATIVA) {
                    ui_msg_erro("A conta esta desativada!");
                    break;
                }

                coletar_novos_dados_tel_agencia(telefone_temp, agencia_temp);
                atualizar_dados_tel_agencia(vetor_de_contas, telefone_temp, agencia_temp, idx);

                ui_msg_ok("Dados atualizados com sucesso!");
                break;
            }

            /* =============================================================
             *                       7. LISTAR CONTAS
             * ============================================================= */
            case 7: {
                limpa_tela();
                ui_titulo("LISTAR CONTAS");

                int filtro;
                printf(" (1) Somente Encerradas\n");
                printf(" (2) Somente Ativas\n");
                printf(" (3) Todas as Contas\n");
                printf("Escolha: ");

                if (scanf("%d", &filtro) != 1) {
                    limpa_buffer();
                    ui_msg_erro("Entrada invalida!");
                    continue;
                }
                limpa_buffer();

                if (filtro < 1 || filtro > 3) {
                    ui_msg_erro("Opcao de filtro invalida!");
                    break;
                }

                int r = listar_contas(vetor_de_contas, quantidade_atual, filtro);

                if (r == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("Nenhuma conta cadastrada no sistema.");
                } else if (r == ERR_NENHUMA_CONTA) {
                    ui_msg_erro("Nenhuma conta encontrada para este filtro.");
                }

                break;
            }

            /* =============================================================
             *                        8. ENCERRAR CONTA
             * ============================================================= */
            case 8: {
                limpa_tela();
                ui_titulo("ENCERRAR CONTA");

                int num_conta = coletar_numero_conta();
                int idx = encontrar_conta_por_numero(vetor_de_contas, num_conta, quantidade_atual);

                if (idx == ERR_CONTA_INEXISTENTE) {
                    ui_msg_erro("A conta nao existe!");
                    break;
                }

                int r = encerrar_conta(vetor_de_contas, idx, quantidade_atual);

                switch (r) {
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
        }

        /* Pequena pausa antes de mostrar o menu novamente */
        printf("\nPressione ENTER para voltar ao menu...");
        getchar();

    } while (opcao != 9);

    return OK;
}
