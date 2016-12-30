#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#define TRUE 1
#define FALSE 0
//#define NULL 0

#include "db.h"
#include <string.h>
#include <stdio.h>
#include "functions.h"
#include "main.h"

//extern int current_user_id;
extern char current_user_id_string[20]; // defined in main.c
extern char current_user_name[20];
extern int gender_code;
extern char gender[10];
int expecting_name;
int expecting_gender;
char debug_string[200];

void handle_class_question(char*);
void handle_class_statement(char*,char*);
void handle_attribute_statement(char*, char*);
void handle_attribute_question(char*, char*);
void handle_color_question(char*);
void handle_color_confirmation_question(char*,char*);
void handle_color_statement(char*,char*);
void handle_have_statement(char*, char*);
void handle_have_question(char*, char*);
void handle_location_question(char*);
void handle_ability_question(char*, char*);
void handle_like_question(char*, char*);
void handle_like_statement(char*, char*);
void handle_list_question(char*);
void handle_login(char*);
void handle_greetings(void);
void handle_help(void);
void handle_pronouns(void);
int handle_question(void);
int handle_statement(void);
int handle_command(void);

#endif // HANDLE_H_INCLUDED
