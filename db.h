#ifndef DB_H
#define DB_H

#include <sqlite3.h>

#include "model.h"

int init_db(sqlite3 **db);
int insert_lyrics(sqlite3 *db, Lyrics *lyrics);
int lookup_lyrics(sqlite3 *db, char *query, Lyrics *lyrics);
void close_db(sqlite3 *db);

#endif