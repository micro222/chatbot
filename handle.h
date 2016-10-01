#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#define TRUE 1
#define FALSE 0
//#define NULL 0

#include "db.h"
#include <string.h>
#include <stdio.h>

extern int current_user_id;
extern char current_user_name[];
extern int gender_code;
int expecting_name;



void handle_class_question(char*);
void handle_class_statement(char*,char*);
void handle_attribute_statement(char*, char*);
void handle_color_question(char*);
void handle_color_confirmation_question(char*,char*);
void handle_color_statement(char*,char*);
void handle_have_statement(char*, char*);
void handle_location_question(char*);
void handle_ability_question(char*, char*);
void handle_rating_question(char*, char*);
void handle_rating_statement(char*, char*, char*);
void handle_list_question(char*);
void handle_login(char*);
void handle_greetings(void);
void handle_help(void);

#endif // HANDLE_H_INCLUDED
