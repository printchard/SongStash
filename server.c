#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <unistd.h>
#include <string.h>

#include "client_handler.h"
#include "model.h"
#include "db.h"

#define USAGE "Usage: %s <port>\n"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, USAGE, argv[0]);
    return 1;
  }

  int port = atoi(argv[1]);
  if (port == 0)
  {
    fprintf(stderr, USAGE, argv[0]);
    return 1;
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    perror("socket");
    return 1;
  }

  struct sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
  {
    perror("setsockopt(SO_REUSEADDR) failed");
    return 1;
  }

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)))
  {
    perror("bind");
    return 1;
  }

  if (listen(sock, 10))
  {
    perror("listen");
    return 1;
  }

  printf("Server started on port %d\n", port);
  while (1)
  {
    int client_sock = accept(sock, 0, 0);
    if (client_sock == -1)
    {
      perror("accept");
      continue;
    }

    int pid = fork();
    if (pid == -1)
    {
      perror("fork");
      close(client_sock);
      continue;
    }
    if (pid == 0)
    {
      handle_client(client_sock);
    }
    // handle_client(client_sock);
  }
  return 0;
}