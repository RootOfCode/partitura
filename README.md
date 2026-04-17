#  partitura.h

> Biblioteca de síntese de sons e músicas estilo retrô para jogos em C puro.
> Arquivo único, sem dependências externas, zero alocações obrigatórias.
> Inspirada em MS-DOS / PC-98 / Chip Music (AdLib, OPN, PSG).

---

## Compilação rápida

```bash
# Compila todos os exemplos
make

# Gera os arquivos .wav
make run

# Compila um exemplo específico
make dungeon_crawler

# Limpa tudo
make clean
```

Ou direto com gcc, sem Makefile:

```c
#include "partitura.h"
```
```bash
gcc minha_musica.c -o musica -lm
./musica
```

---

## Estrutura do projeto

```
partitura/
├── partitura.h          # A biblioteca inteira (arquivo único)
├── Makefile
├── README.md
├── exemplos/            # Músicas de exemplo (.c)
│   ├── eternal_shrine_maiden.c    — Touhou / PSG
│   ├── moonlit_forest_fairy.c     — Touhou / OPN mixolídio
│   ├── phantom_palace_at_dusk.c   — PC-98 / OPL3 FM
│   ├── dungeon_crawler.c          — MS-DOS / AdLib OPL2
│   ├── iron_fortress_march.c      — PC-88 / PSG+OPLL
│   └── starfield_overture.c       — MS-DOS / Sierra OPL2
├── obj/                 # Arquivos .o (gerados pelo make)
└── bin/                 # Binários executáveis (gerados pelo make)
```

---

## Visão geral das seções

