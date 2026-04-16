/*
 * starfield_overture.c
 * "Starfield Overture" — estilo MS-DOS / Space Quest / Commander Keen
 *
 * Música de abertura espacial e épica, no estilo dos jogos de aventura
 * sci-fi da Sierra On-Line e id Software para MS-DOS (1989-1994).
 * Emula OPL2 (SoundBlaster/AdLib) com FM enriquecido por wavetable.
 *
 * Compilar:  gcc starfield_overture.c -o starfield_overture -lm
 * Executar:  ./starfield_overture
 * Saída:     starfield_overture.wav
 */

#include "partitura.h"

int main(void) {
    /* 4 canais: fanfarra FM | strings | baixo | percussão */
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.80f;

    /* Canal 0: fanfarra — trompete FM */
    pt_ativar_fm(&ctx, 0, 3.0f, 4.0f);
    pt_fm_envelope_modulador(&ctx, 0, 0.0f, 0.08f, 0.5f, 0.1f);
    pt_definir_envelope(&ctx, 0, 0.008f, 0.06f, 0.7f, 0.10f);
    pt_definir_pan(&ctx, 0, -0.2f);

    /* Canal 1: strings — wavetable com série de Fourier */
    static float tab_strings[PT_TABELA_TAM];
    pt_tabela_fourier(tab_strings, 6, 0);  /* 6 harmônicos, par+ímpar */
    pt_definir_envelope(&ctx, 1, 0.08f, 0.0f, 0.80f, 0.25f);
    pt_definir_vibrato(&ctx, 1, 0.2f, 4.5f);
    pt_definir_pan(&ctx, 1, 0.2f);

    /* Canal 2: baixo — FM grave */
    pt_ativar_fm(&ctx, 2, 1.0f, 4.5f);
    pt_fm_envelope_modulador(&ctx, 2, 0.0f, 0.05f, 0.3f, 0.1f);
    pt_definir_envelope(&ctx, 2, 0.003f, 0.3f, 0.15f, 0.08f);
    pt_definir_pan(&ctx, 2, 0.0f);

    /* Canal 3: percussão orquestral */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.18f, 0.0f, 0.05f);
    pt_definir_pan(&ctx, 3, 0.0f);

    /* --- Padrão A: fanfarra de abertura (Lá maior, 72 BPM) ------ */
    PT_Padrao abertura;
    pt_iniciar_padrao(&abertura, 72);

    /* Trompete épico — fanfarra ascendente */
    PT_NOTA_F(abertura, 0, PT_LA4,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_MI5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_LA5,  PT_MINIMA,     14, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_SOL5, PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_FAS5, PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_MI5,  PT_MINIMA,     13, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_FAS5, PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_SOL5, PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(abertura, 0, PT_LA5,  PT_SEMIBREVE,  14, PT_ONDA_FM);

    /* Strings sustentadas — acorde de Lá maior */
    PT_NOTA_F(abertura, 1, PT_DO5,  PT_MINIMA,      8, PT_ONDA_TABELA);
    PT_NOTA_F(abertura, 1, PT_MI5,  PT_MINIMA,      8, PT_ONDA_TABELA);
    PT_NOTA_F(abertura, 1, PT_LA5,  PT_SEMIBREVE,   8, PT_ONDA_TABELA);
    PT_NOTA_F(abertura, 1, PT_MI5,  PT_MINIMA,      7, PT_ONDA_TABELA);
    PT_NOTA_F(abertura, 1, PT_DO5,  PT_SEMIBREVE,   7, PT_ONDA_TABELA);

    /* Baixo sustentado */
    PT_NOTA_F(abertura, 2, PT_LA2,  PT_SEMIBREVE,  11, PT_ONDA_FM);
    PT_NOTA_F(abertura, 2, PT_MI3,  PT_SEMIBREVE,  10, PT_ONDA_FM);
    PT_NOTA_F(abertura, 2, PT_LA2,  PT_SEMIBREVE,  11, PT_ONDA_FM);

    /* Tímpano na abertura */
    PT_NOTA_F(abertura, 3, 90.0f,  PT_MINIMA,     13, PT_RUIDO_LFSR);
    PT_PAUSA (abertura, 3, PT_MINIMA);
    PT_NOTA_F(abertura, 3, 90.0f,  PT_COLCHEIA,   12, PT_RUIDO_LFSR);
    PT_NOTA_F(abertura, 3, 90.0f,  PT_COLCHEIA,   13, PT_RUIDO_LFSR);
    PT_NOTA_F(abertura, 3, 90.0f,  PT_SEMIBREVE,  14, PT_RUIDO_LFSR);

    /* --- Padrão B: tema do espaço sideral — contemplativo ------- */
    PT_Padrao espaco;
    pt_iniciar_padrao(&espaco, 88);

    PT_NOTA_F(espaco, 0, PT_DO6,  PT_COLCHEIA_P, 13, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_SI5,  PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_LA5,  PT_MINIMA,     13, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_SOL5, PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_FAS5, PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_SOL5, PT_MINIMA,     12, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_LA5,  PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_SI5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(espaco, 0, PT_DO6,  PT_MINIMA_P,   13, PT_ONDA_FM);

    /* Strings em movimento suave */
    PT_NOTA_F(espaco, 1, PT_MI5,  PT_MINIMA,      7, PT_ONDA_TABELA);
    PT_NOTA_F(espaco, 1, PT_FAS5, PT_MINIMA,      7, PT_ONDA_TABELA);
    PT_NOTA_F(espaco, 1, PT_SOL5, PT_SEMIBREVE,   8, PT_ONDA_TABELA);
    PT_NOTA_F(espaco, 1, PT_MI5,  PT_MINIMA,      7, PT_ONDA_TABELA);
    PT_NOTA_F(espaco, 1, PT_FAS5, PT_MINIMA,      7, PT_ONDA_TABELA);
    PT_NOTA_F(espaco, 1, PT_MI5,  PT_MINIMA_P,    7, PT_ONDA_TABELA);

    float baixo_B[] = { PT_LA2, PT_RE3, PT_MI3, PT_LA3,
                        PT_FAS3,PT_RE3, PT_MI3, PT_LA2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(espaco, 2, baixo_B[b], PT_MINIMA, 10, PT_ONDA_FM);

    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(espaco, 3, 6500.0f, PT_COLCHEIA, 3, PT_RUIDO_BRANCO);
        PT_NOTA_F(espaco, 3, 6500.0f, PT_COLCHEIA, 2, PT_RUIDO_BRANCO);
        PT_NOTA_F(espaco, 3, 90.0f,   PT_COLCHEIA,11, PT_RUIDO_LFSR);
        PT_NOTA_F(espaco, 3, 6500.0f, PT_COLCHEIA, 3, PT_RUIDO_BRANCO);
    }

    /* --- Padrão C: travessia hiperespacial — aceleração épica ---- */
    PT_Padrao hiperespaco;
    pt_iniciar_padrao(&hiperespaco, 128);

    PT_NOTA_F(hiperespaco, 0, PT_LA5,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_DO6,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_MI6,  PT_COLCHEIA,     14, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_RE6,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_DO6,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_SI5,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_LA5,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_SOL5, PT_COLCHEIA,     12, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_FAS5, PT_COLCHEIA,     12, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_MI5,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_FAS5, PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_SOL5, PT_COLCHEIA,     12, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_LA5,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_SI5,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(hiperespaco, 0, PT_DO6,  PT_MINIMA,       13, PT_ONDA_FM);

    float harm_H[] = {
        PT_MI5, PT_LA5, PT_DO6, PT_MI6,
        PT_RE5, PT_SOL5,PT_SI5, PT_RE6,
        PT_DO5, PT_FAS5,PT_LA5, PT_DO6,
        PT_RE5, PT_SOL5,PT_SI5, PT_RE6
    };
    for (int b = 0; b < 16; b++)
        PT_NOTA_F(hiperespaco, 1, harm_H[b], PT_SEMICOLCHEIA, 8, PT_ONDA_TABELA);

    float bass_H[] = { PT_LA2, PT_MI3, PT_RE3, PT_DO3,
                       PT_DO3, PT_RE3, PT_MI3, PT_LA2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(hiperespaco, 2, bass_H[b], PT_COLCHEIA, 12, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(hiperespaco, 3, 180.0f, PT_COLCHEIA,   13, PT_RUIDO_LFSR);
        PT_NOTA_F(hiperespaco, 3, 1800.0f,PT_SEMICOLCHEIA,11, PT_RUIDO_BRANCO);
        PT_NOTA_F(hiperespaco, 3, 7000.0f,PT_SEMICOLCHEIA, 5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão D: nebulosa — repousar entre as estrelas -------- */
    PT_Padrao nebulosa;
    pt_iniciar_padrao(&nebulosa, 72);

    PT_NOTA_F(nebulosa, 0, PT_FAS5, PT_SEMIBREVE,  11, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_MI5,  PT_MINIMA,     10, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_RE5,  PT_MINIMA,     10, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_DO5,  PT_SEMIBREVE,  10, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_SI4,  PT_MINIMA,      9, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_DO5,  PT_MINIMA,     10, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_RE5,  PT_SEMIBREVE,  11, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 0, PT_LA4,  PT_SEMIBREVE,  12, PT_ONDA_FM);

    PT_NOTA_F(nebulosa, 1, PT_DOS5, PT_SEMIBREVE,   6, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_SOL4, PT_SEMIBREVE,   6, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_LA4,  PT_SEMIBREVE,   7, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_RE5,  PT_SEMIBREVE,   6, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_FAS5, PT_SEMIBREVE,   7, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_DOS5, PT_SEMIBREVE,   6, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_LA4,  PT_SEMIBREVE,   7, PT_ONDA_TABELA);
    PT_NOTA_F(nebulosa, 1, PT_DOS5, PT_SEMIBREVE,   6, PT_ONDA_TABELA);

    PT_NOTA_F(nebulosa, 2, PT_LA2,  PT_SEMIBREVE,  10, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_RE3,  PT_SEMIBREVE,   9, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_FAS3, PT_SEMIBREVE,   9, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_RE3,  PT_SEMIBREVE,   9, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_LA2,  PT_SEMIBREVE,  10, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_MI3,  PT_SEMIBREVE,   9, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_RE3,  PT_SEMIBREVE,   9, PT_ONDA_FM);
    PT_NOTA_F(nebulosa, 2, PT_LA2,  PT_SEMIBREVE,  10, PT_ONDA_FM);

    for (int b = 0; b < 8; b++)
        PT_NOTA_F(nebulosa, 3, 7000.0f, PT_MINIMA, 2, PT_RUIDO_BRANCO);

    /* --- Montagem ------------------------------------------------ */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &abertura,    1);
    pt_adicionar_padrao_musica(&musica, &espaco,      2);
    pt_adicionar_padrao_musica(&musica, &hiperespaco, 2);
    pt_adicionar_padrao_musica(&musica, &espaco,      1);
    pt_adicionar_padrao_musica(&musica, &nebulosa,    1);
    pt_adicionar_padrao_musica(&musica, &hiperespaco, 1);
    pt_adicionar_padrao_musica(&musica, &abertura,    1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "starfield_overture.wav", 300.0f);

    printf("Starfield Overture  —  %.2f s\n", (float)frames / 44100.0f);
    printf("Arquivo: starfield_overture.wav\n");

    pt_destruir_contexto(&ctx);
    return 0;
}
