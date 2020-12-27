#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#define NOT_FOUND   0
#define FOUND       1
//#define MAX_WORDS 40
//#define MAX_LETTERS 20

#define EOF 3
#define CANT_OPEN_FILE 4
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "global.h"


int db_lookup(char*,char*);
int db_root_check(char*,char*);
int db_next_available_id();
int db_get_id(char*);
int db_copy_word(char*, int, char*); // copies string up to a space
int copy_to_delimiter(char*, char*, char delimiter); // copies string up to a delimiter
int db_add_pair(char*, char*);

#endif // DB_H_INCLUDED
