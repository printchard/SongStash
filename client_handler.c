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
  printf("Received operation %d\n", (int)op);
  switch (op)
  {
  case LOOKUP:
  {
    char *baseQ = "SELECT * FROM lyrics LIMIT 10;";
    char *q = baseQ;
    char *song_name;
    int song_name_len;
    recv(client_sock, &song_name_len, sizeof(int), 0);
    if (song_name_len > 0)
    {
      song_name = malloc(sizeof(char) * song_name_len);
      recv(client_sock, song_name, sizeof(char) * song_name_len, 0);
      q = malloc(strlen(baseQ) + song_name_len + 1);
      sprintf(q, "SELECT * FROM lyrics WHERE song_name LIKE '%%%s%%';", song_name);
    }
    Lyrics lyrics[50];
    printf("Looking up lyrics: %s\n", q);
    int count = lookup_lyrics(db, q, lyrics);
    printf("Sending %d lyrics\n", count);
    send_lyrics_arr(client_sock, lyrics, count);
    free_lyrics_arr(lyrics, count);
    if (q != baseQ)
    {
      free(q);
      free(song_name);
    }
    break;
  }

  case INSERT:
  {
    Lyrics lyrics;
    recv_lyrics(client_sock, &lyrics);
    if (insert_lyrics(db, &lyrics))
      send(client_sock, "Failed to insert lyrics\n", 25, 0);
    else
      send(client_sock, "Lyrics inserted successfully\n", 30, 0);
  }
  default:
    break;
  }
  close(client_sock);
  close_db(db);
}