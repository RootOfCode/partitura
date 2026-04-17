/*
 * eternal_shrine_maiden.c
 * "Eternal Shrine Maiden" — estilo Touhou / ZUN (PC-98 TH01–TH05)
 *
 * Demonstra a nova API compacta:
 *   pt_setup_touhou()  — configura 4 canais de uma vez
 *   PT_MEL()           — escreve melodia como array
 *   PT_OSTINATO()      — repete figura rítmica
 *   PT_Stream + pt_s() — escreve baixo nota por nota sem verbosidade
 *
 * Compilar:  gcc eternal_shrine_maiden.c -o eternal_shrine_maiden -lm
 * Saida:     eternal_shrine_maiden.wav
 */

#include "../partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.52f;
    pt_setup_touhou(&ctx);   /* lead + harmonia + baixo + percussão */

    /* ── Padrão A: introdução (Ré menor, 120 BPM) ───────────────── */
    PT_Padrao intro;
    pt_iniciar_padrao(&intro, 120);

    /* Melodia via array: {nota, dur, vol, nota, dur, vol, ...} */
    PT_MEL(intro, 0,
        PT_RE5,SC,11,  PT_DO5,SC,10,  PT_RE5,SC,11,  PT_FA5,CL,11,
        PT_MI5,SC,10,  PT_RE5,SC,11,  PT_DO5,CL,10,  PT_LA4,CL,10,
        PT_SI4,SC, 9,  PT_DO5,SC,10,  PT_RE5,MN,11
    );

    /* Harmonia triangular via stream — mais limpo do que PT_NOTA_F repetido */
    PT_Stream h = pt_stream(&intro, 1, TR, 8);
    pt_s(&h, PT_LA4,CL); pt_s(&h, PT_SOL4,SC); pt_s(&h, PT_LA4,SC);
    pt_s(&h, PT_DO5,CL); pt_s(&h, PT_SI4,SC);  pt_s(&h, PT_LA4,SC);
    pt_s(&h, PT_SOL4,CL);pt_s(&h, PT_FA4,CL);
    pt_s(&h, PT_SOL4,SC);pt_s(&h, PT_LA4,SC);  pt_s(&h, PT_LA4,MN);

    /* Baixo: ostinato de 4 notas que se repete por 8 batidas */
    PT_OSTINATO(intro, 2, SA, 8.0f,
        PT_RE3,SC,10,  PT_LA3,SC,9,  PT_FA3,SC,9,  PT_LA3,SC,9
    );

    /* Percussão: ostinato HH + snare */
    PT_OSTINATO(intro, 3, NB, 8.0f,
        6000.0f,SC,5,  2500.0f,SC,9
    );

    /* ── Padrão B: tema "Shrine Dance" (126 BPM) ─────────────────── */
    PT_Padrao tema;
    pt_iniciar_padrao(&tema, 126);

    PT_MEL(tema, 0,
        PT_LA5,SC,11,  PT_SOL5,SC,10,  PT_FA5,CL,10,  PT_MI5,SC,10,
        PT_RE5,SC,11,  PT_MI5,CL,10,   PT_FA5,SC,10,  PT_SOL5,SC,10,
        PT_LA5,CL,11,  PT_SOL5,SC,10,  PT_LA5,SC,11,  PT_SI5,CL,11,
        PT_DO6,SC,12,  PT_SI5,SC,11,   PT_LA5,MN,11
    );

    PT_Stream h2 = pt_stream(&tema, 1, TR, 8);
    pt_s(&h2,PT_MI5,SC); pt_s(&h2,PT_RE5,SC); pt_s(&h2,PT_DO5,CL);
    pt_s(&h2,PT_SI4,SC); pt_s(&h2,PT_LA4,SC); pt_s(&h2,PT_SI4,CL);
    pt_s(&h2,PT_DO5,SC); pt_s(&h2,PT_RE5,SC); pt_s(&h2,PT_MI5,CL);
    pt_s(&h2,PT_RE5,SC); pt_s(&h2,PT_MI5,SC); pt_s(&h2,PT_FAS5,CL);
    pt_s(&h2,PT_SOL5,SC);pt_s(&h2,PT_FAS5,SC);pt_s(&h2,PT_MI5,MN);

    /* Baixo: 8 notas de colcheia via array */
    PT_OSTINATO(tema, 2, SA, 8.0f,
        PT_RE3,CL,10,  PT_MI3,CL,10,  PT_FA3,CL,10,  PT_LA3,CL,10,
        PT_RE3,CL,10,  PT_MI3,CL,10,  PT_SOL3,CL,10, PT_LA3,CL,10
    );

    PT_OSTINATO(tema, 3, NB, 8.0f,
        7000.0f,SC,4,  2000.0f,SC,11
    );

    /* ── Padrão C: variação com vibrato (130 BPM) ────────────────── */
    PT_Padrao variacao;
    pt_iniciar_padrao(&variacao, 130);

    /* Nota com efeito de vibrato usando NE() */
    NE(variacao, 0, PT_SOL5, CL, 11, SQ, PT_EFX_VIBRATO, 0.5f);
    PT_MEL(variacao, 0,
        PT_FA5,CL,10,  PT_MI5,CL,10,  PT_RE5,SM,10,  PT_DO5,MN,11
    );

    PT_Stream h3 = pt_stream(&variacao, 1, TR, 7);
    pt_s(&h3,PT_MI5,CL); pt_s(&h3,PT_RE5,CL); pt_s(&h3,PT_DO5,SM);
    pt_s(&h3,PT_LA4,MN);

    PT_OSTINATO(variacao, 2, SA, 8.0f,
        PT_LA2,CL,10,  PT_MI3,CL,10,  PT_LA2,CL,10,  PT_MI3,CL,10,
        PT_RE3,CL,10,  PT_LA3,CL,10,  PT_RE3,CL,10,  PT_MI3,CL,10
    );
    PT_OSTINATO(variacao, 3, NB, 8.0f,
        7000.0f,SC,4,  2000.0f,SC,11
    );

    /* ── Padrão D: ponte lírica (96 BPM) ─────────────────────────── */
    PT_Padrao ponte;
    pt_iniciar_padrao(&ponte, 96);

    PT_MEL(ponte, 0,
        PT_FA5,MN, 9,  PT_MI5,CL, 8,  PT_RE5,CL, 8,
        PT_DO5,MN, 9,  PT_SI4,CL, 8,  PT_DO5,CL, 9,  PT_RE5,SB,10
    );

    PT_Stream h4 = pt_stream(&ponte, 1, TR, 6);
    pt_s(&h4,PT_DO5,MN); pt_s(&h4,PT_SI4,CL); pt_s(&h4,PT_LA4,CL);
    pt_s(&h4,PT_SOL4,MN);pt_s(&h4,PT_FAS4,CL);pt_s(&h4,PT_SOL4,CL);
    pt_s(&h4,PT_LA4,SB);

    PT_Stream b4 = pt_stream(&ponte, 2, SA, 8);
    pt_s(&b4,PT_RE3,MN); pt_s(&b4,PT_DO3,MN); pt_s(&b4,PT_SI2,MN);
    pt_s(&b4,PT_LA2,SB);

    PT_OSTINATO(ponte, 3, NB, 8.0f,
        6000.0f,CL,3,  6000.0f,CL,3
    );

    /* ── Humanização: adiciona pequenas variações de volume ────────── */
    pt_humanizar_volume(&tema,     0.03f, 0x1A2B);
    pt_humanizar_volume(&variacao, 0.04f, 0x3C4D);

    /* ── Montagem ─────────────────────────────────────────────────── */
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
    printf("Eternal Shrine Maiden — %.2fs\n", (float)frames / 44100.0f);
    pt_destruir_contexto(&ctx);
    return 0;
}
