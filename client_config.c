#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "client_config.h"

void set_url(char *url)
{
  printf("Setting URL to %s\n", url);
  char line[1024];
  int port = 0;

  FILE *fp = fopen(CONFIG_PATH, "r");
  if (fp == NULL)
  {
    printf("No config file found, creating one\n");
  }
  else
  {
    fread(line, 1, 1024, fp);
    char *split = strchr(line, ':');
    port = atoi(split + 1);
  }
  fp = fopen(CONFIG_PATH, "w");
  if (fp == NULL)
  {
    perror("fopen");
    return;
  }
  fprintf(fp, "%s:%d\n", url, port);
  fclose(fp);
}

char *get_url()
{
  char line[1024];
  FILE *fp = fopen(CONFIG_PATH, "r");
  if (fp == NULL)
  {
    perror("fopen");
    return NULL;
  }
  fread(line, 1, 1024, fp);
  char *split = strchr(line, ':');
  split[0] = '\0';
  fclose(fp);
  char *string = strdup(line);
  return string;
}

void set_port(int port)
{
  printf("Setting port to %d\n", port);
  char line[1024];
  char *url = malloc(1024);
  strcpy(url, "localhost");

  FILE *fp = fopen(CONFIG_PATH, "r");
  if (fp == NULL)
  {
    printf("No config file found, creating one\n");
  }
  else
  {
    fread(line, 1, 1024, fp);
    char *split = strchr(line, ':');
    split[0] = '\0';
    url = strcpy(url, line);
  }

  fp = fopen(CONFIG_PATH, "w");
  if (fp == NULL)
  {
    perror("fopen");
    return;
  }
  fprintf(fp, "%s:%d\n", url, port);
  free(url);
  fclose(fp);
}

int get_port()
{
  char line[1024];
  FILE *fp = fopen(CONFIG_PATH, "r");
  if (fp == NULL)
  {
    perror("fopen");
    return 0;
  }
  fread(line, 1, 1024, fp);
  char *split = strchr(line, ':');
  int port = atoi(split + 1);
  fclose(fp);
  return port;
}