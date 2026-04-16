/*
 * ╔══════════════════════════════════════════════════════════════════════════╗
 * ║                           PARTITURA.H  v3.0                              ║
 * ║          Biblioteca de Sons e Músicas Estilo Retrô para Jogos            ║
 * ║                     (MS-DOS / PC-98 / Chip Music)                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║  §1  Constantes              §17 FM         §27 Ring Mod   §37 Env Pitch  ║
 * ║  §2  Frequências             §18 Wavetable  §28 Noise Gate §38 Sínt.Adit. ║
 * ║  §3  Durações                §19 Eco/Chorus §29 Player PCM §39 Karplus-S. ║
 * ║  §4  Enumerações             §20 Automação  §30 Loader WAV §40 Metrônomo  ║
 * ║  §5  Estruturas              §21 Escalas    §31 Phaser     §41 Presets    ║
 * ║  §6  Funções internas        §22 Drum Mach. §32 LFO global §42 Wah-Wah    ║
 * ║  §7  Contexto                §23 Export WAV §33 Arpejador  §43 Widener    ║
 * ║  §8  Controle de canais      §24 Reverb     §34 Polyphony  §44 Recorder   ║
 * ║  §9  Envelope e efeitos      §25 EQ 3 band. §35 Transpor   §45 Tempo/BPM  ║
 * ║  §10 Geração PCM             §26 Distorção  §36 PitchShift §46 Sidechain  ║
 * ║  §11 Utilitários de notas                                                 ║
 * ║  §12 Efeitos sonoros prontos                                              ║
 * ║  §13 Padrões e sequenciador                                               ║
 * ║  §14 Consultas de estado     v3.0 — Domínio público / Zero-Clause BSD    ║
 * ║  §15 Macros de conveniência  USO: #include "partitura.h"  -lm            ║
 * ║  §16 Filtro SVF por canal                                                ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║  USO  : #include "partitura.h"                                           ║
 * ║  DEPS : stdint stdlib string math stdio  (-lm)                           ║
 * ║  LICENÇA: MIT                                                            ║
 * ╚══════════════════════════════════════════════════════════════════════════╝
 */

#ifndef PARTITURA_H
#define PARTITURA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

/* ====================================================================
 *  §1  CONSTANTES GLOBAIS
 * ==================================================================== */

#define PT_CANAIS_MAX         8
#define PT_TAXA_PADRAO    44100
#define PT_VOLUME_MAX        15
#define PT_EVENTOS_MAX      512
#define PT_PADROES_MAX       64
#define PT_AUTO_KF_MAX        8
#define PT_TABELA_TAM       256
#define PT_DRUM_PASSOS_MAX   32
#define PT_DRUM_TRILHAS_MAX   8
#define PT_CHORUS_BUF      4410
#define PT_LFO_GLOBAL_MAX     4
#define PT_REVERB_COMBS       8
#define PT_REVERB_ALLPASS     4
#define PT_REVERB_BUF_MAX  3000
#define PT_PHASER_ETAPAS      6
#define PT_VOZES_MAX          8
#define PT_PI     3.14159265358979323846f


/* ====================================================================
 *  §2  FREQUÊNCIAS DAS NOTAS (Hz)
 *      PT_[NOTA][OITAVA]   s = sustenido (#)
 * ==================================================================== */

#define PT_DO2      65.41f
#define PT_DOS2     69.30f
#define PT_RE2      73.42f
#define PT_RES2     77.78f
#define PT_MI2      82.41f
#define PT_FA2      87.31f
#define PT_FAS2     92.50f
#define PT_SOL2     98.00f
#define PT_SOLS2   103.83f
#define PT_LA2     110.00f
#define PT_LAS2    116.54f
#define PT_SI2     123.47f
#define PT_DO3     130.81f
#define PT_DOS3    138.59f
#define PT_RE3     146.83f
#define PT_RES3    155.56f
#define PT_MI3     164.81f
#define PT_FA3     174.61f
#define PT_FAS3    185.00f
#define PT_SOL3    196.00f
#define PT_SOLS3   207.65f
#define PT_LA3     220.00f
#define PT_LAS3    233.08f
#define PT_SI3     246.94f
#define PT_DO4     261.63f
#define PT_DOS4    277.18f
#define PT_RE4     293.66f
#define PT_RES4    311.13f
#define PT_MI4     329.63f
#define PT_FA4     349.23f
#define PT_FAS4    369.99f
#define PT_SOL4    392.00f
#define PT_SOLS4   415.30f
#define PT_LA4     440.00f
#define PT_LAS4    466.16f
#define PT_SI4     493.88f
#define PT_DO5     523.25f
#define PT_DOS5    554.37f
#define PT_RE5     587.33f
#define PT_RES5    622.25f
#define PT_MI5     659.25f
#define PT_FA5     698.46f
#define PT_FAS5    739.99f
#define PT_SOL5    783.99f
#define PT_SOLS5   830.61f
#define PT_LA5     880.00f
#define PT_LAS5    932.33f
#define PT_SI5     987.77f
#define PT_DO6    1046.50f
#define PT_DOS6   1108.73f
#define PT_RE6    1174.66f
#define PT_RES6   1244.51f
#define PT_MI6    1318.51f
#define PT_FA6    1396.91f
#define PT_FAS6   1479.98f
#define PT_SOL6   1567.98f
#define PT_SOLS6  1661.22f
#define PT_LA6    1760.00f
#define PT_LAS6   1864.66f
#define PT_SI6    1975.53f
#define PT_DO7    2093.00f
#define PT_LA7    3520.00f
#define PT_SILENCIO  0.0f

/* Números MIDI convenientes */
#define PT_MIDI_DO4   60
#define PT_MIDI_LA4   69
#define PT_MIDI_DO5   72

/* ====================================================================
 *  §3  DURAÇÕES DE FIGURA MUSICAL (em batidas)
 *      1 batida = 60 / BPM  segundos
 * ==================================================================== */

#define PT_SEMIBREVE       4.000f
#define PT_MINIMA          2.000f
#define PT_MINIMA_P        3.000f
#define PT_SEMINIMA        1.000f
#define PT_SEMINIMA_P      1.500f
#define PT_COLCHEIA        0.500f
#define PT_COLCHEIA_P      0.750f
#define PT_SEMICOLCHEIA    0.250f
#define PT_SEMICOLCHEIA_P  0.375f
#define PT_FUSA            0.125f
#define PT_SEMIFUSA        0.0625f
#define PT_TERCINA         0.333f
#define PT_SEXTINA         0.167f

/* ====================================================================
 *  §4  ENUMERAÇÕES
 * ==================================================================== */

typedef enum {
    PT_ONDA_QUADRADA    = 0,
    PT_ONDA_TRIANGULAR  = 1,
    PT_ONDA_DENTE_SERRA = 2,
    PT_ONDA_DENTE_INV   = 3,
    PT_ONDA_PULSO       = 4,
    PT_ONDA_SENO        = 5,
    PT_RUIDO_BRANCO     = 6,
    PT_RUIDO_LFSR       = 7,
    PT_ONDA_FM          = 8,
    PT_ONDA_TABELA      = 9,
    PT_ONDA_PCM         = 10,
} PT_FormaOnda;

typedef enum {
    PT_ENV_INATIVO=0, PT_ENV_ATAQUE=1,
    PT_ENV_DECAIMENTO=2, PT_ENV_SUSTENTACAO=3, PT_ENV_LIBERACAO=4,
} PT_FaseEnvelope;

typedef enum {
    PT_EFX_NENHUM=0x00, PT_EFX_PORTAMENTO=0x01, PT_EFX_VIBRATO=0x02,
    PT_EFX_TREMOLO=0x03, PT_EFX_VOLUME=0x04, PT_EFX_PAN=0x05,
    PT_EFX_PULSO=0x06, PT_EFX_FILTRO_CUTOFF=0x07, PT_EFX_FILTRO_RES=0x08,
    PT_EFX_FM_INDICE=0x09, PT_EFX_DISTORCAO=0x0A, PT_EFX_RING_MOD=0x0B,
    PT_EFX_PITCH_SHIFT=0x0C, PT_EFX_PARAR=0xFF,
} PT_CodigoEfeito;

typedef enum { PT_FILTRO_LP=0, PT_FILTRO_HP=1, PT_FILTRO_BP=2, PT_FILTRO_NOTCH=3 } PT_ModoFiltro;

typedef enum {
    PT_DISTORCAO_SUAVE=0, PT_DISTORCAO_DURA=1,
    PT_DISTORCAO_FUZZ=2,  PT_DISTORCAO_CASSETE=3,
} PT_TipoDistorcao;

typedef enum {
    PT_LFO_SENO=0, PT_LFO_QUADRADO=1, PT_LFO_TRIANGULAR=2,
    PT_LFO_SUBIDA=3, PT_LFO_ALEATORIO=4,
} PT_FormaLFO;

typedef enum {
    PT_LFO_ALVO_VOLUME=0, PT_LFO_ALVO_PITCH=1, PT_LFO_ALVO_PAN=2,
    PT_LFO_ALVO_FILTRO=3, PT_LFO_ALVO_FM_IDX=4, PT_LFO_ALVO_REVERB=5,
} PT_AlvoLFO;

typedef enum {
    PT_ESCALA_MAIOR=0, PT_ESCALA_MENOR_NATURAL=1, PT_ESCALA_MENOR_HARMONICA=2,
    PT_ESCALA_PENTATONICA_MAI=3, PT_ESCALA_PENTATONICA_MEN=4, PT_ESCALA_BLUES=5,
    PT_ESCALA_DORICA=6, PT_ESCALA_FRIGIA=7, PT_ESCALA_LIDIA=8,
    PT_ESCALA_MIXOLIDIA=9, PT_ESCALA_LOCRIA=10, PT_ESCALA_CROMATICA=11,
    PT_ESCALA_TONS_INTEIROS=12,
} PT_TipoEscala;

typedef enum {
    PT_ACORDE_MAIOR=0, PT_ACORDE_MENOR=1, PT_ACORDE_DIMINUTO=2,
    PT_ACORDE_AUMENTADO=3, PT_ACORDE_DOM7=4, PT_ACORDE_MAI7=5,
    PT_ACORDE_MEN7=6, PT_ACORDE_SUS2=7, PT_ACORDE_SUS4=8,
    PT_ACORDE_ADD9=9, PT_ACORDE_MAIOR6=10, PT_ACORDE_MENOR6=11,
} PT_TipoAcorde;

typedef enum {
    PT_ARPEJO_SUBIDA=0, PT_ARPEJO_DESCIDA=1, PT_ARPEJO_SOBE_DESCE=2,
    PT_ARPEJO_ALEATORIO=3, PT_ARPEJO_COMO_TOCADO=4,
} PT_ModoArpejo;


/* ====================================================================
 *  §5  ESTRUTURAS
 * ==================================================================== */

typedef struct { float ataque, decaimento, sustentacao, liberacao; } PT_Envelope;
typedef struct {
    float vibrato_profundidade, vibrato_velocidade;
    float tremolo_profundidade, tremolo_velocidade;
    float arpejo[3], arpejo_velocidade;
    float portamento_tempo, portamento_alvo;
    float largura_pulso;
    int   bitcrush;
} PT_Efeitos;
typedef struct { int ativo; PT_ModoFiltro modo; float cutoff, ressonancia, v_lp, v_bp; } PT_Filtro;
typedef struct {
    int ativo; float razao, indice, fase_mod;
    float ataque_m,decaimento_m,sustentacao_m,liberacao_m,env_m,env_m_rel;
    PT_FaseEnvelope fase_env_m;
} PT_FM;
typedef struct {
    float tempos[PT_AUTO_KF_MAX], valores[PT_AUTO_KF_MAX];
    int num_kf; float t_atual; int ativo, repetir;
} PT_Automacao;
typedef struct {
    int ativo; PT_TipoDistorcao tipo;
    float drive, saida, estado;
} PT_Distorcao;
typedef struct { int ativo; float freq, fase, mix; } PT_RingMod;
typedef struct { int ativo; float semitons; float buf[2048]; int cabeca; float fase_leitura; } PT_PitchShift;
typedef struct {
    const int16_t *dados; int num_amostras, taxa;
    float pos; int em_loop, ativo;
} PT_PlayerPCM;

typedef struct {
    int ativo, mudo;
    PT_FormaOnda  forma_onda;
    float frequencia, volume, pan;
    PT_Envelope   envelope;
    PT_Efeitos    efeitos;
    PT_Filtro     filtro;
    PT_FM         fm;
    PT_Distorcao  distorcao;
    PT_RingMod    ring_mod;
    PT_PitchShift pitch_shift;
    PT_PlayerPCM  pcm;
    float        *tabela_onda;
    PT_Automacao  auto_volume, auto_pitch;
    float fase, freq_atual, fase_lfo, fase_arpejo, ruido_fase, ruido_amostra;
    uint32_t lfsr;
    PT_FaseEnvelope fase_env;
    float env_nivel, env_nivel_rel;
} PT_Canal;

typedef struct {
    float frequencia, duracao;
    int8_t volume; PT_FormaOnda forma_onda; uint8_t efeito; float param;
} PT_Evento;

typedef struct {
    PT_Evento eventos[PT_CANAIS_MAX][PT_EVENTOS_MAX];
    int num_eventos[PT_CANAIS_MAX];
    float bpm; int semitons_transpor;
} PT_Padrao;

typedef struct {
    PT_Padrao *padroes[PT_PADROES_MAX];
    int num_padroes, sequencia[PT_PADROES_MAX*4], tam_sequencia, em_loop;
} PT_Musica;

typedef struct { int ativo; float *buf_l,*buf_r; int capacidade,cabeca; float atraso_s,realimentacao,mix; } PT_Eco;
typedef struct { int ativo; float buf_l[PT_CHORUS_BUF],buf_r[PT_CHORUS_BUF]; int cabeca; float taxa,prof_ms,mix,fase_lfo; } PT_Chorus;
typedef struct { int ativo; float limiar,razao,coef_ataque,coef_liberacao,ganho_atual,ganho_makeup; } PT_Compressor;

typedef struct {
    int ativo;
    float buf_comb[PT_REVERB_COMBS][PT_REVERB_BUF_MAX];
    int tam_comb[PT_REVERB_COMBS], cab_comb[PT_REVERB_COMBS];
    float filt_comb[PT_REVERB_COMBS];
    float buf_ap[PT_REVERB_ALLPASS][PT_REVERB_BUF_MAX/2];
    int tam_ap[PT_REVERB_ALLPASS], cab_ap[PT_REVERB_ALLPASS];
    float realimentacao_comb, amortecimento, mix;
} PT_Reverb;

typedef struct {
    int ativo;
    float ls_ganho,ls_freq; float ls_x1,ls_x2,ls_y1,ls_y2,ls_b0,ls_b1,ls_b2,ls_a1,ls_a2;
    float mp_ganho,mp_freq,mp_q; float mp_x1,mp_x2,mp_y1,mp_y2,mp_b0,mp_b1,mp_b2,mp_a1,mp_a2;
    float hs_ganho,hs_freq; float hs_x1,hs_x2,hs_y1,hs_y2,hs_b0,hs_b1,hs_b2,hs_a1,hs_a2;
} PT_Equalizador;

typedef struct {
    int ativo,modo_flanger; float buf[2][PT_PHASER_ETAPAS];
    float fase_lfo,taxa,profundidade,centro,realimentacao,mix;
    float buf_fl[2][4410]; int cab_fl;
} PT_Phaser;

typedef struct { int ativo; float limiar,coef_ataque,coef_liberacao,ganho_atual; } PT_NoiseGate;

typedef struct {
    int ativo; PT_FormaLFO forma; float taxa,fase,profundidade,offset;
    int canal_alvo; PT_AlvoLFO alvo; uint32_t lfsr; float amostra_atual;
} PT_LFOGlobal;

typedef struct {
    uint8_t  passos[PT_DRUM_TRILHAS_MAX][PT_DRUM_PASSOS_MAX];
    float    frequencias[PT_DRUM_TRILHAS_MAX];
    PT_FormaOnda ondas[PT_DRUM_TRILHAS_MAX];
    int      canal_base, num_trilhas, num_passos;
    float    bpm, swing;
    int      passo_atual; float tempo_acc; int reproduzindo;
} PT_PadraoPercussao;

typedef struct {
    int ativo; float notas[12]; int num_notas;
    PT_ModoArpejo modo; float bpm,duracao; int oitavas,canal,volume;
    PT_FormaOnda forma; int indice,direcao; float tempo_acc; int em_topo;
} PT_Arpeggiador;

typedef struct {
    int canal_base,num_vozes;
    float frequencias[PT_VOZES_MAX];
    int ativa[PT_VOZES_MAX],ordem[PT_VOZES_MAX],contador;
} PT_GerenciadorVozes;

typedef struct {
    PT_Canal     canais[PT_CANAIS_MAX];
    int          num_canais; float taxa_amostra,volume_master; int solo_canal;
    PT_Eco       eco; PT_Chorus chorus; PT_Compressor compressor;
    PT_Reverb    reverb; PT_Equalizador eq; PT_Phaser phaser; PT_NoiseGate noise_gate;
    PT_LFOGlobal lfos[PT_LFO_GLOBAL_MAX];
    PT_Musica *musica; int padrao_seq,evento[PT_CANAIS_MAX]; float tempo_ev[PT_CANAIS_MAX];
    int reproduzindo,pausado;
} PT_Contexto;


