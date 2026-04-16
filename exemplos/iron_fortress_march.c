/*
 * iron_fortress_march.c
 * "Iron Fortress March" — estilo MS-DOS / PC-88 / Yamaha PSG + FM
 *
 * Música de fase de fortaleza/castelo para jogo de ação — enérgica,
 * marcial e implacável. Mistura PSG (onda quadrada) com FM para
 * imitar o som híbrido do PC-88 VA e MSX2+ (OPLL + PSG AY-3-8910).
 *
 * Compilar:  gcc iron_fortress_march.c -o iron_fortress_march -lm
 * Executar:  ./iron_fortress_march
 * Saída:     iron_fortress_march.wav
 */

#include "partitura.h"

int main(void) {
    /* 4 canais: PSG lead | PSG harmonia | FM baixo | percussão */
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.82f;

    /* Canal 0: melodia PSG — quadrada agressiva */
    pt_definir_envelope(&ctx, 0, 0.002f, 0.0f, 1.0f, 0.04f);
    pt_definir_pan(&ctx, 0, -0.2f);

    /* Canal 1: harmonia PSG — pulso 25% */
    pt_definir_largura_pulso(&ctx, 1, 0.25f);
    pt_definir_envelope(&ctx, 1, 0.002f, 0.0f, 0.85f, 0.04f);
    pt_definir_pan(&ctx, 1, 0.2f);

    /* Canal 2: baixo FM — pesado e distorcido */
    pt_ativar_fm(&ctx, 2, 2.0f, 7.0f);
    pt_fm_envelope_modulador(&ctx, 2, 0.0f, 0.04f, 0.0f, 0.0f);
    pt_definir_envelope(&ctx, 2, 0.001f, 0.2f, 0.0f, 0.03f);
    pt_definir_pan(&ctx, 2, 0.0f);

    /* Canal 3: percussão SNare/HH PSG */
    pt_definir_envelope(&ctx, 3, 0.001f, 0.055f, 0.0f, 0.01f);
    pt_definir_pan(&ctx, 3, 0.0f);

    /* --- Padrão A: portão de aço — introdução (Mi menor, 148 BPM) */
    PT_Padrao portao;
    pt_iniciar_padrao(&portao, 148);

    /* Riff de abertura — motivo de 4 notas repetido */
    PT_NOTA(portao, 0, PT_MI5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(portao, 0, PT_SOL5, PT_SEMICOLCHEIA, 13);
    PT_NOTA(portao, 0, PT_FAS5, PT_COLCHEIA,     13);
    PT_NOTA(portao, 0, PT_MI5,  PT_COLCHEIA,     12);
    PT_NOTA(portao, 0, PT_MI5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(portao, 0, PT_RE5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(portao, 0, PT_MI5,  PT_COLCHEIA,     13);
    PT_NOTA(portao, 0, PT_SOL5, PT_COLCHEIA,     13);
    PT_NOTA(portao, 0, PT_LA5,  PT_SEMICOLCHEIA, 14);
    PT_NOTA(portao, 0, PT_SOL5, PT_SEMICOLCHEIA, 13);
    PT_NOTA(portao, 0, PT_FAS5, PT_COLCHEIA,     13);
    PT_NOTA(portao, 0, PT_MI5,  PT_MINIMA,       13);

    /* Harmonia quintas paralelas */
    PT_NOTA_F(portao, 1, PT_SI4,  PT_SEMICOLCHEIA, 9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_RE5,  PT_SEMICOLCHEIA, 9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_DOS5, PT_COLCHEIA,     9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_SI4,  PT_COLCHEIA,     9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_SI4,  PT_SEMICOLCHEIA, 9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_LA4,  PT_SEMICOLCHEIA, 8, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_SI4,  PT_COLCHEIA,     9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_RE5,  PT_COLCHEIA,     9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_MI5,  PT_SEMICOLCHEIA,10, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_RE5,  PT_SEMICOLCHEIA, 9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_DOS5, PT_COLCHEIA,     9, PT_ONDA_PULSO);
    PT_NOTA_F(portao, 1, PT_SI4,  PT_MINIMA,       9, PT_ONDA_PULSO);

    float bass_A[] = { PT_MI2, PT_SI2, PT_MI2, PT_SI2,
                       PT_LA2, PT_MI2, PT_RE3, PT_SI2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(portao, 2, bass_A[b], PT_COLCHEIA, 13, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(portao, 3, 200.0f,  PT_SEMICOLCHEIA, 13, PT_RUIDO_LFSR);
        PT_NOTA_F(portao, 3, 2000.0f, PT_SEMICOLCHEIA, (b%2==1)?12:4, PT_RUIDO_BRANCO);
        PT_NOTA_F(portao, 3, 6500.0f, PT_SEMICOLCHEIA,  4, PT_RUIDO_BRANCO);
        PT_NOTA_F(portao, 3, 6500.0f, PT_SEMICOLCHEIA,  4, PT_RUIDO_BRANCO);
    }

    /* --- Padrão B: corredor da fortaleza — tema principal ------- */
    PT_Padrao corredor;
    pt_iniciar_padrao(&corredor, 156);

    PT_NOTA(corredor, 0, PT_SI5,  PT_COLCHEIA,   13);
    PT_NOTA(corredor, 0, PT_LA5,  PT_SEMICOLCHEIA,12);
    PT_NOTA(corredor, 0, PT_SOL5, PT_SEMICOLCHEIA,12);
    PT_NOTA(corredor, 0, PT_FAS5, PT_COLCHEIA,   12);
    PT_NOTA(corredor, 0, PT_MI5,  PT_COLCHEIA,   11);
    PT_NOTA(corredor, 0, PT_FAS5, PT_COLCHEIA,   12);
    PT_NOTA(corredor, 0, PT_SOL5, PT_COLCHEIA,   12);
    PT_NOTA(corredor, 0, PT_LA5,  PT_COLCHEIA,   13);
    PT_NOTA(corredor, 0, PT_SI5,  PT_SEMICOLCHEIA,13);
    PT_NOTA(corredor, 0, PT_DO6,  PT_SEMICOLCHEIA,14);
    PT_NOTA(corredor, 0, PT_SI5,  PT_COLCHEIA,   13);
    PT_NOTA(corredor, 0, PT_LA5,  PT_COLCHEIA,   12);
    PT_NOTA(corredor, 0, PT_SOL5, PT_COLCHEIA,   12);
    PT_NOTA(corredor, 0, PT_FAS5, PT_COLCHEIA,   12);
    PT_NOTA(corredor, 0, PT_MI5,  PT_MINIMA,     13);

    PT_NOTA_F(corredor, 1, PT_FAS5,PT_COLCHEIA,   9, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_MI5, PT_SEMICOLCHEIA,8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_RE5, PT_SEMICOLCHEIA,8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_DOS5,PT_COLCHEIA,   8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_SI4, PT_COLCHEIA,   7, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_DOS5,PT_COLCHEIA,   8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_RE5, PT_COLCHEIA,   8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_MI5, PT_COLCHEIA,   9, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_FAS5,PT_COLCHEIA,   9, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_SOL5,PT_COLCHEIA,  10, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_FAS5,PT_COLCHEIA,   9, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_MI5, PT_COLCHEIA,   9, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_RE5, PT_COLCHEIA,   8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_DOS5,PT_COLCHEIA,   8, PT_ONDA_PULSO);
    PT_NOTA_F(corredor, 1, PT_SI4, PT_MINIMA,     9, PT_ONDA_PULSO);

    float bass_B[] = { PT_MI2, PT_FAS2, PT_SOL2, PT_LA2,
                       PT_SI2, PT_LA2,  PT_SOL2, PT_FAS2 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(corredor, 2, bass_B[b], PT_COLCHEIA, 13, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(corredor, 3, 220.0f, PT_SEMICOLCHEIA, 14, PT_RUIDO_LFSR);
        PT_NOTA_F(corredor, 3, 2200.0f,PT_SEMICOLCHEIA,(b%2==1)?12:5, PT_RUIDO_BRANCO);
        PT_NOTA_F(corredor, 3, 7000.0f,PT_SEMICOLCHEIA, 5, PT_RUIDO_BRANCO);
        PT_NOTA_F(corredor, 3, 7000.0f,PT_SEMICOLCHEIA, 4, PT_RUIDO_BRANCO);
    }

    /* --- Padrão C: sala das máquinas — industrial e repetitivo -- */
    PT_Padrao maquinas;
    pt_iniciar_padrao(&maquinas, 160);

    PT_NOTA(maquinas, 0, PT_MI5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(maquinas, 0, PT_MI5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(maquinas, 0, PT_SOL5, PT_SEMICOLCHEIA, 13);
    PT_NOTA(maquinas, 0, PT_MI5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(maquinas, 0, PT_LA5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(maquinas, 0, PT_MI5,  PT_SEMICOLCHEIA, 11);
    PT_NOTA(maquinas, 0, PT_SOL5, PT_SEMICOLCHEIA, 13);
    PT_NOTA(maquinas, 0, PT_FAS5, PT_SEMICOLCHEIA, 12);
    PT_NOTA(maquinas, 0, PT_MI5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(maquinas, 0, PT_RE5,  PT_SEMICOLCHEIA, 12);
    PT_NOTA(maquinas, 0, PT_MI5,  PT_SEMICOLCHEIA, 13);
    PT_NOTA(maquinas, 0, PT_FAS5, PT_SEMICOLCHEIA, 12);
    PT_NOTA(maquinas, 0, PT_SOL5, PT_COLCHEIA,     13);
    PT_NOTA(maquinas, 0, PT_LA5,  PT_COLCHEIA,     13);
    PT_NOTA(maquinas, 0, PT_SI5,  PT_MINIMA,       14);

    /* Contraponto contínuo */
    float harm_C[] = {
        PT_SI4, PT_MI4, PT_RE5, PT_SI4,
        PT_MI5, PT_SI4, PT_RE5, PT_DOS5,
        PT_SI4, PT_LA4, PT_SI4, PT_DOS5,
        PT_RE5, PT_MI5, PT_FAS5,PT_SOL5
    };
    for (int b = 0; b < 16; b++)
        PT_NOTA_F(maquinas, 1, harm_C[b], PT_SEMICOLCHEIA, 8, PT_ONDA_PULSO);

    float bass_C[] = { PT_MI2, PT_MI2, PT_LA2, PT_MI2,
                       PT_RE3, PT_RE3, PT_SI2, PT_MI3 };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(maquinas, 2, bass_C[b], PT_COLCHEIA, 14, PT_ONDA_FM);

    /* Percussão intensa industrial */
    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(maquinas, 3, 250.0f,  PT_SEMICOLCHEIA, 14, PT_RUIDO_LFSR);
        PT_NOTA_F(maquinas, 3, 250.0f,  PT_SEMICOLCHEIA, 13, PT_RUIDO_LFSR);
        PT_NOTA_F(maquinas, 3, 2500.0f, PT_SEMICOLCHEIA, 12, PT_RUIDO_BRANCO);
        PT_NOTA_F(maquinas, 3, 7000.0f, PT_SEMICOLCHEIA,  5, PT_RUIDO_BRANCO);
    }

    /* --- Padrão D: confronto final — clímax absoluto ------------ */
    PT_Padrao climax;
    pt_iniciar_padrao(&climax, 168);

    PT_NOTA(climax, 0, PT_DO6,  PT_COLCHEIA,   14);
    PT_NOTA(climax, 0, PT_SI5,  PT_SEMICOLCHEIA,13);
    PT_NOTA(climax, 0, PT_LA5,  PT_SEMICOLCHEIA,13);
    PT_NOTA(climax, 0, PT_SOL5, PT_COLCHEIA,   12);
    PT_NOTA(climax, 0, PT_FAS5, PT_COLCHEIA,   12);
    PT_NOTA(climax, 0, PT_SOL5, PT_COLCHEIA,   12);
    PT_NOTA(climax, 0, PT_LA5,  PT_COLCHEIA,   13);
    PT_NOTA(climax, 0, PT_SI5,  PT_COLCHEIA,   13);
    PT_NOTA(climax, 0, PT_DO6,  PT_SEMICOLCHEIA,14);
    PT_NOTA(climax, 0, PT_RE6,  PT_SEMICOLCHEIA,14);
    PT_NOTA(climax, 0, PT_MI6,  PT_MINIMA,     15);
    PT_NOTA(climax, 0, PT_RE6,  PT_COLCHEIA,   14);
    PT_NOTA(climax, 0, PT_DO6,  PT_COLCHEIA,   13);
    PT_NOTA(climax, 0, PT_SI5,  PT_MINIMA,     13);

    float harm_D[] = {
        PT_SOL5,PT_FAS5,PT_MI5, PT_RE5,
        PT_DOS5,PT_RE5, PT_MI5, PT_FAS5,
        PT_SOL5,PT_LA5, PT_SI5, PT_DO6,
        PT_LA5, PT_SOL5,PT_FAS5,PT_MI5
    };
    for (int b = 0; b < 16; b++)
        PT_NOTA_F(climax, 1, harm_D[b], PT_SEMICOLCHEIA, 10, PT_ONDA_PULSO);

    float bass_D[] = { PT_MI2, PT_LA2, PT_RE3, PT_SOL3,
                       PT_DO3, PT_LA2, PT_FAS2,PT_SI2  };
    for (int b = 0; b < 8; b++)
        PT_NOTA_F(climax, 2, bass_D[b], PT_COLCHEIA, 14, PT_ONDA_FM);

    for (int b = 0; b < 8; b++) {
        PT_NOTA_F(climax, 3, 280.0f,  PT_SEMICOLCHEIA, 14, PT_RUIDO_LFSR);
        PT_NOTA_F(climax, 3, 2500.0f, PT_SEMICOLCHEIA, 13, PT_RUIDO_BRANCO);
        PT_NOTA_F(climax, 3, 280.0f,  PT_SEMICOLCHEIA, 13, PT_RUIDO_LFSR);
        PT_NOTA_F(climax, 3, 7000.0f, PT_SEMICOLCHEIA,  6, PT_RUIDO_BRANCO);
    }

    /* --- Montagem ------------------------------------------------ */
    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &portao,   1);
    pt_adicionar_padrao_musica(&musica, &corredor, 2);
    pt_adicionar_padrao_musica(&musica, &maquinas, 2);
    pt_adicionar_padrao_musica(&musica, &corredor, 1);
    pt_adicionar_padrao_musica(&musica, &climax,   2);
    pt_adicionar_padrao_musica(&musica, &maquinas, 1);
    pt_adicionar_padrao_musica(&musica, &corredor, 1);

    int frames = pt_renderizar_musica_wav(
        &ctx, &musica, "iron_fortress_march.wav", 300.0f);

    printf("Iron Fortress March  —  %.2f s\n", (float)frames / 44100.0f);
    printf("Arquivo: iron_fortress_march.wav\n");

    pt_destruir_contexto(&ctx);
    return 0;
}
