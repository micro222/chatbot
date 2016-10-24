#include "main.h"



//-------------------------------------------------------

int main(void) {

//   char out[MAX_WORDS][MAX_LETTERS];
   int n;
   char temp[40][20];
   char key[80];



// Some initializing
   gender_code = 0;

   strcpy(current_user_id_string, "#0");
   strcpy(gender, "unknown");
   strcpy(current_user_name, "unknown");
   expecting_name = FALSE;

   printf("type 'help' for a list of sentences I understand\r\n");

   // THE MAIN LOOP
   while(1) {
      printf(">"); // user prompt
      get_string(); // get user input and store in user_input[]
      parse(); // separate the sentence into individual words

#if 1
      // word substitutions
      for(n=1; n<=number_of_words; n++) {
         //if (strcmp(words[n],"does")==0) strcpy(words[n], "do");
         if (strcmp(words[n],"has")==0)  strcpy(words[n], "have");
         if (strcmp(words[n],"are")==0)  strcpy(words[n], "is");
         if (strcmp(words[n],"wants")==0)strcpy(words[n], "want");
         if (strcmp(words[n],"feels")==0)strcpy(words[n], "feel");
         if (strcmp(words[n],"likes")==0)strcpy(words[n], "like");
      //   if (strcmp(words[n],"i")==0)    strcpy(words[n], current_user_name);
      if (strcmp(words[n],"u")==0)    strcpy(words[n], "you");
         if (strcmp(words[n],"am")==0)	  strcpy(words[n], "is");
         if (strcmp(words[n],"an")==0)	  strcpy(words[n], "a");
       //  if (strcmp(words[n],"you")==0)	  strcpy(words[n], "ivan");
      }
#endif

#if 0
      // Work in progress
      // This is the code that makes use of template_search()
      code = template_search(user_input, &template_info);
      printf("\ncode: %d, template: %s, ", code, template_info.template2);
      printf("\r\nfunction: %s\r", template_info.function_name);
      if(template_info.parameter1 > 0) {
         printf("\np1: %d\r\n", template_info.parameter1);
      }
      if(template_info.parameter2 > 0) {
         printf("\np2: %d\r\n\n\n", template_info.parameter2);
      }

      continue;
#endif
      //----------------

#if 0
      // Does the user input = the template? If so, there are no wild cards
      same = FALSE;
      for(n=1; n<=number_of_words; n++) {
         if(strcmp(words[n], out[n])==0) {
            same=TRUE;
            break;
         }
      }
#endif
      //------------------

#if 0
      // Experimental
      token=0;
      if(same==TRUE) {
         if(strcmp(user_input, "what time is it")==0) token = 1;
         else if(strcmp(user_input, "what is your name")==0) token = 2;
         else if(strcmp(user_input, "hi")==0) token = 3;
         else if(strcmp(user_input, "how are you")==0) token = 4;
         else if(strcmp(user_input, "i am here")==0) token = 5;
      }
      switch(token) {
      case 1:
         printf("i dont have a watch\r\n ");
         break;
      case 2:
         printf("joe king\r\n ");
         break;
      case 3:
         printf("bye \r\n");
         break;
      case 4:
         printf("could be worse \r\n");
         break;
      case 5:
         printf("where is here? \r\n");
         break;
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

      // The main sentence processing starts here.
      // Soon this will be replaced by using the templates in templates2.txt

      if(number_of_words==1 &&
      strcmp(words[1], "help")==0) {
         handle_help();
      }

      //Dealing with 1 word replies to robot questions
      //expected template: my name is *
      if (expecting_name == TRUE && number_of_words == 1) {
         strcpy(temp[1],"my");
         strcpy(temp[2],"name");
         strcpy(temp[3],"is");
         strcpy(temp[4], words[1]);
         memcpy(words, temp, 800);  // MAX_WORDS * MAX_LETTERS
         number_of_words = 4;
         printf("%s,%s,%s,%s\n", words[1],words[2],words[3],words[4]);
      }
      expecting_name = FALSE;

      // Log in?
      // my name is ___
      if(number_of_words==4 &&
      strcmp(words[1],"my")==0 &&
      strcmp(words[2],"name")==0 &&
      strcmp(words[3],"is")==0) {
         handle_login(words[4]);
         continue;
      }

      if(number_of_words==1 &&
      strcmp(words[1], "hi")==0) {
         handle_greetings();
         continue;
      }

      if(number_of_words==1 &&
      strcmp(words[1], "hey")==0) {
         handle_greetings();
         continue;
      }

      if(number_of_words==1 &&
      strcmp(words[1], "hello")==0) {
         handle_greetings();
         continue;
      }


#if 1
      // Logged in? If not, go no further. This can be disabled for testing purposes
      if(strcmp(current_user_id_string, "unknown") == 0) {
         printf("what is your name?\r\n");
         continue;
      }
#endif

      // - - - - MUST BE LOGGED IN TO GET PAST THIS POINT - - - - - - -  - - - - - -

      // my gender is male
      if(number_of_words == 4 &&
      strcmp(words[1],"my")==0 &&
      strcmp(words[2],"gender")==0 &&
      strcmp(words[3],"is")==0 &&
      strcmp(words[4],"male")==0 ) {
         sprintf(key, "%s > gender", current_user_id_string);
         gender_code = 1;
         strcpy(gender, "male");
         db_add_pair(key, "male");
         continue;
      }

      // my gender is female
      if(number_of_words==4 &&
      strcmp(words[1],"my")==0 &&
      strcmp(words[2],"gender")==0 &&
      strcmp(words[3],"is")==0 &&
      strcmp(words[4],"female")==0 ) {
         sprintf(key, "%s > gender", current_user_id_string);
         strcpy(gender, "female");
         db_add_pair(key, "female");
         continue;
      }

      // CLASS (SUBSET OF)
      // what is ___
      if(number_of_words==3 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0) {
         handle_class_question(words[3]);
         continue;
      }

      // what are ___
      if(number_of_words==3 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"are")==0) {
         handle_class_question(words[3]);
         continue;
      }
      // what is a ___
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"a")==0) {
         handle_class_question(words[4]);
         continue;
      }

      // this needs to be placed after "what is ___"
      if(number_of_words==3 &&
      strcmp(words[2],"is")==0) {
         handle_attribute_statement(words[1],words[3]);
         continue;
      }

      // a __ is a __
      // ex: a cat is an animal
      if(number_of_words==5 &&
         strcmp(words[1],"a")==0 &&
         strcmp(words[3],"is")==0 &&
         strcmp(words[4],"a")==0
      ) {
         handle_class_statement(words[2],words[5]);
         continue;
      }

      if(number_of_words==4 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"a")==0) {
         handle_class_statement(words[1],words[4]);
         continue;
      }

      if(number_of_words==3 &&
      strcmp(words[2],"is")==0 ) {
         handle_class_statement(words[1],words[3]);
         continue;
      }

      // does jane have acne
      if(number_of_words==4 &&
      strcmp(words[1],"does")==0 &&
      strcmp(words[3],"have")==0) {
         handle_have_question(words[2],words[4]);
         continue;
      }
