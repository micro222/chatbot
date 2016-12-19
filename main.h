#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include "db.h"
#include "handle.h"
//#include "time.h"
#include "hashtable.h"
#include "functions.h"
#include "main.h"
#include "fa.h"
#include "irc.h"
//#define DEBUG TRUE

// Global Variables
int gender_code;
char gender[10];
int expecting_name;
int expecting_gender;
char current_user_id_string[20];
extern char debug_string[200];
//extern char* current_user_name;
 time_t time_of_last_output;
  time_t time_of_last_input;

#endif // MAIN_H_INCLUDED
