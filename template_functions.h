#ifndef TEMPLATE_FUNCTIONS_H_INCLUDED
#define TEMPLATE_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

// global variables
char template_line[100];
char template_words[80][100];
char template1[100];
int line_position;
int numberoftemplatewords;
int match;

// function list
void test1(void);
int tokenize(char[100], char*[100], char);
int search_template_file(void);
int extract_template(void);
void split_template(void);
int compare_template(void);
void remove_comments(void);
void extract_function_name(void);
void extract_arg1(void);
void extract_arg2(void);
//int str_to_int(char*);

#endif // TEMPLATE_FUNCTIONS_H_INCLUDED
