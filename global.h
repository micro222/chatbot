#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#define MAX_WORDS 80
#define MAX_LETTERS 80

// Global Variables
char user_input[80];
char wholeline[80];
char user_words[MAX_WORDS][MAX_LETTERS];
int number_of_words;
int gender_code;
char current_user_name[20];
int current_user_id ;
char gender[10];
char current_user_id_string[20];

int expecting_name;
int expecting_gender;
char clipboard[100];

extern char debug_string[200];
//extern char* current_user_name;
time_t time_of_last_output;
time_t time_of_last_input;

//char template_line[150];
//char template_line_segments[80][80];
//char template_segments[80][80];
//char template_words[80][80];
char function_name[80];
//char template1[80];
char arg1[40];
char arg2[40];

char key[20];
char value[20];

//#define NULL 0

#endif // GLOBAL_H_INCLUDED