| § | Nome | Descrição |
|---|------|-----------|
| §1 | Constantes | `PT_CANAIS_MAX`, `PT_TAXA_PADRAO`, etc. |
| §2 | Frequências | `PT_DO4`, `PT_LA4`... (Do2 a La7) |
| §3 | Durações | `PT_SEMIBREVE`, `PT_COLCHEIA`... + tercina/sextina |
| §4 | Enumerações | `PT_FormaOnda`, `PT_ModoFiltro`, `PT_TipoAcorde`... |
| §5 | Estruturas | `PT_Contexto`, `PT_Canal`, `PT_Padrao`, `PT_Musica`... |
| §6 | Funções internas | `pt__*` — não usar diretamente |
| §7 | Contexto | `pt_criar_contexto()`, `pt_destruir_contexto()` |
| §8 | Controle de canais | `pt_tocar_nota()`, `pt_parar_nota()`, `pt_mutar_canal()` |
| §9 | Envelope e efeitos | `pt_definir_envelope()`, vibrato, tremolo, portamento |
| §10 | Geração PCM | `pt_gerar_amostras()` estéreo/mono/float |
| §11 | Utilitários de notas | `pt_midi_para_hz()`, `pt_transpor()`, `pt_aplicar_cents()` |
| §12 | Efeitos prontos | `pt_efeito_explosao()`, `_laser()`, `_moeda()`... (25 efeitos) |
| §13 | Sequenciador | `PT_Padrao`, `PT_Musica`, `pt_atualizar()` |
| §14 | Consultas | `pt_canal_ativo()`, `pt_frequencia_atual()` |
| §15 | Macros padrão | `PT_NOTA()`, `PT_PAUSA()`, `PT_NOTA_F()`, `PT_NOTA_EFX()` |
| §16 | Filtro SVF | `pt_ativar_filtro()` LP/HP/BP/Notch por canal |
| §17 | Síntese FM | `pt_ativar_fm()` 2 operadores + 8 presets |
| §18 | Wavetable | `pt_tabela_fourier()`, `_corda()`, `_interpolar()` |
| §19 | Eco/Chorus/Comp. | Bus effects de delay e dinâmica |
| §20 | Automação | Keyframes lineares de volume e pitch por canal |
| §21 | Escalas e acordes | 13 escalas, 12 tipos de acorde, `pt_tocar_acorde()` |
| §22 | Drum machine | 32 passos × 8 trilhas, swing, `pt_drum_atualizar()` |
| §23 | Exportação WAV | `pt_salvar_wav()`, `pt_renderizar_musica_wav()` |
| §24 | Reverb | Schroeder 8 combs + 4 allpass |
| §25 | Equalizador | 3 bandas biquad (low-shelf, peak, high-shelf) |
| §26 | Distorção/OD | Suave/Dura/Fuzz/Cassete por canal |
| §27 | Ring Modulator | Por canal, varredura de frequência |
| §28 | Noise Gate | Bus global com attack/release configuráveis |
| §29 | Player PCM | Reproduz buffer int16 mono com interpolação e loop |
| §30 | Loader WAV | Lê `.wav` PCM 16-bit para buffer, mono/estéreo |
| §31 | Phaser/Flanger | Bus, LFO, realimentação configurável |
| §32 | LFO Global | 4 LFOs com 6 alvos (volume, pitch, pan, filtro, FM, reverb) |
| §33 | Arpeggiador | 5 modos (subida/descida/sobe-desce/aleatório/como-tocado) |
| §34 | Polyphony | Voice stealing LRU com `PT_GerenciadorVozes` |
| §35 | Transpor padrão | Semitons sem alterar dados, aplicado no playback |
| §36 | Pitch shifter | Por canal, ±12 semitons |
| §37 | Envelope de pitch | Chirp up/down, bumbo FM, tom sintético |
| §38 | Síntese aditiva | Até 8 parciais senoidais + presets órgão/clarinete |
| §39 | Karplus-Strong | Corda pinçada física com parâmetro de brilho |
| §40 | Metrônomo | Pulsos com acento, sincronismo de BPM |
| §41 | Presets de canal | `pt_salvar_preset()`, `pt_carregar_preset()`, `pt_copiar_canal()` |
| §42 | Wah-Wah | Auto-wah: envelope follower + filtro BP por canal |
| §43 | Stereo Widener | Haas (delay) e Mid-Side (M/S processing) |
| §44 | Recorder | Buffer circular de até 30s, exporta WAV |
| §45 | Utilitários de tempo | `pt_batidas_para_amostras()`, `pt_swing_dur()`, `pt_fase_compasso()` |
| §46 | Sidechain | Duck clássico: canal gatilho comprime canal alvo |
| **§47** | **Aliases curtos** | `SQ/TR/SA/FM`, `CL/SC/MN/SB`, `ENV/VIB/PAN/FLT` |
| **§48** | **PT_MELODIA** | Array de notas convertido em padrão com um macro |
| **§49** | **Timbres prontos** | `PT_TIMBRE_PSG`, `_SINO_FM`, `_FLAUTA`... + `pt_aplicar_timbre()` |
| **§50** | **Song Builder** | API encadeável `PT_SongBuilder` para montar músicas |
| **§51** | **Humanização** | Jitter de timing e velocity para som orgânico |
| **§52** | **Transformações** | `pt_inverter_melodia()`, `pt_retrograde_canal()`, `pt_escalar_duracoes()` |
| **§53** | **Análise** | `pt_contar_notas()`, `pt_nota_mais_alta/baixa()`, `pt_duracao_canal_s()` |
| **§54** | **PT_Stream** | `pt_s()`, `pt_s_v()`, `pt_s_p()`, `pt_s_e()`, `pt_s_rep()` |
| **§55** | **Progressões** | `PT_Acorde[]` + `pt_adicionar_progressao()` bloco ou arpejado |
| **§56** | **Fade** | `pt_fade_in_padrao()`, `pt_fade_out_padrao()` |
| **§57** | **Ostinato** | `PT_OSTINATO()` repete figura rítmica até N batidas |
| **§58** | **MIDI macros** | `MIDI_DO4`, `PT_HZ(60)` |
| **§59** | **Mix/Layer** | `pt_concatenar_canal()`, `pt_volume_relativo_canal()`, `pt_substituir_forma()` |
| **§60** | **Setups rápidos** | `pt_setup_touhou()`, `pt_setup_pc98_rpg()`, `pt_setup_msdos_acao()` |

---

## Uso básico — Olá, Dó4!

