CREATE DATABASE people;

CREATE SCHEMA IF NOT EXISTS movies;

USE movies

CREATE  TABLE IF NOT EXISTS movie_titles
  ( release_year YEAR,
    title VARCHAR(255) )
  ENGINE=InnoDB;

LOAD DATA LOCAL INFILE '/home/pratap/notes/info/movie-names.csv'
  INTO TABLE movie_titles
  FIELDS 
    TERMINATED BY ','
  LINES 
    TERMINATED BY '\n'
  (release_year, title);

SHOW WARNINGS;
