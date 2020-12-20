#include "main.h"

int main(int argc, char *argv[]){

char out[MAX_WORDS][MAX_LETTERS];
int n;
int result;

while(1){
   printf(">"); // user prompt
   get_string(); // user input

//   result = check_gender_by_name(user_input);
//   printf("result: %d", result);
//   continue;

   parse(); // separates sentence into individual words

// word substitutions
  for(n=1;n<=number_of_words;n++){
	  if (strcmp(user_words[n],"r")==0)    strcpy(user_words[n], "are");
	  //if (strcmp(user_words[n],"does")==0) strcpy(user_words[n], "do");
	  if (strcmp(user_words[n],"has")==0)  strcpy(user_words[n], "have");
	  if (strcmp(user_words[n],"are")==0)  strcpy(user_words[n], "is");
	  if (strcmp(user_words[n],"wants")==0)strcpy(user_words[n], "want");
	  if (strcmp(user_words[n],"feels")==0)strcpy(user_words[n], "feel");
	  if (strcmp(user_words[n],"likes")==0)strcpy(user_words[n], "like");
//	  if (strcmp(user_words[n],"i")==0)    strcpy(user_words[n], current_user_name);
	  if (strcmp(user_words[n],"u")==0)    strcpy(user_words[n], "you");
	  if (strcmp(user_words[n],"you")==0)  strcpy(user_words[n], "bot");
	  if (strcmp(user_words[n],"am")==0)	strcpy(user_words[n], "is");
	  if (strcmp(user_words[n],"an")==0)    strcpy(user_words[n], "a");
  }
//----------------

search_file();


//----------------

	if(number_of_words==1 && strcmp(user_words[1], "help")==0){
        handle_help();
	}

// login?
    // my name is _
    if(number_of_words==4 && strcmp(user_words[1],"my")==0 && strcmp(user_words[2],"name")==0 && strcmp(user_words[3],"is")==0){
       handle_login(user_words[4]);
       continue;
    }

/*
    if(strcmp(current_user_name,"unknown")==0){
      printf("who is this?\n");
      continue;
    }
*/

    // - - - - - - - - - - - - - - - - - - - - - -
    // DEFINITION (SUBSET OF)
    // what is ___
    if(number_of_words==3 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"is")==0){
       handle_class_question(user_words[3]);
    }
      // what are ___
    else if(number_of_words==3 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"are")==0){
       handle_class_question(user_words[3]);
    }
    // what is a ___
    else if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"is")==0 && strcmp(user_words[3],"a")==0){
       handle_class_question(user_words[4]);
    }
    // a __ is a __
    // ex: a cat is an animal
    else if(
      number_of_words==5 &&
      strcmp(user_words[1],"a")==0 &&
      strcmp(user_words[3],"is")==0 &&
      strcmp(user_words[4],"a")==0
    ){
      handle_class_statement(user_words[2],user_words[5]);
    }
    else if(
      number_of_words==4 &&
      strcmp(user_words[2],"is")==0 &&
      strcmp(user_words[3],"a")==0
    ){
      handle_class_statement(user_words[1],user_words[4]);
    }

    else if(
      number_of_words==3 &&
      strcmp(user_words[2],"is")==0
    ){
      handle_class_statement(user_words[1],user_words[3]);
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // COLORS
    // what color is ___
    else if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"color")==0&& strcmp(user_words[3],"is")==0){
       handle_color_question(user_words[4]);
    }
    // is ___ <color>?
    else if(number_of_words==3 &&
       strcmp(user_words[1],"is")==0 &&
       db_root_check(user_words[3],"color")==0)
       {
       handle_color_confirmation_question(user_words[2],user_words[3]);
    }
    // ___ is <color>
    // conditions: 3 words, middle word is "is"
    else if(number_of_words==3 && strcmp(user_words[2],"is")==0 &&
            db_root_check(user_words[3],"color")==0){
       handle_color_statement(user_words[1],user_words[3]);
    }
    // - - - - - - - - - - - - - - - - - - - - - -
    // LOCATION
    // where is ___
    else if(number_of_words==3 && strcmp(user_words[1],"where")==0 && strcmp(user_words[2],"is")==0){
       handle_location_question(user_words[3]);
    }
    // - - - - - - - - - - - - - - - - - - - - - -
    // ABILITY
    // can <subject> <action>
    else if(number_of_words==3 && strcmp(user_words[1],"can")==0 ){
       handle_ability_question(user_words[2],user_words[3]);
    }
    // - - - - - - - - - - - - - - - - - - - - - -
    // OPINION
    // Template: do you like <subject>
    // Example: do you like beer