/* ====================================================================
 *  §6  FUNÇÕES INTERNAS (prefixo pt__ — não usar diretamente)
 * ==================================================================== */

static float pt__clampf(float v,float lo,float hi){return v<lo?lo:(v>hi?hi:v);}

static float pt__interpolar_auto(PT_Automacao *a) {
    if (!a->num_kf) return 1.0f;
    float t=a->t_atual;
    if (a->repetir&&a->num_kf>1){float tf=a->tempos[a->num_kf-1];if(tf>0)t=fmodf(t,tf);}
    if (t<=a->tempos[0]) return a->valores[0];
    if (t>=a->tempos[a->num_kf-1]) return a->valores[a->num_kf-1];
    for(int i=0;i<a->num_kf-1;i++){
        if(t>=a->tempos[i]&&t<a->tempos[i+1]){
            float dt=a->tempos[i+1]-a->tempos[i];
            float fr=(dt>0)?(t-a->tempos[i])/dt:0;
            return a->valores[i]+fr*(a->valores[i+1]-a->valores[i]);
        }
    }
    return a->valores[a->num_kf-1];
}

static float pt__env_fm(PT_FM *fm,float taxa){
    switch(fm->fase_env_m){
        case PT_ENV_INATIVO: fm->env_m=0; break;
        case PT_ENV_ATAQUE:
            if(fm->ataque_m>0){fm->env_m+=1.0f/(fm->ataque_m*taxa);if(fm->env_m>=1){fm->env_m=1;fm->fase_env_m=PT_ENV_DECAIMENTO;}}
            else{fm->env_m=1;fm->fase_env_m=PT_ENV_DECAIMENTO;} break;
        case PT_ENV_DECAIMENTO:{float s=pt__clampf(fm->sustentacao_m,0,1);
            if(fm->decaimento_m>0){fm->env_m-=(1-s)/(fm->decaimento_m*taxa);if(fm->env_m<=s){fm->env_m=s;fm->fase_env_m=PT_ENV_SUSTENTACAO;}}
            else{fm->env_m=s;fm->fase_env_m=PT_ENV_SUSTENTACAO;} break;}
        case PT_ENV_SUSTENTACAO: fm->env_m=pt__clampf(fm->sustentacao_m,0,1); break;
        case PT_ENV_LIBERACAO:
            if(fm->liberacao_m>0){fm->env_m-=fm->env_m_rel/(fm->liberacao_m*taxa);if(fm->env_m<=0){fm->env_m=0;fm->fase_env_m=PT_ENV_INATIVO;}}
            else{fm->env_m=0;fm->fase_env_m=PT_ENV_INATIVO;} break;
    }
    return fm->env_m;
}

static float pt__distorcer(PT_Distorcao *d,float x){
    float y=x*d->drive;
    switch(d->tipo){
        case PT_DISTORCAO_SUAVE:   y=tanhf(y); break;
        case PT_DISTORCAO_DURA:    y=pt__clampf(y,-1,1); break;
        case PT_DISTORCAO_FUZZ:    y=(fabsf(x)<0.001f)?0:((x>=0)?1:-1); break;
        case PT_DISTORCAO_CASSETE: {float s=tanhf(y*0.7f);d->estado+=(x-d->estado)*0.001f;y=s+d->estado*0.05f;break;}
    }
    return y*d->saida;
}

static float pt__biquad(float x,float *x1,float *x2,float *y1,float *y2,
                        float b0,float b1,float b2,float a1,float a2){
    float y=b0*x+b1*(*x1)+b2*(*x2)-a1*(*y1)-a2*(*y2);
    *x2=*x1;*x1=x;*y2=*y1;*y1=y; return y;
}

static void pt__calc_low_shelf(float *b0,float *b1,float *b2,float *a1,float *a2,float g,float f,float sr){
    float A=powf(10,g/40.f),w0=2*PT_PI*f/sr,cs=cosf(w0),sn=sinf(w0);
    float al=sn/2*sqrtf((A+1/A)*(1/0.707f-1)+2);
    float ap1=A+1,am1=A-1,d=(ap1+am1*cs+2*sqrtf(A)*al);
    *b0=A*(ap1-am1*cs+2*sqrtf(A)*al)/d; *b1=2*A*(am1-(A+1)*cs)/d;
    *b2=A*(ap1-am1*cs-2*sqrtf(A)*al)/d; *a1=-2*(am1+(A+1)*cs)/d;
    *a2=(ap1+am1*cs-2*sqrtf(A)*al)/d;
}
static void pt__calc_high_shelf(float *b0,float *b1,float *b2,float *a1,float *a2,float g,float f,float sr){
    float A=powf(10,g/40.f),w0=2*PT_PI*f/sr,cs=cosf(w0),sn=sinf(w0);
    float al=sn/2*sqrtf((A+1/A)*(1/0.707f-1)+2);
    float ap1=A+1,am1=A-1,d=(ap1-am1*cs+2*sqrtf(A)*al);
    *b0=A*(ap1+am1*cs+2*sqrtf(A)*al)/d; *b1=-2*A*(am1+(A+1)*cs)/d;
    *b2=A*(ap1+am1*cs-2*sqrtf(A)*al)/d; *a1=2*(am1-(A+1)*cs)/d;
    *a2=(ap1-am1*cs-2*sqrtf(A)*al)/d;
}
static void pt__calc_peak(float *b0,float *b1,float *b2,float *a1,float *a2,float g,float f,float q,float sr){
    float A=powf(10,g/40.f),w0=2*PT_PI*f/sr,cs=cosf(w0),al=sinf(w0)/(2*q);
    float a0=1+al/A;
    *b0=(1+al*A)/a0; *b1=-2*cs/a0; *b2=(1-al*A)/a0;
    *a1=-2*cs/a0;    *a2=(1-al/A)/a0;
}

static float pt__lfo_tick(PT_LFOGlobal *l){
    float v=0;
    switch(l->forma){
        case PT_LFO_SENO:       v=sinf(l->fase*2*PT_PI); break;
        case PT_LFO_QUADRADO:   v=(l->fase<0.5f)?1:-1; break;
        case PT_LFO_TRIANGULAR: v=(l->fase<0.5f)?(4*l->fase-1):(3-4*l->fase); break;
        case PT_LFO_SUBIDA:     v=2*l->fase-1; break;
        case PT_LFO_ALEATORIO:
            l->lfsr=l->lfsr*1664525u+1013904223u;
            l->amostra_atual=((float)(l->lfsr>>16)/32767.5f)-1; v=l->amostra_atual; break;
    }
    return l->offset+v*l->profundidade;
}

static void pt__processar_lfos(PT_Contexto *ctx){
    for(int li=0;li<PT_LFO_GLOBAL_MAX;li++){
        PT_LFOGlobal *l=&ctx->lfos[li]; if(!l->ativo) continue;
        float val=pt__lfo_tick(l);
        l->fase+=l->taxa/ctx->taxa_amostra; if(l->fase>=1) l->fase-=1;
        int c0=(l->canal_alvo>=0)?l->canal_alvo:0;
        int c1=(l->canal_alvo>=0)?l->canal_alvo+1:ctx->num_canais;
        for(int c=c0;c<c1&&c<ctx->num_canais;c++){
            PT_Canal *ch=&ctx->canais[c];
            switch(l->alvo){
                case PT_LFO_ALVO_VOLUME:  if(!ch->auto_volume.ativo)ch->volume=pt__clampf(val,0,1);break;
                case PT_LFO_ALVO_PITCH:   if(!ch->auto_pitch.ativo&&ch->frequencia>0)ch->freq_atual=ch->frequencia*powf(2,val/12.f);break;
                case PT_LFO_ALVO_PAN:     ch->pan=pt__clampf(val,-1,1);break;
                case PT_LFO_ALVO_FILTRO:  if(ch->filtro.ativo)ch->filtro.cutoff=2*sinf(PT_PI*pt__clampf(val,0,1)*0.5f);break;
                case PT_LFO_ALVO_FM_IDX:  ch->fm.indice=pt__clampf(val,0,20);break;
                case PT_LFO_ALVO_REVERB:  ctx->reverb.mix=pt__clampf(val,0,1);break;
            }
        }
    }
}

static float pt__gerar_canal(PT_Canal *c,float taxa){
    if(c->mudo) return 0;
    if(!c->ativo){
        if(c->fase_env==PT_ENV_LIBERACAO){
            float p=c->envelope.liberacao>0?c->env_nivel_rel/(c->envelope.liberacao*taxa):c->env_nivel;
            c->env_nivel-=p; if(c->env_nivel<=0){c->env_nivel=0;c->fase_env=PT_ENV_INATIVO;}
        }
        if(c->fm.ativo&&c->fm.fase_env_m==PT_ENV_LIBERACAO) pt__env_fm(&c->fm,taxa);
        return 0;
    }
    /* Automação */
    float pm=1;
    if(c->auto_pitch.ativo){pm=pt__interpolar_auto(&c->auto_pitch);c->auto_pitch.t_atual+=1/taxa;
        if(!c->auto_pitch.repetir&&c->auto_pitch.num_kf>0&&c->auto_pitch.t_atual>c->auto_pitch.tempos[c->auto_pitch.num_kf-1])c->auto_pitch.ativo=0;}
    if(c->auto_volume.ativo){c->volume=pt__interpolar_auto(&c->auto_volume);c->auto_volume.t_atual+=1/taxa;
        if(!c->auto_volume.repetir&&c->auto_volume.num_kf>0&&c->auto_volume.t_atual>c->auto_volume.tempos[c->auto_volume.num_kf-1])c->auto_volume.ativo=0;}
    /* Portamento */
    if(c->efeitos.portamento_tempo>0&&c->efeitos.portamento_alvo>0){
        float p=(c->efeitos.portamento_alvo-c->freq_atual)/(c->efeitos.portamento_tempo*taxa);
        c->freq_atual+=p;
        if((p>=0&&c->freq_atual>=c->efeitos.portamento_alvo)||(p<0&&c->freq_atual<=c->efeitos.portamento_alvo))
            c->freq_atual=c->efeitos.portamento_alvo;
    } else c->freq_atual=c->frequencia;
    float ps_mult=c->pitch_shift.ativo?powf(2,c->pitch_shift.semitons/12.f):1;
    float freq=c->freq_atual*pm*ps_mult;
    /* LFO canal */
    float lfo_val=sinf(c->fase_lfo*2*PT_PI),tf=1;
    if(c->efeitos.vibrato_profundidade>0){freq*=powf(2,lfo_val*(c->efeitos.vibrato_profundidade/12));c->fase_lfo+=c->efeitos.vibrato_velocidade/taxa;}
    else if(c->efeitos.tremolo_profundidade>0){tf=1-c->efeitos.tremolo_profundidade*(0.5f+0.5f*lfo_val);c->fase_lfo+=c->efeitos.tremolo_velocidade/taxa;}
    if(c->fase_lfo>=1)c->fase_lfo-=1;
    /* Arpejo */
    if(c->efeitos.arpejo[0]>0){
        int idx=(int)(c->fase_arpejo*3)%3;
        if(c->efeitos.arpejo[idx]>0)freq=c->efeitos.arpejo[idx]*pm;
        c->fase_arpejo+=c->efeitos.arpejo_velocidade/taxa; if(c->fase_arpejo>=1)c->fase_arpejo-=1;
    }
    if(freq<0)freq=0;
    c->fase+=freq/taxa; while(c->fase>=1)c->fase-=1;
    /* Oscilador */
    float am=0, lp=pt__clampf(c->efeitos.largura_pulso>0.001f?c->efeitos.largura_pulso:0.5f,0.01f,0.99f);
    switch(c->forma_onda){
        case PT_ONDA_QUADRADA:    am=(c->fase<0.5f)?1:-1; break;
        case PT_ONDA_TRIANGULAR:  am=(c->fase<0.5f)?(4*c->fase-1):(3-4*c->fase); break;
        case PT_ONDA_DENTE_SERRA: am=2*c->fase-1; break;
        case PT_ONDA_DENTE_INV:   am=1-2*c->fase; break;
        case PT_ONDA_PULSO:       am=(c->fase<lp)?1:-1; break;
        case PT_ONDA_SENO:        am=sinf(c->fase*2*PT_PI); break;
        case PT_RUIDO_BRANCO:
            c->ruido_fase+=freq/taxa; if(c->ruido_fase>=1){c->ruido_fase-=1;c->lfsr=c->lfsr*1664525u+1013904223u;c->ruido_amostra=((float)(c->lfsr>>16)/32767.5f)-1;}
            am=c->ruido_amostra; break;
        case PT_RUIDO_LFSR:{
            c->ruido_fase+=freq/taxa; if(c->ruido_fase>=1){c->ruido_fase-=1;uint32_t b=((c->lfsr>>0)^(c->lfsr>>1))&1u;c->lfsr=(c->lfsr>>1)|(b<<14u);c->ruido_amostra=(c->lfsr&1u)?1:-1;}
            am=c->ruido_amostra; break;}
        case PT_ONDA_FM:{float mf=freq*c->fm.razao;c->fm.fase_mod+=mf/taxa;if(c->fm.fase_mod>=1)c->fm.fase_mod-=1;float em=c->fm.ativo?pt__env_fm(&c->fm,taxa):1;float mod=sinf(c->fm.fase_mod*2*PT_PI)*c->fm.indice*em;am=sinf((c->fase+mod)*2*PT_PI);break;}
        case PT_ONDA_TABELA:
            if(c->tabela_onda){float fi=c->fase*PT_TABELA_TAM;int i0=(int)fi&(PT_TABELA_TAM-1),i1=(i0+1)&(PT_TABELA_TAM-1);float fr=fi-(int)fi;am=c->tabela_onda[i0]*(1-fr)+c->tabela_onda[i1]*fr;} break;
        case PT_ONDA_PCM:
            if(c->pcm.dados&&c->pcm.ativo){
                float ratio=c->pcm.taxa>0?(freq/(float)c->pcm.taxa):1;if(ratio<0.001f)ratio=0.001f;
                int i0=(int)c->pcm.pos; if(i0>=c->pcm.num_amostras){if(c->pcm.em_loop){c->pcm.pos=0;i0=0;}else{c->pcm.ativo=0;break;}}
                int i1=i0+1; if(i1>=c->pcm.num_amostras)i1=c->pcm.em_loop?0:i0;
                float fr=c->pcm.pos-i0;
                am=(c->pcm.dados[i0]/32767.f)*(1-fr)+(c->pcm.dados[i1]/32767.f)*fr;
                c->pcm.pos+=ratio; if(c->pcm.em_loop&&(int)c->pcm.pos>=c->pcm.num_amostras)c->pcm.pos=0;
            } break;
    }
    /* Bitcrush */
    if(c->efeitos.bitcrush>0&&c->efeitos.bitcrush<16){float nv=(float)(1<<c->efeitos.bitcrush);am=floorf(am*nv)/nv;}
    /* SVF */
    if(c->filtro.ativo){float f2=c->filtro.cutoff,q=c->filtro.ressonancia;float hp=am-c->filtro.v_lp-q*c->filtro.v_bp;c->filtro.v_bp+=f2*hp;c->filtro.v_lp+=f2*c->filtro.v_bp;
        switch(c->filtro.modo){case PT_FILTRO_LP:am=c->filtro.v_lp;break;case PT_FILTRO_HP:am=hp;break;case PT_FILTRO_BP:am=c->filtro.v_bp;break;case PT_FILTRO_NOTCH:am=hp+c->filtro.v_lp;break;}}
    /* Ring Mod */
    if(c->ring_mod.ativo){c->ring_mod.fase+=c->ring_mod.freq/taxa;if(c->ring_mod.fase>=1)c->ring_mod.fase-=1;float rm=sinf(c->ring_mod.fase*2*PT_PI);am=am*(1-c->ring_mod.mix)+am*rm*c->ring_mod.mix;}
    /* Distorção */
    if(c->distorcao.ativo) am=pt__distorcer(&c->distorcao,am);
    /* Envelope */
    switch(c->fase_env){
        case PT_ENV_INATIVO: c->env_nivel=0; break;
        case PT_ENV_ATAQUE:
            if(c->envelope.ataque>0){c->env_nivel+=1/(c->envelope.ataque*taxa);if(c->env_nivel>=1){c->env_nivel=1;c->fase_env=PT_ENV_DECAIMENTO;}}
            else{c->env_nivel=1;c->fase_env=PT_ENV_DECAIMENTO;} break;
        case PT_ENV_DECAIMENTO:{float s=pt__clampf(c->envelope.sustentacao,0,1);
            if(c->envelope.decaimento>0){c->env_nivel-=(1-s)/(c->envelope.decaimento*taxa);if(c->env_nivel<=s){c->env_nivel=s;c->fase_env=PT_ENV_SUSTENTACAO;}}
            else{c->env_nivel=s;c->fase_env=PT_ENV_SUSTENTACAO;} break;}
        case PT_ENV_SUSTENTACAO: c->env_nivel=pt__clampf(c->envelope.sustentacao,0,1); break;
        case PT_ENV_LIBERACAO:
            if(c->envelope.liberacao>0){c->env_nivel-=c->env_nivel_rel/(c->envelope.liberacao*taxa);if(c->env_nivel<=0){c->env_nivel=0;c->fase_env=PT_ENV_INATIVO;c->ativo=0;}}
            else{c->env_nivel=0;c->fase_env=PT_ENV_INATIVO;c->ativo=0;} break;
    }
    return am*c->volume*c->env_nivel*tf;
}

