#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "handle.h"
#include "time.h"

#define TRUE 1
#define FALSE 0
#define MAX_WORDS 40
#define MAX_LETTERS 20
#define DEBUG TRUE
//#define NULL 0

// Global Variables
char user_input[80];
char wholeline[80];
int number_of_words;

char words[MAX_WORDS][MAX_LETTERS];  //
char current_user_name[20]="unknown";
int current_user_id = 0;
int gender_code = 0;
int code;
typedef struct test{
  char* line[80];
  char* template2[80];
  char* function_name[80];
  int parameter1;
  int parameter2;
  int parameter3;
  //int code;
} template_info_type;

//  char current_time[MAX_STRING_LEN];
// char current_time[80];
int current_time;

#if 0
typedef struct {
  char* input[80];
  char* words[80][80];
  char* first_name[80];
  int gender_code;
}user_info_type;
#endif

// Prototypes
void get_string(void);
void parse(void);
int isword(char*);
int is_nonsense_word(char*);
int isconsonant(char);
int isvowel(char);
void handle_help(void);
int tokenize(char*, char*, char);
int separate_words(char*, char[MAX_WORDS][MAX_LETTERS]);
int template_search(char*, template_info_type*);
int check_gender_by_name(char*);
//void get_time(char*);
int get_time(void);
//int isvalidname(char*);

//-------------------------------------------------------

