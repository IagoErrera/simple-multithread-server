# Variáveis
CC = g++
CFLAGS = -Wall -Wextra
LDFLAGS =
DEBUGFLAGS = -g

# Arquivos
CLIENT_SRC = src/client.c
SERVER_SRC = src/server.c
TEST_SRC = src/test.c
QUEUE_SRC = src/queue/queue.c
CLIENT_BIN = build/client
SERVER_BIN = build/server
TEST_BIN = build/test
QUEUE_OBJ = build/queue.o  

# Alvo principal
all: $(CLIENT_BIN) $(SERVER_BIN)

# Regra para compilar o cliente
$(CLIENT_BIN): $(CLIENT_SRC) $(QUEUE_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ 

# Regra para compilar o servidor
$(SERVER_BIN): $(SERVER_SRC) $(QUEUE_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^  

# Regra para compilar o arquivo de objetos de queue
build/queue.o: src/queue/queue.c src/queue/queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TEST_BIN)
	
$(TEST_BIN): $(TEST_SRC) $(QUEUE_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^  

# Regra para compilar com depuração
debug: CFLAGS += $(DEBUGFLAGS)
debug: clean all

# Regra de limpeza
clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN) $(QUEUE_OBJ)

# Regra para rodar o cliente (exemplo)
run-client: $(CLIENT_BIN)
	./$(CLIENT_BIN)

# Regra para rodar o servidor (exemplo)
run-server: $(SERVER_BIN)
	./$(SERVER_BIN)

run-test: $(TEST_BIN)
	./$(TEST_BIN)

# Declaração de phony targets
.PHONY: all clean debug run-client run-server
