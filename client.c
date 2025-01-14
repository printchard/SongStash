#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "client_config.h"
#include "client_operations.h"

#define USAGE "Usage: %s <command>\n"
#define HELP "Commands:\n"                                             \
             "  help <command>\n"                                      \
             "  insert <song_name> <artist> <release_year> <lyrics>\n" \
             "  lookup [opts...]\n"                                    \
             "  config [set | get] [url | port]\n"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, USAGE, argv[0]);
    return 0;
  }

  if (strcmp(argv[1], "help") == 0)
  {
    if (argc < 3)
    {
      fprintf(stderr, HELP);
      return 1;
    }

    if (strcmp(argv[2], "insert") == 0)
    {
      fprintf(stderr, "Usage: %s insert <song_name> <artist> <release_year> <lyrics>\n", argv[0]);
    }
    else if (strcmp(argv[2], "lookup") == 0)
    {
      fprintf(stderr, "Usage: %s lookup [opts...]\n", argv[0]);
    }
    else if (strcmp(argv[2], "config") == 0)
    {
      fprintf(stderr, "Usage: %s config [set | get] [url | port]\n", argv[0]);
    }
    else
    {
      fprintf(stderr, "Unknown command: %s\n", argv[2]);
      return 1;
    }
    return 0;
  }

  if (strcmp(argv[1], "insert") == 0)
  {
    if (argc < 6)
    {
      fprintf(stderr, "Usage: %s insert <song_name> <artist> <release_year> <lyrics>\n", argv[0]);
      return 1;
    }

    Lyrics lyrics;
    lyrics.song_name = argv[2];
    lyrics.artist = argv[3];
    lyrics.release_year = atoi(argv[4]);
    lyrics.lyrics = argv[5];
    insert_lyrics(&lyrics);
    }
  else if (strcmp(argv[1], "lookup") == 0)
  {
    lookup_lyrics();
  }
  else if (strcmp(argv[1], "config") == 0)
  {
    if (argc < 4)
    {
      fprintf(stderr, "Usage: %s config [set | get] [url | port]\n", argv[0]);
      return 1;
    }

    if (strcmp(argv[2], "set") == 0)
    {
      if (strcmp(argv[3], "url") == 0)
        set_url(argv[4]);
      else if (strcmp(argv[3], "port") == 0)
        set_port(atoi(argv[4]));
      else
      {
        fprintf(stderr, "Unknown config option: %s\n", argv[3]);
        return 1;
      }
    }
    else if (strcmp(argv[2], "get") == 0)
    {
      if (strcmp(argv[3], "url") == 0)
      {
        char *url = get_url();
        printf("URL: %s\n", url);
        free(url);
      }
      else if (strcmp(argv[3], "port") == 0)
      {
        int port = get_port();
        printf("Port: %d\n", port);
      }
      else
      {
        fprintf(stderr, "Unknown config option: %s\n", argv[3]);
        return 1;
      }
    }
    else
    {
      fprintf(stderr, "Unknown config command: %s\n", argv[2]);
      return 1;
    }
  }
  return 0;
}