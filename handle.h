#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#define TRUE 1
#define FALSE 0
//#define NULL 0

#include "db.h"
#include <string.h>
#include <stdio.h>

void handle_def_question(char*);
void handle_def_statement(char*,char*);
void handle_attribute_question(char*,char*);
void handle_color_question(char*);
void handle_color_confirmation_question(char*,char*);
void handle_color_statement(char*,char*);

void handle_location_question(char*);

void handle_ability_question(char*, char*);


void handle_list_question(char*);
void handle_help(void);
void handle_login(char*);

#endif // HANDLE_H_INCLUDED
