#include <sqlite3.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "client_handler.h"
#include "model.h"
#include "db.h"
#include "utils.h"

void handle_client(int client_sock)
{
  char buf[11] = {0};
  int len = recv(client_sock, buf, sizeof(buf), 0);
  if (len == -1)
  {
    perror("recv");
    close(client_sock);
    return;
  }

  if (strcmp(buf, HANDSHAKE))
  {
    printf("Invalid handshake\n");
    send(client_sock, "Invalid handshake\n", 18, 0);
    close(client_sock);
    return;
  }
  printf("Client connected\n");

  sqlite3 *db;
  if (init_db(&db))
  {
    return;
  }

  Operation op;
  recv(client_sock, &op, sizeof(Operation), 0);
  printf("Received operation %d\n", op);
  switch (op)
  {
  case LOOKUP:
  {
    char *q = "SELECT * FROM lyrics LIMIT 10;";
    Lyrics *lyrics = (Lyrics *)malloc(sizeof(Lyrics) * 10);
    int count = lookup_lyrics(db, q, lyrics);
    printf("Sending %d lyrics\n", count);
    send_lyrics_arr(client_sock, lyrics, count);
    free_lyrics_arr(lyrics, count);
    break;
  }

  case INSERT:
    break;

  default:
    break;
  }
  close(client_sock);
  close_db(db);
}