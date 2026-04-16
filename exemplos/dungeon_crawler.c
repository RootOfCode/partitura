/*
 * dungeon_crawler.c
 * "Dungeon Crawler" — estilo MS-DOS / AdLib / OPL2 (SoundBlaster)
 *
 * Música de masmorra típica de RPG dos anos 1990 (Ultima, Might & Magic,
 * Eye of the Beholder). Tom tenso, marcial e repetitivo. Emula o chip
 * OPL2 (YM3812) do AdLib card e Sound Blaster.
 *
 * Compilar:  gcc dungeon_crawler.c -o dungeon_crawler -lm
 * Executar:  ./dungeon_crawler
 * Saída:     dungeon_crawler.wav
 */

#include "partitura.h"

int main(void) {
    /* 4 canais FM emulando OPL2 */
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.82f;

    /* Canal 0: melodia — brass/horn FM (tipo AdLib "trumpet") */
    pt_ativar_fm(&ctx, 0, 2.0f, 3.5f);
    pt_fm_envelope_modulador(&ctx, 0, 0.0f, 0.1f, 0.4f, 0.15f);
    pt_definir_envelope(&ctx, 0, 0.005f, 0.12f, 0.55f, 0.12f);
    pt_definir_pan(&ctx, 0, -0.2f);

    /* Canal 1: counter-melody — strings FM */
    pt_ativar_fm(&ctx, 1, 1.0f, 0.8f);
    pt_fm_envelope_modulador(&ctx, 1, 0.08f, 0.0f, 0.85f, 0.3f);
    pt_definir_envelope(&ctx, 1, 0.06f, 0.0f, 0.75f, 0.2f);
    pt_definir_pan(&ctx, 1, 0.2f);

    /* Canal 2: baixo — bass FM */
    pt_ativar_fm(&ctx, 2, 2.0f, 6.0f);
    pt_fm_envelope_modulador(&ctx, 2, 0.0f, 0.06f, 0.0f, 0.0f);
    pt_definir_envelope(&ctx, 2, 0.001f, 0.25f, 0.0f, 0.05f);
    pt_definir_pan(&ctx, 2, 0.0f);

    /* Canal 3: percussão OPL2 (noise channel) */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.08f, 0.0f, 0.02f);
    pt_definir_pan(&ctx, 3, 0.0f);

    /* --- Padrão A: marcha de masmorra (Mi menor, 112 BPM) ------- */
    PT_Padrao marcha;
    pt_iniciar_padrao(&marcha, 112);

    /* Melodia marcial */
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_SOL4, PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_LA4,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_SI4,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_LA4,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_SOL4, PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_COLCHEIA,     12, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_RE4,  PT_COLCHEIA,     11, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_MINIMA,       12, PT_ONDA_FM);

    /* Strings em contraponto */
    PT_NOTA_F(marcha, 1, PT_SI3,  PT_COLCHEIA,      8, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_DO4,  PT_COLCHEIA,      8, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_RE4,  PT_MINIMA,        8, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_DO4,  PT_COLCHEIA,      7, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_SI3,  PT_COLCHEIA,      7, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_LA3,  PT_COLCHEIA,      7, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_SI3,  PT_MINIMA,        8, PT_ONDA_FM);

    /* Baixo marcado */
    float bass_A[] = { PT_MI2, PT_SI2, PT_MI2, PT_SI2,
                       PT_LA2, PT_MI2, PT_LA2, PT_SI2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(marcha, 2, bass_A[b], PT_COLCHEIA, 13, PT_ONDA_FM);

    /* Percussão simples OPL */
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(marcha, 3, 180.0f,  PT_COLCHEIA,   13, PT_RUIDO_LFSR);
        PT_NOTA_F(marcha, 3, 1800.0f, PT_COLCHEIA, (b%2==1)?12:5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão B: tema da masmorra — tenso e pesado ------------ */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 104);

    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_SEMICOLCHEIA,12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_SEMICOLCHEIA,11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_FA5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_MINIMA,     12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_SI4,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_MINIMA,     12, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_MINIMA_P,   12, PT_ONDA_FM);

    PT_NOTA_F(tema, 1, PT_DO5,  PT_MINIMA,      8, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SI4,  PT_MINIMA,      7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_LA4,  PT_SEMIBREVE,   8, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SOL4, PT_MINIMA,      7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_FAS4, PT_MINIMA,      7, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SOL4, PT_MINIMA_P,    8, PT_ONDA_FM);

    float bass_B[] = { PT_LA2, PT_MI3, PT_LA2, PT_MI3,
                       PT_RE3, PT_LA3, PT_RE3, PT_SI3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(tema, 2, bass_B[b], PT_COLCHEIA, 12, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 3, 180.0f, PT_SEMICOLCHEIA, 13, PT_RUIDO_LFSR);
        PT_NOTA_F(tema, 3, 1800.0f, PT_SEMICOLCHEIA,(b%2==1)?11:4, PT_RUIDO_BRANCO);
        PT_NOTA_F(tema, 3, 6000.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
        PT_NOTA_F(tema, 3, 6000.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
    }

    /* --- Padrão C: corredor de armadilhas — rápido e agitado ---- */
    PT_Padrao corredor;
    pt_iniciar_padrao(&corredor, 132);

    PT_NOTA_F(corredor, 0, PT_LA5,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_FA5,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_MI5,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_RE5,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_MI5,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_FA5,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_LA5,  PT_COLCHEIA,     13, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_LA5,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SI5,  PT_COLCHEIA,     14, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_DO6,  PT_SEMICOLCHEIA, 14, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SI5,  PT_SEMICOLCHEIA, 13, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_LA5,  PT_MINIMA,       13, PT_ONDA_FM);

    PT_NOTA_F(corredor, 1, PT_MI5,  PT_COLCHEIA,     9, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_RE5,  PT_COLCHEIA,     8, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_DO5,  PT_COLCHEIA,     8, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_RE5,  PT_MINIMA,       9, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_MI5,  PT_COLCHEIA,     9, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_FAS5, PT_COLCHEIA,    10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_SOL5, PT_SEMIBREVE,   10, PT_ONDA_FM);

    float bass_C[] = { PT_LA2, PT_LA2, PT_MI3, PT_MI3,
                       PT_FA3, PT_FA3, PT_MI3, PT_RE3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(corredor, 2, bass_C[b], PT_COLCHEIA, 13, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(corredor, 3, 200.0f,  PT_SEMICOLCHEIA, 14, PT_RUIDO_LFSR);
        PT_NOTA_F(corredor, 3, 2000.0f, PT_SEMICOLCHEIA, 12, PT_RUIDO_BRANCO);
        PT_NOTA_F(corredor, 3, 6500.0f, PT_SEMICOLCHEIA,  5, PT_RUIDO_BRANCO);
        PT_NOTA_F(corredor, 3, 6500.0f, PT_SEMICOLCHEIA,  5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão D: sala do boss — grave e ameaçador ------------- */
    PT_Padrao boss;
    pt_iniciar_padrao(&boss, 90);

    PT_NOTA_F(boss, 0, PT_MI4,  PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_PAUSA (boss, 0, PT_SEMICOLCHEIA);
    PT_NOTA_F(boss, 0, PT_MI4,  PT_SEMICOLCHEIA,13, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_SOL4, PT_COLCHEIA,   13, PT_ONDA_FM);
    PT_PAUSA (boss, 0, PT_SEMICOLCHEIA);
    PT_NOTA_F(boss, 0, PT_FA4,  PT_SEMICOLCHEIA,12, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_MI4,  PT_MINIMA,     12, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_RE4,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_DO4,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_SI3,  PT_COLCHEIA,   10, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_LA3,  PT_MINIMA_P,   12, PT_ONDA_FM);

    PT_NOTA_F(boss, 1, PT_DO4,  PT_MINIMA,      8, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_RE4,  PT_MINIMA,      8, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_DO4,  PT_MINIMA,      7, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_SI3,  PT_MINIMA,      7, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_LA3,  PT_MINIMA,      8, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_SOL3, PT_MINIMA_P,    7, PT_ONDA_FM);

    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(boss, 2, PT_MI2,  PT_COLCHEIA, 14, PT_ONDA_FM);
        PT_NOTA_F(boss, 2, PT_MI2,  PT_COLCHEIA, 13, PT_ONDA_FM);
        PT_NOTA_F(boss, 2, PT_LA2,  PT_COLCHEIA, 13, PT_ONDA_FM);
        PT_NOTA_F(boss, 2, PT_SI2,  PT_COLCHEIA, 12, PT_ONDA_FM);
    }

    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(boss, 3, 100.0f,  PT_COLCHEIA, 14, PT_RUIDO_LFSR);
        PT_NOTA_F(boss, 3, 1500.0f, PT_COLCHEIA, 11, PT_RUIDO_BRANCO);
        PT_NOTA_F(boss, 3, 100.0f,  PT_COLCHEIA, 13, PT_RUIDO_LFSR);
        PT_NOTA_F(boss, 3, 6000.0f, PT_COLCHEIA,  4, PT_RUIDO_BRANCO);
    }

    /* --- Montagem ------------------------------------------------ */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &marcha,   1);
    pt_adicionar_padrao_musica(&musica, &tema,     2);
    pt_adicionar_padrao_musica(&musica, &corredor, 2);
    pt_adicionar_padrao_musica(&musica, &tema,     1);
    pt_adicionar_padrao_musica(&musica, &boss,     2);
    pt_adicionar_padrao_musica(&musica, &corredor, 1);
    pt_adicionar_padrao_musica(&musica, &tema,     1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "dungeon_crawler.wav", 300.0f);

    printf("Dungeon Crawler  —  %.2f s\n", (float)frames / 44100.0f);
    printf("Arquivo: dungeon_crawler.wav\n");

    pt_destruir_contexto(&ctx);
    return 0;
}
