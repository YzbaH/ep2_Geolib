CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -fPIC -g
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests

LIB_NAME = geolib
STATIC_LIB = lib$(LIB_NAME).a
DYNAMIC_LIB = lib$(LIB_NAME).so
TEST_EXEC = test_runner

PREFIX ?= /usr/local

# Captura todos os arquivos .c automaticamente
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SRCS))

.PHONY: all clean run test install

# all: Compila a biblioteca e a aplicação
all: $(STATIC_LIB) $(DYNAMIC_LIB)

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
	$(CC) -shared -o $@ $^

# clean: Remove os artefatos gerados pela compilação
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(TEST_EXEC)

# run: Compila quando necessário e executa a aplicação
run: all
	@echo "Aplicação executada com sucesso."

# test: Compila e executa automaticamente os testes
.PHONY: test

test: $(OBJS) $(TEST_OBJS)
	@for teste in $(TEST_DIR)/*.o; do \
		nome=$${teste%.o}; \
		echo "Executando $$nome..."; \
		$(CC) $(CFLAGS) "$$teste" $(OBJS) $(LDFLAGS) -o "$$nome" || exit 1; \
		"$$nome" || exit 1; \
	done

# install: Instala a biblioteca e os arquivos de interface
install: all
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 644 $(STATIC_LIB) $(PREFIX)/lib/
	install -m 755 $(DYNAMIC_LIB) $(PREFIX)/lib/
	install -m 644 $(INC_DIR)/*.h $(PREFIX)/include/