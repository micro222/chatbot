#include "main.h"

int main(int argc, char *argv[]){

//char out[MAX_WORDS][MAX_LETTERS];
char id_string[20];
int n;
int result;


while(1){
   printf(">"); // user prompt
   get_string(); // user input
   parse(); // separates sentence into individual words

   // login?
    // my name is _
    if(number_of_words==4 && strcmp(user_words[1],"my")==0 && strcmp(user_words[2],"name")==0 && strcmp(user_words[3],"is")==0){
       handle_login(user_words[4]);
       continue;
    }

// word substitutions
  for(n=1; n <= number_of_words; n++){
	  if (strcmp(user_words[n],"r")==0)    strcpy(user_words[n], "are");
	  //if (strcmp(user_words[n],"does")==0) strcpy(user_words[n], "do");
	  if (strcmp(user_words[n],"has")==0)  strcpy(user_words[n], "have");
	  if (strcmp(user_words[n],"are")==0)  strcpy(user_words[n], "is");
	  if (strcmp(user_words[n],"wants")==0)strcpy(user_words[n], "want");
	  if (strcmp(user_words[n],"feels")==0)strcpy(user_words[n], "feel");
	  if (strcmp(user_words[n],"likes")==0)strcpy(user_words[n], "like");
	  if (strcmp(user_words[n],"i")==0)    strcpy(user_words[n], current_user_name);
	  if (strcmp(user_words[n],"you")==0)  strcpy(user_words[n], "#1");
	  if (strcmp(user_words[n],"am")==0)	strcpy(user_words[n], "is");
	  if (strcmp(user_words[n],"an")==0)    strcpy(user_words[n], "a");
	  result = db_get_id(user_words[n]);
	  sprintf(id_string, "#%d", result);
      if(result > 0) strcpy(user_words[n], id_string);
  }
//----------------

// Check the template file for a matching template
// If found, the required function name and its arguments are returned in global variables
result = search_template_file();
if(result == 0) printf("no matching template\n");

// Help
//if(result == 1 && strcmp(function_name,"handle_help")==0)  {
    //printf("help is coming  ");
//     handle_help();
//}

//printf("\nnumber_of_words: %d\n", number_of_words);

if(result == 1){
    if(strcmp(function_name,"handle_class_statement")==0)          {handle_class_statement(arg1, arg2);    continue;}
    else if(strcmp(function_name,"handle_class_question")==0)      {handle_class_question(arg1);           continue;}
    else if(strcmp(function_name,"handle_attribute_question")==0)  {handle_attribute_question(arg1, arg2); continue;}
    else if(strcmp(function_name,"handle_attribute_statement")==0) {handle_attribute_statement(arg1, arg2);continue;}
    else if(strcmp(function_name,"handle_have_statement")==0)      {handle_have_statement(arg1, arg2);     continue;}
    else if(strcmp(function_name,"handle_have_question")==0)       {handle_have_question(arg1, arg2);      continue;}

    /*
    else if(strcmp(function_name,"handle_ability_question")==0)    handle_ability_question(arg1, arg2);
    else if(strcmp(function_name,"handle_color_confirmation_question")==0) handle_color_confirmation_question(arg1, arg2);
    //else if(strcmp(function_name,"handle_opinion_question")==0)    handle_opinion_question(arg1, arg2);
    //else if(strcmp(function_name,"handle_opinion_statement")==0)   handle_opinion_statement(arg1, arg2);
    */
}
printf("after template search\n");

    // - - - - - - - - - - - - - - - - - - - - - -
    // what is my name
    if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"is")==0 && strcmp(user_words[3],"my")==0 && strcmp(user_words[4],"name")==0){
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

    // one word?
    else if(number_of_words==1){
       handle_single_word();
    }

    // nothing typed?
    else if(number_of_words==0){
      printf("You didn't type anything..\n");
    }

    // default
    else printf("I'm not familiar with that kind of sentence\n");

 } // main loop

} // main

//-----------------------------------------------------------

