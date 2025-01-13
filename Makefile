SERVER_SRC = server.c db.c client_handler.c utils.c
SERVER_HDR = db.h client_handler.h model.h utils.h
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_SRC = client.c client_config.c client_operations.c utils.c
CLIENT_HDR = client_config.h client_operations.h model.h utils.h
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

COMMON_HDR = model.h utils.h

server: $(SERVER_SRC) $(SERVER_HDR)
	gcc -o server $(SERVER_SRC) -lsqlite3

client: $(CLIENT_SRC) $(CLIENT_HDR)
	gcc -o client $(CLIENT_SRC)