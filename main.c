#include "main.h"

int main(int argc, char *argv[]){

char out[MAX_WORDS][MAX_LETTERS];
int n;
int result;


#if 0
// STRUCT TEST
typedef struct users{
  int age;
  int weight;
} User;
User user;
user.age = 35;
printf("=== %d ===\n", user.age);
while(1);
#endif // 0


while(1){
   printf(">"); // user prompt
   get_string(); // user input
   parse(); // separates sentence into individual words

// word substitutions
  for(n=1; n <= number_of_words; n++){
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

result = search_file();

#if 0

// Testing
   printf("FN:%s l:%d ", function_name, strlen(function_name)  );
   printf("F10:%2x ", function_name[10]);
   printf("F11:%2x ", function_name[11]);
   printf("F12:%2x ", function_name[12]);
   printf("F13:%2x ", function_name[13]);
#endif // 0

//if(result == 1 && strcmp(function_name,"handle_help")==0)  {
    //printf("help is coming  ");
//     handle_help();
//}



if(strcmp(function_name,"handle_class_statement")==0)          handle_class_statement(arg1, arg2);
else if(strcmp(function_name,"handle_class_question")==0)      handle_class_question(arg1, arg2);
//else if(strcmp(function_name,"handle_attribute_question")==0)  handle_attribute_question(arg1, arg2); // doesnt exist
else if(strcmp(function_name,"handle_attribute_statement")==0) handle_attribute_statement(arg1, arg2); // exists
else if(strcmp(function_name,"handle_color_question")==0)      handle_color_question(arg1);
/*
else if(strcmp(function_name,"handle_ability_question")==0)    handle_ability_question(arg1, arg2);
else if(strcmp(function_name,"handle_list_question")==0)       handle_list_question(arg1);

else if(strcmp(function_name,"handle_color_confirmation_question")==0) handle_color_confirmation_question(arg1, arg2);
//else if(strcmp(function_name,"handle_opinion_question")==0)    handle_opinion_question(arg1, arg2);
//else if(strcmp(function_name,"handle_opinion_statement")==0)   handle_opinion_statement(arg1, arg2);
*/

printf("\noriginal %d\n", number_of_words);


//----------------
#if 0
	if(number_of_words==1 && strcmp(user_words[1], "help")==0){
        handle_help();
	}
#endif


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
  //    handle_class_statement(user_words[1],user_words[3]);
      handle_attribute_statement(user_words[1],user_words[3]);


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
    else printf("I'm not familiar with that kind of sentence\n");

  //  system("PAUSE");
  //  return EXIT_SUCCESS;
} // main loop

} // main

//-----------------------------------------------------------

