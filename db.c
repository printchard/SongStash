#ifndef DB_C
#define DB_C

#include <stdio.h>
#include <string.h>

#include "db.h"

const char *CREATE_TABLE_SQL = "CREATE TABLE IF NOT EXISTS lyrics (id INTEGER PRIMARY KEY, song_name TEXT, artist TEXT, release_year INTEGER, lyrics TEXT);";

int init_db(sqlite3 **db)
{
  int rc = sqlite3_open("lyrics.db", db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    return 1;
  }

  char *errMsg = 0;

  rc = sqlite3_exec(*db, CREATE_TABLE_SQL, 0, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
    return 1;
  }

  return 0;
}

int insert_lyrics(sqlite3 *db, Lyrics *lyrics)
{
  char *errMsg = 0;
  int rc;

  char *sql = sqlite3_mprintf("INSERT INTO lyrics (song_name, artist, release_year, lyrics) VALUES ('%q', '%q', %d, '%q');", lyrics->song_name, lyrics->artist, lyrics->release_year, lyrics->lyrics);
  rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
    return 1;
  }

  return 0;
}

int lookup_lyrics(sqlite3 *db, char *query, Lyrics *lyrics)
{
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  int count = 0;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    lyrics[count].id = sqlite3_column_int(stmt, 0);
    lyrics[count].song_name = strdup((char *)sqlite3_column_text(stmt, 1));
    lyrics[count].artist = strdup((char *)sqlite3_column_text(stmt, 2));
    lyrics[count].release_year = sqlite3_column_int(stmt, 3);
    lyrics[count].lyrics = strdup((char *)sqlite3_column_text(stmt, 4));
    count++;
  }

  if (rc != SQLITE_DONE)
  {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  sqlite3_finalize(stmt);
  return count;
}

void close_db(sqlite3 *db)
{
  sqlite3_close(db);
}

#endif