//    else if(number_of_words==4 && strcmp(user_words[1],"do")==0 && strcmp(user_words[2],"you")==0 && strcmp(user_words[3],"like")==0 ){
//       handle_opinion_question();
//    }
    // Template: __ like __
    // Example: i like beer
    else if(number_of_words==3 && strcmp(user_words[2],"like")==0){
       handle_opinion_statement(user_words[1], user_words[3], "7");
    }
    // Template: <person> hate __
    // Example: i hate beer
    else if(number_of_words==3 && strcmp(user_words[2],"hate")==0){
       handle_opinion_statement(user_words[1], user_words[3], "0");
    }
    // <creature> love ___
    // conditions: 3 words, middle word is "love"
    else if(number_of_words==3 && strcmp(user_words[2],"love")==0){
       handle_opinion_statement(user_words[1], user_words[3], "10");
    }
    // ___ dont like ___
    else if(number_of_words==4 && strcmp(user_words[2],"dont")==0 && strcmp(user_words[3],"like")==0){
       handle_opinion_statement(user_words[1], user_words[3], "3");
    }

    // Template: does <person> like <subject>
    // Example: does fred like beer
    else if(number_of_words==4 && strcmp(user_words[1],"does")==0 && strcmp(user_words[3],"like")==0 ){
       handle_opinion_question(user_words[2], user_words[4]);
    }

    // Template: list <def>
    // Example: list action
    else if(number_of_words==2 && strcmp(user_words[1],"list")==0){
       handle_list_question(user_words[2]);
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // what is my name
    else if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"is")==0 && strcmp(user_words[3],"my")==0 && strcmp(user_words[4],"name")==0){
       printf("%s\n",current_user_name);
    }

    // what is my gender
    else if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"is")==0 && strcmp(user_words[3],"my")==0 && strcmp(user_words[4],"gender")==0){
            switch(gender_code)
            {
            case 0:
            case 3:
                printf("I don't know. I can't tell from your name\n");
                break;
            case 1:
                printf("male, based on your name\n");
                break;
            case 2:
                printf("female, based on your name\n");
                break;
            }
    }

    // say my name
    else if(number_of_words==3 && strcmp(user_words[1],"say")==0 && strcmp(user_words[2],"my")==0 && strcmp(user_words[3],"name")==0){
       printf("%s\n",current_user_name);
    }

   else if(number_of_words==1 && strcmp(user_words[1],"id")==0){
       printf("%d\n",current_user_id);
    }

   else if(number_of_words==1 && strcmp(user_words[1],"g")==0){
       printf("%d\n",gender_code);
    }

    // one word?
    else if(number_of_words==1){
      if(isword(user_words[1])==0){
        printf("Yep, that's a word...\n");
      }
      else printf("That's not a word...\n");
    }

    // nothing typed?
    else if(number_of_words==0){
      printf("You didn't type anything..\n");
    }

    // default
    else printf("I'm not familiar with that kind of sentance\n");

  //  system("PAUSE");
  //  return EXIT_SUCCESS;
} // main loop

} // main

//-----------------------------------------------------------
/*
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
        user_words[word_position][letter_position] = 0;
        number_of_words = word_position;
        return;
      }

      //end of word?
      if(user_input[position]==' '){
        user_words[word_position][letter_position] = 0;  // terminate the word
        letter_position = 0;  // probably not needed
        position++;  // skip over the space
        break;
      }

      //
      user_words[word_position][letter_position] = user_input[position];
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

inarow=0;
for(i=0;i<80-3;i++){
  if(user_input[i]==0) break;
  if(isvowel(user_input[i])==0) inarow++;
  else inarow=0;
  if(inarow>=4) break;
}
if(inarow>=3)printf("  3viar  \n");  // (3 vowels in arow)

// replace all occurances of CH GH SC SP TH CK PP ST with vowels
for(i=0;i<80-3;i++){
  if(user_input[i]==0) break;
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
if(inarow>=4)printf("  pile of garbage!  \n");

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
*/
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
// 2 is this person known? (search for first_name:s1)
// 3 if not known, create new entry
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
    }
    else
    {
        known=FALSE;
    }