/* ====================================================================
 *  §7  API DE CONTEXTO
 * ==================================================================== */

static inline PT_Contexto pt_criar_contexto(float taxa, int num_canais) {
    PT_Contexto ctx; memset(&ctx,0,sizeof(ctx));
    ctx.taxa_amostra=(taxa>0)?taxa:(float)PT_TAXA_PADRAO;
    ctx.num_canais=(num_canais>=1&&num_canais<=PT_CANAIS_MAX)?num_canais:4;
    ctx.volume_master=1; ctx.solo_canal=-1;
    for(int i=0;i<PT_CANAIS_MAX;i++){
        ctx.canais[i].lfsr=0x6A7Fu+(uint32_t)i*0x1F3Bu;
        ctx.canais[i].efeitos.largura_pulso=0.5f;
        ctx.canais[i].envelope.sustentacao=1;
        ctx.canais[i].fm.razao=2; ctx.canais[i].fm.indice=1; ctx.canais[i].fm.sustentacao_m=1;
        ctx.canais[i].distorcao.saida=0.7f; ctx.canais[i].distorcao.drive=3;
        ctx.canais[i].ring_mod.mix=1;
    }
    ctx.compressor.ganho_atual=1; ctx.compressor.ganho_makeup=1;
    ctx.noise_gate.ganho_atual=1;
    for(int i=0;i<PT_LFO_GLOBAL_MAX;i++){ctx.lfos[i].offset=0.5f;ctx.lfos[i].lfsr=0xACE1u+(uint32_t)i*0x3C7u;}
    return ctx;
}

static inline void pt_destruir_contexto(PT_Contexto *ctx){
    if(!ctx)return;
    if(ctx->eco.buf_l){free(ctx->eco.buf_l);ctx->eco.buf_l=NULL;}
    if(ctx->eco.buf_r){free(ctx->eco.buf_r);ctx->eco.buf_r=NULL;}
    ctx->eco.ativo=0;
}

/* ====================================================================
 *  §8  CONTROLE DE CANAIS
 * ==================================================================== */

static inline void pt_tocar_nota(PT_Contexto *ctx,int canal,float freq,int vol,PT_FormaOnda forma){
    if(canal<0||canal>=ctx->num_canais)return;
    PT_Canal *c=&ctx->canais[canal];
    c->frequencia=freq; c->freq_atual=freq;
    c->volume=pt__clampf((float)vol/PT_VOLUME_MAX,0,1);
    c->forma_onda=forma; c->fase_lfo=c->fase_arpejo=c->ruido_fase=0;
    c->auto_volume.t_atual=c->auto_pitch.t_atual=0;
    if(freq>0){c->ativo=1;c->fase=0;c->fase_env=PT_ENV_ATAQUE;c->env_nivel=0;
        if(c->fm.ativo){c->fm.fase_mod=0;c->fm.env_m=0;c->fm.fase_env_m=PT_ENV_ATAQUE;}}
    else{c->ativo=0;c->fase_env=PT_ENV_INATIVO;}
}
static inline void pt_parar_nota(PT_Contexto *ctx,int canal){
    if(canal<0||canal>=ctx->num_canais)return;
    PT_Canal *c=&ctx->canais[canal];
    c->env_nivel_rel=c->env_nivel; c->fase_env=PT_ENV_LIBERACAO;
    if(c->fm.ativo){c->fm.env_m_rel=c->fm.env_m;c->fm.fase_env_m=PT_ENV_LIBERACAO;}
}
static inline void pt_parar_tudo(PT_Contexto *ctx){
    for(int i=0;i<ctx->num_canais;i++){ctx->canais[i].ativo=0;ctx->canais[i].fase_env=PT_ENV_INATIVO;ctx->canais[i].env_nivel=0;}
}
static inline void pt_mutar_canal(PT_Contexto *ctx,int c,int m){if(c>=0&&c<ctx->num_canais)ctx->canais[c].mudo=m?1:0;}
static inline void pt_desmutar_canal(PT_Contexto *ctx,int c){pt_mutar_canal(ctx,c,0);}
static inline void pt_definir_solo(PT_Contexto *ctx,int c){ctx->solo_canal=(c>=0&&c<ctx->num_canais)?c:-1;}

/* ====================================================================
 *  §9  ENVELOPE E EFEITOS
 * ==================================================================== */

static inline void pt_definir_envelope(PT_Contexto *ctx,int c,float a,float d,float s,float r){
    if(c<0||c>=ctx->num_canais)return;
    PT_Envelope *e=&ctx->canais[c].envelope;
    e->ataque=a<0?0:a; e->decaimento=d<0?0:d; e->sustentacao=pt__clampf(s,0,1); e->liberacao=r<0?0:r;
}
static inline void pt_definir_vibrato(PT_Contexto *ctx,int c,float p,float v){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].efeitos.vibrato_profundidade=p; ctx->canais[c].efeitos.vibrato_velocidade=v;
    ctx->canais[c].efeitos.tremolo_profundidade=0;
}
static inline void pt_definir_tremolo(PT_Contexto *ctx,int c,float p,float v){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].efeitos.tremolo_profundidade=p; ctx->canais[c].efeitos.tremolo_velocidade=v;
    ctx->canais[c].efeitos.vibrato_profundidade=0;
}
static inline void pt_definir_arpejo(PT_Contexto *ctx,int c,float f1,float f2,float f3,float v){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].efeitos.arpejo[0]=f1; ctx->canais[c].efeitos.arpejo[1]=f2;
    ctx->canais[c].efeitos.arpejo[2]=f3; ctx->canais[c].efeitos.arpejo_velocidade=v;
}
static inline void pt_definir_portamento(PT_Contexto *ctx,int c,float alvo,float t){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].efeitos.portamento_alvo=alvo; ctx->canais[c].efeitos.portamento_tempo=t;
}
static inline void pt_definir_largura_pulso(PT_Contexto *ctx,int c,float lp){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].efeitos.largura_pulso=pt__clampf(lp,0.01f,0.99f);
}
static inline void pt_definir_bitcrush(PT_Contexto *ctx,int c,int bits){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].efeitos.bitcrush=(bits>=1&&bits<=15)?bits:0;
}
static inline void pt_definir_pan(PT_Contexto *ctx,int c,float pan){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].pan=pt__clampf(pan,-1,1);
}
static inline void pt_definir_volume_canal(PT_Contexto *ctx,int c,int vol){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].volume=pt__clampf((float)vol/PT_VOLUME_MAX,0,1);
}

/* ====================================================================
 *  §10  GERAÇÃO DE AMOSTRAS PCM
 * ==================================================================== */

static inline void pt_gerar_amostras(PT_Contexto *ctx,int16_t *buf,int n){
    float esc=ctx->volume_master/(float)ctx->num_canais;
    int taxa=(int)ctx->taxa_amostra;
    for(int i=0;i<n;i++){
        pt__processar_lfos(ctx);
        float esq=0,dir=0;
        for(int c=0;c<ctx->num_canais;c++){
            PT_Canal *ch=&ctx->canais[c];
            if(ctx->solo_canal>=0&&c!=ctx->solo_canal)continue;
            if(!ch->ativo&&ch->fase_env==PT_ENV_INATIVO&&!ch->pcm.ativo)continue;
            float s=pt__gerar_canal(ch,ctx->taxa_amostra);
            float p=ch->pan;
            esq+=s*((p<=0)?1:(1-p)); dir+=s*((p>=0)?1:(1+p));
        }
        esq*=esc; dir*=esc;
        /* EQ */
        if(ctx->eq.ativo){PT_Equalizador *q=&ctx->eq;
            esq=pt__biquad(esq,&q->ls_x1,&q->ls_x2,&q->ls_y1,&q->ls_y2,q->ls_b0,q->ls_b1,q->ls_b2,q->ls_a1,q->ls_a2);
            dir=pt__biquad(dir,&q->ls_x1,&q->ls_x2,&q->ls_y1,&q->ls_y2,q->ls_b0,q->ls_b1,q->ls_b2,q->ls_a1,q->ls_a2);
            esq=pt__biquad(esq,&q->mp_x1,&q->mp_x2,&q->mp_y1,&q->mp_y2,q->mp_b0,q->mp_b1,q->mp_b2,q->mp_a1,q->mp_a2);
            dir=pt__biquad(dir,&q->mp_x1,&q->mp_x2,&q->mp_y1,&q->mp_y2,q->mp_b0,q->mp_b1,q->mp_b2,q->mp_a1,q->mp_a2);
            esq=pt__biquad(esq,&q->hs_x1,&q->hs_x2,&q->hs_y1,&q->hs_y2,q->hs_b0,q->hs_b1,q->hs_b2,q->hs_a1,q->hs_a2);
            dir=pt__biquad(dir,&q->hs_x1,&q->hs_x2,&q->hs_y1,&q->hs_y2,q->hs_b0,q->hs_b1,q->hs_b2,q->hs_a1,q->hs_a2);}
        /* Phaser/Flanger */
        if(ctx->phaser.ativo){PT_Phaser *ph=&ctx->phaser;
            ph->fase_lfo+=ph->taxa/ctx->taxa_amostra; if(ph->fase_lfo>=1)ph->fase_lfo-=1;
            float lfo=sinf(ph->fase_lfo*2*PT_PI);
            if(ph->modo_flanger){
                int d=(int)(ctx->taxa_amostra*0.001f*(1+ph->profundidade*11*(0.5f+0.5f*lfo)));
                if(d<1)d=1;
                if(d>=4410)d=4409;
                int rd=(ph->cab_fl-d+4410)%4410;
                float fl=ph->buf_fl[0][rd],fr=ph->buf_fl[1][rd];
                ph->buf_fl[0][ph->cab_fl]=esq+fl*ph->realimentacao;
                ph->buf_fl[1][ph->cab_fl]=dir+fr*ph->realimentacao;
                ph->cab_fl=(ph->cab_fl+1)%4410;
                esq=esq*(1-ph->mix)+fl*ph->mix; dir=dir*(1-ph->mix)+fr*ph->mix;
            }else{
                float fc=ph->centro+ph->profundidade*0.45f*lfo;
                fc=pt__clampf(fc,0.001f,0.99f);
                float apc=(1-fc)/(1+fc);
                for(int e=0;e<PT_PHASER_ETAPAS;e++){
                    float ne=apc*(esq-ph->buf[0][e])+ph->buf[0][e>0?e-1:0]; ph->buf[0][e]=ne; esq=ne;
                    float nd=apc*(dir-ph->buf[1][e])+ph->buf[1][e>0?e-1:0]; ph->buf[1][e]=nd; dir=nd;
                }
            }}
        /* Chorus */
        if(ctx->chorus.ativo){PT_Chorus *ch=&ctx->chorus;
            float lfo=sinf(ch->fase_lfo*2*PT_PI); ch->fase_lfo+=ch->taxa/ctx->taxa_amostra; if(ch->fase_lfo>=1)ch->fase_lfo-=1;
            int d=(int)((ch->prof_ms/1000.f)*(0.5f+0.5f*lfo)*ctx->taxa_amostra);
            if(d<1)d=1;
            if(d>=PT_CHORUS_BUF)d=PT_CHORUS_BUF-1;
            int rd=(ch->cabeca-d+PT_CHORUS_BUF)%PT_CHORUS_BUF;
            float cl=ch->buf_l[rd],cr=ch->buf_r[rd];
            ch->buf_l[ch->cabeca]=esq; ch->buf_r[ch->cabeca]=dir;
            ch->cabeca=(ch->cabeca+1)%PT_CHORUS_BUF;
            esq=esq*(1-ch->mix)+cl*ch->mix; dir=dir*(1-ch->mix)+cr*ch->mix;}
        /* Eco */
        if(ctx->eco.ativo&&ctx->eco.buf_l&&ctx->eco.buf_r){PT_Eco *eco=&ctx->eco;
            int d=(int)(eco->atraso_s*taxa); if(d<1)d=1;if(d>=eco->capacidade)d=eco->capacidade-1;
            int rd=(eco->cabeca-d+eco->capacidade)%eco->capacidade;
            float el=eco->buf_l[rd],er=eco->buf_r[rd];
            eco->buf_l[eco->cabeca]=esq+el*eco->realimentacao;
            eco->buf_r[eco->cabeca]=dir+er*eco->realimentacao;
            eco->cabeca=(eco->cabeca+1)%eco->capacidade;
            esq=esq*(1-eco->mix)+el*eco->mix; dir=dir*(1-eco->mix)+er*eco->mix;}
        /* Reverb */
        if(ctx->reverb.ativo){PT_Reverb *rv=&ctx->reverb;
            float mono=(esq+dir)*0.5f,cout=0;
            for(int c2=0;c2<PT_REVERB_COMBS;c2++){float *b=rv->buf_comb[c2];int t=rv->tam_comb[c2],hd=rv->cab_comb[c2];
                float out=b[hd];rv->filt_comb[c2]=out*(1-rv->amortecimento)+rv->filt_comb[c2]*rv->amortecimento;
                b[hd]=mono+rv->filt_comb[c2]*rv->realimentacao_comb;rv->cab_comb[c2]=(hd+1)%t;cout+=out;}
            cout/=PT_REVERB_COMBS;
            for(int a=0;a<PT_REVERB_ALLPASS;a++){float *b=rv->buf_ap[a];int t=rv->tam_ap[a],hd=rv->cab_ap[a];
                float in=cout,bs=b[hd];b[hd]=in+bs*0.5f;rv->cab_ap[a]=(hd+1)%t;cout=bs-0.5f*in;}
            esq=esq*(1-rv->mix)+cout*rv->mix; dir=dir*(1-rv->mix)+cout*rv->mix;}
        /* Compressor */
        if(ctx->compressor.ativo){PT_Compressor *cmp=&ctx->compressor;
            float pk=fabsf(esq)>fabsf(dir)?fabsf(esq):fabsf(dir),tgt=1;
            if(pk>cmp->limiar&&pk>0.0001f){float gr=cmp->limiar+(pk-cmp->limiar)/cmp->razao;tgt=gr/pk;}
            float coef=(tgt<cmp->ganho_atual)?cmp->coef_ataque:cmp->coef_liberacao;
            cmp->ganho_atual+=( tgt-cmp->ganho_atual)*coef; cmp->ganho_atual=pt__clampf(cmp->ganho_atual,0,2);
            float g=cmp->ganho_atual*cmp->ganho_makeup; esq*=g; dir*=g;}
        /* Noise Gate */
        if(ctx->noise_gate.ativo){PT_NoiseGate *ng=&ctx->noise_gate;
            float pk=fabsf(esq)>fabsf(dir)?fabsf(esq):fabsf(dir),tgt=(pk>=ng->limiar)?1:0;
            float coef=(tgt>ng->ganho_atual)?ng->coef_ataque:ng->coef_liberacao;
            ng->ganho_atual+=(tgt-ng->ganho_atual)*coef; esq*=ng->ganho_atual; dir*=ng->ganho_atual;}
        buf[i*2+0]=(int16_t)(pt__clampf(esq,-1,1)*32767);
        buf[i*2+1]=(int16_t)(pt__clampf(dir,-1,1)*32767);
    }
}
static inline void pt_gerar_amostras_mono(PT_Contexto *ctx,int16_t *buf,int n){
    float esc=ctx->volume_master/(float)ctx->num_canais;
    for(int i=0;i<n;i++){float mix=0;
        for(int c=0;c<ctx->num_canais;c++){PT_Canal *ch=&ctx->canais[c];
            if(ctx->solo_canal>=0&&c!=ctx->solo_canal)continue;
            if(!ch->ativo&&ch->fase_env==PT_ENV_INATIVO)continue;
            mix+=pt__gerar_canal(ch,ctx->taxa_amostra);}
        buf[i]=(int16_t)(pt__clampf(mix*esc,-1,1)*32767);}
}
static inline void pt_gerar_amostras_float(PT_Contexto *ctx,float *buf,int n){
    int16_t *tmp=(int16_t*)malloc((size_t)n*2*sizeof(int16_t));if(!tmp)return;
    pt_gerar_amostras(ctx,tmp,n);
    for(int i=0;i<n*2;i++)buf[i]=tmp[i]/32767.f;
    free(tmp);
}

/* ====================================================================
 *  §11  UTILITÁRIOS DE NOTAS
 * ==================================================================== */

