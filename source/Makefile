#flags
CC=gcc
CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -Iinclude

SRCDIR = src
OBJDIR = obj
BIN = bin

# Lista de arquivos fonte
SERVER_SRCS = $(SRCDIR)/server.c $(SRCDIR)/serverCore.c $(SRCDIR)/socketUtils.c $(SRCDIR)/terminalPrinter.c $(SRCDIR)/coordinateUtils.c
CLIENT_SRCS = $(SRCDIR)/client.c $(SRCDIR)/clientCore.c $(SRCDIR)/socketUtils.c $(SRCDIR)/terminalPrinter.c $(SRCDIR)/coordinateUtils.c

# Lista de arquivos objeto
SERVER_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SERVER_SRCS))
CLIENT_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CLIENT_SRCS))

# Nome dos executáveis
SERVER_EXEC = ./bin/server
CLIENT_EXEC = ./bin/client

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

$(CLIENT_EXEC): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(SERVER_EXEC) $(CLIENT_EXEC)
