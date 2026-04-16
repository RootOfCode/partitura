# Partitura — Framework mínimo de síntese de áudio em C

Partitura é um framework de síntese de áudio escrito em C distribuído como um único arquivo de cabeçalho. Ele oferece os componentes essenciais para geração de som, prototipação musical e experimentos de DSP sem dependências externas.

## Funcionalidades

- Osciladores com múltiplas formas de onda
- Envelopes ADSR
- Mixer polifônico com múltiplos canais
- Síntese FM
- Filtros (passa‑baixa, passa‑alta, passa‑banda)
- Síntese de cordas Karplus‑Strong
- Ring modulation
- Distorção
- Stereo widener (Haas / Mid‑Side)
- Metrônomo baseado em BPM
- Compressor sidechain
- Gravador para WAV
- Wah‑wah automático
- Presets de canal
- Utilitários de tempo e swing

## Estrutura do Projeto

```
partitura/
│
├── partitura.h
├── Makefile
└── exemplos/
    ├── dungeon_crawler.c
    ├── moonlit_forest_fairy.c
    ├── starfield_overture.c
    ├── iron_fortress_march.c
    ├── eternal_shrine_maiden.c
    └── phantom_palace_at_dusk.c
```

## Início Rápido

### 1. Incluir o header

```c
#define PARTITURA_IMPLEMENTATION
#include "partitura.h"
```

### 2. Exemplo mínimo

```c
#include "partitura.h"

int main() {
    PT_Contexto ctx;
    pt_inicializar(&ctx, 44100, 2);

    pt_tocar_nota(&ctx, 0, 440.0f, 12, PT_SENO);

    return 0;
}
```

## Compilando os Exemplos

Utilize o Makefile fornecido:

```
make
```

Os binários serão gerados em:

```
bin/
```

Executar um exemplo:

```
./bin/dungeon_crawler
```

## Requisitos

- Compilador compatível com C99
- GCC ou Clang recomendados
- Sistema POSIX (Linux ou macOS)
- Biblioteca matemática (-lm)

## Conceitos Principais

### Contexto

Estrutura principal do motor de áudio:

```c
PT_Contexto ctx;
pt_inicializar(&ctx, 44100, 8);
```

### Canais

Cada canal funciona como uma voz independente:

```c
pt_tocar_nota(&ctx, canal, freq, volume, PT_SERRA);
```

### Envelope

```c
pt_definir_envelope(&ctx, canal,
    attack,
    decay,
    sustain,
    release);
```

### Filtros

```c
pt_ativar_filtro(&ctx, canal, PT_FILTRO_LP, 1000.0f, 0.7f);
```

### Karplus-Strong

```c
pt_ks_tocar(&ctx, canal, 220.0f, 12, 0.5f);
```

### Metrônomo

```c
PT_Metronomo m;
pt_metronomo_iniciar(&m, 120.0f, 4, 0);
```

### Gravador

```c
pt_recorder_iniciar(10, 44100);
pt_recorder_gravar();
```

Exportar WAV:

```c
pt_recorder_exportar("output.wav", 44100);
```

## Efeitos Disponíveis

- Distorção
- Filtros LP / HP / BP
- Síntese FM
- Ring modulation
- Wah-wah
- Stereo widener
- Compressor sidechain
- Envelope ADSR
- Controle de pan

## Utilitários Rítmicos

```
pt_batidas_para_amostras()
pt_quantizar_tempo()
pt_fase_compasso()
pt_swing_dur()
```

## Casos de Uso

- Áudio para jogos
- Música procedural
- Síntese chiptune
- Gerador de efeitos sonoros
- Experimentos DSP
- Live coding musical
- Síntese embarcada

## Compilação Manual

Sem Makefile:

```
gcc exemplos/dungeon_crawler.c -o dungeon -lm
```

## Licença

Defina conforme desejado (exemplo: MIT).

## Autor

Bruno Dos Santos Umpierre

