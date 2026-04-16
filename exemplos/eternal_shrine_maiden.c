/*
 * eternal_shrine_maiden.c
 * "Eternal Shrine Maiden" — estilo Touhou / ZUN
 *
 * Melodia rápida e enérgica em Ré menor, com harmonia em arpejo,
 * baixo pulsante e percussão leve. Referência sonora: PC-98 OPN/OPNA
 * (YM2608) como usado nos primeiros jogos Touhou (TH01-TH05).
 *
 * Compilar:  gcc eternal_shrine_maiden.c -o eternal_shrine_maiden -lm
 * Executar:  ./eternal_shrine_maiden
 * Saída:     eternal_shrine_maiden.wav
 */

#include "partitura.h"

int main(void) {
    /* 4 canais: melodia | contra-melodia | baixo | percussão */
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.82f;

    /* --- Timbre dos canais (OPNA-style) ------------------------ */
    /* Canal 0: melodia — onda quadrada agressiva */
    pt_definir_envelope(&ctx, 0, 0.003f, 0.04f, 0.75f, 0.06f);
    pt_definir_pan(&ctx, 0, -0.2f);

    /* Canal 1: contra-melodia / harmonia — triangular suave */
    pt_definir_envelope(&ctx, 1, 0.005f, 0.06f, 0.60f, 0.08f);
    pt_definir_pan(&ctx, 1,  0.2f);

    /* Canal 2: baixo — dente de serra com decaimento curto */
    pt_definir_envelope(&ctx, 2, 0.001f, 0.18f, 0.10f, 0.04f);
    pt_definir_pan(&ctx, 2,  0.0f);

    /* Canal 3: percussão — ruído LFSR (SNare/HH estilo PSG) */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.05f, 0.0f, 0.01f);
    pt_definir_pan(&ctx, 3,  0.0f);

    /* --- Padrão A: frase de abertura (Ré menor, 180 BPM) ------- */
    PT_Padrao intro;
    pt_iniciar_padrao(&intro, 180);

    /* Melodia — escala de Ré menor natural com cromatismos */
    PT_NOTA(intro, 0, PT_RE5,  PT_COLCHEIA,     13);
    PT_NOTA(intro, 0, PT_DO5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(intro, 0, PT_RE5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(intro, 0, PT_FA5,  PT_COLCHEIA,     13);
    PT_NOTA(intro, 0, PT_MI5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(intro, 0, PT_RE5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(intro, 0, PT_DO5,  PT_COLCHEIA,     12);
    PT_NOTA(intro, 0, PT_LA4,  PT_COLCHEIA,     12);
    PT_NOTA(intro, 0, PT_SI4,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(intro, 0, PT_DO5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(intro, 0, PT_RE5,  PT_MINIMA,       13);

    /* Contra-melodia — harmonia em terças */
    PT_NOTA_F(intro, 1, PT_LA4,  PT_COLCHEIA,     10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SOL4, PT_SEMICOLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_SEMICOLCHEIA, 10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_DO5,  PT_COLCHEIA,     10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SI4,  PT_SEMICOLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_SEMICOLCHEIA, 10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SOL4, PT_COLCHEIA,      9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_FA4,  PT_COLCHEIA,      9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SOL4, PT_SEMICOLCHEIA,  9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_SEMICOLCHEIA, 10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_MINIMA,       10, PT_ONDA_TRIANGULAR);

    /* Baixo — pedal de Ré com movimento cromático */
    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(intro, 2, PT_RE3,  PT_SEMICOLCHEIA, 12, PT_ONDA_DENTE_SERRA);
        PT_NOTA_F(intro, 2, PT_LA3,  PT_SEMICOLCHEIA, 11, PT_ONDA_DENTE_SERRA);
        PT_NOTA_F(intro, 2, PT_FA3,  PT_SEMICOLCHEIA, 11, PT_ONDA_DENTE_SERRA);
        PT_NOTA_F(intro, 2, PT_LA3,  PT_SEMICOLCHEIA, 11, PT_ONDA_DENTE_SERRA);
    }

    /* Percussão — padrão básico */
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(intro, 3, 6000.0f, PT_SEMICOLCHEIA,  6, PT_RUIDO_LFSR);
        PT_NOTA_F(intro, 3, 2500.0f, PT_SEMICOLCHEIA, 11, PT_RUIDO_BRANCO);
    }

    /* --- Padrão B: tema principal — "Shrine Dance" ------------- */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 180);

    /* Melodia principal — ágil, saltitante */
    PT_NOTA(tema, 0, PT_LA5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 12);
    PT_NOTA(tema, 0, PT_FA5,  PT_COLCHEIA,     12);
    PT_NOTA(tema, 0, PT_MI5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(tema, 0, PT_RE5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(tema, 0, PT_MI5,  PT_COLCHEIA,     12);
    PT_NOTA(tema, 0, PT_FA5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 12);
    PT_NOTA(tema, 0, PT_LA5,  PT_COLCHEIA,     13);
    PT_NOTA(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 12);
    PT_NOTA(tema, 0, PT_LA5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(tema, 0, PT_SI5,  PT_COLCHEIA,     13);
    PT_NOTA(tema, 0, PT_DO6,  PT_SEMICOLCHEIA, 14);
    PT_NOTA(tema, 0, PT_SI5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(tema, 0, PT_LA5,  PT_MINIMA,       13);

    /* Harmonia com arpejo em terças */
    PT_NOTA_F(tema, 1, PT_MI5,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_RE5,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_DO5,  PT_COLCHEIA,     9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_SI4,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_LA4,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_SI4,  PT_COLCHEIA,     9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_DO5,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_RE5,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_MI5,  PT_COLCHEIA,    10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_RE5,  PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_MI5,  PT_SEMICOLCHEIA,10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_FAS5, PT_COLCHEIA,    10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_SOL5, PT_SEMICOLCHEIA,10, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_FAS5, PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_MI5,  PT_MINIMA,      10, PT_ONDA_TRIANGULAR);

    /* Baixo — ostinato pulsar */
    float baixo_B[] = { PT_RE3, PT_MI3, PT_FA3, PT_LA3,
                        PT_RE3, PT_MI3, PT_SOL3, PT_LA3 };
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 2, baixo_B[b], PT_COLCHEIA, 12, PT_ONDA_DENTE_SERRA);
    }

    /* Percussão — hi-hat + snare */
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 3, 7000.0f, PT_SEMICOLCHEIA,  5, PT_RUIDO_BRANCO);
        if (b == 1 || b == 3 || b == 5 || b == 7)
            PT_NOTA_F(tema, 3, 2000.0f, PT_SEMICOLCHEIA, 13, PT_RUIDO_BRANCO);
        else
            PT_NOTA_F(tema, 3, 7000.0f, PT_SEMICOLCHEIA,  5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão C: variação intensa — modulação para Lá menor -- */
    PT_Padrao variacao;
    pt_iniciar_padrao(&variacao, 186);

    PT_NOTA_EFX(variacao, 0, PT_LA5, PT_COLCHEIA, 13, PT_ONDA_QUADRADA, PT_EFX_VIBRATO, 0.6f);
    PT_NOTA(variacao, 0, PT_SOL5, PT_SEMICOLCHEIA, 12);
    PT_NOTA(variacao, 0, PT_FA5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(variacao, 0, PT_MI5,  PT_COLCHEIA,     13);
    PT_NOTA(variacao, 0, PT_RE5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(variacao, 0, PT_DO5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(variacao, 0, PT_RE5,  PT_COLCHEIA,     12);
    PT_NOTA(variacao, 0, PT_MI5,  PT_COLCHEIA,     13);
    PT_NOTA(variacao, 0, PT_FA5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(variacao, 0, PT_MI5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(variacao, 0, PT_RE5,  PT_MINIMA_P,     14);

    PT_NOTA_F(variacao, 1, PT_MI5, PT_COLCHEIA,     9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_RE5, PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_DO5, PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_SI4, PT_COLCHEIA,     9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_LA4, PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_SOL4,PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_LA4, PT_COLCHEIA,     8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_SI4, PT_COLCHEIA,     9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_DO5, PT_SEMICOLCHEIA, 9, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_SI4, PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_LA4, PT_MINIMA_P,    10, PT_ONDA_TRIANGULAR);

    float baixo_C[] = { PT_LA2, PT_MI3, PT_LA2, PT_MI3,
                        PT_RE3, PT_LA3, PT_RE3, PT_MI3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(variacao, 2, baixo_C[b], PT_COLCHEIA, 12, PT_ONDA_DENTE_SERRA);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(variacao, 3, 7000.0f, PT_SEMICOLCHEIA,  5, PT_RUIDO_BRANCO);
        PT_NOTA_F(variacao, 3, (b%2==1)?2000.0f:7000.0f, PT_SEMICOLCHEIA,
                  (b%2==1)?13:5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão D: ponte lírica — desacelera, mais suave -------- */
    PT_Padrao ponte;
    pt_iniciar_padrao(&ponte, 150);

    PT_NOTA(ponte, 0, PT_FA5,  PT_MINIMA,   11);
    PT_NOTA(ponte, 0, PT_MI5,  PT_COLCHEIA, 10);
    PT_NOTA(ponte, 0, PT_RE5,  PT_COLCHEIA, 10);
    PT_NOTA(ponte, 0, PT_DO5,  PT_MINIMA,   11);
    PT_NOTA(ponte, 0, PT_SI4,  PT_COLCHEIA, 10);
    PT_NOTA(ponte, 0, PT_DO5,  PT_COLCHEIA, 11);
    PT_NOTA(ponte, 0, PT_RE5,  PT_SEMIBREVE, 12);

    PT_NOTA_F(ponte, 1, PT_DO5, PT_MINIMA,    8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_SI4, PT_COLCHEIA,  7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_LA4, PT_COLCHEIA,  7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_SOL4,PT_MINIMA,    8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_FAS4,PT_COLCHEIA,  7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_SOL4,PT_COLCHEIA,  8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_LA4, PT_SEMIBREVE, 9, PT_ONDA_TRIANGULAR);

    PT_NOTA_F(ponte, 2, PT_RE3, PT_MINIMA,   10, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(ponte, 2, PT_DO3, PT_MINIMA,    9, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(ponte, 2, PT_SI2, PT_MINIMA,    9, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(ponte, 2, PT_LA2, PT_SEMIBREVE,10, PT_ONDA_DENTE_SERRA);

    /* Percussão mais suave na ponte */
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(ponte, 3, 6000.0f, PT_COLCHEIA, 4, PT_RUIDO_BRANCO);

    /* --- Montagem da música -------------------------------------- */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &intro,    1);
    pt_adicionar_padrao_musica(&musica, &tema,     2);
    pt_adicionar_padrao_musica(&musica, &variacao, 2);
    pt_adicionar_padrao_musica(&musica, &ponte,    1);
    pt_adicionar_padrao_musica(&musica, &tema,     2);
    pt_adicionar_padrao_musica(&musica, &variacao, 1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "eternal_shrine_maiden.wav", 300.0f);

    printf("Eternal Shrine Maiden  —  %.2f s\n", (float)frames / 44100.0f);
    printf("Arquivo: eternal_shrine_maiden.wav\n");

    pt_destruir_contexto(&ctx);
    return 0;
}
