CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -fPIC -g -MMD -MP
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests

LIB_NAME = geolib
STATIC_LIB = lib$(LIB_NAME).a
DYNAMIC_LIB = lib$(LIB_NAME).so
TEST_EXEC = test_runner
APP_SRC = app/main.c
APP_EXEC = app/main
APP_DYN = app/main_dyn

PREFIX ?= $(HOME)/.local

# Captura todos os arquivos .c automaticamente
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SRCS))
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%,$(TEST_SRCS))

# Arquivos .d gerados por -MMD: dizem quais headers cada .o usa
DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d) app/main.d app/main_dyn.d

.PHONY: all clean run run-dynamic test install

# all: Compila as bibliotecas e as duas versões da aplicação
all: $(STATIC_LIB) $(DYNAMIC_LIB) $(APP_EXEC) $(APP_DYN)

# Compilação dos objetos em src/
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilação dos objetos em tests/
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regras de criação das bibliotecas
$(STATIC_LIB): $(OBJS)
	ar rcs $@ $^

$(DYNAMIC_LIB): $(OBJS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# clean: Remove os artefatos gerados pela compilação
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o \
	      $(TEST_BINS) $(STATIC_LIB) $(DYNAMIC_LIB) \
	      $(TEST_EXEC) $(APP_EXEC) $(APP_DYN) \
	      $(DEPS)

# Aplicação ligada estaticamente (código da biblioteca copiado para dentro do executável)
$(APP_EXEC): $(APP_SRC) $(STATIC_LIB)
	$(CC) $(CFLAGS) $(APP_SRC) $(STATIC_LIB) $(LDFLAGS) -o $@

# Aplicação ligada dinamicamente: usa libgeolib.so em tempo de execução.
# O rpath $ORIGIN/.. faz o executável procurar a .so na pasta acima de app/.
$(APP_DYN): $(APP_SRC) $(DYNAMIC_LIB)
	$(CC) $(CFLAGS) $(APP_SRC) -L. -l$(LIB_NAME) $(LDFLAGS) -Wl,-rpath,'$$ORIGIN/..' -o $@

# run: Compila quando necessário e executa a aplicação (versão estática)
run: $(APP_EXEC)
	./$(APP_EXEC)

# run-dynamic: Executa a aplicação ligada à biblioteca dinâmica
run-dynamic: $(APP_DYN)
	./$(APP_DYN)

# test: Compila e executa todos os testes; roda todos, mostra resumo e
# termina com erro (exit 1) se algum falhar.
test: $(OBJS) $(TEST_OBJS)
	@falhas=0; total=0; \
	for teste in $(TEST_DIR)/*.o; do \
		nome=$${teste%.o}; total=$$((total+1)); \
		echo "Executando $$nome..."; \
		$(CC) $(CFLAGS) "$$teste" $(OBJS) $(LDFLAGS) -o "$$nome" || exit 1; \
		if ! "$$nome"; then echo "[FALHOU] $$nome"; falhas=$$((falhas+1)); fi; \
	done; \
	echo "Resumo: $$((total-falhas)) de $$total testes passaram."; \
	[ $$falhas -eq 0 ]

# install: Instala a biblioteca e os arquivos de interface
install: all
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 644 $(STATIC_LIB) $(PREFIX)/lib/
	install -m 755 $(DYNAMIC_LIB) $(PREFIX)/lib/
	install -m 644 $(INC_DIR)/*.h $(PREFIX)/include/

# Inclui as dependências de headers (o '-' ignora se ainda não existirem)
-include $(DEPS)
