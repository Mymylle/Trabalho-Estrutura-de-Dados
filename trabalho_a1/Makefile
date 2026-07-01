# Makefile
# Compilacao do sistema de playlist de musicas
# Tema A1 - Estrutura de Dados - UniJorge

CC     = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic
TARGET = playlist
SRCS   = main.c lista.c arquivo.c menu.c
OBJS   = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c playlist.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
