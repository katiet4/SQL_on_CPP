# SQL_on_CPP

types:
  int;
  string

commands:
  CREATE <name_of_database>(<type> <name_of_colomn>, ..., <type> <name_of_colomn>); - create new database;
  ADD <name_of_database>(<name_of_colomn>, ..., <name_of_colomn>) VALUES (<data>, ..., <data>); - add to database new row;
  IMPORT <name_of_database> <name_of_file>; - create file with data of database;
  EXPORT <name_of_file>; - create database from data of file;
  SHOW <name_of_database>; - show database;
  SHOW_DATABASES; - show all databases; 
  