// Step 3: add to database
    if(known==FALSE)
    {
        // Get an id number
        id_number = db_next_available_id();
        // Add the following to the database
        //   #1 > def: person
        //   #1 > firstname:bob
        //   #1 > gender:male
        itoa(id_number, id_string, 10);

        strcpy(key, "#");
        strcat(key, id_string);
        strcat(key, " > def");
        db_add_pair(key, "person");

        strcpy(key, "#");
        strcat(key, id_string);
        strcat(key, " > firstname");
        db_add_pair(key, name);


        strcpy(key, "#");
        strcat(key, id_string);
        strcat(key, " > gender");
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
	   printf(" say my name\n");
	   printf(" what color is ___, ex: what color is grass\n");
	   printf(" is <subject> <color>, ex: is grass green\n" );
	   printf(" where is <object>\n" );
	   printf(" can ___ ___, ");
	   printf(" what are ___\n" );
	   printf(" what is a ___\n" );
       printf(" what is _\n" );
	   printf(" a <object> is a _, ex: a cat is an animal\n" );
	   printf(" ___ is <color>\n" );
	   printf(" ___ like _, ex: I like pizza\n" );
	   printf(" ___ hate _\n" );
	   printf(" ___ love _\n" );
	   printf(" ___ dont like _\n" );
       printf(" do you like ___\n" );
        //printf("who am i, ");
		//printf("i am  _\r\n");
		//printf("bye\r\n");
		//printf("is _ _, ");
		//printf("what is _, ");
		//printf("have you heard of _, ");
		//printf("_ is _\r\n");
		//printf("can _ _, ");
		//printf("do _ _, ");
		//printf("_ can _\r\n");
		//printf("_ like _, ");
		//printf("do _ like _\r\n");
		//printf("_ hates _, ");
		//printf("do _ hate _\r\n");
		//printf("_ is in _, ");
		//printf("where is _\r\n");
		//printf("how old is/are _\r\n");
		//printf("do _ feel _, ");
		//printf("_ feels _\r\n");
		//printf("do _ want _, ");
		//printf("_ want _\r\n");
		//printf("do _ have _\r\n");
		//printf("what is the _ of _, _ is the _ of_\r\n");
		//printf("what time is it\r\n");
        //printf("lookup _\r\n");
       // continue;
}

//-------------------------------------------------------------
/*
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

/*

// new function for chat 10
// compares user input with a sentance template
//
// example:
//  user input: what color is grass?
//  template  : what color is *, color_question, 4
//
// the old way:
  //  else if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"color")==0&& strcmp(user_words[3],"is")==0){
  //     handle_color_question(user_words[4]);


// number of words: 4
// word 1: what
// word 2: color
// word 3: is

// function: color_question()
// parameter 1: word 4

// new proceedure:
// parse template by comma
// parse template sentance by space
// compare specified words in user sentance with template sentance


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
/*
//--------------------------------------------------
//
//  TEMPLATE SEARCH
//
//  inputs
//
//
//  returns
//
//
//  1) opens the tempate file
//  2) gets a line
//  3) extracts the template
//  4) checks the template to see if it's a match

int template_search(char*user, char*template2)
{

#define TEMPLATE_LINE_LENGTH 120
    FILE *templatex;
    int linepos;
    char *status;
    char line[TEMPLATE_LINE_LENGTH];
    char out[MAX_WORDS][MAX_LETTERS];
    int n;
    int match;
    int number_of_words2;



    //  open template file
    templatex = fopen("templates.txt","r");
    if(templatex == NULL) return CANT_OPEN_FILE;

    // search for template
    while(1)
    {
        // get a template line
        status = fgets(line, TEMPLATE_LINE_LENGTH, templatex);
        if (status==0)
        {
            fclose(templatex);
            return 0;
        }

        if (line[0] == '/' && line[1] == '/') continue;  // skip comments
        if(line[0] <= ' ')continue; // skip any line that begins with a space or control character

        // extract the template
        linepos = copy_to_delimiter(line, template2, ',');
        number_of_words2 = separate_words(template2, out);

        if(number_of_words2 != number_of_words) continue;

#if 1
        match = TRUE;
        for(n=1; n<=number_of_words2; n++)
        {
            if(strcmp(out[n], "*") == 0) continue;
            if(strcmp(out[n], user_words[n]) != 0)
            {
                match = FALSE;
                // printf("NO MATCH: %s, %s\r\n\n", out[n], user_words[n]);
                break;
            }
        }

#endif

        if(match == TRUE) printf("template match: %s\r\n\n", template2);

    }
    fclose(templatex);

    return template2;  // (found)

}
*/
//-----------------------------------------------------


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
    if(male == NULL) return CANT_OPEN_FILE;

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

    //  open female file
    female = fopen("female_names.txt","r");
    if(female == NULL) return CANT_OPEN_FILE;

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
return 3;
}












