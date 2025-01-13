import sqlite3

# Connect to the database
connection = sqlite3.connect("lyrics.db")

# Insert 9 fake entries into the lyrics table (id, song_name, artist, release_year, lyrics)
cursor = connection.cursor()
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song1', 'artist1', 2001, 'lyrics1')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song2', 'artist2', 2002, 'lyrics2')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song3', 'artist3', 2003, 'lyrics3')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song4', 'artist4', 2004, 'lyrics4')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song5', 'artist5', 2005, 'lyrics5')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song6', 'artist6', 2006, 'lyrics6')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song7', 'artist7', 2007, 'lyrics7')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song8', 'artist8', 2008, 'lyrics8')"
)
cursor.execute(
    "INSERT INTO lyrics(song_name, artist, release_year, lyrics) VALUES ('song9', 'artist9', 2009, 'lyrics9')"
)
connection.commit()
