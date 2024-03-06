import sqlite3
import pandas as pd
conn = sqlite3.connect('db.sqlite')
c = conn.cursor()

movies = pd.read_csv('movie_title.csv')
movies.to_sql('movies', conn, if_exists='append', index = False)
