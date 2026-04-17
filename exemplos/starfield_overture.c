/*
 * starfield_overture.c
 * "Starfield Overture" — estilo MS-DOS / Sierra OPL2
 *
 * Demonstra progressão de acordes automática (§55),
 * song builder (§50) e análise de padrão (§53).
 *
 * Compilar:  gcc starfield_overture.c -o starfield_overture -lm
 * Saida:     starfield_overture.wav
 */

#include "../partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.50f;

    /* Canal 0: trompete FM */
    pt_ativar_fm(&ctx, 0, 3.0f, 4.0f);
    pt_fm_envelope_modulador(&ctx, 0, 0.0f, 0.08f, 0.5f, 0.1f);
    ENV(&ctx, 0,  0.008f, 0.06f, 0.65f, 0.10f);
    PAN(&ctx, 0, -0.2f);

    /* Canal 1: strings via wavetable Fourier */
    static float tab_str[PT_TABELA_TAM];
    pt_tabela_fourier(tab_str, 6, 0);
    pt_aplicar_timbre(&ctx, 1, &PT_TIMBRE_CORDAS);
    pt_definir_tabela_onda(&ctx, 1, tab_str);

    /* Canal 2: baixo FM grave */
    pt_ativar_fm(&ctx, 2, 1.0f, 4.5f);
    pt_fm_envelope_modulador(&ctx, 2, 0.0f, 0.05f, 0.3f, 0.1f);
    ENV(&ctx, 2,  0.003f, 0.3f, 0.12f, 0.08f);

    /* Canal 3: percussão */
    ENV(&ctx, 3,  0.001f, 0.18f, 0.0f, 0.05f);

    /* ── Padrão A: fanfarra épica (58 BPM) ────────────────────────── */
    PT_Padrao abertura;
    pt_iniciar_padrao(&abertura, 58);

    PT_MEL_FM(abertura, 0,
        PT_LA4,CL,11,  PT_MI5,CL,11,  PT_LA5,MN,12,
        PT_SOL5,CL,10, PT_FAS5,CL,10, PT_MI5,MN,11,
        PT_FAS5,CL,11, PT_SOL5,CL,11, PT_LA5,SB,12
    );

    /* Strings — progressão de acordes arpejada (§55) */
    static const PT_Acorde prog_abertura[] = {
        { PT_LA4, PT_ACORDE_MAIOR, SB, 0 },
        { PT_MI4, PT_ACORDE_MAI7,  SB, 0 },
        { PT_RE4, PT_ACORDE_MAIOR, SB, 0 },
    };
    pt_adicionar_progressao(&abertura, 1, prog_abertura, 3, WT, 5);

    PT_Stream baixo_a = pt_stream(&abertura, 2, FM, 9);
    pt_s(&baixo_a,PT_LA2,SB); pt_s(&baixo_a,PT_MI3,SB); pt_s(&baixo_a,PT_LA2,SB);

    /* Tímpano */
    PT_Stream timp = pt_stream(&abertura, 3, NL, 11);
    pt_s(&timp,PT_SILENCIO,MN); pt_s_p(&timp,MN);
    pt_s_v(&timp,90.0f,CL,10); pt_s_v(&timp,90.0f,CL,11);
    pt_s_v(&timp,90.0f,SB,12);

    /* ── Padrão B: tema sideral contemplativo (70 BPM) ────────────── */
    PT_Padrao espaco;
    pt_iniciar_padrao(&espaco, 70);

    PT_MEL_FM(espaco, 0,
        PT_DO6,CLP,11, PT_SI5,CL,10,  PT_LA5,MN,11,
        PT_SOL5,CL, 9, PT_FAS5,CL, 9, PT_SOL5,MN,10,
        PT_LA5,CL,10,  PT_SI5,CL,11,  PT_DO6,MNP,11
    );

    /* Progressão de acordes arpejada ascendente para as strings */
    static const PT_Acorde prog_espaco[] = {
        { PT_LA4, PT_ACORDE_MAI7,  MN, 1 },
        { PT_FAS4,PT_ACORDE_MENOR, MN, 1 },
        { PT_RE4, PT_ACORDE_MAIOR, MN, 1 },
        { PT_MI4, PT_ACORDE_MAI7,  MN, 1 },
        { PT_LA4, PT_ACORDE_MAIOR, MN, 1 },
        { PT_FAS4,PT_ACORDE_MENOR, MN, 1 },
    };
    pt_adicionar_progressao(&espaco, 1, prog_espaco, 6, WT, 5);

    PT_OSTINATO(espaco, 2, FM, 16.0f,
        PT_LA2,MN, 8,  PT_RE3,MN, 8,
        PT_MI3,MN, 8,  PT_LA2,MN, 8
    );

    PT_OSTINATO(espaco, 3, NB, 16.0f,
        6500.0f,CL,2,  6500.0f,CL,2,
         90.0f, CL,9,  6500.0f,CL,2
    );

    /* ── Padrão C: travessia hiperespacial (96 BPM) ──────────────── */
    PT_Padrao hiper;
    pt_iniciar_padrao(&hiper, 96);

    PT_MEL_FM(hiper, 0,
        PT_LA5,SC,11,  PT_DO6,SC,11,  PT_MI6,CL,12,
        PT_RE6,SC,11,  PT_DO6,SC,11,  PT_SI5,CL,11,
        PT_LA5,CL,11,  PT_SOL5,CL,10, PT_FAS5,CL,10,
        PT_MI5,SC,10,  PT_FAS5,SC,10, PT_SOL5,CL,10,
        PT_LA5,CL,11,  PT_SI5,CL,11,  PT_DO6,MN,11
    );

    /* Arpejo 16x via progressão arpejada */
    static const PT_Acorde prog_hiper[] = {
        { PT_LA4, PT_ACORDE_MAIOR,  MN, 1 },
        { PT_RE4, PT_ACORDE_MAI7,   MN, 1 },
        { PT_DO4, PT_ACORDE_MAIOR,  MN, 2 },
        { PT_MI4, PT_ACORDE_MAI7,   MN, 1 },
        { PT_LA4, PT_ACORDE_MAIOR,  MN, 1 },
    };
    pt_adicionar_progressao(&hiper, 1, prog_hiper, 5, WT, 6);

    PT_OSTINATO(hiper, 2, FM, 8.0f,
        PT_LA2,CL,10,  PT_MI3,CL,10,
        PT_RE3,CL,10,  PT_DO3,CL,10
    );
    PT_OSTINATO(hiper, 3, NL, 8.0f,
        180.0f,CL,11,  1800.0f,SC,9,  7000.0f,SC,4
    );

    /* ── Padrão D: nebulosa tranquila (58 BPM) ───────────────────── */
    PT_Padrao nebulosa;
    pt_iniciar_padrao(&nebulosa, 58);

    PT_MEL_FM(nebulosa, 0,
        PT_FAS5,SB, 9,  PT_MI5,MN, 8,  PT_RE5,MN, 8,
        PT_DO5, SB, 8,  PT_SI4,MN, 7,  PT_DO5,MN, 8,
        PT_RE5, SB, 9,  PT_LA4,SB,10
    );

    /* Accordes em bloco — strings preenchem a harmonia */
    static const PT_Acorde prog_neb[] = {
        { PT_FAS4, PT_ACORDE_MENOR,  SB, 0 },
        { PT_LA4,  PT_ACORDE_MENOR,  SB, 0 },
        { PT_FAS4, PT_ACORDE_MAIOR6, SB, 0 },
        { PT_DOS5, PT_ACORDE_MAI7,   SB, 0 },
    };
    pt_adicionar_progressao(&nebulosa, 1, prog_neb, 4, WT, 4);

    PT_OSTINATO(nebulosa, 2, FM, 16.0f,
        PT_LA2,SB,8,  PT_RE3,SB,7,  PT_FAS3,SB,7,  PT_RE3,SB,7,
        PT_LA2,SB,8,  PT_MI3,SB,7,  PT_RE3, SB,7,  PT_LA2,SB,8
    );
    PT_OSTINATO(nebulosa, 3, NB, 16.0f, 7000.0f,MN,2);

    /* ── Análise (opcional — imprime info dos padrões) ──────────────  */
    printf("Analise dos padroes:\n");
    printf("  abertura canal 0: %d notas, %.1f batidas (%.1fs)\n",
           pt_contar_notas(&abertura, 0),
           pt_duracao_canal(&abertura, 0),
           pt_duracao_canal_s(&abertura, 0));
    printf("  hiper canal 0: nota mais alta %.0f Hz, mais baixa %.0f Hz\n",
           pt_nota_mais_alta(&hiper, 0),
           pt_nota_mais_baixa(&hiper, 0));

    /* ── Montagem ─────────────────────────────────────────────────── */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &abertura, 1);
    pt_adicionar_padrao_musica(&musica, &espaco,   2);
    pt_adicionar_padrao_musica(&musica, &hiper,    2);
    pt_adicionar_padrao_musica(&musica, &espaco,   1);
    pt_adicionar_padrao_musica(&musica, &nebulosa, 1);
    pt_adicionar_padrao_musica(&musica, &hiper,    1);
    pt_adicionar_padrao_musica(&musica, &abertura, 1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "starfield_overture.wav", 300.0f);
    printf("Starfield Overture — %.2fs\n", (float)frames / 44100.0f);
    pt_destruir_contexto(&ctx);
    return 0;
}
