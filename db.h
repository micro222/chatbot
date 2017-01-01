#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#define NOT_FOUND   0
#define FOUND       1
#define MATCH       2
#define NO_MATCH    3
#define DB_EOF         4
#define CANT_OPEN_FILE 5
#define MAX_WORDS 40
#define MAX_LETTERS 20
#define DEBUG FALSE

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"

int db_check(char*); // returns TRUE if word is in the database
int db_get_value(char*, char*); // give it a key and it gives the value
int db_root_check(char*, char*); // checks if the class matches. Will dig through to the root if needed
int db_check_pair(char*, char*); // returns TRUE if the key and value are in the database
int db_add_pair(char*, char*); // adds a key/value pair to the end of the database
int db_add_pair2(char*, char*, char*);
int db_next_available_id(void);
int db_next_available_id_string(char* id_string);
int db_get_id(char*);
int db_copy_word(char*, int, char*); // copies string up to a space
int copy_to_delimiter(char*, char*, char, int); // copies string up to a delimiter
int db_get_id_string(char*, char*);
int db_get_id_string2(char*, char*);

#endif // DB_H_INCLUDED
