#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "model.h"
#include "client_config.h"
#include "utils.h"

int setup_connection()
{
  char *url = get_url();
  int port = get_port();

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    perror("socket");
    return -1;
  }

  struct sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  inet_aton(url, &addr.sin_addr);

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
  {
    perror("connect");
    return -1;
  }

  send(sock, HANDSHAKE, sizeof(HANDSHAKE), 0);
  free(url);
  return sock;
}

void lookup_lyrics(char *song_name)
{
  int socket = setup_connection();
  if (socket == -1)
    return;

  Operation op_type = LOOKUP;
  send(socket, &op_type, sizeof(Operation), 0);
  int song_name_len = strlen(song_name);
  if (song_name_len > 0)
  {
    send(socket, &song_name_len, sizeof(int), 0);
    send(socket, song_name, song_name_len, 0);
  }
  else
  {
    send(socket, &song_name_len, sizeof(int), 0);
  }
  recv(socket, NULL, 10, 0);
  Lyrics *lyrics;
  int count = recv_lyrics_arr(socket, &lyrics);
  printf("Received %d lyrics\n", count);
  for (int i = 0; i < count; i++)
  {
    printf("ID: %d\n", lyrics[i].id);
    printf("Song Name: %s\n", lyrics[i].song_name);
    printf("Artist: %s\n", lyrics[i].artist);
    printf("Release Year: %d\n", lyrics[i].release_year);
    printf("Lyrics: %s\n", lyrics[i].lyrics);
  }
  free(lyrics);
  close(socket);
}

void insert_lyrics(Lyrics *lyrics)
{
  int socket = setup_connection();
  if (socket == -1)
    return;
  Operation op_type = INSERT;
  send(socket, &op_type, sizeof(Operation), 0);
  send_lyrics(socket, *lyrics);
  char buf[30] = {0};
  recv(socket, buf, sizeof(buf), 0);
  printf("%s\n", buf);
  close(socket);
}