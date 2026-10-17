CC = gcc

# -Iinclude: diz ao gcc para procurar os cabeçalhos (.h) dentro da pasta include
CFLAGS = -Wall -Wextra -Iinclude -fPIC -g
LDFLAGS = -lm

# Diretórios
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests	

# Nomes das bibliotecas e executáveis
LIB_NAME = vecoperations
STATIC_LIB = lib$(LIB_NAME).a
DYNAMIC_LIB = lib$(LIB_NAME).so
TEST_EXEC = test_runner

# Diretório padrão para instalação (Linux/Unix)
PREFIX ?= /usr/local