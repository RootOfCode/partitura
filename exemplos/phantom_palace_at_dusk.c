/*
 * phantom_palace_at_dusk.c
 * "Phantom Palace at Dusk" — estilo PC-98 / FM Towns / OPL3
 *
 * Atmosfera misteriosa e melancólica em Sol menor, inspirada nos
 * jogos de aventura e RPG japoneses para PC-98 (1989-1995).
 * Usa síntese FM 2 operadores e wavetable para imitar o chip OPL2/OPL3.
 *
 * Compilar:  gcc phantom_palace_at_dusk.c -o phantom_palace_at_dusk -lm
 * Executar:  ./phantom_palace_at_dusk
 * Saída:     phantom_palace_at_dusk.wav
 */

#include "partitura.h"

int main(void) {
    /* 4 canais: FM lead | FM pad | baixo FM | percussão */
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.80f;

    /* Canal 0: melodia FM — tipo piano elétrico sombrio */
    pt_ativar_fm(&ctx, 0, 14.0f, 2.8f);
    pt_fm_envelope_modulador(&ctx, 0, 0.0f, 0.6f, 0.2f, 0.3f);
    pt_definir_envelope(&ctx, 0, 0.008f, 0.8f, 0.20f, 0.35f);
    pt_definir_pan(&ctx, 0, -0.25f);

    /* Canal 1: pad FM — órgão misterioso */
    pt_ativar_fm(&ctx, 1, 1.0f, 1.5f);
    pt_fm_envelope_modulador(&ctx, 1, 0.05f, 0.0f, 1.0f, 0.4f);
    pt_definir_envelope(&ctx, 1, 0.12f, 0.0f, 0.7f, 0.4f);
    pt_definir_pan(&ctx, 1,  0.25f);

    /* Canal 2: baixo FM — brass grave */
    pt_ativar_fm(&ctx, 2, 2.0f, 5.0f);
    pt_fm_envelope_modulador(&ctx, 2, 0.0f, 0.08f, 0.0f, 0.0f);
    pt_definir_envelope(&ctx, 2, 0.002f, 0.35f, 0.0f, 0.06f);
    pt_definir_pan(&ctx, 2, 0.0f);

    /* Canal 3: percussão ritualística */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.12f, 0.0f, 0.03f);
    pt_definir_pan(&ctx, 3, 0.0f);

    /* --- Padrão A: abertura atmosférica (Sol menor, 96 BPM) ----- */
    PT_Padrao abertura;
    pt_iniciar_padrao(&abertura, 96);

    /* Melodia FM — fragmento temático lento */
    PT_NOTA_F(abertura, 0, PT_RE5,  PT_MINIMA,    12, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_DO5,  PT_COLCHEIA,  11, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_SI4,  PT_COLCHEIA,  11, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_LA4,  PT_MINIMA_P,  12, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_SOL4, PT_COLCHEIA,  11, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_LA4,  PT_COLCHEIA,  11, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_SI4,  PT_SEMIBREVE, 12, PT_ONDA_FM);

    /* Pad sustentado — acorde de Sol menor */
    PT_NOTA_F(abertura, 1, PT_SOL4, PT_SEMIBREVE,  7, PT_ONDA_FM);
    PT_NOTA_F(abertura, 1, PT_SI4,  PT_SEMIBREVE,  6, PT_ONDA_FM);
    PT_NOTA_F(abertura, 1, PT_RE5,  PT_SEMIBREVE,  6, PT_ONDA_FM);

    /* Baixo esparso */
    PT_NOTA_F(abertura, 2, PT_SOL2, PT_MINIMA,   11, PT_ONDA_FM);
    PT_PAUSA (abertura, 2, PT_MINIMA);
    PT_NOTA_F(abertura, 2, PT_RE3,  PT_MINIMA,   10, PT_ONDA_FM);
    PT_PAUSA (abertura, 2, PT_MINIMA);
    PT_NOTA_F(abertura, 2, PT_LA2,  PT_MINIMA,   11, PT_ONDA_FM);
    PT_PAUSA (abertura, 2, PT_MINIMA);
    PT_NOTA_F(abertura, 2, PT_SOL2, PT_SEMIBREVE,12, PT_ONDA_FM);

    /* Percussão — bumbo grave lento + hi-hat */
    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(abertura, 3, 120.0f,  PT_COLCHEIA,   13, PT_RUIDO_LFSR);
        PT_NOTA_F(abertura, 3, 6000.0f, PT_COLCHEIA,    4, PT_RUIDO_BRANCO);
        PT_NOTA_F(abertura, 3, 6000.0f, PT_COLCHEIA,    4, PT_RUIDO_BRANCO);
        PT_NOTA_F(abertura, 3, 1800.0f, PT_COLCHEIA,    9, PT_RUIDO_BRANCO);
    }

    /* --- Padrão B: tema principal — "Halls of Twilight" --------- */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 108);

    /* Melodia FM expressiva */
    PT_NOTA_F(tema, 0, PT_SOL5, PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_FA5,  PT_SEMICOLCHEIA,11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_SEMICOLCHEIA,11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_MINIMA,     12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_SI4,  PT_MINIMA,     12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_LA4,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_SOL4, PT_COLCHEIA,   10, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_LA4,  PT_MINIMA_P,   12, PT_ONDA_FM);

    /* Pad harmônico — acorde se movendo */
    PT_NOTA_F(tema, 1, PT_SOL4, PT_MINIMA,     7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SI4,  PT_MINIMA,     7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_DO5,  PT_SEMIBREVE,  7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_RE5,  PT_MINIMA,     7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_MI5,  PT_MINIMA,     7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_FA5,  PT_SEMIBREVE,  7, PT_ONDA_FM);

    /* Baixo pulsante */
    float baixo_t[] = { PT_SOL2, PT_LA2, PT_SI2, PT_DO3,
                        PT_RE3, PT_DO3, PT_SI2, PT_LA2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(tema, 2, baixo_t[b], PT_MINIMA, 11, PT_ONDA_FM);

    /* Percussão com mais groove */
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 3, 120.0f,  PT_COLCHEIA,  13, PT_RUIDO_LFSR);
        PT_NOTA_F(tema, 3, 6000.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
        if (b % 2 == 1)
            PT_NOTA_F(tema, 3, 1800.0f, PT_SEMICOLCHEIA, 11, PT_RUIDO_BRANCO);
        else
            PT_NOTA_F(tema, 3, 6000.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
    }

    /* --- Padrão C: desenvolvimento — tensão crescente ----------- */
    PT_Padrao tensao;
    pt_iniciar_padrao(&tensao, 120);

    PT_NOTA_F(tensao, 0, PT_LA5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_SOL5, PT_SEMICOLCHEIA,12, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_FAS5, PT_SEMICOLCHEIA,12, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_SOL5, PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_LA5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_SI5,  PT_MINIMA,     14, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_DO6,  PT_COLCHEIA,   14, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_SI5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_LA5,  PT_MINIMA,     13, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_SOL5, PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_FAS5, PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tensao, 0, PT_SOL5, PT_SEMIBREVE,  13, PT_ONDA_FM);

    PT_NOTA_F(tensao, 1, PT_RE5,  PT_MINIMA,      8, PT_ONDA_FM);
    PT_NOTA_F(tensao, 1, PT_DO5,  PT_MINIMA,      7, PT_ONDA_FM);
    PT_NOTA_F(tensao, 1, PT_SI4,  PT_SEMIBREVE,   8, PT_ONDA_FM);
    PT_NOTA_F(tensao, 1, PT_DO5,  PT_SEMIBREVE,   8, PT_ONDA_FM);
    PT_NOTA_F(tensao, 1, PT_RE5,  PT_SEMIBREVE,   8, PT_ONDA_FM);

    float baixo_c[] = { PT_RE3, PT_RE3, PT_MI3, PT_MI3,
                        PT_FAS3, PT_SOL3, PT_LA3, PT_SOL3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(tensao, 2, baixo_c[b], PT_COLCHEIA, 12, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tensao, 3, 200.0f, PT_COLCHEIA, (b%4==0)?13:10, PT_RUIDO_LFSR);
        PT_NOTA_F(tensao, 3, 6000.0f,PT_COLCHEIA,  5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão D: coda — repouso final ------------------------- */
    PT_Padrao coda;
    pt_iniciar_padrao(&coda, 88);

    PT_NOTA_F(coda, 0, PT_RE5,  PT_MINIMA_P,  11, PT_ONDA_FM);
    PT_NOTA_F(coda, 0, PT_DO5,  PT_COLCHEIA,  10, PT_ONDA_FM);
    PT_NOTA_F(coda, 0, PT_SI4,  PT_MINIMA,    11, PT_ONDA_FM);
    PT_NOTA_F(coda, 0, PT_LA4,  PT_MINIMA,    10, PT_ONDA_FM);
    PT_NOTA_F(coda, 0, PT_SOL4, PT_SEMIBREVE, 12, PT_ONDA_FM);

    PT_NOTA_F(coda, 1, PT_SOL4, PT_SEMIBREVE,  6, PT_ONDA_FM);
    PT_NOTA_F(coda, 1, PT_SI4,  PT_SEMIBREVE,  6, PT_ONDA_FM);
    PT_NOTA_F(coda, 1, PT_RE5,  PT_SEMIBREVE,  6, PT_ONDA_FM);
    PT_NOTA_F(coda, 1, PT_SOL4, PT_SEMIBREVE,  7, PT_ONDA_FM);

    PT_NOTA_F(coda, 2, PT_SOL2, PT_SEMIBREVE, 11, PT_ONDA_FM);
    PT_NOTA_F(coda, 2, PT_RE3,  PT_SEMIBREVE, 10, PT_ONDA_FM);
    PT_NOTA_F(coda, 2, PT_SOL2, PT_SEMIBREVE, 12, PT_ONDA_FM);

    for (int b = 0; b < 8; b++)
        PT_NOTA_F(coda, 3, 6000.0f, PT_COLCHEIA, 3, PT_RUIDO_BRANCO);

    /* --- Montagem ------------------------------------------------ */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &abertura, 1);
    pt_adicionar_padrao_musica(&musica, &tema,     2);
    pt_adicionar_padrao_musica(&musica, &tensao,   2);
    pt_adicionar_padrao_musica(&musica, &tema,     1);
    pt_adicionar_padrao_musica(&musica, &tensao,   1);
    pt_adicionar_padrao_musica(&musica, &coda,     1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "phantom_palace_at_dusk.wav", 300.0f);

    printf("Phantom Palace at Dusk  —  %.2f s\n", (float)frames / 44100.0f);
    printf("Arquivo: phantom_palace_at_dusk.wav\n");

    pt_destruir_contexto(&ctx);
    return 0;
}
