#ifndef UTILS_H
#define UTILS_H

#include "model.h"

int send_lyrics_arr(int socket, Lyrics *lyrics, int count);
int send_lyrics(int socket, Lyrics lyrics);
int recv_lyrics_arr(int socket, Lyrics **lyrics);
int recv_lyrics(int socket, Lyrics *lyrics);
void free_lyrics(Lyrics *lyrics);
void free_lyrics_arr(Lyrics *lyrics, int count);

#endif