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

result = search_file();

#if 0
// Testing
   printf("FN:%s l:%d ", function_name, strlen(function_name)  );
   printf("F10:%2x ", function_name[10]);
   printf("F11:%2x ", function_name[11]);
   printf("F12:%2x ", function_name[12]);
   printf("F13:%2x ", function_name[13]);
#endif // 0

//printf("FFF:%s ", function_name);

if(result == 1 && strcmp(function_name,"handle_help")==0)  {

    //printf("help is coming  ");

     handle_help();

}
//if(strcmp(function_name,"handle_class_statement")==0) handle_class_statement(arg1, arg2);




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
    else printf("I'm not familiar with that kind of sentence\n");

  //  system("PAUSE");
  //  return EXIT_SUCCESS;
} // main loop

} // main

//-----------------------------------------------------------


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

//-------------------------------------------------------------

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












