#ifndef MODEL_H
#define MODEL_H

#define HANDSHAKE "songstash\n"

typedef struct Lyrics
{
  int id;
  char *song_name;
  char *artist;
  int release_year;
  char *lyrics;
} Lyrics;

typedef enum Operation
{
  INSERT,
  LOOKUP
} Operation;

#endif