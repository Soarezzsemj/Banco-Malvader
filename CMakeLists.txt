# Versão mínima do CMake
cmake_minimum_required(VERSION 3.20)

# Nome do projeto (e diz que é em C)
project(BancoMalvader C)

# Diga ao CMake onde encontrar os arquivos .h (o "banco.h")
include_directories(banco)

# O COMANDO MAIS IMPORTANTE:
# Cria um executável chamado "banco" juntando todos os seus arquivos .c
add_executable(banco
    banco/main.c
        banco/abrir_conta.c
    banco/utils.c
        banco/deposito.c
        banco/funcao-transferir.c
        banco/listar_contas.c
        banco/mostrar_dados.c
        banco/atualizar-telefone-agencia.c
)