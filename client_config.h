#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#define CONFIG_PATH ".songstash.conf"

void set_url(char *url);
void set_port(int port);
char *get_url();
int get_port();

#endif