/*
      // does jane have a dog
      if(number_of_words==5 &&
      strcmp(words[1],"does")==0 &&
      strcmp(words[3],"have")==0) &&
      strcmp(words[4],"a")==0) {
         handle_have_question(words[1],words[5]);
         continue;
      }
*/
      // - - - - - - COLORS - - - - - - - - - - - - - - - -
      //
      // what color is ___
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"color")==0&&
      strcmp(words[3],"is")==0) {
         handle_color_question(words[4]);
         continue;
      }

      // is ___ <color>?
      if(number_of_words==3 &&
      strcmp(words[1],"is")==0 &&
      db_root_check(words[3],"color")==FOUND) {
         handle_color_confirmation_question(words[2],words[3]);
         continue;
      }
/*
      // ___ is <color>
      // conditions: 3 words, middle word is "is"
      if(number_of_words==3 &&
      strcmp(words[2],"is")==0 &&
      db_root_check(words[3],"color")==FOUND) {
         handle_color_statement(words[1],words[3]);
         continue;
      }
*/
      // - - - - - - - - - - - - - - - - - - - - - -
      // LOCATION
      // where is ___
      if(number_of_words==3 &&
      strcmp(words[1],"where")==0 &&
      strcmp(words[2],"is")==0) {
         handle_location_question(words[3]);
         continue;
      }

      // - - - - - - - - - - - - - - - - - - - - - -
      // ABILITY
      // can <subject> <action>
      if(number_of_words==3 &&
      strcmp(words[1],"can")==0 ) {
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
      if(number_of_words==3 &&
      strcmp(words[2],"like")==0) {
         handle_rating_statement(words[1], words[3], "7");
         continue;
      }

      // Template: <person> hate __
      // Example: i hate beer
      if(number_of_words==3 &&
      strcmp(words[2],"hate")==0) {
         handle_rating_statement(words[1], words[3], "0");
         continue;
      }

      // <creature> love ___
      // conditions: 3 words, middle word is "love"
      if(number_of_words==3 &&
      strcmp(words[2],"love")==0) {
         handle_rating_statement(words[1], words[3], "10");
         continue;
      }

      // ___ dont like ___
      if(number_of_words==4 &&
      strcmp(words[2],"dont")==0 &&
      strcmp(words[3],"like")==0) {
         handle_rating_statement(words[1], words[3], "3");
         continue;
      }

      // Template: does <person> like <subject>
      // Example: does fred like beer
      if(number_of_words==4 &&
      strcmp(words[1],"does")==0 &&
      strcmp(words[3],"like")==0 ) {
         handle_rating_question(words[2], words[4]);
         continue;
      }


     // Template: i have *
      // Example: i have rabies
      if(number_of_words==3 &&
      strcmp(words[2],"have")==0 ){
         handle_have_statement(words[1], words[3]);
         continue;
      }

    // Template: i have a *
      // Example: i have a dog
      if(number_of_words==4 &&
      strcmp(words[2],"have")==0 &&
      strcmp(words[3],"a")==0 ) {
         handle_have_statement(words[1], words[4]);
         continue;
      }


      // Template: list <class>
      // Example: list action
      if(number_of_words==2 &&
      strcmp(words[1],"list")==0) {
         handle_list_question(words[2]);
         continue;
      }

      // - - - - - - - - - - - - - - - - - - - - - -
      // "what is my name"
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"my")==0 &&
      strcmp(words[4],"name")==0) {
         printf("%s\n",current_user_name);
         continue;
      }
      // "what is my gender"
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"my")==0 &&
      strcmp(words[4],"gender")==0) {
         printf("%s\n", gender);




      }

