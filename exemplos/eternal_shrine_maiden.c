/*
 * eternal_shrine_maiden.c
 * "Eternal Shrine Maiden" — estilo Touhou / ZUN (PC-98 TH01–TH05 era)
 *
 * Compilar:  gcc eternal_shrine_maiden.c -o eternal_shrine_maiden -lm
 * Executar:  ./eternal_shrine_maiden
 * Saida:     eternal_shrine_maiden.wav
 */

#include "partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.52f;   /* volume moderado */

    /* Canal 0: melodia — quadrada */
    pt_definir_envelope(&ctx, 0, 0.004f, 0.06f, 0.68f, 0.10f);
    pt_definir_pan(&ctx, 0, -0.2f);

    /* Canal 1: harmonia — triangular suave */
    pt_definir_envelope(&ctx, 1, 0.006f, 0.08f, 0.55f, 0.12f);
    pt_definir_pan(&ctx, 1,  0.2f);

    /* Canal 2: baixo — dente de serra curto */
    pt_definir_envelope(&ctx, 2, 0.001f, 0.22f, 0.08f, 0.06f);
    pt_definir_pan(&ctx, 2,  0.0f);

    /* Canal 3: percussão LFSR */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.06f, 0.0f, 0.01f);
    pt_definir_pan(&ctx, 3,  0.0f);

    /* ── Padrão A: introdução (Ré menor, 120 BPM) ── */
    PT_Padrao intro;
    pt_iniciar_padrao(&intro, 120);

    PT_NOTA(intro, 0, PT_RE5,  PT_COLCHEIA,     11);
    PT_NOTA(intro, 0, PT_DO5,  PT_SEMICOLCHEIA, 10);
    PT_NOTA(intro, 0, PT_RE5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(intro, 0, PT_FA5,  PT_COLCHEIA,     11);
    PT_NOTA(intro, 0, PT_MI5,  PT_SEMICOLCHEIA, 10);
    PT_NOTA(intro, 0, PT_RE5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(intro, 0, PT_DO5,  PT_COLCHEIA,     10);
    PT_NOTA(intro, 0, PT_LA4,  PT_COLCHEIA,     10);
    PT_NOTA(intro, 0, PT_SI4,  PT_SEMICOLCHEIA,  9);
    PT_NOTA(intro, 0, PT_DO5,  PT_SEMICOLCHEIA, 10);
    PT_NOTA(intro, 0, PT_RE5,  PT_MINIMA,       11);

    PT_NOTA_F(intro, 1, PT_LA4,  PT_COLCHEIA,     8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SOL4, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_DO5,  PT_COLCHEIA,     8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SI4,  PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SOL4, PT_COLCHEIA,     7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_FA4,  PT_COLCHEIA,     7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_SOL4, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(intro, 1, PT_LA4,  PT_MINIMA,       8, PT_ONDA_TRIANGULAR);

    for (int b = 0; b < 4; b++) {
        PT_NOTA_F(intro, 2, PT_RE3, PT_SEMICOLCHEIA, 10, PT_ONDA_DENTE_SERRA);
        PT_NOTA_F(intro, 2, PT_LA3, PT_SEMICOLCHEIA,  9, PT_ONDA_DENTE_SERRA);
        PT_NOTA_F(intro, 2, PT_FA3, PT_SEMICOLCHEIA,  9, PT_ONDA_DENTE_SERRA);
        PT_NOTA_F(intro, 2, PT_LA3, PT_SEMICOLCHEIA,  9, PT_ONDA_DENTE_SERRA);
    }
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(intro, 3, 6000.0f, PT_SEMICOLCHEIA, 5, PT_RUIDO_LFSR);
        PT_NOTA_F(intro, 3, 2500.0f, PT_SEMICOLCHEIA, 9, PT_RUIDO_BRANCO);
    }

    /* ── Padrão B: tema "Shrine Dance" (126 BPM) ── */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 126);

    PT_NOTA(tema, 0, PT_LA5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 10);
    PT_NOTA(tema, 0, PT_FA5,  PT_COLCHEIA,     10);
    PT_NOTA(tema, 0, PT_MI5,  PT_SEMICOLCHEIA, 10);
    PT_NOTA(tema, 0, PT_RE5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(tema, 0, PT_MI5,  PT_COLCHEIA,     10);
    PT_NOTA(tema, 0, PT_FA5,  PT_SEMICOLCHEIA, 10);
    PT_NOTA(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 10);
    PT_NOTA(tema, 0, PT_LA5,  PT_COLCHEIA,     11);
    PT_NOTA(tema, 0, PT_SOL5, PT_SEMICOLCHEIA, 10);
    PT_NOTA(tema, 0, PT_LA5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(tema, 0, PT_SI5,  PT_COLCHEIA,     11);
    PT_NOTA(tema, 0, PT_DO6,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(tema, 0, PT_SI5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(tema, 0, PT_LA5,  PT_MINIMA,       11);

    PT_NOTA_F(tema, 1, PT_MI5, PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_RE5, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_DO5, PT_COLCHEIA,     7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_SI4, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_LA4, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_SI4, PT_COLCHEIA,     7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_DO5, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_RE5, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_MI5, PT_COLCHEIA,     8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_RE5, PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_MI5, PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_FAS5,PT_COLCHEIA,     8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_SOL5,PT_SEMICOLCHEIA, 8, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_FAS5,PT_SEMICOLCHEIA, 7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(tema, 1, PT_MI5, PT_MINIMA,       8, PT_ONDA_TRIANGULAR);

    float baixo_B[] = { PT_RE3, PT_MI3, PT_FA3, PT_LA3,
                        PT_RE3, PT_MI3, PT_SOL3, PT_LA3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(tema, 2, baixo_B[b], PT_COLCHEIA, 10, PT_ONDA_DENTE_SERRA);
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(tema, 3, 7000.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
        PT_NOTA_F(tema, 3, (b%2==1)?2000.0f:7000.0f, PT_SEMICOLCHEIA,
                  (b%2==1)?11:4, PT_RUIDO_BRANCO);
    }

    /* ── Padrão C: variação intensa (130 BPM) ── */
    PT_Padrao variacao;
    pt_iniciar_padrao(&variacao, 130);

    PT_NOTA_EFX(variacao, 0, PT_SOL5, PT_COLCHEIA, 11, PT_ONDA_QUADRADA, PT_EFX_VIBRATO, 0.5f);
    PT_NOTA(variacao, 0, PT_FA5,  PT_COLCHEIA,     10);
    PT_NOTA(variacao, 0, PT_MI5,  PT_COLCHEIA,     10);
    PT_NOTA(variacao, 0, PT_RE5,  PT_SEMINIMA,     10);
    PT_NOTA(variacao, 0, PT_DO5,  PT_MINIMA,       11);

    PT_NOTA_F(variacao, 1, PT_MI5, PT_COLCHEIA,  7, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_RE5, PT_COLCHEIA,  6, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_DO5, PT_SEMINIMA,  6, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(variacao, 1, PT_LA4, PT_MINIMA,    7, PT_ONDA_TRIANGULAR);

    float baixo_C[] = { PT_LA2, PT_MI3, PT_LA2, PT_MI3,
                        PT_RE3, PT_LA3, PT_RE3, PT_MI3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(variacao, 2, baixo_C[b], PT_COLCHEIA, 10, PT_ONDA_DENTE_SERRA);
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(variacao, 3, 7000.0f, PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
        PT_NOTA_F(variacao, 3, (b%2==1)?2000.0f:7000.0f, PT_SEMICOLCHEIA,
                  (b%2==1)?11:4, PT_RUIDO_BRANCO);
    }

    /* ── Padrão D: ponte lírica (96 BPM) ── */
    PT_Padrao ponte;
    pt_iniciar_padrao(&ponte, 96);

    PT_NOTA(ponte, 0, PT_FA5,   PT_MINIMA,    9);
    PT_NOTA(ponte, 0, PT_MI5,   PT_COLCHEIA,  8);
    PT_NOTA(ponte, 0, PT_RE5,   PT_COLCHEIA,  8);
    PT_NOTA(ponte, 0, PT_DO5,   PT_MINIMA,    9);
    PT_NOTA(ponte, 0, PT_SI4,   PT_COLCHEIA,  8);
    PT_NOTA(ponte, 0, PT_DO5,   PT_COLCHEIA,  9);
    PT_NOTA(ponte, 0, PT_RE5,   PT_SEMIBREVE,10);

    PT_NOTA_F(ponte, 1, PT_DO5, PT_MINIMA,   6, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_SI4, PT_COLCHEIA, 5, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_LA4, PT_COLCHEIA, 5, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_SOL4,PT_MINIMA,   6, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_FAS4,PT_COLCHEIA, 5, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_SOL4,PT_COLCHEIA, 6, PT_ONDA_TRIANGULAR);
    PT_NOTA_F(ponte, 1, PT_LA4, PT_SEMIBREVE,7, PT_ONDA_TRIANGULAR);

    PT_NOTA_F(ponte, 2, PT_RE3, PT_MINIMA,   8, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(ponte, 2, PT_DO3, PT_MINIMA,   7, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(ponte, 2, PT_SI2, PT_MINIMA,   7, PT_ONDA_DENTE_SERRA);
    PT_NOTA_F(ponte, 2, PT_LA2, PT_SEMIBREVE,8, PT_ONDA_DENTE_SERRA);
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(ponte, 3, 6000.0f, PT_COLCHEIA, 3, PT_RUIDO_BRANCO);

    /* ── Montagem ── */
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
    printf("Eternal Shrine Maiden  —  %.2fs\nArquivo: eternal_shrine_maiden.wav\n",
           (float)frames / 44100.0f);
    pt_destruir_contexto(&ctx);
    return 0;
}
