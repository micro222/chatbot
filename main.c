#include "main.h"
#include <sys/socket.h>

/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);

//-------------------------------------------------------

int main(void) {

//   char out[MAX_WORDS][MAX_LETTERS];
   int n;
   char temp[40][20];
   char key[80];
   char buffer[256];
   char output[80];
   time_t seconds1, seconds2;

 // char *output; // this causes a segmentation fault
//------------------

   struct sockaddr_in server, from;
   char* message,server_reply[2000];
char *ret1;
char *ret2;
   char *hostname = "chat.freenode.net";
   char ip[100];
   struct hostent *he;
   struct in_addr **addr_list;
   int i;
   ssize_t ssize;

   irc = TRUE;
   // Look up the IP address
   if ( (he = gethostbyname( hostname ) ) == NULL) {
      herror("gethostbyname"); //gethostbyname failed
      return 1;
   }

   //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
   addr_list = (struct in_addr **) he->h_addr_list;

   for(i = 0; addr_list[i] != NULL; i++) {
      //Return the first one;
      strcpy(ip , inet_ntoa(*addr_list[i]) );
   }

   sprintf(output, "%s resolved to : %s" , hostname , ip);

   //Create a socket
   socket_desc = socket(AF_INET , SOCK_STREAM , 0);
   if (socket_desc == -1) {
      sprintf(output, "Could not create a socket"); stioc(output);
   }

   server.sin_addr.s_addr = inet_addr(ip);
   server.sin_family = AF_INET;
   server.sin_port = htons( 6667 );  // IRC port number

   //Connect to remote server
   if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
      puts("connect error");
   }
   else puts("Connected to IRC");

//Send NICK command
   message = "NICK robot22\r\n";
   puts(message);
   send(socket_desc , message , strlen(message) , 0);

//Send USER command
   message = "USER user_name 8 * :real name\r\n";
   puts(message);
   send(socket_desc , message , strlen(message) , 0);

//Join chatroom
   message    = "JOIN #chatbot\r\n";
//   user_input = "this is a test";
   puts(message);
   send(socket_desc , message , strlen(message) , 0);

//-----------------

   gender_code = 0;
   strcpy(debug_string, "");
   strcpy(current_user_id_string, "#0");
   strcpy(gender, "unknown");
   strcpy(current_user_name, "unknown");
   expecting_name = FALSE;

   printf("type 'help' for a list of sentences I understand\r\n");

   // THE MAIN LOOP
   while(1) {
      // for console I/O
      if(irc == FALSE) {
         printf(">"); // user prompt
         get_string(); // get user input from console and store in user_input[]
      }
      // for IRC
      else{
         //Receive a reply from the server
         bzero(server_reply,2000); // clear the buffer
         recv(socket_desc, server_reply , 2000 , 0);
         puts(server_reply);
         // Handle pings
         if(!strncmp(server_reply, "PING ", 5)) {
            server_reply[1] = 'O';  // turn a ping into a pong
            send(socket_desc , server_reply , strlen(server_reply) , 0);  // send pong
            puts("pong\n");
            continue;
         }
         ret1 = strstr(server_reply, "PRIVMSG");
         if(ret1 == NULL) continue; // if it's not a message, go back to the top of the loop
         ret2 = strstr(ret1, ":"); // get rid of everything before the :
         ret2++; // move past the :
         *(ret2 + strlen(ret2) -2) = 0; // get rid of the CR at the end
         strcpy(user_input,ret2);
//user_input = "this is a test";
         printf("extracted message: %s\r\n", user_input); // show the extracted message
      }
  seconds1 = time(NULL);
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
         if (strcmp(words[n],"am")==0)	  strcpy(words[n], "is");
         if (strcmp(words[n],"an")==0)	  strcpy(words[n], "a");

      }
#endif