/*

      {
         switch(gender_code) {
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
*/
      // "say my name"
      if(number_of_words==3 &&
      strcmp(words[1],"say")==0 &&
      strcmp(words[2],"my")==0 &&
      strcmp(words[3],"name")==0) {
         printf("%s\n",current_user_name);
         continue;
      }

      // Log out
      if(number_of_words==1 &&
      strcmp(words[1],"bye")==0) {
         printf("talk to you later %s\r\n\r\n",current_user_name);
//       current_user_name[20]="unknown";
         strcpy(current_user_name, "unknown");
         strcpy(current_user_id_string, "#0");
         //current_user_id = 0;
         gender_code = 0;
         strcpy(gender, "unknown");
         continue;      }

      // Get ID number
      if(number_of_words==1 &&
      strcmp(words[1],"id")==0) {
         printf("%s\n",current_user_id_string);
         continue;
      }

      // Get gender code
      if(number_of_words==1 &&
      strcmp(words[1],"g")==0) {
         printf("%s\n",gender);
         continue;

      }     // Get gender code
      if(number_of_words==1 &&
      strcmp(words[1],"d")==0) {
         printf("%s",debug_string);
         continue;
      }
      // Single word
      if(number_of_words==1) {
         sprintf(key, "%s > class", words[1]);  // assemble a key
 //        if(db_lookup(key, value) == FOUND) {
          if(db_get_value(key, value) == FOUND) {
            printf("That's a %s\n", value);
            continue;
         }
         if(isword(words[1])==0) {
            printf("%s is in my dictionary, but I'm not familiar with it\n", words[1]);
         } else
            printf("That's not in my dictionary\n");
         continue;
      }

      // Nothing typed?
      if(number_of_words==0) {
         printf("You didn't type anything..\n");
         continue;
      }

      // Default
      printf("I'm not familiar with that kind of sentence\n");
      continue;

      // - - - - - -
      // experimental
#if 0
      switch(F) {
      case:
         HELP handle_help();
         break;
      case:
         handle_ability_question();
         break;
      case:
         handle_attribute_statement();
         break;
      case:
         handle_class_question();
         break;
      case:
         handle_class_statement();
         break;
      case:
         handle_ability_question();
         break;
      case:
         handle_color_confirmation_question();
         break;
      case:
         handle_color_question();
         break;
      case:
         handle_color_statement();
         break;
      case:
         handle_def_question();
         break;
      case:
         handle_def_statement();
         break;
      case:
         handle_list_question();
         break;
      case:
         handle_location_question();
         break;
      case:
         handle_login();
         break;
      case:
         handle_rating_question();
         break;
      case:
         handle_rating_statement();
         break;
      }
#endif

   } // main loop

   return 0;

} // main








