/*
 * dungeon_crawler.c
 * "Dungeon Crawler" — estilo MS-DOS / AdLib OPL2
 *
 * Usa a nova API compacta:
 *   pt_setup_pc98_rpg() — configura timbres FM de uma vez
 *   PT_MEL_FM()         — melodia FM via array
 *   PT_Stream           — baixo e harmonia sem verbosidade
 *   pt_fade_in_padrao() — fade de volume dentro do padrão
 *
 * Compilar:  gcc dungeon_crawler.c -o dungeon_crawler -lm
 * Saida:     dungeon_crawler.wav
 */

#include "../partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.52f;
    pt_setup_pc98_rpg(&ctx);

    /* ── Padrão A: marcha de masmorra (Mi menor, 86 BPM) ─────────── */
    PT_Padrao marcha;
    pt_iniciar_padrao(&marcha, 86);

    PT_MEL_FM(marcha, 0,
        PT_MI4,SC,10,  PT_MI4,SC,10,  PT_SOL4,CL,11,  PT_LA4,CL,11,
        PT_SI4,CL,11,  PT_LA4,SC,10,  PT_SOL4,SC,10,  PT_MI4,CL,10,
        PT_RE4,CL, 9,  PT_MI4,MN,10
    );

    /* Harmonia strings */
    PT_Stream hs = pt_stream(&marcha, 1, FM, 6);
    pt_s(&hs,PT_SI3,CL); pt_s(&hs,PT_DO4,CL); pt_s(&hs,PT_RE4,MN);
    pt_s(&hs,PT_DO4,CL); pt_s(&hs,PT_SI3,CL); pt_s(&hs,PT_LA3,CL);
    pt_s(&hs,PT_SI3,MN);

    PT_OSTINATO(marcha, 2, FM, 8.0f,
        PT_MI2,CL,11,  PT_SI2,CL,11,  PT_MI2,CL,11,  PT_SI2,CL,11,
        PT_LA2,CL,11,  PT_MI2,CL,11,  PT_LA2,CL,11,  PT_SI2,CL,11
    );
    PT_OSTINATO(marcha, 3, NB, 8.0f,
        180.0f,CL,11,  1800.0f,CL,10
    );

    /* ── Padrão B: tema da masmorra (80 BPM) ─────────────────────── */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 80);

    PT_MEL_FM(tema, 0,
        PT_MI5,CL,11,  PT_RE5,SC,10,  PT_DO5,SC, 9,  PT_RE5,CL,10,
        PT_MI5,CL,11,  PT_FA5,CL,11,  PT_MI5,CL,10,  PT_RE5,MN,10,
        PT_DO5,CL, 9,  PT_SI4,CL, 9,  PT_DO5,MN,10,
        PT_MI5,CL,11,  PT_RE5,MNP,10
    );

    PT_Stream ht = pt_stream(&tema, 1, FM, 6);
    pt_s(&ht,PT_DO5,MN); pt_s(&ht,PT_SI4,MN); pt_s(&ht,PT_LA4,SB);
    pt_s(&ht,PT_SOL4,MN);pt_s(&ht,PT_FAS4,MN);pt_s(&ht,PT_SOL4,MNP);

    PT_OSTINATO(tema, 2, FM, 8.0f,
        PT_LA2,CL,10,  PT_MI3,CL,10,  PT_LA2,CL,10,  PT_MI3,CL,10,
        PT_RE3,CL,10,  PT_LA3,CL,10,  PT_RE3,CL,10,  PT_SI3,CL,10
    );
    PT_OSTINATO(tema, 3, NB, 8.0f,
        180.0f,SC,11,  1800.0f,SC,10,  6000.0f,SC,3,  6000.0f,SC,3
    );

    /* ── Padrão C: corredor (100 BPM) ─────────────────────────────── */
    PT_Padrao corredor;
    pt_iniciar_padrao(&corredor, 100);

    PT_MEL_FM(corredor, 0,
        PT_LA5,SC,11,  PT_SOL5,SC,10,  PT_FA5,SC,10,  PT_MI5,SC,11,
        PT_RE5,SC,10,  PT_MI5,SC,10,   PT_FA5,SC,11,  PT_SOL5,SC,10,
        PT_LA5,CL,11,  PT_SOL5,SC,10,  PT_LA5,SC,11,  PT_SI5,CL,12,
        PT_DO6,SC,12,  PT_SI5,SC,11,   PT_LA5,MN,11
    );

    PT_Stream hc = pt_stream(&corredor, 1, FM, 7);
    pt_s(&hc,PT_MI5,CL); pt_s(&hc,PT_RE5,CL); pt_s(&hc,PT_DO5,CL);
    pt_s(&hc,PT_RE5,MN); pt_s(&hc,PT_MI5,CL); pt_s(&hc,PT_FAS5,CL);
    pt_s(&hc,PT_SOL5,SB);

    PT_OSTINATO(corredor, 2, FM, 8.0f,
        PT_LA2,CL,11,  PT_LA2,CL,11,  PT_MI3,CL,11,  PT_MI3,CL,11,
        PT_FA3,CL,11,  PT_FA3,CL,11,  PT_MI3,CL,11,  PT_RE3,CL,11
    );
    PT_OSTINATO(corredor, 3, NB, 8.0f,
        200.0f,SC,12,  2000.0f,SC,10,  6500.0f,SC,4,  6500.0f,SC,4
    );

    /* ── Padrão D: sala do boss (68 BPM) ─────────────────────────── */
    PT_Padrao boss;
    pt_iniciar_padrao(&boss, 68);

    PT_Stream mb = pt_stream(&boss, 0, FM, 11);
    pt_s(&mb,PT_MI4,CL);  pt_s_p(&mb,SC);  pt_s(&mb,PT_MI4,SC);
    pt_s(&mb,PT_SOL4,CL); pt_s_p(&mb,SC);  pt_s(&mb,PT_FA4,SC);
    pt_s(&mb,PT_MI4,MN);
    pt_s(&mb,PT_RE4,CL); pt_s(&mb,PT_DO4,CL); pt_s(&mb,PT_SI3,CL);
    pt_s_v(&mb,PT_LA3,MNP,12);  /* nota final mais forte */

    PT_Stream hb = pt_stream(&boss, 1, FM, 6);
    pt_s(&hb,PT_DO4,MN); pt_s(&hb,PT_RE4,MN); pt_s(&hb,PT_DO4,MN);
    pt_s(&hb,PT_SI3,MN); pt_s(&hb,PT_LA3,MN); pt_s(&hb,PT_SOL3,MNP);

    PT_OSTINATO(boss, 2, FM, 8.0f,
        PT_MI2,CL,12,  PT_MI2,CL,11,  PT_LA2,CL,11,  PT_SI2,CL,10
    );
    PT_OSTINATO(boss, 3, NL, 8.0f,
        100.0f,CL,12,  1500.0f,CL,9,  100.0f,CL,11,  6000.0f,CL,3
    );

    /* Fade in nas dinâmicas do boss */
    pt_fade_in_padrao(&boss, 0, 7, 12);

    /* ── Montagem ─────────────────────────────────────────────────── */
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
    printf("Dungeon Crawler — %.2fs\n", (float)frames / 44100.0f);
    pt_destruir_contexto(&ctx);
    return 0;
}