static inline float pt_midi_para_hz(int m){return 440.f*powf(2.f,(m-69)/12.f);}
static inline int   pt_hz_para_midi(float f){return (int)roundf(69+12*log2f(f/440.f));}
static inline float pt_nota_para_hz(int oct,int st){return 440.f*powf(2.f,(oct*12+st-57)/12.f);}
static inline float pt_transpor(float f,float st){return f*powf(2.f,st/12.f);}
static inline float pt_hz_para_nota_temperada(float f){if(f<=0)return 0;float s=roundf(12*log2f(f/440.f))+69;return 440.f*powf(2.f,(s-69)/12.f);}
static inline float pt_aplicar_cents(float f,float c){return f*powf(2.f,c/1200.f);}
static inline float pt_frequencia_batimento(float f,float b){return f+b;}
static inline float pt_bpm_para_hz(float bpm){return bpm/60.f;}
static inline float pt_hz_para_bpm(float hz){return hz*60.f;}
static inline float pt_bpm_para_ms(float bpm){return 60000.f/bpm;}
static inline float pt_semitons_entre(float f1,float f2){return (f1>0&&f2>0)?12.f*log2f(f2/f1):0;}

/* ====================================================================
 *  §12  EFEITOS SONOROS PRONTOS (estilo chip retrô)
 * ==================================================================== */

static inline void pt_efeito_explosao(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.002f,.25f,0,.15f);pt_definir_portamento(c,ch,20,.5f);pt_tocar_nota(c,ch,180,v,PT_RUIDO_LFSR);}
static inline void pt_efeito_tiro(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.08f,0,.02f);pt_definir_portamento(c,ch,80,.12f);pt_tocar_nota(c,ch,600,v,PT_ONDA_QUADRADA);}
static inline void pt_efeito_laser(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.12f,0,.03f);pt_definir_portamento(c,ch,1200,.15f);pt_tocar_nota(c,ch,200,v,PT_ONDA_DENTE_SERRA);}
static inline void pt_efeito_pulo(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,0,1,.04f);pt_definir_portamento(c,ch,PT_DO5,.1f);pt_tocar_nota(c,ch,PT_DO4,v,PT_ONDA_QUADRADA);}
static inline void pt_efeito_moeda(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,0,1,.06f);pt_definir_portamento(c,ch,PT_SOL5,.09f);pt_tocar_nota(c,ch,PT_MI5,v,PT_ONDA_QUADRADA);}
static inline void pt_efeito_dano(PT_Contexto *c,int ch,int v){pt_definir_largura_pulso(c,ch,.25f);pt_definir_envelope(c,ch,.001f,.2f,0,.1f);pt_definir_portamento(c,ch,PT_DO3,.22f);pt_tocar_nota(c,ch,PT_LA3,v,PT_ONDA_PULSO);}
static inline void pt_efeito_cursor(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,0,1,.025f);pt_tocar_nota(c,ch,PT_LA4,v,PT_ONDA_QUADRADA);}
static inline void pt_efeito_vitoria(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.005f,.05f,.85f,.2f);pt_tocar_nota(c,ch,PT_DO5,v,PT_ONDA_QUADRADA);}
static inline void pt_efeito_power_up(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,0,1,.08f);pt_definir_portamento(c,ch,PT_DO6,.3f);pt_tocar_nota(c,ch,PT_DO4,v,PT_ONDA_TRIANGULAR);}
static inline void pt_efeito_game_over(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.01f,.5f,.3f,.5f);pt_definir_portamento(c,ch,PT_LA2,1.2f);pt_tocar_nota(c,ch,PT_LA4,v,PT_ONDA_TRIANGULAR);}
static inline void pt_efeito_sirene(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.05f,0,1,.1f);pt_definir_vibrato(c,ch,3.5f,3.f);pt_tocar_nota(c,ch,PT_LA5,v,PT_ONDA_DENTE_SERRA);}
static inline void pt_efeito_bumbo(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.18f,0,.05f);pt_definir_portamento(c,ch,30,.2f);pt_tocar_nota(c,ch,150,v,PT_RUIDO_LFSR);}
static inline void pt_efeito_caixa(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.07f,0,.02f);pt_tocar_nota(c,ch,2000,v,PT_RUIDO_BRANCO);}
static inline void pt_efeito_hihat(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.02f,0,.01f);pt_tocar_nota(c,ch,8000,v,PT_RUIDO_BRANCO);}
static inline void pt_efeito_hihat_aberto(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.15f,0,.08f);pt_tocar_nota(c,ch,7000,v,PT_RUIDO_BRANCO);}
static inline void pt_efeito_rimshot(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.04f,0,.01f);pt_tocar_nota(c,ch,900,v,PT_RUIDO_BRANCO);}
static inline void pt_efeito_tom_alto(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.12f,0,.04f);pt_definir_portamento(c,ch,100,.12f);pt_tocar_nota(c,ch,300,v,PT_RUIDO_LFSR);}
static inline void pt_efeito_tom_baixo(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.18f,0,.06f);pt_definir_portamento(c,ch,50,.18f);pt_tocar_nota(c,ch,180,v,PT_RUIDO_LFSR);}
static inline void pt_efeito_telefone(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.01f,0,1,.05f);pt_definir_tremolo(c,ch,.8f,20.f);pt_tocar_nota(c,ch,PT_LA4,v,PT_ONDA_SENO);}
static inline void pt_efeito_portal(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.1f,0,1,.5f);pt_definir_vibrato(c,ch,.5f,.3f);pt_definir_portamento(c,ch,PT_DO6,1.5f);pt_tocar_nota(c,ch,PT_DO3,v,PT_ONDA_SENO);}
static inline void pt_efeito_foguete(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.05f,0,1,.3f);pt_definir_portamento(c,ch,PT_DO7,2.f);pt_tocar_nota(c,ch,PT_DO3,v,PT_RUIDO_LFSR);}
static inline void pt_efeito_eco_retro(PT_Contexto *c,int ch,int v){pt_definir_bitcrush(c,ch,6);pt_definir_envelope(c,ch,.001f,.3f,0,.1f);pt_tocar_nota(c,ch,PT_LA3,v,PT_ONDA_QUADRADA);pt_definir_bitcrush(c,ch,0);}
static inline void pt_efeito_warp(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,0,1,.4f);pt_definir_portamento(c,ch,PT_DO7,.8f);pt_definir_bitcrush(c,ch,4);pt_tocar_nota(c,ch,PT_DO5,v,PT_ONDA_QUADRADA);}
static inline void pt_efeito_clique(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,.005f,0,.002f);pt_tocar_nota(c,ch,5000,v,PT_RUIDO_BRANCO);}
static inline void pt_efeito_subida_epica(PT_Contexto *c,int ch,int v){pt_definir_envelope(c,ch,.001f,0,1,.6f);pt_definir_portamento(c,ch,PT_DO7,3.f);pt_definir_vibrato(c,ch,0.2f,1.f);pt_tocar_nota(c,ch,PT_DO3,v,PT_ONDA_DENTE_SERRA);}


/* ====================================================================
 *  §13  PADRÕES E SEQUENCIADOR
 * ==================================================================== */

static inline void pt_iniciar_padrao(PT_Padrao *p,float bpm){memset(p,0,sizeof(*p));p->bpm=bpm>0?bpm:120;}
static inline void pt_adicionar_nota_padrao(PT_Padrao *p,int c,float f,float d,int v,PT_FormaOnda fo){
    if(c<0||c>=PT_CANAIS_MAX)return;
    int n=p->num_eventos[c];if(n>=PT_EVENTOS_MAX)return;
    PT_Evento *ev=&p->eventos[c][n];ev->frequencia=f;ev->duracao=d;ev->volume=(int8_t)v;ev->forma_onda=fo;ev->efeito=PT_EFX_NENHUM;ev->param=0;p->num_eventos[c]++;
}
static inline void pt_adicionar_efeito_padrao(PT_Padrao *p,int c,float f,float d,int v,PT_FormaOnda fo,PT_CodigoEfeito e,float pm){
    if(c<0||c>=PT_CANAIS_MAX)return;
    int n=p->num_eventos[c];if(n>=PT_EVENTOS_MAX)return;
    PT_Evento *ev=&p->eventos[c][n];ev->frequencia=f;ev->duracao=d;ev->volume=(int8_t)v;ev->forma_onda=fo;ev->efeito=(uint8_t)e;ev->param=pm;p->num_eventos[c]++;
}
static inline void pt_iniciar_musica(PT_Musica *m){memset(m,0,sizeof(*m));}
static inline void pt_adicionar_padrao_musica(PT_Musica *m,PT_Padrao *p,int rep){
    if(m->num_padroes>=PT_PADROES_MAX)return;
    int idx=m->num_padroes++;m->padroes[idx]=p;
    for(int r=0;r<rep;r++){if(m->tam_sequencia>=PT_PADROES_MAX*4)break;m->sequencia[m->tam_sequencia++]=idx;}
}
static inline void pt_reproduzir_musica(PT_Contexto *ctx,PT_Musica *m,int loop){
    ctx->musica=m;ctx->padrao_seq=0;ctx->reproduzindo=1;ctx->pausado=0;m->em_loop=loop;
    for(int i=0;i<PT_CANAIS_MAX;i++){ctx->evento[i]=0;ctx->tempo_ev[i]=0;}
}
static inline void pt_pausar_musica(PT_Contexto *ctx){ctx->pausado=1;}
static inline void pt_retomar_musica(PT_Contexto *ctx){ctx->pausado=0;}
static inline void pt_parar_musica(PT_Contexto *ctx){ctx->reproduzindo=0;ctx->musica=NULL;pt_parar_tudo(ctx);}

static inline void pt_atualizar(PT_Contexto *ctx,float dt){
    if(!ctx->reproduzindo||ctx->pausado||!ctx->musica)return;
    PT_Musica *m=ctx->musica; if(ctx->padrao_seq>=m->tam_sequencia)return;
    int idx=m->sequencia[ctx->padrao_seq]; PT_Padrao *p=m->padroes[idx];if(!p)return;
    float bat=60.f/p->bpm;
    for(int c=0;c<ctx->num_canais;c++){
        ctx->tempo_ev[c]-=dt;
        while(ctx->tempo_ev[c]<=0){
            int ei=ctx->evento[c]; if(ei>=p->num_eventos[c]){ctx->tempo_ev[c]=9999;break;}
            PT_Evento *ev=&p->eventos[c][ei]; float dur=ev->duracao*bat;
            if(ev->frequencia>0){
                float freq=ev->frequencia;
                if(p->semitons_transpor!=0)freq*=powf(2.f,(float)p->semitons_transpor/12.f);
                int vol=(ev->volume>=0)?(int)ev->volume:PT_VOLUME_MAX;
                pt_tocar_nota(ctx,c,freq,vol,ev->forma_onda);
            }else pt_parar_nota(ctx,c);
            switch((PT_CodigoEfeito)ev->efeito){
                case PT_EFX_PORTAMENTO:    pt_definir_portamento(ctx,c,ev->param,dur);break;
                case PT_EFX_VIBRATO:       pt_definir_vibrato(ctx,c,ev->param,6.f);break;
                case PT_EFX_TREMOLO:       pt_definir_tremolo(ctx,c,ev->param,8.f);break;
                case PT_EFX_VOLUME:        pt_definir_volume_canal(ctx,c,(int)ev->param);break;
                case PT_EFX_PAN:           pt_definir_pan(ctx,c,ev->param);break;
                case PT_EFX_PULSO:         pt_definir_largura_pulso(ctx,c,ev->param);break;
                case PT_EFX_FILTRO_CUTOFF: if(ctx->canais[c].filtro.ativo)ctx->canais[c].filtro.cutoff=2*sinf(PT_PI*ev->param*0.5f);break;
                case PT_EFX_FILTRO_RES:    ctx->canais[c].filtro.ressonancia=pt__clampf(ev->param,0,0.99f);break;
                case PT_EFX_FM_INDICE:     ctx->canais[c].fm.indice=ev->param;break;
                case PT_EFX_DISTORCAO:     ctx->canais[c].distorcao.drive=ev->param;break;
                case PT_EFX_RING_MOD:      ctx->canais[c].ring_mod.freq=ev->param;break;
                case PT_EFX_PITCH_SHIFT:   ctx->canais[c].pitch_shift.semitons=ev->param;break;
                case PT_EFX_PARAR:         pt_parar_nota(ctx,c);break;
                default:break;
            }
            ctx->tempo_ev[c]+=dur; ctx->evento[c]++;
        }
    }
    int ok=1; for(int c=0;c<ctx->num_canais;c++)if(ctx->evento[c]<p->num_eventos[c]){ok=0;break;}
    if(ok){ctx->padrao_seq++;for(int c=0;c<PT_CANAIS_MAX;c++){ctx->evento[c]=0;ctx->tempo_ev[c]=0;}
        if(ctx->padrao_seq>=m->tam_sequencia){if(m->em_loop)ctx->padrao_seq=0;else pt_parar_musica(ctx);}}
}

/* ====================================================================
 *  §14  CONSULTAS DE ESTADO
 * ==================================================================== */

static inline int   pt_esta_reproduzindo(const PT_Contexto *ctx){return ctx->reproduzindo&&!ctx->pausado;}
static inline int   pt_canal_ativo(const PT_Contexto *ctx,int c){
    if(c<0||c>=ctx->num_canais)return 0;
    return ctx->canais[c].ativo||ctx->canais[c].fase_env!=PT_ENV_INATIVO||ctx->canais[c].pcm.ativo;}
static inline float pt_volume_envelope(const PT_Contexto *ctx,int c){if(c<0||c>=ctx->num_canais)return 0;return ctx->canais[c].env_nivel;}
static inline float pt_frequencia_atual(const PT_Contexto *ctx,int c){if(c<0||c>=ctx->num_canais)return 0;return ctx->canais[c].freq_atual;}
static inline int   pt_esta_mutado(const PT_Contexto *ctx,int c){if(c<0||c>=ctx->num_canais)return 0;return ctx->canais[c].mudo;}
static inline int   pt_num_canais_ativos(const PT_Contexto *ctx){int n=0;for(int c=0;c<ctx->num_canais;c++)if(pt_canal_ativo(ctx,c))n++;return n;}

/* ====================================================================
 *  §15  MACROS DE CONVENIÊNCIA PARA PADRÕES
 * ==================================================================== */

#define PT_NOTA(p,c,f,d,v)          pt_adicionar_nota_padrao(&(p),(c),(f),(d),(v),PT_ONDA_QUADRADA)
#define PT_PAUSA(p,c,d)             pt_adicionar_nota_padrao(&(p),(c),PT_SILENCIO,(d),-1,PT_ONDA_QUADRADA)
#define PT_NOTA_F(p,c,f,d,v,fm)    pt_adicionar_nota_padrao(&(p),(c),(f),(d),(v),(fm))
#define PT_NOTA_EFX(p,c,f,d,v,fm,e,pm) pt_adicionar_efeito_padrao(&(p),(c),(f),(d),(v),(fm),(e),(pm))

/* ====================================================================
 *  §16  FILTRO SVF POR CANAL
 * ==================================================================== */

static inline void pt_ativar_filtro(PT_Contexto *ctx,int c,PT_ModoFiltro modo,float hz,float res){
    if(c<0||c>=ctx->num_canais)return;
    PT_Filtro *f=&ctx->canais[c].filtro; f->ativo=1;f->modo=modo;
    f->cutoff=pt__clampf(2*sinf(PT_PI*hz/ctx->taxa_amostra),0.0001f,0.9999f);
    f->ressonancia=pt__clampf(res,0,0.99f); f->v_lp=f->v_bp=0;
}
static inline void pt_desativar_filtro(PT_Contexto *ctx,int c){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].filtro.ativo=0;ctx->canais[c].filtro.v_lp=ctx->canais[c].filtro.v_bp=0;
}
static inline void pt_filtro_cutoff(PT_Contexto *ctx,int c,float hz){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].filtro.cutoff=pt__clampf(2*sinf(PT_PI*hz/ctx->taxa_amostra),0.0001f,0.9999f);
}
static inline void pt_filtro_ressonancia(PT_Contexto *ctx,int c,float r){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].filtro.ressonancia=pt__clampf(r,0,0.99f);
}


/* ====================================================================
 *  §17  SÍNTESE FM (2 OPERADORES)
 * ==================================================================== */

static inline void pt_ativar_fm(PT_Contexto *ctx,int c,float razao,float indice){
    if(c<0||c>=ctx->num_canais)return;
    PT_FM *fm=&ctx->canais[c].fm;
    fm->ativo=1;fm->razao=razao>0?razao:1;fm->indice=indice>=0?indice:1;
    fm->fase_mod=0;fm->env_m=1;fm->fase_env_m=PT_ENV_SUSTENTACAO;
    ctx->canais[c].forma_onda=PT_ONDA_FM;
}
static inline void pt_fm_envelope_modulador(PT_Contexto *ctx,int c,float a,float d,float s,float r){
    if(c<0||c>=ctx->num_canais)return;
    PT_FM *fm=&ctx->canais[c].fm;
    fm->ataque_m=a;fm->decaimento_m=d;fm->sustentacao_m=pt__clampf(s,0,1);fm->liberacao_m=r;
    fm->fase_env_m=PT_ENV_ATAQUE;fm->env_m=0;
}
static inline void pt_fm_indice(PT_Contexto *ctx,int c,float i){if(c>=0&&c<ctx->num_canais)ctx->canais[c].fm.indice=i>=0?i:0;}
static inline void pt_fm_razao(PT_Contexto *ctx,int c,float r){if(c>=0&&c<ctx->num_canais)ctx->canais[c].fm.razao=r>0?r:1;}
static inline void pt_desativar_fm(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais){ctx->canais[c].fm.ativo=0;ctx->canais[c].forma_onda=PT_ONDA_SENO;}}

