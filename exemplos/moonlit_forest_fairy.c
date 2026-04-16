/*
 * moonlit_forest_fairy.c
 * "Moonlit Forest Fairy" — estilo Touhou / ZUN (TH07-TH10 era)
 *
 * Tema de área de floresta: levemente etéreo, com melodia em modo
 * mixolídio e acompanhamento de arpejo rápido. Inspirado nas faixas
 * de bosque e natureza da série (Perfect Cherry Blossom, Imperishable Night).
 *
 * Compilar:  gcc moonlit_forest_fairy.c -o moonlit_forest_fairy -lm
 * Executar:  ./moonlit_forest_fairy
 * Saída:     moonlit_forest_fairy.wav
 */

#include "partitura.h"

int main(void) {
    /* 4 canais: flauta | arpejo rápido | baixo | percussão sutil */
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.80f;

    /* Canal 0: flauta — onda triangular com vibrato */
    pt_definir_envelope(&ctx, 0, 0.015f, 0.0f, 0.88f, 0.12f);
    pt_definir_vibrato(&ctx, 0, 0.35f, 5.8f);
    pt_definir_pan(&ctx, 0, -0.15f);

    /* Canal 1: arpejo rápido — pulso 25% (koto / harpa) */
    pt_definir_envelope(&ctx, 1, 0.001f, 0.18f, 0.0f, 0.05f);
    pt_definir_largura_pulso(&ctx, 1, 0.25f);
    pt_definir_pan(&ctx, 1, 0.3f);

    /* Canal 2: baixo pizzicato — dente de serra curto */
    pt_definir_envelope(&ctx, 2, 0.001f, 0.22f, 0.0f, 0.04f);
    pt_definir_pan(&ctx, 2, 0.0f);

    /* Canal 3: percussão etérea — hi-hat + splash suaves */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.035f, 0.0f, 0.01f);
    pt_definir_pan(&ctx, 3, 0.0f);

    /* --- Padrão A: prelúdio — lua nascendo (Lá mixolídio, 152 BPM) */
    PT_Padrao preludio;
    pt_iniciar_padrao(&preludio, 152);

    /* Flauta — frase suave e ondulante */
    PT_NOTA_F(preludio, 0, PT_LA4,  PT_MINIMA,   10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_SI4,  PT_COLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_DO5,  PT_COLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_RE5,  PT_MINIMA,   10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_MI5,  PT_COLCHEIA, 10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_RE5,  PT_COLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_DO5,  PT_COLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_SI4,  PT_COLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(preludio, 0, PT_LA4,  PT_SEMIBREVE,10, PT_ONDA_TRIANGULAR);

    /* Arpejo — acorde de Lá maior em colcheias rápidas */
    float arp_A[] = { PT_LA3, PT_DO4, PT_MI4, PT_LA4,
                      PT_LA3, PT_DO4, PT_MI4, PT_SOL4 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(preludio, 1, arp_A[b], PT_COLCHEIA, 8, PT_ONDA_PULSO);

    /* Baixo pizzicato */
    PT_NOTA_F(preludio, 2, PT_LA2,  PT_MINIMA,   10, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(preludio, 2, PT_MI3,  PT_MINIMA,    9, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(preludio, 2, PT_RE3,  PT_MINIMA,    9, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(preludio, 2, PT_LA2,  PT_MINIMA,   10, PT_ONDA_DENTE_SERRA);

    /* Percussão leve */
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(preludio, 3, 7500.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
        PT_NOTA_F(preludio, 3, 7500.0f, PT_SEMICOLCHEIA, 3, PT_RUIDO_BRANCO);
    }

    /* --- Padrão B: tema da fada — ágil e brincalhão ------------- */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 168);

    /* Flauta viva — modo mixolídio (Lá com Sol natural) */
    PT_NOTA_F(tema, 0, PT_MI5,  PT_SEMICOLCHEIA, 11, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_SEMICOLCHEIA, 10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_COLCHEIA,     10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_SEMICOLCHEIA, 10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_SEMICOLCHEIA, 11, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_FAS5, PT_COLCHEIA,     11, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_SOL5, PT_COLCHEIA,     12, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_LA5,  PT_MINIMA,       12, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 11, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_FAS5, PT_SEMICOLCHEIA, 11, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,     11, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_COLCHEIA,     10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_COLCHEIA,     10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_SI4,  PT_COLCHEIA,      9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 0, PT_LA4,  PT_MINIMA,       11, PT_ONDA_TRIANGULAR);

    /* Arpejo koto rápido — padrão de 16 notas */
    float arp_B[] = {
        PT_LA3, PT_MI4, PT_LA4, PT_DO5,
        PT_RE3, PT_LA3, PT_RE4, PT_FAS4,
        PT_MI3, PT_SI3, PT_MI4, PT_SOL4,
        PT_LA3, PT_MI4, PT_LA4, PT_MI5
    };
    for (int b = 0; b < 16; b++)
        PT_NOTA_F(tema, 1, arp_B[b], PT_SEMICOLCHEIA, 8, PT_ONDA_PULSO);

    float baixo_B[] = { PT_LA2, PT_RE3, PT_MI3, PT_LA2,
                        PT_LA2, PT_SOL3, PT_MI3, PT_RE3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(tema, 2, baixo_B[b], PT_COLCHEIA, 11, PT_ONDA_DENTE_SERRA);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 3, 7500.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
        PT_NOTA_F(tema, 3, (b%2==1)?2200.0f:7500.0f,
                  PT_SEMICOLCHEIA, (b%2==1)?10:4, PT_RUIDO_BRANCO);
    }

    /* --- Padrão C: perseguição — modo mais tenso (Lá menor) ----- */
    PT_Padrao perseguicao;
    pt_iniciar_padrao(&perseguicao, 178);

    PT_NOTA_F(perseguicao, 0, PT_LA5, PT_COLCHEIA,   12, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_SOL5,PT_SEMICOLCHEIA,11, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_FA5, PT_SEMICOLCHEIA,11, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_SOL5,PT_COLCHEIA,   11, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_LA5, PT_COLCHEIA,   12, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_SI5, PT_COLCHEIA,   13, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_DO6, PT_MINIMA,     14, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_SI5, PT_COLCHEIA,   13, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_LA5, PT_COLCHEIA,   12, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_SOL5,PT_COLCHEIA,   11, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_FA5, PT_SEMICOLCHEIA,11, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_MI5, PT_SEMICOLCHEIA,11, PT_ONDA_QUADRADA);
    PT_NOTA_F(perseguicao, 0, PT_RE5, PT_MINIMA,     11, PT_ONDA_QUADRADA);

    float arp_C[] = {
        PT_LA3, PT_DO4, PT_MI4, PT_LA4,
        PT_FA3, PT_LA3, PT_DO4, PT_FA4,
        PT_SOL3,PT_SI3, PT_RE4, PT_SOL4,
        PT_LA3, PT_MI4, PT_LA4, PT_MI5
    };
    for (int b = 0; b < 16; b++)
        PT_NOTA_F(perseguicao, 1, arp_C[b], PT_SEMICOLCHEIA, 9, PT_ONDA_PULSO);

    float baixo_C[] = { PT_LA2, PT_LA2, PT_FA2, PT_FA2,
                        PT_SOL2,PT_SOL2,PT_MI3, PT_RE3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(perseguicao, 2, baixo_C[b], PT_COLCHEIA, 12, PT_ONDA_DENTE_SERRA);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(perseguicao, 3, 7500.0f, PT_SEMICOLCHEIA, 5, PT_RUIDO_BRANCO);
        PT_NOTA_F(perseguicao, 3, 2000.0f, PT_SEMICOLCHEIA, 12, PT_RUIDO_BRANCO);
    }

    /* --- Padrão D: encerramento — floresta se acalma ------------ */
    PT_Padrao encerramento;
    pt_iniciar_padrao(&encerramento, 130);

    PT_NOTA_F(encerramento, 0, PT_LA5, PT_MINIMA,   10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(encerramento, 0, PT_SOL5,PT_MINIMA,    9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(encerramento, 0, PT_FAS5,PT_SEMIBREVE,10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(encerramento, 0, PT_MI5, PT_MINIMA,    9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(encerramento, 0, PT_RE5, PT_MINIMA,    9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(encerramento, 0, PT_MI5, PT_SEMIBREVE,10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(encerramento, 0, PT_LA4, PT_SEMIBREVE,11, PT_ONDA_TRIANGULAR);

    float arp_D[] = { PT_LA3, PT_MI4, PT_LA4, PT_MI4,
                      PT_RE4, PT_LA3, PT_RE4, PT_LA3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(encerramento, 1, arp_D[b], PT_COLCHEIA, 6, PT_ONDA_PULSO);

    PT_NOTA_F(encerramento, 2, PT_LA2, PT_SEMIBREVE, 9, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(encerramento, 2, PT_RE3, PT_SEMIBREVE, 8, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(encerramento, 2, PT_LA2, PT_SEMIBREVE,10, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(encerramento, 2, PT_MI3, PT_SEMIBREVE, 9, PT_ONDA_DENTE_SERRA);

    for (int b = 0; b < 8; b++)
        PT_NOTA_F(encerramento, 3, 7500.0f, PT_COLCHEIA, 3, PT_RUIDO_BRANCO);

    /* --- Montagem ------------------------------------------------ */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &preludio,      1);
    pt_adicionar_padrao_musica(&musica, &tema,          2);
    pt_adicionar_padrao_musica(&musica, &perseguicao,   2);
    pt_adicionar_padrao_musica(&musica, &tema,          1);
    pt_adicionar_padrao_musica(&musica, &perseguicao,   1);
    pt_adicionar_padrao_musica(&musica, &encerramento,  1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "moonlit_forest_fairy.wav", 300.0f);

    printf("Moonlit Forest Fairy  —  %.2f s\n", (float)frames / 44100.0f);
    printf("Arquivo: moonlit_forest_fairy.wav\n");

    pt_destruir_contexto(&ctx);
    return 0;
}
