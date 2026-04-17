# ╔══════════════════════════════════════════════════════════╗
# ║              PARTITURA.H  v4.0  —  Makefile              ║
# ╚══════════════════════════════════════════════════════════╝
#
# Uso:
#   make              Compila todos os exemplos
#   make run          Compila e executa todos (gera WAVs)
#   make clean        Remove obj/, bin/ e WAVs
#   make <nome>       Compila um exemplo específico
#                     ex: make dungeon_crawler
#
# Saída:
#   obj/<nome>.o      Objeto compilado
#   bin/<nome>        Binário executável
#   *.wav             Gerado ao executar o binário (na pasta raiz)

CC      := gcc
CFLAGS  := -O2 -Wall -Wextra \
            -Wno-unused-function \
            -Wno-unused-variable \
            -Wno-misleading-indentation \
            -I.
LIBS    := -lm

SRCDIR  := exemplos
OBJDIR  := obj
BINDIR  := bin

# Descobre automaticamente todos os .c em exemplos/
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TARGETS := $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%, $(SOURCES))

# ── Alvos principais ──────────────────────────────────────
.PHONY: all run clean help

all: $(TARGETS)

# Compilação: .c → .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c partitura.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link: .o → binário
$(BINDIR)/%: $(OBJDIR)/%.o | $(BINDIR)
	$(CC) $< -o $@ $(LIBS)

# Cria diretórios se não existirem
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# ── Alvo run: compila e executa todos ────────────────────
run: all
	@echo ""
	@echo "┌─────────────────────────────────────────────┐"
	@echo "│  Gerando WAVs de todos os exemplos...       │"
	@echo "└─────────────────────────────────────────────┘"
	@for bin in $(TARGETS); do \
	    name=$$(basename $$bin); \
	    echo ""; \
	    echo "  ▶  $$name"; \
	    ./$$bin; \
	done
	@echo ""
	@echo "  WAVs gerados:"
	@ls -lh *.wav 2>/dev/null | awk '{printf "    %-35s %s\n", $$9, $$5}' || echo "    (nenhum WAV encontrado)"
	@echo ""

# ── Alvo individual (ex: make dungeon_crawler) ────────────
$(addprefix bin/, $(notdir $(TARGETS))): bin/%: obj/%.o | $(BINDIR)
	$(CC) $< -o $@ $(LIBS)

# ── Limpeza ───────────────────────────────────────────────
clean:
	rm -rf $(OBJDIR) $(BINDIR) *.wav
	@echo "  Limpo."

# ── Ajuda ────────────────────────────────────────────────
help:
	@echo ""
	@echo "  PARTITURA.H v4.0 — Makefile"
	@echo ""
	@echo "  make              Compila todos os exemplos"
	@echo "  make run          Compila e gera os WAVs"
	@echo "  make clean        Remove obj/, bin/ e *.wav"
	@echo "  make <nome>       Compila um exemplo, ex:"
	@for src in $(SOURCES); do \
	    echo "    make $$(basename $${src%.c})"; \
	done
	@echo ""