/* Presets FM */
static inline void pt_fm_preset_piano_eletrico(PT_Contexto *ctx,int c,int v){pt_ativar_fm(ctx,c,14,3.5f);pt_fm_envelope_modulador(ctx,c,0,.8f,0,.3f);pt_definir_envelope(ctx,c,.01f,1.2f,0,.3f);pt_tocar_nota(ctx,c,PT_DO4,v,PT_ONDA_FM);}
static inline void pt_fm_preset_orgao(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,1,2);pt_definir_envelope(ctx,c,.01f,0,1,.05f);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}
static inline void pt_fm_preset_sino(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,3.5f,5);pt_fm_envelope_modulador(ctx,c,0,2,0,.5f);pt_definir_envelope(ctx,c,.001f,2.5f,0,.5f);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}
static inline void pt_fm_preset_baixo(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,2,6);pt_fm_envelope_modulador(ctx,c,0,.1f,0,0);pt_definir_envelope(ctx,c,.001f,.3f,0,.08f);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}
static inline void pt_fm_preset_voz(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,1,1.5f);pt_definir_envelope(ctx,c,.15f,0,.9f,.3f);pt_definir_vibrato(ctx,c,.4f,5.5f);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}
static inline void pt_fm_preset_gongo(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,7,8);pt_fm_envelope_modulador(ctx,c,0,.05f,0,.2f);pt_definir_envelope(ctx,c,.001f,3,0,.8f);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}
static inline void pt_fm_preset_flute(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,1,.5f);pt_fm_envelope_modulador(ctx,c,.1f,.1f,.8f,.2f);pt_definir_envelope(ctx,c,.12f,.05f,.85f,.25f);pt_definir_vibrato(ctx,c,.3f,5);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}
static inline void pt_fm_preset_braco(PT_Contexto *ctx,int c,float f,int v){pt_ativar_fm(ctx,c,0.5f,4);pt_fm_envelope_modulador(ctx,c,0,.3f,.4f,.5f);pt_definir_envelope(ctx,c,.05f,.1f,.8f,.4f);pt_tocar_nota(ctx,c,f,v,PT_ONDA_FM);}

/* ====================================================================
 *  §18  WAVETABLE PERSONALIZADO
 * ==================================================================== */

static inline void pt_definir_tabela_onda(PT_Contexto *ctx,int c,float *t){
    if(c<0||c>=ctx->num_canais)return;
    ctx->canais[c].tabela_onda=t;ctx->canais[c].forma_onda=PT_ONDA_TABELA;
}
static inline void pt_tabela_seno(float *t){for(int i=0;i<PT_TABELA_TAM;i++)t[i]=sinf((float)i/PT_TABELA_TAM*2*PT_PI);}
static inline void pt_tabela_quadrada(float *t){for(int i=0;i<PT_TABELA_TAM;i++)t[i]=(i<PT_TABELA_TAM/2)?1:-1;}
static inline void pt_tabela_dente_serra(float *t){for(int i=0;i<PT_TABELA_TAM;i++)t[i]=2.f*(float)i/PT_TABELA_TAM-1;}
static inline void pt_tabela_triangular(float *t){for(int i=0;i<PT_TABELA_TAM;i++){float p=(float)i/PT_TABELA_TAM;t[i]=(p<.5f)?(4*p-1):(3-4*p);}}
static inline void pt_tabela_fourier(float *t,int nh,int so_impares){
    for(int i=0;i<PT_TABELA_TAM;i++)t[i]=0;
    for(int h=1;h<=nh;h++){int n=so_impares?(2*h-1):h;float a=1.f/n;for(int i=0;i<PT_TABELA_TAM;i++)t[i]+=a*sinf((float)(n*i)/PT_TABELA_TAM*2*PT_PI);}
    float mx=0;for(int i=0;i<PT_TABELA_TAM;i++)if(fabsf(t[i])>mx)mx=fabsf(t[i]);if(mx>0)for(int i=0;i<PT_TABELA_TAM;i++)t[i]/=mx;
}
static inline void pt_tabela_interpolar(float *dst,const float *a,const float *b,float alpha){
    alpha=pt__clampf(alpha,0,1);for(int i=0;i<PT_TABELA_TAM;i++)dst[i]=a[i]*(1-alpha)+b[i]*alpha;
}
static inline void pt_tabela_normalizar(float *t){
    float mx=0;for(int i=0;i<PT_TABELA_TAM;i++)if(fabsf(t[i])>mx)mx=fabsf(t[i]);if(mx>0)for(int i=0;i<PT_TABELA_TAM;i++)t[i]/=mx;
}
static inline void pt_tabela_corda(float *t,uint32_t seed){
    uint32_t s=seed; for(int i=0;i<PT_TABELA_TAM;i++){s=s*1664525u+1013904223u;t[i]=((float)(s>>16)/32767.5f)-1;}
    for(int k=0;k<64;k++)for(int i=0;i<PT_TABELA_TAM;i++){int j=(i+1)%PT_TABELA_TAM;t[i]=(t[i]+t[j])*0.5f;}
    pt_tabela_normalizar(t);
}
static inline void pt_tabela_somar_harmonico(float *t,int harmonic,float amp){
    for(int i=0;i<PT_TABELA_TAM;i++)t[i]+=amp*sinf((float)(harmonic*i)/PT_TABELA_TAM*2*PT_PI);
}

/* ====================================================================
 *  §19  ECO, CHORUS E COMPRESSOR
 * ==================================================================== */

static inline int pt_ativar_eco(PT_Contexto *ctx,float atraso,float rf,float mix){
    PT_Eco *e=&ctx->eco; int cap=(int)(ctx->taxa_amostra*(atraso+0.1f))+512;
    if(!e->buf_l||e->capacidade<cap){free(e->buf_l);free(e->buf_r);
        e->buf_l=(float*)calloc((size_t)cap,sizeof(float));e->buf_r=(float*)calloc((size_t)cap,sizeof(float));
        if(!e->buf_l||!e->buf_r){free(e->buf_l);free(e->buf_r);e->buf_l=e->buf_r=NULL;e->ativo=0;return 0;}e->capacidade=cap;}
    e->cabeca=0;e->atraso_s=pt__clampf(atraso,.01f,2);e->realimentacao=pt__clampf(rf,0,.95f);e->mix=pt__clampf(mix,0,1);e->ativo=1;return 1;
}
static inline void pt_desativar_eco(PT_Contexto *ctx){ctx->eco.ativo=0;}
static inline void pt_ativar_chorus(PT_Contexto *ctx,float taxa,float prof,float mix){
    PT_Chorus *ch=&ctx->chorus;memset(ch->buf_l,0,sizeof(ch->buf_l));memset(ch->buf_r,0,sizeof(ch->buf_r));
    ch->cabeca=0;ch->taxa=pt__clampf(taxa,.01f,10);ch->prof_ms=pt__clampf(prof,1,50);ch->mix=pt__clampf(mix,0,1);ch->fase_lfo=0;ch->ativo=1;
}
static inline void pt_desativar_chorus(PT_Contexto *ctx){ctx->chorus.ativo=0;}
static inline void pt_ativar_compressor(PT_Contexto *ctx,float lim,float razao,float a_ms,float r_ms,float mk){
    PT_Compressor *c=&ctx->compressor;c->limiar=pt__clampf(lim,0,1);c->razao=razao>1?razao:1;
    c->coef_ataque=1-expf(-1.f/(ctx->taxa_amostra*a_ms/1000));c->coef_liberacao=1-expf(-1.f/(ctx->taxa_amostra*r_ms/1000));
    c->ganho_makeup=mk>0?mk:1;c->ganho_atual=1;c->ativo=1;
}
static inline void pt_desativar_compressor(PT_Contexto *ctx){ctx->compressor.ativo=0;}

/* ====================================================================
 *  §20  AUTOMAÇÃO DE VOLUME E PITCH
 * ==================================================================== */

static inline void pt_auto_volume_iniciar(PT_Contexto *ctx,int c,int rep){
    if(c<0||c>=ctx->num_canais){return;}
    memset(&ctx->canais[c].auto_volume,0,sizeof(PT_Automacao));
    ctx->canais[c].auto_volume.repetir=rep;ctx->canais[c].auto_volume.ativo=1;
}
static inline void pt_auto_volume_keyframe(PT_Contexto *ctx,int c,float t,float v){
    if(c<0||c>=ctx->num_canais){return;}
    PT_Automacao *a=&ctx->canais[c].auto_volume;if(a->num_kf>=PT_AUTO_KF_MAX)return;
    a->tempos[a->num_kf]=t;a->valores[a->num_kf]=pt__clampf(v,0,1);a->num_kf++;
}
static inline void pt_auto_volume_parar(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais)ctx->canais[c].auto_volume.ativo=0;}
static inline void pt_auto_volume_fade(PT_Contexto *ctx,int c,float vi,float vf,float dur){
    pt_auto_volume_iniciar(ctx,c,0);pt_auto_volume_keyframe(ctx,c,0,vi);pt_auto_volume_keyframe(ctx,c,dur,vf);
}
static inline void pt_auto_pitch_iniciar(PT_Contexto *ctx,int c,int rep){
    if(c<0||c>=ctx->num_canais){return;}
    memset(&ctx->canais[c].auto_pitch,0,sizeof(PT_Automacao));
    ctx->canais[c].auto_pitch.repetir=rep;ctx->canais[c].auto_pitch.ativo=1;
}
static inline void pt_auto_pitch_keyframe(PT_Contexto *ctx,int c,float t,float mult){
    if(c<0||c>=ctx->num_canais){return;}
    PT_Automacao *a=&ctx->canais[c].auto_pitch;if(a->num_kf>=PT_AUTO_KF_MAX)return;
    a->tempos[a->num_kf]=t;a->valores[a->num_kf]=mult>0?mult:1;a->num_kf++;
}
static inline void pt_auto_pitch_parar(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais)ctx->canais[c].auto_pitch.ativo=0;}


/* ====================================================================
 *  §21  ESCALAS E ACORDES
 * ==================================================================== */

static const int pt__iv_esc[][13]={{0,2,4,5,7,9,11,-1,-1,-1,-1,-1,-1},{0,2,3,5,7,8,10,-1,-1,-1,-1,-1,-1},{0,2,3,5,7,8,11,-1,-1,-1,-1,-1,-1},{0,2,4,7,9,-1,-1,-1,-1,-1,-1,-1,-1},{0,3,5,7,10,-1,-1,-1,-1,-1,-1,-1,-1},{0,3,5,6,7,10,-1,-1,-1,-1,-1,-1,-1},{0,2,3,5,7,9,10,-1,-1,-1,-1,-1,-1},{0,1,3,5,7,8,10,-1,-1,-1,-1,-1,-1},{0,2,4,6,7,9,11,-1,-1,-1,-1,-1,-1},{0,2,4,5,7,9,10,-1,-1,-1,-1,-1,-1},{0,1,3,5,6,8,10,-1,-1,-1,-1,-1,-1},{0,1,2,3,4,5,6,7,8,9,10,11,-1},{0,2,4,6,8,10,-1,-1,-1,-1,-1,-1,-1}};
static const int pt__iv_acd[][5]={{0,4,7,-1,-1},{0,3,7,-1,-1},{0,3,6,-1,-1},{0,4,8,-1,-1},{0,4,7,10,-1},{0,4,7,11,-1},{0,3,7,10,-1},{0,2,7,-1,-1},{0,5,7,-1,-1},{0,4,7,14,-1},{0,4,7,9,-1},{0,3,7,9,-1}};

static inline void pt_gerar_escala(float raiz,PT_TipoEscala tipo,float *notas,int *num,int oitavas){
    const int *iv=pt__iv_esc[(int)tipo];int n=0;
    for(int o=0;o<oitavas;o++)for(int i=0;iv[i]>=0&&n<13*oitavas;i++)notas[n++]=raiz*powf(2.f,(iv[i]+o*12)/12.f);
    if(n<13*oitavas)notas[n++]=raiz*powf(2.f,(float)oitavas);
    if(num)*num=n;
}
static inline float pt_nota_escala(float raiz,PT_TipoEscala tipo,int grau){
    const int *iv=pt__iv_esc[(int)tipo];int tam=0;while(iv[tam]>=0)tam++;if(!tam)return raiz;
    int oct=grau/tam,idx=grau%tam;if(idx<0){idx+=tam;oct--;}return raiz*powf(2.f,(iv[idx]+oct*12)/12.f);
}
static inline int pt_gerar_acorde(float raiz,PT_TipoAcorde tipo,float *notas){
    const int *iv=pt__iv_acd[(int)tipo];int n=0;
    for(;iv[n]>=0&&n<5;n++)notas[n]=raiz*powf(2.f,iv[n]/12.f);
    return n;
}
static inline int pt_tocar_acorde(PT_Contexto *ctx,float raiz,PT_TipoAcorde tipo,int cb,int v,PT_FormaOnda fo){
    float ns[5];int n=pt_gerar_acorde(raiz,tipo,ns);
    for(int i=0;i<n&&(cb+i)<ctx->num_canais;i++)
        pt_tocar_nota(ctx,cb+i,ns[i],v,fo);
    return n;
}
static inline void pt_parar_acorde(PT_Contexto *ctx,int cb,int n){
    for(int i=0;i<n&&(cb+i)<ctx->num_canais;i++)pt_parar_nota(ctx,cb+i);
}

/* ====================================================================
 *  §22  DRUM MACHINE
 * ==================================================================== */

static inline void pt_iniciar_percussao(PT_PadraoPercussao *d,int cb,int nt,int np,float bpm){
    memset(d,0,sizeof(*d));d->canal_base=cb;d->num_trilhas=(nt>=1&&nt<=PT_DRUM_TRILHAS_MAX)?nt:4;
    d->num_passos=(np==8||np==16||np==32)?np:16;d->bpm=bpm>0?bpm:120;
    for(int t=0;t<PT_DRUM_TRILHAS_MAX;t++){d->frequencias[t]=200;d->ondas[t]=PT_RUIDO_LFSR;}
}
static inline void pt_drum_passo(PT_PadraoPercussao *d,int t,int p,int v){
    if(t<0||t>=PT_DRUM_TRILHAS_MAX||p<0||p>=PT_DRUM_PASSOS_MAX){return;}
    d->passos[t][p]=(uint8_t)pt__clampf((float)v,0,15);
}
static inline void pt_drum_preenchimento(PT_PadraoPercussao *d,int t,uint32_t bits,int v){
    if(t<0||t>=PT_DRUM_TRILHAS_MAX){return;}
    for(int p=0;p<d->num_passos;p++)d->passos[t][p]=(bits&(1u<<p))?(uint8_t)v:0;
}
static inline void pt_drum_som(PT_PadraoPercussao *d,int t,float f,PT_FormaOnda o){
    if(t<0||t>=PT_DRUM_TRILHAS_MAX){return;}
    d->frequencias[t]=f;d->ondas[t]=o;
}
static inline void pt_drum_reproduzir(PT_PadraoPercussao *d){d->passo_atual=0;d->tempo_acc=0;d->reproduzindo=1;}
static inline void pt_drum_parar(PT_PadraoPercussao *d){d->reproduzindo=0;}
static inline void pt_drum_atualizar(PT_Contexto *ctx,PT_PadraoPercussao *d,float dt){
    if(!d->reproduzindo)return;
    float dur=(60.f/d->bpm)*4.f/(float)d->num_passos;
    float duref=dur; if(d->swing>0&&(d->passo_atual&1)==0)duref*=(1+d->swing);
    d->tempo_acc+=dt;
    while(d->tempo_acc>=duref){
        d->tempo_acc-=duref;
        for(int t=0;t<d->num_trilhas;t++){int v=d->passos[t][d->passo_atual];if(!v)continue;int c=d->canal_base+t;if(c<ctx->num_canais)pt_tocar_nota(ctx,c,d->frequencias[t],v,d->ondas[t]);}
        d->passo_atual=(d->passo_atual+1)%d->num_passos;
        duref=dur;if(d->swing>0&&(d->passo_atual&1)==0)duref*=(1+d->swing);
    }
}
static inline void pt_drum_configurar_padrao(PT_Contexto *ctx,PT_PadraoPercussao *d){
    pt_definir_envelope(ctx,d->canal_base+0,.001f,.18f,0,.05f);pt_drum_som(d,0,150,PT_RUIDO_LFSR);
    pt_definir_envelope(ctx,d->canal_base+1,.001f,.07f,0,.02f);pt_drum_som(d,1,2000,PT_RUIDO_BRANCO);
    pt_definir_envelope(ctx,d->canal_base+2,.001f,.02f,0,.01f);pt_drum_som(d,2,8000,PT_RUIDO_BRANCO);
    if(d->num_trilhas>3){pt_definir_envelope(ctx,d->canal_base+3,.001f,.12f,0,.04f);pt_drum_som(d,3,300,PT_RUIDO_LFSR);}
}

/* ====================================================================
 *  §23  EXPORTAÇÃO WAV
 * ==================================================================== */