#if 0
      // Work in progress
      // This is the code that makes use of template_search()
      code = template_search(user_input, &template_info);
      sprintf(output, "\ncode: %d, template: %s, ", code, template_info.template2);
      sprintf(output, "\r\nfunction: %s\r", template_info.function_name);
      if(template_info.parameter1 > 0) {
         sprintf(output, "\np1: %d\r\n", template_info.parameter1);
      }
      if(template_info.parameter2 > 0) {
         sprintf(output, "\np2: %d\r\n\n\n", template_info.parameter2);
      }

      continue;
#endif
      //----------------

 //sprintf(output, "%ld",seconds1); stioc(output);
      // The main sentence processing starts here.
      // Soon this will be replaced by using the templates in templates2.txt

      if(number_of_words==1 &&
      strcmp(words[1], "help")==0) {
         handle_help();
      }

      if(number_of_words==1 &&
      strcmp(words[1],"d")==0) {
         sprintf(output, "%s",debug_string); stioc(output);
         continue;
      }
      strcpy(debug_string, "");

      //Dealing with 1 word replies to robot questions
      //expected template: my name is *
      if (expecting_name == TRUE && number_of_words == 1) {
         strcpy(temp[1],"my");
         strcpy(temp[2],"name");
         strcpy(temp[3],"is");
         strcpy(temp[4], words[1]);
         memcpy(words, temp, 800);  // MAX_WORDS * MAX_LETTERS
         number_of_words = 4;
         //printf("%s,%s,%s,%s\n", words[1],words[2],words[3],words[4]);
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
         sprintf(output, "what is your name?\r\n"); stioc(output);
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
         //gender_code = 1;
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

      // what are you
      if(number_of_words==333 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"you")==0) {
         sprintf(output, "a robot named ivan\n"); stioc(output);
         continue;
      }
      // who are you
      if(number_of_words==3 &&
      strcmp(words[1],"who")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"you")==0) {
         sprintf(output, "a robot named ivan\n"); stioc(output);
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

      // does jane have a dog
      if(number_of_words==5 &&
      strcmp(words[1],"does")==0 &&
      strcmp(words[3],"have")==0 &&
      strcmp(words[4],"a")==0) {
         handle_have_question(words[2],words[5]);
         continue;
      }

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
         sprintf(output, "%s\n",current_user_name); stioc(output);
         continue;
      }

      // "what is my gender"
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"my")==0 &&
      strcmp(words[4],"gender")==0) {
         sprintf(output, "%s\n", gender); stioc(output);
         continue;
      }

      // "say my name"
      if(number_of_words==3 &&
      strcmp(words[1],"say")==0 &&
      strcmp(words[2],"my")==0 &&
      strcmp(words[3],"name")==0) {
         sprintf(output, "%s\n",current_user_name); stioc(output);
         continue;
      }

      // Log out
      if(number_of_words==1 &&
      strcmp(words[1],"bye")==0) {
         sprintf(output, "talk to you later %s\r\n\r\n",current_user_name); stioc(output);
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
         {sprintf(output, "%s\n",current_user_id_string); stioc(output);}
         continue;
      }

      // Get gender code
      if(number_of_words==1 &&
      strcmp(words[1],"g")==0) {
         {sprintf(output, "%s\n",gender); stioc(output);}
         continue;

      }

      // Single word
      if(number_of_words==1) {
         sprintf(key, "%s > class", words[1]);  // assemble a key
 //        if(db_lookup(key, value) == FOUND) {
          if(db_get_value(key, value) == FOUND) {
            sprintf(output, "That's a %s\n", value); stioc(output);
            continue;
         }
         if(isword(words[1])==0) {
            sprintf(output, "%s is in my dictionary, but I'm not familiar with it\n", words[1]); stioc(output);
         } else
            {sprintf(output, "That's not in my dictionary\n"); stioc(output);}
         continue;
      }

      // Nothing typed?
      if(number_of_words==0) {
         sprintf(output, "You didn't type anything..\n"); stioc(output);
         continue;
      }

      // Default
      sprintf(output, "I'm not familiar with that kind of sentence\n"); stioc(output);
      continue;

    } // main loop

   return 0;

} // main



void error(const char *msg)
{
    perror(msg);
    exit(0);
}