```c
#include "partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 2);
    ctx.volume_master = 0.7f;

    pt_definir_envelope(&ctx, 0, 0.005f, 0.1f, 0.7f, 0.1f);
    pt_tocar_nota(&ctx, 0, PT_DO4, 12, PT_ONDA_QUADRADA);

    int frames = pt_renderizar_wav(&ctx, "ola.wav", 2.0f);
    printf("%.2fs gerado\n", (float)frames / 44100.0f);

    pt_destruir_contexto(&ctx);
    return 0;
}
```

---

## Escrevendo músicas — API compacta

A forma mais ergonômica para escrever músicas usa as macros dos **§47–§60**:

```c
#include "partitura.h"

int main(void) {
    PT_Contexto ctx = pt_criar_contexto(44100, 4);
    ctx.volume_master = 0.55f;

    // Configura 4 canais estilo Touhou de uma vez
    pt_setup_touhou(&ctx);

    PT_Padrao A;
    pt_iniciar_padrao(&A, 120); // 120 BPM

    // Melodia via array — muito mais legível do que linha por linha
    PT_MEL(A, 0,
        PT_DO5,CL,12,  PT_RE5,CL,12,  PT_MI5,MN,12,
        PT_RE5,CL,11,  PT_DO5,MN,13
    );

    // Baixo via stream — sem repetir padrão/canal/forma
    PT_Stream b = pt_stream(&A, 2, SA, 10);
    pt_s(&b, PT_DO3, CL);
    pt_s(&b, PT_SOL3, CL);
    pt_s(&b, PT_DO3, MN);

    // Ostinato de hi-hat — preenche automaticamente as batidas
    PT_OSTINATO(A, 3, NB, 4.0f,
        6000.0f,SC,5,  2000.0f,SC,11
    );

    PT_Musica musica;
    pt_iniciar_musica(&musica);
    pt_adicionar_padrao_musica(&musica, &A, 4); // repete 4x

    int frames = pt_renderizar_musica_wav(&ctx, &musica, "musica.wav", 60.0f);
    printf("%.2fs\n", (float)frames / 44100.0f);

    pt_destruir_contexto(&ctx);
    return 0;
}
```

---

## Síntese FM

```c
// Ativa FM: razão do modulador e índice de modulação
pt_ativar_fm(&ctx, 0, 14.0f, 3.5f);   // piano elétrico
pt_ativar_fm(&ctx, 0, 1.0f,  2.0f);   // órgão
pt_ativar_fm(&ctx, 0, 3.5f,  5.0f);   // sino
pt_ativar_fm(&ctx, 0, 7.0f,  8.0f);   // gongo/percussão

// Envelope do modulador independente do carrier
pt_fm_envelope_modulador(&ctx, 0, atq, dec, sus, lib);
```

Ou use os presets prontos:
```c
pt_fm_preset_sino        (&ctx, canal, frequencia, volume);
pt_fm_preset_piano_eletrico(&ctx, canal, volume);
pt_fm_preset_orgao       (&ctx, canal, frequencia, volume);
pt_fm_preset_voz         (&ctx, canal, frequencia, volume);
pt_fm_preset_flute       (&ctx, canal, frequencia, volume);
```

---

## Bus effects (aplicados ao mix final)

```c
// Reverb Schroeder (tamanho 0.1–2.0, amortecimento, mix)
pt_ativar_reverb(&ctx, 0.5f, 0.4f, 0.15f);

// Equalizador 3 bandas (graves dB, Hz, médios dB, Hz, Q, agudos dB, Hz)
pt_ativar_eq(&ctx, +4.0f, 200.0f,  -2.0f, 1000.0f, 0.8f,  +3.0f, 8000.0f);

// Compressor (limiar, razão, atq ms, lib ms, makeup gain)
pt_ativar_compressor(&ctx, 0.3f, 4.0f, 5.0f, 100.0f, 1.2f);

// Eco/Delay (atraso s, realimentação, mix)
pt_ativar_eco(&ctx, 0.375f, 0.5f, 0.35f);

// Chorus (taxa Hz, profundidade ms, mix)
pt_ativar_chorus(&ctx, 1.2f, 12.0f, 0.4f);

// Phaser (taxa Hz, profundidade, centro, realimentação, mix)
pt_ativar_phaser(&ctx, 0.5f, 0.8f, 0.2f, 0.3f, 0.45f);

// Flanger
pt_ativar_flanger(&ctx, 0.3f, 0.8f, 0.6f, 0.4f);
```