int main(int argc, char *argv[]){

  char out[MAX_WORDS][MAX_LETTERS];
  int n;
  int result;
  int same, token;
  template_info_type template_info;
  char key[80];

  printf("type 'help' for a list of sentences I understand\r\n");
  while(1){
    printf(">"); // user prompt
    get_string(); // user input
    parse(); // separates sentence into individual words

#if 1
    // word substitutions
    for(n=1;n<=number_of_words;n++){
      //if (strcmp(words[n],"does")==0) strcpy(words[n], "do");
      if (strcmp(words[n],"has")==0)  strcpy(words[n], "have");
      if (strcmp(words[n],"are")==0)  strcpy(words[n], "is");
      if (strcmp(words[n],"wants")==0)strcpy(words[n], "want");
      if (strcmp(words[n],"feels")==0)strcpy(words[n], "feel");
      if (strcmp(words[n],"likes")==0)strcpy(words[n], "like");
      if (strcmp(words[n],"i")==0)    strcpy(words[n], current_user_name);
      if (strcmp(words[n],"u")==0)    strcpy(words[n], "you");
      //	  if (strcmp(words[n],"you")==0)  strcpy(words[n], "bot");
      if (strcmp(words[n],"am")==0)	  strcpy(words[n], "is");
      if (strcmp(words[n],"an")==0)	  strcpy(words[n], "a");
    }
#endif

    //---------------
#if 0
    // Work in progress
    // This is the code that makes use of template_search()
    code = template_search(user_input, &template_info);
    printf("\ncode: %d, template: %s, ", code, template_info.template2);
    printf("\r\nfunction: %s\r", template_info.function_name);
    if(template_info.parameter1 > 0){
      printf("\np1: %d\r\n", template_info.parameter1);
    }
    if(template_info.parameter2 > 0){
      printf("\np2: %d\r\n\n\n", template_info.parameter2);
    }

    continue;
#endif
    //----------------

#if 0
    // Does the user input = the template? If so, there are no wild cards
    same = FALSE;
    for(n=1; n<=number_of_words; n++){
      if(strcmp(words[n], out[n])==0){
	same=TRUE;
	break;
      }
    }
#endif
    //------------------

#if 0
    // Experimental
    token=0;
    if(same==TRUE){
      if(strcmp(user_input, "what time is it")==0) token = 1;
      else if(strcmp(user_input, "what is your name")==0) token = 2;
      else if(strcmp(user_input, "hi")==0) token = 3;
      else if(strcmp(user_input, "how are you")==0) token = 4;
      else if(strcmp(user_input, "i am here")==0) token = 5;
    }
    switch(token){
    case 1: printf("i dont have a watch\r\n "); break;
    case 2: printf("joe king\r\n "); break;
    case 3: printf("bye \r\n"); break;
    case 4: printf("could be worse \r\n"); break;
    case 5: printf("where is here? \r\n"); break;
    }
    //printf("%d   ", token);
#endif
    //----------------

#if 0
    // experimenting with delays
    current_time = get_time();
    while (get_time() < current_time +5);
    //printf("time: %d", current_time);
#endif
    //------------------

    // The main sentence processing starts here. Soon this will be replaced by using the templates in templates.txt

    if(number_of_words==1 && strcmp(words[1], "help")==0){
      handle_help();
    }

    // Log in?
    // my name is ___
    if(number_of_words==4 && strcmp(words[1],"my")==0 && strcmp(words[2],"name")==0 && strcmp(words[3],"is")==0){
      handle_login(words[4]);
      continue;
    }

    if(number_of_words==1 && strcmp(words[1], "hi")==0){
      handle_greetings();
      continue;
    }

    if(number_of_words==1 && strcmp(words[1], "hey")==0){
      handle_greetings();
      continue;
    }

    if(number_of_words==1 && strcmp(words[1], "hello")==0){
      handle_greetings();
      continue;
    }

    // Logged in? If not, go no further
    if(current_user_id == 0){
      printf("what is your name?\r\n");
      continue;
    }

    // - - - - MUST BE LOGGED IN TO GET PAST THIS POINT - - - - - - - - - - - - - - - - - -

    // Determine gender from the first name
    // (known person) is male
    if(db_get_id(words[1]) !=0 && strcmp(words[2],"is")==0 && strcmp(words[3],"male")==0 ) {
      sprintf(key, "#%d > gender", current_user_id);
      if(strcmp(words[1],current_user_name)==0)
	gender_code = 1;
      db_add_pair(key, "male");
      continue;
    }

    // my gender is male
    if(number_of_words==4 &&
       strcmp(words[1],"my")==0 && strcmp(words[2],"gender")==0 && strcmp(words[3],"is")==0 && strcmp(words[4],"male")==0 ) {
      sprintf(key, "#%d > gender", current_user_id);
      gender_code = 1;
      db_add_pair(key, "male");
      continue;
    }

    // (known person) is female
    if(db_get_id(words[1]) !=0 && strcmp(words[2],"is")==0 && strcmp(words[3],"female")==0 ) {
      sprintf(key, "#%d > gender", current_user_id);
      if(strcmp(words[1],current_user_name)==0)
	gender_code = 2;
      db_add_pair(key, "female");
      continue;
    }

    // my gender is female
    if(number_of_words==4 &&
       strcmp(words[1],"my")==0 && strcmp(words[2],"gender")==0 && strcmp(words[3],"is")==0 && strcmp(words[4],"female")==0 ) {
      sprintf(key, "#%d > gender", current_user_id);
      gender_code = 2;
      db_add_pair(key, "female");
      continue;
    }

    // this needs to be placed before "___ is ___"
    if(
       number_of_words==3 && strcmp(words[2],"is")==0 && db_root_check(words[3],"color")==MATCH){
      handle_color_statement(words[1],words[3]);
      continue;
    }

    // CLASS (SUBSET OF)
    // what is ___
    if(number_of_words==3 && strcmp(words[1],"what")==0 && strcmp(words[2],"is")==0){
      handle_class_question(words[3]);
      continue;
    }

    // what are ___
    if(number_of_words==3 && strcmp(words[1],"what")==0 && strcmp(words[2],"are")==0){
      handle_class_question(words[3]);
      continue;
    }
    // what is a ___
    if(number_of_words==4 && strcmp(words[1],"what")==0 && strcmp(words[2],"is")==0 && strcmp(words[3],"a")==0){
      handle_class_question(words[4]);
      continue;
    }

    // a __ is a __
    // ex: a cat is an animal
    if(
       number_of_words==5 &&
       strcmp(words[1],"a")==0 &&
       strcmp(words[3],"is")==0 &&
       strcmp(words[4],"a")==0
       ){
      handle_class_statement(words[2],words[5]);
      continue;
    }

    if(number_of_words==4 && strcmp(words[2],"is")==0 && strcmp(words[3],"a")==0){
      handle_class_statement(words[1],words[4]);
      continue;
    }

    if(number_of_words==3 && strcmp(words[2],"is")==0 ){
      handle_class_statement(words[1],words[3]);
      continue;
    }

    // - - - - - - COLORS - - - - - - - - - - - - - - - -
    //
    // what color is ___
    if(number_of_words==4 && strcmp(words[1],"what")==0 && strcmp(words[2],"color")==0&& strcmp(words[3],"is")==0){
      handle_color_question(words[4]);
      continue;
    }

    // is ___ <color>?
    if(number_of_words==3 && strcmp(words[1],"is")==0 && db_root_check(words[3],"color")==FOUND){
      handle_color_confirmation_question(words[2],words[3]);
      continue;
    }

    // ___ is <color>
    // conditions: 3 words, middle word is "is"
    if(number_of_words==3 && strcmp(words[2],"is")==0 && db_root_check(words[3],"color")==FOUND){
      handle_color_statement(words[1],words[3]);
      continue;
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // LOCATION
    // where is ___
    if(number_of_words==3 && strcmp(words[1],"where")==0 && strcmp(words[2],"is")==0){
      handle_location_question(words[3]);
      continue;
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // ABILITY
    // can <subject> <action>
    if(number_of_words==3 && strcmp(words[1],"can")==0 ){
      handle_ability_question(words[2],words[3]);
      continue;
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // rating
    // Template: do you like <subject>
    // Example: do you like beer
    //    else if(number_of_words==4 && strcmp(words[1],"do")==0 && strcmp(words[2],"you")==0 && strcmp(words[3],"like")==0 ){
    //       handle_rating_question();
    //    }
    // Template: __ like __
    // Example: i like beer
    if(number_of_words==3 && strcmp(words[2],"like")==0){
      handle_rating_statement(words[1], words[3], "7");
      continue;
    }

    // Template: <person> hate __
    // Example: i hate beer
    if(number_of_words==3 && strcmp(words[2],"hate")==0){
      handle_rating_statement(words[1], words[3], "0");
      continue;
    }

    // <creature> love ___
    // conditions: 3 words, middle word is "love"
    if(number_of_words==3 && strcmp(words[2],"love")==0){
      handle_rating_statement(words[1], words[3], "10");
      continue;
    }

    // ___ dont like ___
    if(number_of_words==4 && strcmp(words[2],"dont")==0 && strcmp(words[3],"like")==0){
      handle_rating_statement(words[1], words[3], "3");
      continue;
    }

    // Template: does <person> like <subject>
    // Example: does fred like beer
    if(number_of_words==4 && strcmp(words[1],"does")==0 && strcmp(words[3],"like")==0 ){
      handle_rating_question(words[2], words[4]);
      continue;
    }

    // Template: list <class>
    // Example: list action
    if(number_of_words==2 && strcmp(words[1],"list")==0){
      handle_list_question(words[2]);
      continue;
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // "what is my name"
    if(number_of_words==4 && strcmp(words[1],"what")==0 && strcmp(words[2],"is")==0 && strcmp(words[3],"my")==0 && strcmp(words[4],"name")==0){
      printf("%s\n",current_user_name);
      continue;
    }

    // "what is my gender"
    if(number_of_words==4 && strcmp(words[1],"what")==0 && strcmp(words[2],"is")==0 && strcmp(words[3],"my")==0 && strcmp(words[4],"gender")==0){
      switch(gender_code)
	{
	case 1:
	  printf("male\n");
	  break;
	case 2:
	  printf("female\n");
	  break;
	case 0:
	case 3:
	  printf("I don't know\n");
	  break;

	}
      continue;
    }

    // "say my name"
    if(number_of_words==3 && strcmp(words[1],"say")==0 && strcmp(words[2],"my")==0 && strcmp(words[3],"name")==0){
      printf("%s\n",current_user_name);
      continue;
    }

    // Log out
    if(number_of_words==1 && strcmp(words[1],"bye")==0){
      printf("%talk to you later %s\r\n\r\n",current_user_name);
      current_user_name[20]="unknown";
      current_user_id = 0;
      gender_code = 0;
      continue;
    }

    if(number_of_words==1 && strcmp(words[1],"id")==0){
      printf("%d\n",current_user_id);
      continue;
    }

    if(number_of_words==1 && strcmp(words[1],"g")==0){
      printf("%d\n",gender_code);
      continue;
    }

    if(number_of_words==1) {
      if(isword(words[1])==0) {
	printf("Yep, that's a word...\n");
      }
      else
	printf("That's not a word...\n");
      continue;
    }

    // Nothing typed?
    if(number_of_words==0){
      printf("You didn't type anything..\n");
      continue;
    }

    // Default
    printf("I'm not familiar with that kind of sentence\n");

    // - - - - - -
    // experimental
#if 0
    switch(F){
    case: HELP handle_help(); break;
    case: handle_ability_question();  break;
    case: handle_attribute_statement(); break;
    case: handle_class_question(); break;
    case: handle_class_statement(); break;
    case: handle_ability_question(); break;
    case: handle_color_confirmation_question(); break;
    case: handle_color_question(); break;
    case: handle_color_statement(); break;
    case: handle_def_question(); break;
    case: handle_def_statement(); break;
    case: handle_list_question(); break;
    case: handle_location_question(); break;
    case: handle_login(); break;
    case: handle_rating_question(); break;
    case: handle_rating_statement(); break;
    }
#endif

    // - - - - - -


  } // main loop

} // main

//-----------------------------------------------------------

void get_string(void){

  int position;

  for(position = 0; position <= 78; position++){
    user_input[position] = getchar();
    if(user_input[position]==10)break; // CR
    if(user_input[position]==13)break; // LF
  }
  user_input[position] = 0;

}

//--------------------------------------------------------------

void parse(void){

  // input: user_input
  // output: words, number_of_words

  int position = 0;
  int letter_position;
  int word_position;
  //while(1);
  for(word_position=1; word_position < MAX_WORDS; word_position++) {
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){

      // End of user input?
      if(user_input[position]==0 || position >= 80){
        words[word_position][letter_position] = 0;
        number_of_words = word_position;
        return;
      }

      //end of word?
      if(user_input[position]==' '){
        words[word_position][letter_position] = 0;  // terminate the word
        letter_position = 0;  // probably not needed
        position++;  // skip over the space
        break;
      }

      //
      words[word_position][letter_position] = user_input[position];
      position++;
    }
  }

}
//------------------------------------------------------------------

int isvowel(char c1){

  char vowels[6]="aeiouy";
  int i;

  for(i=0;i<6;i++){
    if(c1 == vowels[i])return 0;
  }
  return 1;

}

//---------------------------------------

int isconsonant(char c1){

  char consonants[20]="bcdfghjklmnpqrstvwxz";
  int i;

  for(i=0;i<20;i++){
    if(c1 == consonants[i]) return 0;
  }
  return 1;

}

//-----------------------------------------------------------------------

int is_nonsense_word(char* s1){
  //
  //  curently has trouble with: you, crackpot,apple,substance
  //
  //

  // 3 vowels in a row?
  int i,inarow;
  char *list_nonsense[] = {"ch", "gh", "sc", "sp", "th", "ck", "pp", "tt"};

  inarow=0;
  for(i=0;i<80-3;i++){
    if(user_input[i]==0) break;
    if(isvowel(user_input[i])==0) inarow++;
    else inarow=0;
    if(inarow>=4) break;
  }
  if(inarow>=3)printf("  3 vowels in a row  \n");
  // replace all occurances of CH GH SC SP TH CK PP ST with vowels
  for(i=0;i<80-3;i++){
    if(user_input[i]==0) break;
    for (j=0; j<sizeof(list_nonsense)
    if(strncmp(&user_input[i], "ch", 2)
				
    if((user_input[i]== 'c' && user_input[i+1]== 'h') ||
       (user_input[i]== 'g' && user_input[i+1]== 'h') ||
       (user_input[i]== 's' && user_input[i+1]== 'c') ||
       (user_input[i]== 's' && user_input[i+1]== 'p') ||
       (user_input[i]== 's' && user_input[i+1]== 't') ||
       (user_input[i]== 'p' && user_input[i+1]== 'p') ||
       (user_input[i]== 'c' && user_input[i+1]== 'k') ){
      user_input[i]='a'; user_input[i+1]='a';
    }
  }

  // 3 consonants in a row?
  inarow=0;
  for(i=0;i<80-3;i++){
    if(user_input[i]==0) break;
    if(isconsonant(user_input[i])==0) inarow++;
    else inarow=0;
    if(inarow>=4) break;
  }
  if(inarow>=4)printf("  that's jiberish\n");

}

//--------------------------------------------------------

int isword(char*word_to_lookup){
  FILE *general;

  int result = 1;
  char word_from_list[80];
  char *status;

  //  open word list
  general = fopen("word100k.txt","r");
  if(general == NULL) {printf("fopen failed while trying to open word100k.txt\n");}

  while(1){
    status = fgets(word_from_list,40,general);
    if (status==0)break;
    // remove the newline character
    word_from_list[strlen(word_from_list)-1] = '\0';

    if (strcmp(word_to_lookup, word_from_list) == 0){
      result = 0;
      break;
    }

  }// end of while

  fclose(general);
  return result;

}
// --------------------------------------

void handle_login(char*name)
{
  int result, i;
  int known=FALSE;
  int new = TRUE;
  char first_name[20], id_string[20];
  char s2[20], value[20];
  char key[80];
  int id_number;

  // Proceedure
  //
  // 1 is the person the current user?
  // 2 is this person known? (search for first name in database)
  // 3 if not known, create new entry in database
  // 4 update user_id, user_name, gender)
  //
  ////////////////////////////////////////////////////////////

  // Step 1: check if already current user
  if(strcmp(name, current_user_name)==0)
    {
      printf("You told me that already\n");
      known=TRUE;
      return;
    }

  // Step #2
  id_number = db_get_id(name);
  if(id_number != 0)
    {
      known=TRUE;
      new = FALSE;
      // get gender
      sprintf(key,"#%d > gender", id_number);
      result = db_lookup(key, value);
      if(result != FOUND) {gender_code=0;}
      if(strcmp(value, "male")==0){gender_code=1;}
      if(strcmp(value, "female")==0){gender_code=2;}




    }
  else
    {
      known=FALSE;
    }

  // Step 3: add user to database
  if(known==FALSE)
    {
      // Get an id number
      id_number = db_next_available_id();

      // Add the following to the database
      //   #1 > class: person
      //   #1 > firstname:bob
      //   #1 > gender:male
      itoa(id_number, id_string, 10);
      sprintf(key, "#%s > class", id_string);
      db_add_pair(key, "person");

      sprintf(key,"#%s > firstname", id_string);
      db_add_pair(key, name);

      sprintf(key,"#%s > gender", id_string);
      gender_code = check_gender_by_name(name);
      switch(gender_code)
        {
	case 1:
	  db_add_pair(key, "male"); break;
	case 2:
	  db_add_pair(key, "female");
        }
      known=TRUE;
      new = TRUE;
    }

  // Step 4:
  strcpy(current_user_name, name);
  current_user_id = id_number;
  if(new == TRUE){
    printf("hello %s\n", current_user_name);
  }
  else{
    printf("hi %s\n", current_user_name);
  }
}

//-------------------------------------------------------


/*
  int isvalidname(char* s1){

  //  valid characters are a-z 0-1 _
  if ((isalpha(s1)==0) && (isdigit(s1)==0) && s1!='_'){
  return 0;  // not valid
  }
  else return 1;  // is valid
  }
*/
//--------------------------------------------------

void handle_help(void){
  printf("I can handle the following sentences\r\n\r\n");
  printf(" my name is ___\n");
  printf(" what is my name\n");
  printf(" what is my gender\n");
  printf(" I am male\n");
  printf(" I am female\n");
  printf(" my gender is male\n");
  printf(" my gender is female\n");
  printf(" say my name\n");
  printf(" what color is ___, ex: what color is grass\n");
  printf(" is <subject> <color>, ex: is grass green\n" );
  printf(" where is <object>\n" );
  printf(" can ___ ___, ");
  printf(" what are ___\n" );
  printf(" what is a ___\n" );
  printf(" what is ___\n" );
  printf(" a <object> is a ___, ex: a cat is an animal\n" );
  printf(" ___ is <color>\n" );
  printf(" ___ like ___, ex: I like pizza\n" );
  printf(" ___ hate ___\n" );
  printf(" ___ love ___\n" );
  printf(" ___ dont like ___\n" );
  printf(" do you like ___\n" );
  //printf("who am i, ");
  //printf("i am ___\r\n");
  printf("bye\r\n");
  //printf("is ___ ___, ");
  //printf("what is ___, ");
  //printf("have you heard of ___, ");
  //printf("___ is ___\r\n");
  //printf("can ___ ___, ");
  //printf("do ___ ___, ");
  //printf("___ can ___\r\n");
  //printf("___ like ___, ");
  //printf("do ___ like ___\r\n");
  //printf("___ hates ___, ");
  //printf("do ___ hate ___\r\n");
  //printf("___ is in ___, ");
  //printf("where is ___\r\n");
  //printf("how old is/are ___\r\n");
  //printf("do ___ feel ___, ");
  //printf("___ feels ___\r\n");
  //printf("do ___ want ___, ");
  //printf("___ want _\r\n");
  //printf("do ___ have ___\r\n");
  //printf("what is the ___ of ___, ___ is the ___ of___\r\n");
  //printf("what time is it\r\n");
  //printf("lookup ___\r\n");
  // continue;
}

//-------------------------------------------------------------
// Experimental. Not in use.
int tokenize(char* in_string, char* word_array, char delimiter){

  // input: in_string
  // output: words, number_of_words

  int position = 0;
  int letter_position;
  int word_position;

  for(word_position=1; word_position < MAX_WORDS; word_position++) {
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){
      // End of in_string?
      if(in_string[position]==0 || position >= 80){
	////        word_array[word_position][letter_position] = 0;
        return word_position;
      }

      //end of word?
      if(in_string[position] == delimiter){
	////       word_array[word_position][letter_position] = 0;  // terminate the word
        letter_position = 0;  // probably not needed
        position++;  // skip over the delimiter
        break;
      }

      ////     word_array[word_position][letter_position] = in_string[position];
      position++;

    }
  }

}



// new function for chat 10
// compares user input with a sentence template
//
// example:
//  user input: what color is grass?
//  template  : what color is *, color_question, 4
//
// the old way:
//  else if(number_of_words==4 && strcmp(words[1],"what")==0 && strcmp(words[2],"color")==0&& strcmp(words[3],"is")==0){
//     handle_color_question(words[4]);


// number of words: 4
// word 1: what
// word 2: color
// word 3: is

// function: color_question()
// parameter 1: word 4

// new proceedure:
// parse template by comma
// parse template sentence by space
// compare specified words in user sentence with template sentence


/*

  void template_search (void)
  open template.txt

  outer loop
  read template

  inner loop
  tokenize(template, token_array, ',');
  tokenize(token_array[0], word_array, ' ');

  // do the words match?
  for(i=0, i<WORD_MAX, i++){
  if(words!=word_array[i]) break;
  if(w=='*') continue;
  }
*/

//--------------------------------------------------
// This partialy works, but is not currently in use
//  TEMPLATE SEARCH
//
//  inputs
//      what the user typed
//
//  returns
//      the matching template
//      the result code

//  1) opens the tempate file
//  2) gets a line
//  3) extracts the template
//  4) checks the template to see if it's a match

//int template_search(char*user, char*template2)
//int template_search(char*user, char out[MAX_WORDS][MAX_LETTERS]){
int template_search(char*user, template_info_type* template_info){


#define TEMPLATE_LINE_LENGTH 120

  FILE *template_file_handle;
  int line_position;
  char *status;
  char line[TEMPLATE_LINE_LENGTH];
  char out[MAX_WORDS][MAX_LETTERS];
  char template2[MAX_WORDS][MAX_LETTERS];
  int n;
  int match;
  int number_of_template_words;
  char* temp[80];

  //  open template file
  template_file_handle = fopen("templates.txt","r");
  if(template_file_handle == NULL) return CANT_OPEN_FILE;

  // search for template
  while(1)
    {
      // get a template line
      status = fgets(template_info->line, TEMPLATE_LINE_LENGTH, template_file_handle);

      if (status==0)
        {
	  fclose(template_file_handle);
	  return 0;
        }

      // skip the comments
      if (template_info->line[0] == '/' && template_info->line[1] == '/') continue;  // skip comments

      // skip any line that begins with a space or control character
      if(template_info->line[0] <= ' ')continue;

      // extract the template from the line
      line_position = copy_to_delimiter(template_info->line, template_info->template2, ',', 0);

      // separate the words
      number_of_template_words = separate_words(template_info->template2, out);  // 1d 2d

      // check if the number of words are the same
      if(number_of_template_words != number_of_words) continue;

      // check the words one by one
      match = TRUE;
      for(n=1; n<=number_of_template_words; n++)
        {
	  if(strcmp(out[n], "*") == 0) continue;
	  if(strcmp(out[n], words[n]) != 0)
            {
	      match = FALSE;
	      break;
            }
        }

      if(match == TRUE){
	break;
      }
    }

  // extract function name
  line_position = copy_to_delimiter(template_info->line, template_info->function_name, ',' ,line_position);

  template_info->parameter1 = 0;
  template_info->parameter2 = 0;

  // extract parameter1

  if(line_position>0){
    line_position = copy_to_delimiter(template_info->line, temp, ',' ,line_position);
    //printf("temp:%s pos: %d", temp, line_position);
    template_info->parameter1 = atoi(temp);
  }

  //printf("LP: %d", line_position);

  if(line_position>0){
    // extract parameter2
    line_position = copy_to_delimiter(template_info->line, temp, ',' ,line_position);
    //printf("temp:%s pos: %d", temp, line_position);
    template_info->parameter2 = atoi(temp);
  }

  fclose(template_file_handle);

  return FOUND;  // (found)




}

//-----------------------------------------------------

int separate_words(char* in, char out[MAX_WORDS][MAX_LETTERS]){

  // input:
  // output: out, number_of_words

  int position = 0;
  int letter_position;
  int word_position;
  int number_of_words = 0;

  for(word_position=1; word_position < MAX_WORDS; word_position++) {
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){

      // End of sentence?
      if(in[position]==NULL || position >= 200){
        out[word_position][letter_position] = NULL;
        number_of_words = word_position;
        return number_of_words;
      }

      //end of word?
      if(in[position]==' '){
        out[word_position][letter_position] = NULL;  // terminate the word
        letter_position = 0;  // probably not needed
        position++;  // skip over the space
        break;
      }

      out[word_position][letter_position] = in[position];
      position++;
    }
  }
}

int check_gender_by_name(char* name)
{

#define LINE_LENGTH 20
  FILE *male;
  FILE *female;
  char *status;
  char line[LINE_LENGTH];
  int n, i;

  //  open male file
  male = fopen("male_names.txt","r");
  if(male == NULL)
    return CANT_OPEN_FILE;

  for(n=0; n<1000; n++)
    {
      // get a line
      status = fgets(line, LINE_LENGTH, male);
      if (status==0)
        {
	  fclose(male);
	  break;
        }

      // teminate the word
      for(i=0; i<LINE_LENGTH; i++)
        {
	  if(line[i] == 10)
            {
	      line[i] = 0;
	      break;
            }
        }

      if(strcmp(name, line) == 0)
        {
	  fclose(male);
	  return 1;
        }

    }

  fclose(male);

  //  open female file
  female = fopen("female_names.txt","r");
  if(female == NULL)
    return CANT_OPEN_FILE;

  for(n=0; n<1000; n++)
    {
      // get a line
      status = fgets(line, LINE_LENGTH, female);
      if (status==0)
        {
	  fclose(female);
	  break;
        }

      // teminate the word
      for(i=0; i<LINE_LENGTH; i++)
        {
	  if(line[i] == 10)
            {
	      line[i] = 0;
	      break;
            }
        }

      if(strcmp(name, line) == 0)
        {
	  fclose(female);
	  return 2;
        }

    }
  fclose(female);
  return 3;
}

/*
 * Get current time. Store time as a string in current_time.
 */
int get_time() {
  time_t t;
  struct tm *tm;

  //  current_time[0] = '\0';

  t = time(NULL);
  tm = localtime(&t);

  if (tm == NULL)
    return;

  return (tm->tm_hour*3600) + (tm->tm_min*60) + (tm->tm_sec);
  // sprintf(current_time, "%d:%02d:%02d on %d-%d-%d ",
  //	  tm->tm_hour, tm->tm_min, tm->tm_sec,
  //	  1900 + tm->tm_year, tm->tm_mon, tm->tm_mday);

} /* get_time */











