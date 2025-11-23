#include <stdio.h>
#include <stdarg.h>
#include "banco.h"
#include <string.h>

#define UI_WIDTH 40

/* limpador simples */
void limpa_tela() {
    for (int i = 0; i < 30; ++i) putchar('\n');
}

/* linha separadora */
void ui_linha() {
    for (int i = 0; i < UI_WIDTH; ++i) putchar('=');
    putchar('\n');
}

/* título grande */
void ui_titulo(const char *titulo) {
    putchar('\n');
    ui_linha();
    /* centraliza de forma simples */
    int len = (int)strlen(titulo);
    int pad = (UI_WIDTH - len) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; ++i) putchar(' ');
    printf("%s\n", titulo);
    ui_linha();
}

/* subtítulo */
void ui_subtitulo(const char *texto) {
    putchar('\n');
    int len = (int)strlen(texto);
    int pad = (UI_WIDTH - len) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; ++i) putchar(' ');
    printf("%s\n", texto);
    for (int i = 0; i < UI_WIDTH; ++i) putchar('-');
    putchar('\n');
}

/* bloco de início (uso genérico) */
void ui_bloco_inicio() {
    putchar('\n');
    ui_linha();
}

/* bloco de fim (uso genérico) */
void ui_bloco_fim() {
    ui_linha();
    putchar('\n');
}

/* mensagem de sucesso: prefixo e quebra de linha */
void ui_msg_ok(const char *msg) {
    printf("[ OK ] %s\n", msg);
}

/* versão com formato (recomendado para quando precisa inserir números) */
void ui_msg_okf(const char *fmt, ...) {
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    ui_msg_ok(buf);
}

/* mensagem de erro */
void ui_msg_erro(const char *msg) {
    printf("[ ERRO ] %s\n", msg);
}

/* versão formatada de erro */
void ui_msg_errof(const char *fmt, ...) {
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    ui_msg_erro(buf);
}
