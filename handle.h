#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#define TRUE 1
#define FALSE 0
//#define NULL 0

#include "db.h"
#include "functions.h"
#include <string.h>
#include <stdio.h>

void handle_class_question(char*);
void handle_class_statement(char*,char*);
void handle_attribute_question(char*,char*);
void handle_attribute_statement(char*,char*);

void handle_color_question(char*);
void handle_color_confirmation_question(char*,char*);
void handle_color_statement(char*,char*);
void handle_have_statement(char*,char*);
void handle_have_question(char*,char*);

void handle_location_question(char*);

void handle_ability_question(char*, char*);


void handle_list_question(char*);
void handle_help(void);
void handle_login(char*);
void handle_single_word(void);

#endif // HANDLE_H_INCLUDED