typedef struct{uint8_t riff[4];uint32_t sz;uint8_t wave[4];uint8_t fmt[4];uint32_t fsz;uint16_t tag,ch;uint32_t rate,brate;uint16_t align,bps;uint8_t data[4];uint32_t dsz;}PT__WH;
static void pt__u16(uint8_t *p,uint16_t v){p[0]=(uint8_t)(v&0xFF);p[1]=(uint8_t)(v>>8);}
static void pt__u32(uint8_t *p,uint32_t v){p[0]=(uint8_t)(v&0xFF);p[1]=(uint8_t)(v>>8);p[2]=(uint8_t)(v>>16);p[3]=(uint8_t)(v>>24);}
static void pt__mkhdr(PT__WH *h,uint32_t rate,uint16_t ch,uint32_t n){uint32_t ds=n*ch*2;memcpy(h->riff,"RIFF",4);memcpy(h->wave,"WAVE",4);memcpy(h->fmt,"fmt ",4);memcpy(h->data,"data",4);pt__u32((uint8_t*)&h->sz,ds+36);pt__u32((uint8_t*)&h->fsz,16);pt__u16((uint8_t*)&h->tag,1);pt__u16((uint8_t*)&h->ch,ch);pt__u32((uint8_t*)&h->rate,rate);pt__u32((uint8_t*)&h->brate,rate*ch*2);pt__u16((uint8_t*)&h->align,(uint16_t)(ch*2));pt__u16((uint8_t*)&h->bps,16);pt__u32((uint8_t*)&h->dsz,ds);}
static int pt__wpcm(FILE *f,const int16_t *b,int n){uint8_t p[2];for(int i=0;i<n;i++){p[0]=(uint8_t)(b[i]&0xFF);p[1]=(uint8_t)((b[i]>>8)&0xFF);if(fwrite(p,1,2,f)!=2)return 0;}return 1;}

static inline int pt_salvar_wav(const char *cam,const int16_t *buf,int n,int taxa){
    if(!cam||!buf||n<=0||taxa<=0)return 0;
    FILE *f=fopen(cam,"wb");
    if(!f){perror("pt_salvar_wav");return 0;}
    PT__WH h;pt__mkhdr(&h,(uint32_t)taxa,2,(uint32_t)n);if(fwrite(&h,sizeof(h),1,f)!=1){fclose(f);return 0;}
    int ok=pt__wpcm(f,buf,n*2);fclose(f);return ok;
}
static inline int pt_salvar_wav_mono(const char *cam,const int16_t *buf,int n,int taxa){
    if(!cam||!buf||n<=0||taxa<=0)return 0;
    FILE *f=fopen(cam,"wb");
    if(!f){perror("pt_salvar_wav_mono");return 0;}
    PT__WH h;pt__mkhdr(&h,(uint32_t)taxa,1,(uint32_t)n);if(fwrite(&h,sizeof(h),1,f)!=1){fclose(f);return 0;}
    int ok=pt__wpcm(f,buf,n);fclose(f);return ok;
}
static inline int pt_renderizar_wav(PT_Contexto *ctx,const char *cam,float max_s){
    if(!ctx||!cam||max_s<=0){return -1;}
    int taxa=(int)ctx->taxa_amostra,mx=(int)(max_s*taxa);
    int16_t *buf=(int16_t*)malloc((size_t)mx*2*sizeof(int16_t));if(!buf)return -1;
    const int BLK=512;int tot=0;
    while(tot+BLK<=mx){int tem=0;for(int c=0;c<ctx->num_canais;c++)if(ctx->canais[c].ativo||ctx->canais[c].fase_env!=PT_ENV_INATIVO||ctx->canais[c].pcm.ativo){tem=1;break;}if(!tem)break;pt_gerar_amostras(ctx,buf+tot*2,BLK);tot+=BLK;}
    int ok=(tot>0)?pt_salvar_wav(cam,buf,tot,taxa):0;free(buf);return ok?tot:-1;
}
static inline int pt_renderizar_musica_wav(PT_Contexto *ctx,PT_Musica *m,const char *cam,float max_s){
    if(!ctx||!m||!cam||max_s<=0){return -1;}
    int taxa=(int)ctx->taxa_amostra,mx=(int)(max_s*taxa);
    int16_t *buf=(int16_t*)malloc((size_t)mx*2*sizeof(int16_t));if(!buf)return -1;
    const int BLK=512;float dt=(float)BLK/taxa;int tot=0;
    pt_reproduzir_musica(ctx,m,0);
    while(pt_esta_reproduzindo(ctx)&&tot+BLK<=mx){pt_atualizar(ctx,dt);pt_gerar_amostras(ctx,buf+tot*2,BLK);tot+=BLK;}
    int tail=0,tm=taxa;
    while(tail+BLK<=tm&&tot+BLK<=mx){int tem=0;for(int c=0;c<ctx->num_canais;c++)if(ctx->canais[c].fase_env!=PT_ENV_INATIVO){tem=1;break;}if(!tem)break;pt_gerar_amostras(ctx,buf+tot*2,BLK);tot+=BLK;tail+=BLK;}
    int ok=(tot>0)?pt_salvar_wav(cam,buf,tot,taxa):0;free(buf);return ok?tot:-1;
}


/* ====================================================================
 *  §24  REVERB (SCHROEDER)
 * ==================================================================== */

static inline void pt_ativar_reverb(PT_Contexto *ctx,float tamanho,float amort,float mix){
    PT_Reverb *rv=&ctx->reverb;memset(rv,0,sizeof(*rv));
    float esc=pt__clampf(tamanho,0.1f,2.0f);
    int bc[PT_REVERB_COMBS]={1116,1188,1277,1356,1422,1491,1557,1617};
    int ba[PT_REVERB_ALLPASS]={556,441,341,225};
    for(int i=0;i<PT_REVERB_COMBS;i++){rv->tam_comb[i]=(int)(bc[i]*esc);if(rv->tam_comb[i]<1)rv->tam_comb[i]=1;if(rv->tam_comb[i]>=PT_REVERB_BUF_MAX)rv->tam_comb[i]=PT_REVERB_BUF_MAX-1;}
    for(int i=0;i<PT_REVERB_ALLPASS;i++){rv->tam_ap[i]=(int)(ba[i]*esc);if(rv->tam_ap[i]<1)rv->tam_ap[i]=1;if(rv->tam_ap[i]>=PT_REVERB_BUF_MAX/2)rv->tam_ap[i]=PT_REVERB_BUF_MAX/2-1;}
    rv->realimentacao_comb=0.84f+pt__clampf(tamanho,0,1)*0.1f;
    rv->amortecimento=pt__clampf(amort,0,0.99f);rv->mix=pt__clampf(mix,0,1);rv->ativo=1;
}
static inline void pt_desativar_reverb(PT_Contexto *ctx){ctx->reverb.ativo=0;}
static inline void pt_reverb_mix(PT_Contexto *ctx,float mix){ctx->reverb.mix=pt__clampf(mix,0,1);}
static inline void pt_reverb_amortecimento(PT_Contexto *ctx,float a){ctx->reverb.amortecimento=pt__clampf(a,0,0.99f);}

/* ====================================================================
 *  §25  EQUALIZADOR 3 BANDAS
 * ==================================================================== */

static inline void pt_ativar_eq(PT_Contexto *ctx,float ls_g,float ls_f,float mp_g,float mp_f,float mp_q,float hs_g,float hs_f){
    PT_Equalizador *q=&ctx->eq;memset(q,0,sizeof(*q));float taxa=ctx->taxa_amostra;
    pt__calc_low_shelf(&q->ls_b0,&q->ls_b1,&q->ls_b2,&q->ls_a1,&q->ls_a2,ls_g,ls_f,taxa);
    pt__calc_peak(&q->mp_b0,&q->mp_b1,&q->mp_b2,&q->mp_a1,&q->mp_a2,mp_g,mp_f,mp_q>0?mp_q:0.707f,taxa);
    pt__calc_high_shelf(&q->hs_b0,&q->hs_b1,&q->hs_b2,&q->hs_a1,&q->hs_a2,hs_g,hs_f,taxa);q->ativo=1;
}
static inline void pt_desativar_eq(PT_Contexto *ctx){ctx->eq.ativo=0;}
static inline void pt_eq_graves(PT_Contexto *ctx,float g,float f){
    if(!ctx->eq.ativo){return;}
    pt__calc_low_shelf(&ctx->eq.ls_b0,&ctx->eq.ls_b1,&ctx->eq.ls_b2,&ctx->eq.ls_a1,&ctx->eq.ls_a2,g,f,ctx->taxa_amostra);memset(&ctx->eq.ls_x1,0,4*sizeof(float));
}
static inline void pt_eq_medios(PT_Contexto *ctx,float g,float f,float q){
    if(!ctx->eq.ativo){return;}
    pt__calc_peak(&ctx->eq.mp_b0,&ctx->eq.mp_b1,&ctx->eq.mp_b2,&ctx->eq.mp_a1,&ctx->eq.mp_a2,g,f,q>0?q:0.707f,ctx->taxa_amostra);memset(&ctx->eq.mp_x1,0,4*sizeof(float));
}
static inline void pt_eq_agudos(PT_Contexto *ctx,float g,float f){
    if(!ctx->eq.ativo){return;}
    pt__calc_high_shelf(&ctx->eq.hs_b0,&ctx->eq.hs_b1,&ctx->eq.hs_b2,&ctx->eq.hs_a1,&ctx->eq.hs_a2,g,f,ctx->taxa_amostra);memset(&ctx->eq.hs_x1,0,4*sizeof(float));
}

/* ====================================================================
 *  §26  DISTORÇÃO E OVERDRIVE POR CANAL
 * ==================================================================== */

static inline void pt_ativar_distorcao(PT_Contexto *ctx,int c,PT_TipoDistorcao tipo,float drive,float saida){
    if(c<0||c>=ctx->num_canais){return;}
    PT_Distorcao *d=&ctx->canais[c].distorcao;
    d->ativo=1;d->tipo=tipo;d->drive=drive>0?drive:1;d->saida=pt__clampf(saida,0,1);d->estado=0;
}
static inline void pt_desativar_distorcao(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais)ctx->canais[c].distorcao.ativo=0;}
static inline void pt_distorcao_drive(PT_Contexto *ctx,int c,float drive){if(c>=0&&c<ctx->num_canais)ctx->canais[c].distorcao.drive=drive>0?drive:1;}

/* ====================================================================
 *  §27  RING MODULATOR POR CANAL
 * ==================================================================== */

static inline void pt_ativar_ring_mod(PT_Contexto *ctx,int c,float freq,float mix){
    if(c<0||c>=ctx->num_canais){return;}
    PT_RingMod *r=&ctx->canais[c].ring_mod;
    r->ativo=1;r->freq=freq>0?freq:100;r->mix=pt__clampf(mix,0,1);r->fase=0;
}
static inline void pt_desativar_ring_mod(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais)ctx->canais[c].ring_mod.ativo=0;}
static inline void pt_ring_mod_freq(PT_Contexto *ctx,int c,float f){if(c>=0&&c<ctx->num_canais)ctx->canais[c].ring_mod.freq=f>0?f:1;}

/* ====================================================================
 *  §28  NOISE GATE (BUS)
 * ==================================================================== */

static inline void pt_ativar_noise_gate(PT_Contexto *ctx,float lim,float a_ms,float r_ms){
    PT_NoiseGate *ng=&ctx->noise_gate;ng->limiar=pt__clampf(lim,0,1);
    ng->coef_ataque=1-expf(-1.f/(ctx->taxa_amostra*a_ms/1000));ng->coef_liberacao=1-expf(-1.f/(ctx->taxa_amostra*r_ms/1000));
    ng->ganho_atual=1;ng->ativo=1;
}
static inline void pt_desativar_noise_gate(PT_Contexto *ctx){ctx->noise_gate.ativo=0;}

/* ====================================================================
 *  §29  PLAYER DE AMOSTRA PCM (PT_ONDA_PCM)
 * ==================================================================== */

static inline void pt_pcm_carregar(PT_Contexto *ctx,int c,const int16_t *dados,int n,int taxa,int loop){
    if(c<0||c>=ctx->num_canais||!dados||n<=0){return;}
    PT_PlayerPCM *p=&ctx->canais[c].pcm;
    p->dados=dados;p->num_amostras=n;p->taxa=taxa>0?taxa:(int)ctx->taxa_amostra;p->em_loop=loop;p->pos=0;p->ativo=0;ctx->canais[c].forma_onda=PT_ONDA_PCM;
}
static inline void pt_pcm_tocar(PT_Contexto *ctx,int c,float freq,int vol){
    if(c<0||c>=ctx->num_canais||!ctx->canais[c].pcm.dados)return;
    PT_Canal *ch=&ctx->canais[c];ch->pcm.pos=0;ch->pcm.ativo=1;ch->frequencia=freq;ch->freq_atual=freq;
    ch->volume=pt__clampf((float)vol/PT_VOLUME_MAX,0,1);ch->ativo=1;ch->fase_env=PT_ENV_ATAQUE;ch->env_nivel=0;
}
static inline void pt_pcm_parar(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais){ctx->canais[c].pcm.ativo=0;pt_parar_nota(ctx,c);}}

/* ====================================================================
 *  §30  LOADER DE ARQUIVO WAV
 *
 *  Lê um arquivo .wav PCM 16-bit (mono ou estéreo) e retorna um buffer
 *  int16_t alocado com malloc(). Libere com free() quando não precisar mais.
 * ==================================================================== */

static inline int16_t *pt_carregar_wav(const char *cam,int *n_out,int *taxa_out,int *ch_out){
    if(!cam||!n_out||!taxa_out||!ch_out)return NULL;
    FILE *f=fopen(cam,"rb");if(!f)return NULL;
    uint8_t hdr[44];if(fread(hdr,1,44,f)!=44){fclose(f);return NULL;}
    if(hdr[0]!='R'||hdr[8]!='W'){fclose(f);return NULL;}
    uint16_t fmt=(uint16_t)(hdr[20]|(hdr[21]<<8)),chs=(uint16_t)(hdr[22]|(hdr[23]<<8));
    uint32_t rate=(uint32_t)(hdr[24]|(hdr[25]<<8)|(hdr[26]<<16)|(hdr[27]<<24));
    uint16_t bps=(uint16_t)(hdr[34]|(hdr[35]<<8));
    if(fmt!=1||bps!=16){fclose(f);return NULL;}
    fseek(f,36,SEEK_SET);uint32_t dsz=0;
    while(1){uint8_t hd[8];if(fread(hd,1,8,f)!=8)break;uint32_t csz=(uint32_t)(hd[4]|(hd[5]<<8)|(hd[6]<<16)|(hd[7]<<24));if(hd[0]=='d'&&hd[1]=='a'){dsz=csz;break;}fseek(f,(long)csz,SEEK_CUR);}
    if(!dsz){fclose(f);return NULL;}
    int total=(int)(dsz/2),frames=total/(int)chs;
    int16_t *raw=(int16_t*)malloc((size_t)total*sizeof(int16_t));if(!raw){fclose(f);return NULL;}
    int rd=(int)fread(raw,sizeof(int16_t),(size_t)total,f);fclose(f);if(rd<=0){free(raw);return NULL;}
    int16_t *mono=raw;
    if(chs==2){mono=(int16_t*)malloc((size_t)frames*sizeof(int16_t));if(!mono){free(raw);return NULL;}
        for(int i=0;i<frames;i++)mono[i]=(int16_t)(((int)raw[i*2]+(int)raw[i*2+1])/2);
    free(raw);}
    *n_out=frames;*taxa_out=(int)rate;*ch_out=(int)chs;return mono;
}

/* ====================================================================
 *  §31  PHASER E FLANGER (BUS)
 * ==================================================================== */

static inline void pt_ativar_phaser(PT_Contexto *ctx,float taxa,float prof,float centro,float rf,float mix){
    PT_Phaser *ph=&ctx->phaser;memset(ph,0,sizeof(*ph));ph->taxa=pt__clampf(taxa,.01f,10);
    ph->profundidade=pt__clampf(prof,0,1);ph->centro=pt__clampf(centro,0.001f,0.5f);
    ph->realimentacao=pt__clampf(rf,-0.95f,0.95f);ph->mix=pt__clampf(mix,0,1);ph->modo_flanger=0;ph->ativo=1;
}
static inline void pt_ativar_flanger(PT_Contexto *ctx,float taxa,float prof,float rf,float mix){
    PT_Phaser *ph=&ctx->phaser;memset(ph,0,sizeof(*ph));ph->taxa=pt__clampf(taxa,.01f,5);
    ph->profundidade=pt__clampf(prof,0,1);ph->realimentacao=pt__clampf(rf,-0.95f,0.95f);
    ph->mix=pt__clampf(mix,0,1);ph->modo_flanger=1;ph->ativo=1;
}
static inline void pt_desativar_phaser(PT_Contexto *ctx){ctx->phaser.ativo=0;}

/* ====================================================================
 *  §32  LFO GLOBAL
 * ==================================================================== */

