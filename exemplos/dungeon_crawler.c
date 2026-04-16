/*
 * dungeon_crawler.c
 * "Dungeon Crawler" — estilo MS-DOS / AdLib OPL2 (SoundBlaster)
 *
 * Compilar:  gcc dungeon_crawler.c -o dungeon_crawler -lm
 * Executar:  ./dungeon_crawler
 * Saida:     dungeon_crawler.wav
 */

#include "partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.52f;

    /* Canal 0: brass FM */
    pt_ativar_fm(&ctx, 0, 2.0f, 3.5f);
    pt_fm_envelope_modulador(&ctx, 0, 0.0f, 0.1f, 0.4f, 0.15f);
    pt_definir_envelope(&ctx, 0, 0.005f, 0.12f, 0.50f, 0.12f);
    pt_definir_pan(&ctx, 0, -0.2f);

    /* Canal 1: strings FM */
    pt_ativar_fm(&ctx, 1, 1.0f, 0.8f);
    pt_fm_envelope_modulador(&ctx, 1, 0.08f, 0.0f, 0.85f, 0.3f);
    pt_definir_envelope(&ctx, 1, 0.06f, 0.0f, 0.70f, 0.2f);
    pt_definir_pan(&ctx, 1, 0.2f);

    /* Canal 2: bass FM */
    pt_ativar_fm(&ctx, 2, 2.0f, 6.0f);
    pt_fm_envelope_modulador(&ctx, 2, 0.0f, 0.06f, 0.0f, 0.0f);
    pt_definir_envelope(&ctx, 2, 0.001f, 0.25f, 0.0f, 0.05f);
    pt_definir_pan(&ctx, 2, 0.0f);

    /* Canal 3: noise */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.08f, 0.0f, 0.02f);

    /* ── Padrão A: marcha de masmorra (Mi menor, 86 BPM) ── */
    PT_Padrao marcha;
    pt_iniciar_padrao(&marcha, 86);

    PT_NOTA_F(marcha, 0, PT_MI4,  PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_SOL4, PT_COLCHEIA,     11, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_LA4,  PT_COLCHEIA,     11, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_SI4,  PT_COLCHEIA,     11, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_LA4,  PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_SOL4, PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_COLCHEIA,     10, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_RE4,  PT_COLCHEIA,      9, PT_ONDA_FM);
    PT_NOTA_F(marcha, 0, PT_MI4,  PT_MINIMA,       10, PT_ONDA_FM);

    PT_NOTA_F(marcha, 1, PT_SI3,  PT_COLCHEIA,     6, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_DO4,  PT_COLCHEIA,     6, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_RE4,  PT_MINIMA,       6, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_DO4,  PT_COLCHEIA,     5, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_SI3,  PT_COLCHEIA,     5, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_LA3,  PT_COLCHEIA,     5, PT_ONDA_FM);
    PT_NOTA_F(marcha, 1, PT_SI3,  PT_MINIMA,       6, PT_ONDA_FM);

    float bass_A[] = { PT_MI2, PT_SI2, PT_MI2, PT_SI2,
                       PT_LA2, PT_MI2, PT_LA2, PT_SI2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(marcha, 2, bass_A[b], PT_COLCHEIA, 11, PT_ONDA_FM);
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(marcha, 3, 180.0f,  PT_COLCHEIA,   11, PT_RUIDO_LFSR);
        PT_NOTA_F(marcha, 3, 1800.0f, PT_COLCHEIA, (b%2==1)?10:4, PT_RUIDO_BRANCO);
    }

    /* ── Padrão B: tema da masmorra (80 BPM) ── */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 80);

    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_SEMICOLCHEIA,10, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_SEMICOLCHEIA, 9, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_COLCHEIA,   10, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_FA5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   10, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_MINIMA,     10, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_COLCHEIA,    9, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_SI4,  PT_COLCHEIA,    9, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_DO5,  PT_MINIMA,     10, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_MI5,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_NOTA_F(tema, 0, PT_RE5,  PT_MINIMA_P,   10, PT_ONDA_FM);

    PT_NOTA_F(tema, 1, PT_DO5,  PT_MINIMA,      6, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SI4,  PT_MINIMA,      5, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_LA4,  PT_SEMIBREVE,   6, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SOL4, PT_MINIMA,      5, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_FAS4, PT_MINIMA,      5, PT_ONDA_FM);
    PT_NOTA_F(tema, 1, PT_SOL4, PT_MINIMA_P,    6, PT_ONDA_FM);

    float bass_B[] = { PT_LA2, PT_MI3, PT_LA2, PT_MI3,
                       PT_RE3, PT_LA3, PT_RE3, PT_SI3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(tema, 2, bass_B[b], PT_COLCHEIA, 10, PT_ONDA_FM);
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 3, 180.0f, PT_SEMICOLCHEIA, 11, PT_RUIDO_LFSR);
        PT_NOTA_F(tema, 3, 1800.0f,PT_SEMICOLCHEIA,(b%2==1)?9:3, PT_RUIDO_BRANCO);
        PT_NOTA_F(tema, 3, 6000.0f,PT_SEMICOLCHEIA, 3, PT_RUIDO_BRANCO);
        PT_NOTA_F(tema, 3, 6000.0f,PT_SEMICOLCHEIA, 3, PT_RUIDO_BRANCO);
    }

    /* ── Padrão C: corredor de armadilhas (100 BPM) ── */
    PT_Padrao corredor;
    pt_iniciar_padrao(&corredor, 100);

    PT_NOTA_F(corredor, 0, PT_LA5,  PT_SEMICOLCHEIA, 11, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_FA5,  PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_MI5,  PT_SEMICOLCHEIA, 11, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_RE5,  PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_MI5,  PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_FA5,  PT_SEMICOLCHEIA, 11, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_LA5,  PT_COLCHEIA,     11, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA, 10, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_LA5,  PT_SEMICOLCHEIA, 11, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SI5,  PT_COLCHEIA,     12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_DO6,  PT_SEMICOLCHEIA, 12, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_SI5,  PT_SEMICOLCHEIA, 11, PT_ONDA_FM);
    PT_NOTA_F(corredor, 0, PT_LA5,  PT_MINIMA,       11, PT_ONDA_FM);

    PT_NOTA_F(corredor, 1, PT_MI5, PT_COLCHEIA,  7, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_RE5, PT_COLCHEIA,  6, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_DO5, PT_COLCHEIA,  6, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_RE5, PT_MINIMA,    7, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_MI5, PT_COLCHEIA,  7, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_FAS5,PT_COLCHEIA,  8, PT_ONDA_FM);
    PT_NOTA_F(corredor, 1, PT_SOL5,PT_SEMIBREVE, 8, PT_ONDA_FM);

    float bass_C[] = { PT_LA2, PT_LA2, PT_MI3, PT_MI3,
                       PT_FA3, PT_FA3, PT_MI3, PT_RE3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(corredor, 2, bass_C[b], PT_COLCHEIA, 11, PT_ONDA_FM);
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(corredor, 3, 200.0f,  PT_SEMICOLCHEIA, 12, PT_RUIDO_LFSR);
        PT_NOTA_F(corredor, 3, 2000.0f, PT_SEMICOLCHEIA, 10, PT_RUIDO_BRANCO);
        PT_NOTA_F(corredor, 3, 6500.0f, PT_SEMICOLCHEIA,  4, PT_RUIDO_BRANCO);
        PT_NOTA_F(corredor, 3, 6500.0f, PT_SEMICOLCHEIA,  4, PT_RUIDO_BRANCO);
    }

    /* ── Padrão D: sala do boss (68 BPM) ── */
    PT_Padrao boss;
    pt_iniciar_padrao(&boss, 68);

    PT_NOTA_F(boss, 0, PT_MI4,  PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_PAUSA (boss, 0, PT_SEMICOLCHEIA);
    PT_NOTA_F(boss, 0, PT_MI4,  PT_SEMICOLCHEIA,11, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_SOL4, PT_COLCHEIA,   11, PT_ONDA_FM);
    PT_PAUSA (boss, 0, PT_SEMICOLCHEIA);
    PT_NOTA_F(boss, 0, PT_FA4,  PT_SEMICOLCHEIA,10, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_MI4,  PT_MINIMA,     10, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_RE4,  PT_COLCHEIA,    9, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_DO4,  PT_COLCHEIA,    9, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_SI3,  PT_COLCHEIA,    8, PT_ONDA_FM);
    PT_NOTA_F(boss, 0, PT_LA3,  PT_MINIMA_P,   10, PT_ONDA_FM);

    PT_NOTA_F(boss, 1, PT_DO4,  PT_MINIMA,      6, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_RE4,  PT_MINIMA,      6, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_DO4,  PT_MINIMA,      5, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_SI3,  PT_MINIMA,      5, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_LA3,  PT_MINIMA,      6, PT_ONDA_FM);
    PT_NOTA_F(boss, 1, PT_SOL3, PT_MINIMA_P,    5, PT_ONDA_FM);

    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(boss, 2, PT_MI2, PT_COLCHEIA, 12, PT_ONDA_FM);
        PT_NOTA_F(boss, 2, PT_MI2, PT_COLCHEIA, 11, PT_ONDA_FM);
        PT_NOTA_F(boss, 2, PT_LA2, PT_COLCHEIA, 11, PT_ONDA_FM);
        PT_NOTA_F(boss, 2, PT_SI2, PT_COLCHEIA, 10, PT_ONDA_FM);
    }
    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(boss, 3, 100.0f,  PT_COLCHEIA, 12, PT_RUIDO_LFSR);
        PT_NOTA_F(boss, 3, 1500.0f, PT_COLCHEIA,  9, PT_RUIDO_BRANCO);
        PT_NOTA_F(boss, 3, 100.0f,  PT_COLCHEIA, 11, PT_RUIDO_LFSR);
        PT_NOTA_F(boss, 3, 6000.0f, PT_COLCHEIA,  3, PT_RUIDO_BRANCO);
    }

    /* ── Montagem ── */
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
    printf("Dungeon Crawler  —  %.2fs\nArquivo: dungeon_crawler.wav\n",
           (float)frames / 44100.0f);
    pt_destruir_contexto(&ctx);
    return 0;
}
