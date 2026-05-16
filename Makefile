# Nome do executável final
TARGET = jogo.exe

# Compilador
CC = gcc

# Diretórios do projeto
SRC_DIR = src
INC_DIR = include
LIB_DIR = lib

# Encontra todos os arquivos .c dentro da pasta src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Substitui a extensão .c por .o para gerar os arquivos objeto
OBJS = $(SRCS:.c=.o)

# Flags do compilador (Avisos, Debug e Diretório de Includes)
CFLAGS = -Wall -g -I$(INC_DIR)

# Flags do linker (Diretório de Libs e bibliotecas do Windows/Raylib)
LDFLAGS = -L$(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm

# Regra padrão executada ao digitar apenas 'make'
all: $(TARGET)

# Regra para gerar o executável final juntando os .o
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regra genérica para compilar cada .c em um .o correspondente
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados e começar do zero
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Declara que 'all' e 'clean' não são nomes de arquivos físicos
.PHONY: all clean