static inline void pt_lfo_ativar(PT_Contexto *ctx,int idx,PT_FormaLFO forma,float taxa,float prof,float offset,int canal,PT_AlvoLFO alvo){
    if(idx<0||idx>=PT_LFO_GLOBAL_MAX){return;}
    PT_LFOGlobal *l=&ctx->lfos[idx];
    l->forma=forma;l->taxa=taxa;l->profundidade=prof;l->offset=offset;l->canal_alvo=canal;l->alvo=alvo;l->fase=0;l->ativo=1;
}
static inline void pt_lfo_desativar(PT_Contexto *ctx,int idx){if(idx>=0&&idx<PT_LFO_GLOBAL_MAX)ctx->lfos[idx].ativo=0;}
static inline void pt_lfo_taxa(PT_Contexto *ctx,int idx,float hz){if(idx>=0&&idx<PT_LFO_GLOBAL_MAX)ctx->lfos[idx].taxa=hz;}
static inline void pt_lfo_profundidade(PT_Contexto *ctx,int idx,float p){if(idx>=0&&idx<PT_LFO_GLOBAL_MAX)ctx->lfos[idx].profundidade=pt__clampf(p,0,1);}
static inline void pt_lfo_sincronizar(PT_Contexto *ctx,int idx){if(idx>=0&&idx<PT_LFO_GLOBAL_MAX)ctx->lfos[idx].fase=0;}

/* ====================================================================
 *  §33  ARPEGGIADOR
 * ==================================================================== */

static inline void pt_arp_iniciar(PT_Arpeggiador *a,int canal,PT_ModoArpejo modo,float bpm,float dur,int oitavas,PT_FormaOnda fo,int vol){
    memset(a,0,sizeof(*a));a->canal=canal;a->modo=modo;a->bpm=bpm>0?bpm:120;a->duracao=dur>0?dur:0.5f;
    a->oitavas=oitavas>=1?(oitavas<=4?oitavas:4):1;a->forma=fo;a->volume=vol;a->direcao=1;
}
static inline void pt_arp_adicionar_nota(PT_Arpeggiador *a,float f){if(a->num_notas<12)a->notas[a->num_notas++]=f;}
static inline void pt_arp_adicionar_acorde(PT_Arpeggiador *a,float raiz,PT_TipoAcorde tipo){
    float ns[5];int n=pt_gerar_acorde(raiz,tipo,ns);for(int i=0;i<n;i++)pt_arp_adicionar_nota(a,ns[i]);
}
static inline void pt_arp_reproduzir(PT_Arpeggiador *a){a->ativo=1;a->indice=0;a->tempo_acc=0;}
static inline void pt_arp_parar(PT_Arpeggiador *a){a->ativo=0;}
static inline void pt_arp_atualizar(PT_Contexto *ctx,PT_Arpeggiador *a,float dt){
    if(!a->ativo||!a->num_notas)return;
    float dur=(60.f/a->bpm)*a->duracao;a->tempo_acc+=dt;
    while(a->tempo_acc>=dur){
        a->tempo_acc-=dur;int total=a->num_notas*a->oitavas,cur=a->indice,ni=0,oi=0;
        switch(a->modo){
            case PT_ARPEJO_SUBIDA:       ni=cur%a->num_notas;oi=cur/a->num_notas;break;
            case PT_ARPEJO_DESCIDA:      ni=(total-1-cur)%a->num_notas;oi=(total-1-cur)/a->num_notas;break;
            case PT_ARPEJO_SOBE_DESCE:   ni=cur%a->num_notas;oi=cur/a->num_notas;break;
            case PT_ARPEJO_ALEATORIO:{uint32_t h=(uint32_t)(a->tempo_acc*99999)^0xDEAD;h=h*1664525u+1013904223u;ni=(int)(h>>16)%a->num_notas;oi=(int)(h>>24)%a->oitavas;break;}
            default:ni=cur%a->num_notas;oi=cur/a->num_notas;break;
        }
        if(oi>=a->oitavas)oi=a->oitavas-1;
        float freq=a->notas[ni]*powf(2.f,(float)oi);
        if(ctx&&a->canal<ctx->num_canais)pt_tocar_nota(ctx,a->canal,freq,a->volume,a->forma);
        if(a->modo==PT_ARPEJO_SOBE_DESCE){cur+=a->direcao;if(cur>=total-1){a->direcao=-1;cur=total-2;}else if(cur<=0){a->direcao=1;}a->indice=cur;}
        else if(a->modo!=PT_ARPEJO_ALEATORIO)a->indice=(cur+1)%total;
    }
}

/* ====================================================================
 *  §34  GERENCIADOR DE VOZES (POLYPHONY / VOICE STEALING)
 * ==================================================================== */

static inline void pt_vozes_iniciar(PT_GerenciadorVozes *gv,int cb,int nv){
    memset(gv,0,sizeof(*gv));gv->canal_base=cb;gv->num_vozes=(nv>=1&&nv<=PT_VOZES_MAX)?nv:4;
    for(int i=0;i<PT_VOZES_MAX;i++)gv->ordem[i]=i;
}
static inline int pt_vozes_tocar(PT_Contexto *ctx,PT_GerenciadorVozes *gv,float freq,int vol,PT_FormaOnda fo){
    int voz=-1,mais_ant=gv->contador+1;
    for(int i=0;i<gv->num_vozes;i++){if(!gv->ativa[i]){voz=i;break;}if(gv->ordem[i]<mais_ant){mais_ant=gv->ordem[i];voz=i;}}
    if(voz<0){return -1;}
    int canal=gv->canal_base+voz;if(canal>=ctx->num_canais)return -1;
    gv->frequencias[voz]=freq;gv->ativa[voz]=1;gv->ordem[voz]=gv->contador++;pt_tocar_nota(ctx,canal,freq,vol,fo);return canal;
}
static inline void pt_vozes_parar(PT_Contexto *ctx,PT_GerenciadorVozes *gv,float freq){
    for(int i=0;i<gv->num_vozes;i++)if(gv->ativa[i]&&fabsf(gv->frequencias[i]-freq)<0.5f){gv->ativa[i]=0;pt_parar_nota(ctx,gv->canal_base+i);return;}
}
static inline void pt_vozes_parar_tudo(PT_Contexto *ctx,PT_GerenciadorVozes *gv){
    for(int i=0;i<gv->num_vozes;i++){gv->ativa[i]=0;pt_parar_nota(ctx,gv->canal_base+i);}
}

/* ====================================================================
 *  §35  TRANSPOSIÇÃO DE PADRÃO
 * ==================================================================== */

static inline void pt_transpor_padrao(PT_Padrao *p,int semitons){p->semitons_transpor=semitons;}
static inline void pt_resetar_transpor_padrao(PT_Padrao *p){p->semitons_transpor=0;}

/* ====================================================================
 *  §36  PITCH SHIFTER POR CANAL
 * ==================================================================== */

static inline void pt_ativar_pitch_shift(PT_Contexto *ctx,int c,float semitons){
    if(c<0||c>=ctx->num_canais){return;}
    PT_PitchShift *ps=&ctx->canais[c].pitch_shift;
    ps->semitons=semitons;ps->ativo=1;memset(ps->buf,0,sizeof(ps->buf));ps->cabeca=0;ps->fase_leitura=0;
}
static inline void pt_desativar_pitch_shift(PT_Contexto *ctx,int c){if(c>=0&&c<ctx->num_canais)ctx->canais[c].pitch_shift.ativo=0;}
static inline void pt_pitch_shift_semitons(PT_Contexto *ctx,int c,float st){if(c>=0&&c<ctx->num_canais)ctx->canais[c].pitch_shift.semitons=st;}



/* ====================================================================
 *  §37  ENVELOPE DE PITCH (ADSR independente para frequência)
 *
 *  Aplica um envelope de frequência separado do envelope de amplitude,
 *  permitindo ataques com chirp, decaimentos de pitch e efeitos de
 *  "pitch drop" estilo percussão sintetizada.
 * ==================================================================== */

/* Envelope de pitch por canal (multiplicador de frequência) */
typedef struct {
    int   ativo;
    float inicio;      /* Multiplicador na nota-on  (ex: 2.0 = uma oitava acima) */
    float fim;         /* Multiplicador no sustain  (1.0 = frequência nominal)   */
    float tempo;       /* Tempo de transição em segundos                         */
    float fase;        /* Estado interno 0.0 → 1.0                               */
    float valor_atual; /* Multiplicador interpolado corrente                      */
} PT_EnvPitch;

/* pt__env_pitch_tick: integrado em pt_definir_env_pitch via automacao */

/* Adiciona ep->valor_atual ao campo freq_atual no gerar_canal */
/* A integração é feita via pt_definir_env_pitch que instala um hook
   de automação de pitch com 2 keyframes (onset → target) */

static inline void pt_definir_env_pitch(PT_Contexto *ctx, int canal,
                                        float multiplicador_inicio,
                                        float multiplicador_fim,
                                        float tempo_s) {
    if (canal < 0 || canal >= ctx->num_canais) return;
    pt_auto_pitch_iniciar(ctx, canal, 0);
    pt_auto_pitch_keyframe(ctx, canal, 0.0f, multiplicador_inicio);
    pt_auto_pitch_keyframe(ctx, canal, tempo_s, multiplicador_fim);
}

/* Presets comuns de envelope de pitch */
static inline void pt_env_pitch_chirp_cima(PT_Contexto *ctx, int c)
    { pt_definir_env_pitch(ctx, c, 0.5f, 1.0f, 0.04f); }
static inline void pt_env_pitch_chirp_baixo(PT_Contexto *ctx, int c)
    { pt_definir_env_pitch(ctx, c, 2.0f, 1.0f, 0.06f); }
static inline void pt_env_pitch_bumbo_fm(PT_Contexto *ctx, int c)
    { pt_definir_env_pitch(ctx, c, 3.5f, 1.0f, 0.12f); }
static inline void pt_env_pitch_tom_sintetico(PT_Contexto *ctx, int c)
    { pt_definir_env_pitch(ctx, c, 4.0f, 1.0f, 0.25f); }

/* ====================================================================
 *  §38  SÍNTESE ADITIVA (até 8 parciais por canal)
 *
 *  Gera formas de onda como soma de senos com amplitudes, frequências
 *  e fases independentes. Preenche uma wavetable que é usada como
 *  PT_ONDA_TABELA no canal.
 * ==================================================================== */

#define PT_ADITIVA_PARCIAIS_MAX 8

typedef struct {
    float harmonic;  /* Número do harmônico (1.0 = fundamental, 2.0 = oitava) */
    float amplitude; /* Amplitude (0.0-1.0)                                    */
    float fase;      /* Fase inicial em radianos                               */
} PT_Parcial;

static inline void pt_sintese_aditiva(float *tabela, PT_Parcial *parciais, int n) {
    for (int i = 0; i < PT_TABELA_TAM; i++) tabela[i] = 0.0f;
    for (int p = 0; p < n; p++) {
        for (int i = 0; i < PT_TABELA_TAM; i++) {
            tabela[i] += parciais[p].amplitude *
                sinf(parciais[p].harmonic * (float)i / PT_TABELA_TAM * 2.0f * PT_PI
                     + parciais[p].fase);
        }
    }
    pt_tabela_normalizar(tabela);
}

/* Preenche parciais a partir de uma série harmônica decrescente (tipo órgão de tubos) */
static inline void pt_parciais_orgao(PT_Parcial *p, int num_registros) {
    float amps[] = {1.0f, 0.5f, 0.33f, 0.25f, 0.2f, 0.16f, 0.14f, 0.12f};
    for (int i = 0; i < num_registros && i < PT_ADITIVA_PARCIAIS_MAX; i++) {
        p[i].harmonic  = (float)(i + 1);
        p[i].amplitude = amps[i];
        p[i].fase      = 0.0f;
    }
}

/* Preenche parciais ímpares (clarinete) */
static inline void pt_parciais_clarinete(PT_Parcial *p, int n) {
    for (int i = 0; i < n && i < PT_ADITIVA_PARCIAIS_MAX; i++) {
        int h = 2 * i + 1;
        p[i].harmonic  = (float)h;
        p[i].amplitude = 1.0f / (float)h;
        p[i].fase      = 0.0f;
    }
}

/* ====================================================================
 *  §39  KARPLUS-STRONG (CORDA PINÇADA FÍSICA)
 *
 *  Algoritmo de Karplus-Strong: uma linha de atraso preenchida com
 *  ruído é continuamente filtrada, simulando a ressonância de uma corda.
 *  Produz sons de cordas pinçadas, harpa, koto, etc.
 *  Buffer interno alocado por canal — use pt_ks_limpar() ao encerrar.
 * ==================================================================== */

#define PT_KS_BUF_MAX  4096  /* Suporta frequências até ~10 Hz a 44100Hz */

typedef struct {
    int   ativo;
    float buf[PT_KS_BUF_MAX];
    int   tam;      /* Comprimento do delay = round(taxa / freq)          */
    int   pos;
    float coef_lp;  /* Coeficiente do filtro de média (0.4-0.5 = brilho)  */
    float amort;    /* Amortecimento adicional (0.0-0.01)                  */
    float ganho;    /* Amplitude de saída                                  */
} PT_KarplusStrong;

/* Inicia e dispara uma nota Karplus-Strong num canal.
   O estado interno é armazenado em ctx->canais[canal].  Como PT_Canal
   não tem campo KS, usamos a tabela_onda + PlayerPCM de forma criativa:
   exponemos via buffer estático por simplicidade nesta implementação. */

/* Buffer global por canal (simple, thread-unsafe) */
static PT_KarplusStrong pt__ks[PT_CANAIS_MAX];

static inline void pt_ks_tocar(PT_Contexto *ctx, int canal, float freq,
                                int volume, float brilho) {
    if (canal < 0 || canal >= ctx->num_canais || freq <= 0.0f) return;
    PT_KarplusStrong *ks = &pt__ks[canal];

    int tam = (int)(ctx->taxa_amostra / freq);
    if (tam < 2) tam = 2;
    if (tam > PT_KS_BUF_MAX) tam = PT_KS_BUF_MAX;

    ks->tam     = tam;
    ks->pos     = 0;
    ks->coef_lp = pt__clampf(brilho, 0.01f, 0.99f);
    ks->amort   = 0.0f;
    ks->ganho   = pt__clampf((float)volume / PT_VOLUME_MAX, 0.0f, 1.0f);
    ks->ativo   = 1;

    /* Preenche buffer com ruído branco */
    uint32_t rng = 0xBADF00Du + (uint32_t)canal;
    for (int i = 0; i < tam; i++) {
        rng = rng * 1664525u + 1013904223u;
        ks->buf[i] = ((float)(rng >> 16) / 32767.5f) - 1.0f;
    }

    /* Canal sintetizador passa por aqui via ganho */
    pt_definir_envelope(ctx, canal, 0.0f, 0.0f, 1.0f, 0.02f);
    ctx->canais[canal].volume    = ks->ganho;
    ctx->canais[canal].ativo     = 0;  /* KS gerencia o sinal diretamente */
    ctx->canais[canal].fase_env  = PT_ENV_INATIVO;
}

/* Gera N amostras Karplus-Strong e mistura em buf (estéreo intercalado) */
static inline void pt_ks_gerar(PT_Contexto *ctx, int canal,
                                int16_t *buf_out, int n) {
    if (canal < 0 || canal >= ctx->num_canais) return;
    PT_KarplusStrong *ks = &pt__ks[canal];
    if (!ks->ativo) return;

    float pan = ctx->canais[canal].pan;
    float ve  = (pan <= 0.0f) ? 1.0f : (1.0f - pan);
    float vd  = (pan >= 0.0f) ? 1.0f : (1.0f + pan);

    for (int i = 0; i < n; i++) {
        int  next = (ks->pos + 1) % ks->tam;
        float s   = ks->buf[ks->pos];

        /* Filtro de média ponderada (Karplus-Strong) */
        ks->buf[ks->pos] = (ks->coef_lp * s +
                            (1.0f - ks->coef_lp) * ks->buf[next])
                           * (1.0f - ks->amort);
        ks->pos = next;

        float out = s * ks->ganho * ctx->volume_master;
        int16_t sv = (int16_t)(pt__clampf(out, -1.0f, 1.0f) * 32767.0f);
        buf_out[i * 2 + 0] = (int16_t)pt__clampf(buf_out[i*2+0] + sv * ve, -32767, 32767);
        buf_out[i * 2 + 1] = (int16_t)pt__clampf(buf_out[i*2+1] + sv * vd, -32767, 32767);
    }
}

static inline void pt_ks_parar(int canal) {
    if (canal >= 0 && canal < PT_CANAIS_MAX) pt__ks[canal].ativo = 0;
}

/* ====================================================================
 *  §40  METRÔNOMO / SINCRONISMO DE BPM
 *
 *  Gera pulsos periódicos de click e expõe callbacks de beat para
 *  sincronizar drum machine, arpeggiador e sequenciador externos.
 * ==================================================================== */

typedef struct {
    int   ativo;
    float bpm;
    int   batidas_por_compasso;  /* Numerador do compasso (ex: 4)          */
    float acumulador;            /* Tempo acumulado em segundos            */
    int   batida_atual;          /* 0 .. batidas_por_compasso-1            */
    int   batida_disparada;      /* Flag: 1 se nova batida neste frame     */
    int   compasso_disparado;    /* Flag: 1 se início de compasso          */
    float volume_acento;         /* Volume do acento (tempo 1) 0-15        */
    float volume_normal;         /* Volume dos outros tempos 0-15          */
    int   canal;                 /* Canal para tocar o click               */
} PT_Metronomo;