---

## Progressão de acordes automática

```c
static const PT_Acorde prog[] = {
    { PT_LA3, PT_ACORDE_MENOR, PT_MINIMA,  0 },  // bloco
    { PT_FA3, PT_ACORDE_MAIOR, PT_MINIMA,  1 },  // arpejo ascendente
    { PT_SOL3,PT_ACORDE_DOM7,  PT_MINIMA,  2 },  // arpejo descendente
    { PT_LA3, PT_ACORDE_MENOR, PT_SEMIBREVE,0 },
};
pt_adicionar_progressao(&padrao, canal_base, prog, 4, PT_ONDA_TRIANGULAR, 10);
```

---

## Efeitos sonoros prontos

```c
pt_efeito_pulo       (&ctx, canal, volume);
pt_efeito_moeda      (&ctx, canal, volume);
pt_efeito_tiro       (&ctx, canal, volume);
pt_efeito_laser      (&ctx, canal, volume);
pt_efeito_explosao   (&ctx, canal, volume);
pt_efeito_dano       (&ctx, canal, volume);
pt_efeito_vitoria    (&ctx, canal, volume);
pt_efeito_power_up   (&ctx, canal, volume);
pt_efeito_game_over  (&ctx, canal, volume);
pt_efeito_sirene     (&ctx, canal, volume);
pt_efeito_portal     (&ctx, canal, volume);
pt_efeito_warp       (&ctx, canal, volume);
// ... e mais 13 efeitos
```

---

## Formas de onda disponíveis

| Constante | Alias | Descrição |
|-----------|-------|-----------|
| `PT_ONDA_QUADRADA` | `SQ` | Onda quadrada (PSG clássico) |
| `PT_ONDA_TRIANGULAR` | `TR` | Triangular suave (NES, flauta) |
| `PT_ONDA_DENTE_SERRA` | `SA` | Dente de serra (lead brilhante) |
| `PT_ONDA_DENTE_INV` | `SI` | Dente de serra invertido |
| `PT_ONDA_PULSO` | `PU` | Pulso de largura variável |
| `PT_ONDA_SENO` | `SN` | Senoidal pura |
| `PT_RUIDO_BRANCO` | `NB` | Ruído branco (prato, vento) |
| `PT_RUIDO_LFSR` | `NL` | LFSR de 15 bits (percussão PSG) |
| `PT_ONDA_FM` | `FM` | FM 2 operadores |
| `PT_ONDA_TABELA` | `WT` | Wavetable personalizada |
| `PT_ONDA_PCM` | `PC` | Reprodução de amostra PCM |

---

## Durações (aliases)

| Macro | Alias | Batidas |
|-------|-------|---------|
| `PT_SEMIBREVE` | `SB` | 4.000 |
| `PT_MINIMA` | `MN` | 2.000 |
| `PT_MINIMA_P` | `MNP` | 3.000 |
| `PT_SEMINIMA` | `SM` | 1.000 |
| `PT_COLCHEIA` | `CL` | 0.500 |
| `PT_COLCHEIA_P` | `CLP` | 0.750 |
| `PT_SEMICOLCHEIA` | `SC` | 0.250 |
| `PT_FUSA` | `FS` | 0.125 |
| `PT_TERCINA` | `TC` | 0.333 |
| `PT_SEXTINA` | `SX` | 0.167 |

---

## Integração com SDL2 / miniaudio

```c
// Callback SDL2
void audio_callback(void *userdata, uint8_t *stream, int len) {
    PT_Contexto *ctx = (PT_Contexto *)userdata;
    int n_frames = len / (2 * sizeof(int16_t));  // estéreo 16-bit
    pt_atualizar(ctx, (float)n_frames / ctx->taxa_amostra);
    pt_gerar_amostras(ctx, (int16_t *)stream, n_frames);
}

// miniaudio — use pt_gerar_amostras_float() para saída float32
```

---

## Licença

Domínio público — Zero-Clause BSD.
Faça o que quiser, sem restrições, sem necessidade de atribuição.
