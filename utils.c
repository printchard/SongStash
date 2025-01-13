#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

int send_lyrics(int socket, Lyrics lyrics)
{
  if (send(socket, &lyrics.id, sizeof(int), 0) == -1)
    return -1;
  int len = strlen(lyrics.song_name);
  if (send(socket, &len, sizeof(int), 0) == -1)
    return -1;
  if (send(socket, lyrics.song_name, len, 0) == -1)
    return -1;
  len = strlen(lyrics.artist);
  if (send(socket, &len, sizeof(int), 0) == -1)
    return -1;
  if (send(socket, lyrics.artist, len, 0) == -1)
    return -1;
  if (send(socket, &lyrics.release_year, sizeof(int), 0) == -1)
    return -1;
  len = strlen(lyrics.lyrics);
  if (send(socket, &len, sizeof(int), 0) == -1)
    return -1;
  if (send(socket, lyrics.lyrics, len, 0) == -1)
    return -1;
  return 0;
}

int send_lyrics_arr(int socket, Lyrics *lyrics, int count)
{
  if (send(socket, &count, sizeof(int), 0) == -1)
    return -1;
  for (int i = 0; i < count; i++)
  {
    if (send_lyrics(socket, lyrics[i]) == -1)
      return -1;
  }
  return 0;
}

int recv_lyrics(int socket, Lyrics *lyrics)
{
  int len;
  if (recv(socket, &lyrics->id, sizeof(int), 0) == -1)
    return -1;
  if (recv(socket, &len, sizeof(int), 0) == -1)
    return -1;
  lyrics->song_name = (char *)malloc(sizeof(char) * len);
  if (recv(socket, lyrics->song_name, sizeof(char) * len, 0) == -1)
    return -1;
  if (recv(socket, &len, sizeof(int), 0) == -1)
    return -1;
  lyrics->artist = (char *)malloc(sizeof(char) * len);
  if (recv(socket, lyrics->artist, sizeof(char) * len, 0) == -1)
    return -1;
  if (recv(socket, &lyrics->release_year, sizeof(int), 0) == -1)
    return -1;
  if (recv(socket, &len, sizeof(int), 0) == -1)
    return -1;
  lyrics->lyrics = (char *)malloc(sizeof(char) * len);
  if (recv(socket, lyrics->lyrics, sizeof(char) * len, 0) == -1)
    return -1;

  return 0;
}

int recv_lyrics_arr(int socket, Lyrics **lyrics)
{
  int count;
  if (recv(socket, &count, sizeof(int), 0) == -1)
    return -1;
  printf("count: %d\n", count);
  *lyrics = (Lyrics *)malloc(sizeof(Lyrics) * count);
  for (int i = 0; i < count; i++)
  {
    if (recv_lyrics(socket, &((*lyrics)[i])) == -1)
      return -1;
  }
  return count;
}

void free_lyrics(Lyrics *lyrics)
{
  free(lyrics->song_name);
  free(lyrics->artist);
  free(lyrics->lyrics);
}

void free_lyrics_arr(Lyrics *lyrics, int count)
{
  for (int i = 0; i < count; i++)
    free_lyrics(&lyrics[i]);
  free(lyrics);
}