static inline void pt_metronomo_iniciar(PT_Metronomo *m, float bpm,
                                        int bat_compasso, int canal) {
    memset(m, 0, sizeof(*m));
    m->bpm                 = bpm > 0.0f ? bpm : 120.0f;
    m->batidas_por_compasso= bat_compasso > 0 ? bat_compasso : 4;
    m->canal               = canal;
    m->volume_acento       = 14.0f;
    m->volume_normal       = 9.0f;
    m->ativo               = 1;
}

static inline void pt_metronomo_parar(PT_Metronomo *m)  { m->ativo = 0; }
static inline void pt_metronomo_retomar(PT_Metronomo *m){ m->ativo = 1; }

static inline void pt_metronomo_bpm(PT_Metronomo *m, float bpm) {
    m->bpm = bpm > 0.0f ? bpm : 120.0f;
}

/* Atualiza o metrônomo; chame a cada frame junto com pt_atualizar().
   Retorna 1 se houve batida neste frame, 0 caso contrário. */
static inline int pt_metronomo_atualizar(PT_Contexto *ctx, PT_Metronomo *m, float dt) {
    if (!m->ativo) return 0;
    float periodo = 60.0f / m->bpm;
    m->batida_disparada   = 0;
    m->compasso_disparado = 0;
    m->acumulador += dt;

    if (m->acumulador >= periodo) {
        m->acumulador -= periodo;
        m->batida_disparada = 1;
        m->compasso_disparado = (m->batida_atual == 0);

        /* Toca click */
        int vol = (m->batida_atual == 0)
                  ? (int)m->volume_acento
                  : (int)m->volume_normal;
        if (m->canal >= 0 && m->canal < ctx->num_canais) {
            pt_definir_envelope(ctx, m->canal, 0.001f, 0.015f, 0.0f, 0.005f);
            float freq = (m->batida_atual == 0) ? 1800.0f : 1200.0f;
            pt_tocar_nota(ctx, m->canal, freq, vol, PT_RUIDO_BRANCO);
        }

        m->batida_atual = (m->batida_atual + 1) % m->batidas_por_compasso;
    }
    return m->batida_disparada;
}

/* ====================================================================
 *  §41  PRESETS DE CANAL (SALVA / RESTAURA CONFIGURAÇÃO)
 *
 *  Captura o estado de configuração de um canal (envelope, efeitos,
 *  filtro, FM, distorção) e restaura mais tarde — sem o estado de
 *  oscilador ou fase, portanto seguro para troca a quente.
 * ==================================================================== */

typedef struct {
    PT_Envelope  envelope;
    PT_Efeitos   efeitos;
    PT_Filtro    filtro;
    PT_FM        fm;
    PT_Distorcao distorcao;
    PT_RingMod   ring_mod;
    float        volume;
    float        pan;
    PT_FormaOnda forma_onda;
} PT_PresetCanal;

static inline void pt_salvar_preset(PT_Contexto *ctx, int canal, PT_PresetCanal *pr) {
    if (canal < 0 || canal >= ctx->num_canais || !pr) return;
    PT_Canal *c = &ctx->canais[canal];
    pr->envelope  = c->envelope;
    pr->efeitos   = c->efeitos;
    pr->filtro    = c->filtro;
    pr->fm        = c->fm;
    pr->distorcao = c->distorcao;
    pr->ring_mod  = c->ring_mod;
    pr->volume    = c->volume;
    pr->pan       = c->pan;
    pr->forma_onda= c->forma_onda;
}

static inline void pt_carregar_preset(PT_Contexto *ctx, int canal, const PT_PresetCanal *pr) {
    if (canal < 0 || canal >= ctx->num_canais || !pr) return;
    PT_Canal *c   = &ctx->canais[canal];
    c->envelope   = pr->envelope;
    c->efeitos    = pr->efeitos;
    c->filtro     = pr->filtro;
    c->fm         = pr->fm;
    c->distorcao  = pr->distorcao;
    c->ring_mod   = pr->ring_mod;
    c->volume     = pr->volume;
    c->pan        = pr->pan;
    c->forma_onda = pr->forma_onda;
}

/* Copia configuração de um canal para outro */
static inline void pt_copiar_canal(PT_Contexto *ctx, int origem, int destino) {
    PT_PresetCanal pr;
    pt_salvar_preset(ctx, origem, &pr);
    pt_carregar_preset(ctx, destino, &pr);
}

/* ====================================================================
 *  §42  WAH-WAH (ENVELOPE FOLLOWER + FILTRO BP)
 *
 *  Detecta a amplitude do sinal do canal e usa como controlador do
 *  cutoff do filtro passa-banda — "auto-wah" sensível ao toque.
 * ==================================================================== */

typedef struct {
    int   ativo;
    float freq_min;       /* Frequência mínima do filtro (Hz)              */
    float freq_max;       /* Frequência máxima do filtro (Hz)              */
    float ressonancia;    /* 0.0-0.99                                       */
    float sensibilidade;  /* Quão rapidamente o follower responde (0-1)     */
    float envelope;       /* Estado interno do follower                     */
    float taxa;           /* Cache da taxa de amostragem                    */
} PT_WahWah;

/* Cada canal pode ter seu próprio wah */
static PT_WahWah pt__wah[PT_CANAIS_MAX];

static inline void pt_ativar_wah(PT_Contexto *ctx, int canal,
                                 float freq_min, float freq_max,
                                 float ressonancia, float sensibilidade) {
    if (canal < 0 || canal >= ctx->num_canais) return;
    PT_WahWah *w    = &pt__wah[canal];
    w->freq_min     = freq_min > 0.0f ? freq_min : 400.0f;
    w->freq_max     = freq_max > 0.0f ? freq_max : 3000.0f;
    w->ressonancia  = pt__clampf(ressonancia, 0.0f, 0.99f);
    w->sensibilidade= pt__clampf(sensibilidade, 0.001f, 1.0f);
    w->envelope     = 0.0f;
    w->taxa         = ctx->taxa_amostra;
    w->ativo        = 1;
    pt_ativar_filtro(ctx, canal, PT_FILTRO_BP, freq_min, ressonancia);
}

static inline void pt_desativar_wah(PT_Contexto *ctx, int canal) {
    if (canal >= 0 && canal < PT_CANAIS_MAX) pt__wah[canal].ativo = 0;
    pt_desativar_filtro(ctx, canal);
}

/* Chame uma vez por amostra gerada para o canal — atualiza o cutoff */
static inline void pt_wah_tick(PT_Contexto *ctx, int canal, float amostra_entrada) {
    if (canal < 0 || canal >= PT_CANAIS_MAX) return;
    PT_WahWah *w = &pt__wah[canal];
    if (!w->ativo) return;

    float amp = fabsf(amostra_entrada);
    w->envelope += (amp - w->envelope) * w->sensibilidade;

    float cutoff = w->freq_min + w->envelope * (w->freq_max - w->freq_min);
    pt_filtro_cutoff(ctx, canal, cutoff);
}

/* ====================================================================
 *  §43  STEREO WIDENER (HAAS + MID-SIDE)
 *
 *  Duas técnicas clássicas de alargamento estéreo:
 *  1. Efeito Haas: atrasa ligeiramente o canal direito (1-30ms)
 *  2. Mid-Side: aumenta ou reduz o lado S em relação ao centro M
 * ==================================================================== */

typedef struct {
    int   ativo;
    int   modo;           /* 0 = Haas, 1 = Mid-Side                       */
    /* Haas */
    float delay_ms;
    float buf_haas[2646]; /* ~60ms a 44100Hz                              */
    int   cab_haas;
    /* Mid-Side */
    float largura;        /* 0.0 = mono, 1.0 = normal, 2.0 = ultra-wide  */
} PT_Widener;

static PT_Widener pt__widener;

static inline void pt_ativar_haas(float delay_ms) {
    PT_Widener *w = &pt__widener;
    memset(w, 0, sizeof(*w));
    w->modo      = 0;
    w->delay_ms  = pt__clampf(delay_ms, 1.0f, 60.0f);
    w->ativo     = 1;
}

static inline void pt_ativar_mid_side(float largura) {
    PT_Widener *w = &pt__widener;
    memset(w, 0, sizeof(*w));
    w->modo    = 1;
    w->largura = pt__clampf(largura, 0.0f, 2.0f);
    w->ativo   = 1;
}

static inline void pt_desativar_widener(void) { pt__widener.ativo = 0; }

/* Aplica widener a um par de amostras L/R */
static inline void pt_widener_processar(float *esq, float *dir, float taxa) {
    PT_Widener *w = &pt__widener;
    if (!w->ativo) return;

    if (w->modo == 0) {
        /* Haas: atrasa canal direito */
        int d = (int)(taxa * w->delay_ms / 1000.0f);
        if (d < 1) d = 1;
        if (d >= 2646) d = 2645;
        int rd = (w->cab_haas - d + 2646) % 2646;
        float delayed = w->buf_haas[rd];
        w->buf_haas[w->cab_haas] = *dir;
        w->cab_haas = (w->cab_haas + 1) % 2646;
        *dir = delayed;
    } else {
        /* Mid-Side */
        float m = (*esq + *dir) * 0.5f;
        float s = (*esq - *dir) * 0.5f * w->largura;
        *esq = m + s;
        *dir = m - s;
    }
}

/* ====================================================================
 *  §44  GRAVADOR DE BUFFER (RECORDER)
 *
 *  Grava o mix final em um buffer circular (ring buffer) para
 *  captura ao vivo, preview ou exportação de trechos.
 * ==================================================================== */

#define PT_RECORDER_MAX (44100 * 30)  /* Até 30 segundos a 44100 Hz */

typedef struct {
    int      ativo;
    int      gravando;
    int16_t *buf;          /* Alocado por pt_recorder_iniciar()           */
    int      capacidade;   /* Em frames estéreo                           */
    int      pos_escrita;
    int      pos_leitura;
    int      frames_gravados;
} PT_Recorder;

static PT_Recorder pt__recorder;

static inline int pt_recorder_iniciar(int max_segundos, float taxa) {
    PT_Recorder *r = &pt__recorder;
    int cap = (int)(taxa * (max_segundos > 0 ? max_segundos : 10));
    if (cap > PT_RECORDER_MAX) cap = PT_RECORDER_MAX;
    free(r->buf);
    r->buf = (int16_t*)calloc((size_t)cap * 2, sizeof(int16_t));
    if (!r->buf) return 0;
    r->capacidade    = cap;
    r->pos_escrita   = 0;
    r->pos_leitura   = 0;
    r->frames_gravados = 0;
    r->gravando      = 0;
    r->ativo         = 1;
    return 1;
}

static inline void pt_recorder_gravar(void)  { pt__recorder.gravando = 1; }
static inline void pt_recorder_pausar(void)  { pt__recorder.gravando = 0; }
static inline void pt_recorder_limpar(void)  {
    pt__recorder.pos_escrita = 0;
    pt__recorder.pos_leitura = 0;
    pt__recorder.frames_gravados = 0;
}
static inline void pt_recorder_destruir(void) {
    free(pt__recorder.buf); pt__recorder.buf = NULL; pt__recorder.ativo = 0;
}

/* Alimenta o recorder com um frame estéreo (chame após pt_gerar_amostras) */
static inline void pt_recorder_alimentar(const int16_t *buf_estereo, int n_frames) {
    PT_Recorder *r = &pt__recorder;
    if (!r->ativo || !r->gravando || !r->buf) return;
    for (int i = 0; i < n_frames; i++) {
        if (r->pos_escrita >= r->capacidade) break;
        r->buf[r->pos_escrita * 2 + 0] = buf_estereo[i * 2 + 0];
        r->buf[r->pos_escrita * 2 + 1] = buf_estereo[i * 2 + 1];
        r->pos_escrita++;
        r->frames_gravados++;
    }
}

/* Exporta o conteúdo gravado para um arquivo .wav */
static inline int pt_recorder_exportar(const char *caminho, float taxa) {
    PT_Recorder *r = &pt__recorder;
    if (!r->ativo || !r->buf || r->frames_gravados <= 0) return 0;
    return pt_salvar_wav(caminho, r->buf, r->frames_gravados, (int)taxa);
}

/* Retorna a duração gravada em segundos */
static inline float pt_recorder_duracao(float taxa) {
    return (taxa > 0.0f) ? (float)pt__recorder.frames_gravados / taxa : 0.0f;
}

/* ====================================================================
 *  §45  UTILITÁRIOS DE TEMPO E RITMO
 * ==================================================================== */

/* Converte duração em batidas para amostras */
static inline int pt_batidas_para_amostras(float batidas, float bpm, float taxa) {
    return (int)((60.0f / bpm) * batidas * taxa);
}

/* Quantiza um tempo em segundos para a grade de batidas mais próxima */
static inline float pt_quantizar_tempo(float tempo_s, float bpm, float grade) {
    float periodo_grade = (60.0f / bpm) * grade;
    return roundf(tempo_s / periodo_grade) * periodo_grade;
}

/* Retorna o phase (0.0-1.0) dentro do compasso atual dado o tempo e BPM */
static inline float pt_fase_compasso(float tempo_s, float bpm, int bat_compasso) {
    float bat_s = 60.0f / bpm;
    float dur_compasso = bat_s * bat_compasso;
    return fmodf(tempo_s, dur_compasso) / dur_compasso;
}

/* Gera uma sequência de notas com duração de swing (par=longa, ímpar=curta) */
static inline float pt_swing_dur(float dur_base, float swing, int passo) {
    if ((passo & 1) == 0)
        return dur_base * (1.0f + pt__clampf(swing, 0.0f, 0.5f));
    else
        return dur_base * (1.0f - pt__clampf(swing, 0.0f, 0.5f));
}

/* ====================================================================
 *  §46  SIDECHAIN COMPRESSOR
 *
 *  O compressor é acionado pela amplitude de um canal "gatilho" (ex: bumbo)
 *  e comprime o volume de outro canal (ex: baixo ou pad).
 *  Efeito de "ducking" clássico em música eletrônica.
 * ==================================================================== */

typedef struct {
    int   ativo;
    int   canal_gatilho;  /* Canal cuja amplitude controla a compressão   */
    int   canal_alvo;     /* Canal que tem seu volume reduzido             */
    float limiar;         /* Nível do gatilho que inicia o duck            */
    float reducao;        /* Quanto reduzir (0.0=silencia, 1.0=sem efeito)*/
    float coef_ataque;
    float coef_liberacao;
    float ganho_atual;    /* Estado interno                                */
} PT_Sidechain;

static PT_Sidechain pt__sidechain[PT_CANAIS_MAX / 2];
static int pt__sidechain_n = 0;

static inline int pt_ativar_sidechain(PT_Contexto *ctx,
                                       int canal_gatilho, int canal_alvo,
                                       float limiar, float reducao,
                                       float ataque_ms, float lib_ms) {
    if (pt__sidechain_n >= PT_CANAIS_MAX / 2) return -1;
    PT_Sidechain *sc  = &pt__sidechain[pt__sidechain_n];
    sc->canal_gatilho = canal_gatilho;
    sc->canal_alvo    = canal_alvo;
    sc->limiar        = pt__clampf(limiar, 0.0f, 1.0f);
    sc->reducao       = pt__clampf(reducao, 0.0f, 1.0f);
    sc->coef_ataque   = 1.0f - expf(-1.0f / (ctx->taxa_amostra * ataque_ms / 1000.0f));
    sc->coef_liberacao= 1.0f - expf(-1.0f / (ctx->taxa_amostra * lib_ms  / 1000.0f));
    sc->ganho_atual   = 1.0f;
    sc->ativo         = 1;
    return pt__sidechain_n++;
}

static inline void pt_desativar_sidechain(int idx) {
    if (idx >= 0 && idx < pt__sidechain_n) pt__sidechain[idx].ativo = 0;
}

/* Atualiza todos os sidechains; chame uma vez por amostra antes de mix */
static inline void pt_sidechain_tick(PT_Contexto *ctx) {
    for (int si = 0; si < pt__sidechain_n; si++) {
        PT_Sidechain *sc = &pt__sidechain[si];
        if (!sc->ativo) continue;
        int cg = sc->canal_gatilho, ca = sc->canal_alvo;
        if (cg < 0 || cg >= ctx->num_canais) continue;
        if (ca < 0 || ca >= ctx->num_canais) continue;

        float nv_gatilho = ctx->canais[cg].env_nivel * ctx->canais[cg].volume;
        float target     = 1.0f;
        if (nv_gatilho > sc->limiar)
            target = sc->reducao;

        float coef = (target < sc->ganho_atual) ? sc->coef_ataque : sc->coef_liberacao;
        sc->ganho_atual += (target - sc->ganho_atual) * coef;

        /* Aplica duck no volume do canal alvo via automação direta */
        ctx->canais[ca].volume = pt__clampf(
            ctx->canais[ca].volume * sc->ganho_atual, 0.0f, 1.0f);
    }
}

/* ====================================================================
 *  FIM — PARTITURA.H  v3.0
 * ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* PARTITURA_H */
