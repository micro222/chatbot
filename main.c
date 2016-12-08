#include "main.h"
#include <sys/socket.h>

/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

void error(const char *);

//-------------------------------------------------------

int main(void) {

//   char out[MAX_WORDS][MAX_LETTERS];
  int n,flags,length;
   char temp[40][20];
   char key[80];
   char buffer[256];
   char output[80];
   time_t seconds1, seconds2;
 // int current_time;
 // int time_of_last_output;
 // int time_of_last_input;
time_t current_time;
  time_t time_of_last_output;
  time_t time_of_last_input;

 // char *output; // this causes a segmentation fault
//------------------

   struct sockaddr_in server, from;
   char message[2000];
   char server_reply[2000];
char *ret1;
char *ret2;
   char *hostname = "chat.freenode.net";

   char ip[100];
   struct hostent *he;
   struct in_addr **addr_list;
   int i;

   ssize_t ssize;

   irc = TRUE;
   // irc = FALSE;
      strcpy(channel, "#chatbot");

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
 //  message = "NICK robot22\r\n";
   strcpy(message, "NICK robot23\r\n");
   puts(message);
   send(socket_desc , message , strlen(message) , 0);

//Send USER command
   strcpy(message, "USER user_name 8 * :real name\r\n");
   puts(message);
   send(socket_desc , message , strlen(message) , 0);

//Join chatroom
   sprintf(message,"JOIN %s\r\n", channel);
   //user_input = "this is a test";
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

   flags = fcntl(socket_desc,F_GETFL,0); // return the flags
   assert(flags != -1); // quit if the above failed
   fcntl(socket_desc, F_SETFL, flags | O_NONBLOCK); // set the non blocking flag

   flags = fcntl(socket_desc, F_GETFL, 0);
   if ((flags & O_NONBLOCK) == O_NONBLOCK) {
     printf("it's nonblocking\n");
   }
   else {
     printf("it's blocking.\n");
   }

//current_time = 0;
time_of_last_input=time(NULL);
time_of_last_output=time(NULL);

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
         length = recv(socket_desc, server_reply , 2000 , 0);
         if (length <  0) {
            /*
                        if(strcmp(current_user_id_string, "#0") != 0 &&
             //           current_time > time_of_last_input + 10 &&
             //           current_time > time_of_last_output + 10) {
                        time(NULL) > time_of_last_input + 10 &&
                        time(NULL) > time_of_last_output + 10) {
                           printf(" are you still there?\n");
                           time_of_last_output = time(NULL);
                        }
            */
            if(strcmp(current_user_id_string, "#0") != 0 &&
            time(NULL) > time_of_last_input + 200 &&
            time(NULL) > time_of_last_output + 9) {
               sprintf(output, " it looks like %s has wandered off somewhere\n", current_user_name);
               stioc(output);
               strcpy(current_user_id_string, "#0");
               strcpy(current_user_name, "unknown");
               time_of_last_output = time(NULL);
            }
            continue;
         }
         puts(server_reply);
         // Handle pings
         if(!strncmp(server_reply, "PING ", 5)) {
            server_reply[1] = 'O';  // turn a ping into a pong
            send(socket_desc , server_reply , strlen(server_reply) , 0);  // send pong
            printf("%s\n",server_reply);
            continue;
         }
         ret1 = strstr(server_reply, "PRIVMSG");
         if(ret1 == NULL) continue; // if it's not a message, go back to the top of the loop
         ret2 = strstr(ret1, ":"); // get rid of everything before the :
         ret2++; // move past the :
         *(ret2 + strlen(ret2) -2) = 0; // get rid of the CR at the end
         strcpy(user_input,ret2);
         printf("extracted message: %s\r\n", user_input); // show the extracted message
         time_of_last_input = time(NULL);
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

      //----------------

      // The main sentence processing starts here.

      // Help
      if(number_of_words==1 &&
      strcmp(words[1], "help")==0) {
         handle_help();
      }

      // Show debug info
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
         printf("*");
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

      // Hi
      if(number_of_words==1 &&
      strcmp(words[1], "hi")==0) {
         handle_greetings();
         continue;
      }

      // Hello
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
      if(strcmp(current_user_id_string, "#0") == 0) {
         //sprintf(output, "what is your name?\r\n"); stioc(output);
         //expecting_name = TRUE;
         handle_greetings();
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


      if(strcmp(user_input, "what are you")==0){sprintf(output, "a robot.\n"); stioc(output); continue;}
      if(strcmp(user_input, "are you human")==0){sprintf(output, "no\n"); stioc(output); continue;}
      if(strcmp(user_input, "are you a robot")==0){sprintf(output, "yes\n"); stioc(output); continue;}
      if(strcmp(user_input, "are you a person")==0){sprintf(output, "no\n"); stioc(output); continue;}
      if(strcmp(user_input, "where are you")==0){sprintf(output, "home\n"); stioc(output); continue;}
      if(strcmp(user_input, "who are you")==0){sprintf(output, "a robot\n"); stioc(output); continue;}
      if(strcmp(user_input, "where is home")==0){sprintf(output, "canada\n"); stioc(output); continue;}
      if(strcmp(user_input, "how are you")==0){sprintf(output, "partialy functional\n"); stioc(output); continue;}
      if(strcmp(user_input, "what is your name")==0){sprintf(output, "ivan\n"); stioc(output); continue;}
      //if(strcmp(user_input, "")==0){printf(output, "\n"); stioc(output); continue;}


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

      if(number_of_words==3 &&
      strcmp(words[1],"where")==0 &&
      strcmp(words[2],"is")==0 ) {
         handle_location_question(words[3]);
      //   handle_attribute_question(words[3], "location");
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
         handle_attribute_question(words[4], words[2]);
         continue;
      }
 /*
      // what color is ___
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"color")==0&&
      strcmp(words[3],"is")==0) {
         handle_color_question(words[4]);
         continue;
      }
*/
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
      strcmp(words[2],"have")==0 ) {
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
         sprintf(output, "%s\n",current_user_name);
         stioc(output);
         continue;
      }

      // "what is my gender"
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"my")==0 &&
      strcmp(words[4],"gender")==0) {
         sprintf(output, "%s\n", gender);
         stioc(output);
         continue;
      }
      // "what is my *"
      if(number_of_words==4 &&
      strcmp(words[1],"what")==0 &&
      strcmp(words[2],"is")==0 &&
      strcmp(words[3],"your")==0 ) {
         handle_attribute_question("#1", words[4]);
         //stioc(output);
         continue;
      }

      // "say my name"
      if(number_of_words==3 &&
      strcmp(words[1],"say")==0 &&
      strcmp(words[2],"my")==0 &&
      strcmp(words[3],"name")==0) {
         sprintf(output, "%s\n",current_user_name);
         stioc(output);
         continue;
      }

      // Log out
      if(number_of_words==1 &&
      strcmp(words[1],"bye")==0) {
         sprintf(output, "talk to you later %s\r\n\r\n",current_user_name);
         stioc(output);
//       current_user_name[20]="unknown";
         strcpy(current_user_name, "unknown");
         strcpy(current_user_id_string, "#0");
         //current_user_id = 0;
         gender_code = 0;
         strcpy(gender, "unknown");
         continue;
      }

      // Get ID number
      if(number_of_words==1 &&
      strcmp(words[1],"id")==0) {
         {
            sprintf(output, "%s\n",current_user_id_string);
            stioc(output);
         }
         continue;
      }

      // Get gender code
      if(number_of_words==1 &&
            strcmp(words[1],"g")==0) {
         {
            sprintf(output, "%s\n",gender);
            stioc(output);
         }
         continue;

      }

      // Single word
      if(number_of_words==1) {
         sprintf(key, "%s > class", words[1]);  // assemble a key
//        if(db_lookup(key, value) == FOUND) {
         if(db_get_value(key, value) == FOUND) {
            sprintf(output, "That's a %s\n", value);
            stioc(output);
            continue;
         }
         if(isword(words[1])==0) {
            sprintf(output, "%s is in my dictionary, but I'm not familiar with it\n", words[1]);
            stioc(output);
         } else {
            sprintf(output, "That's not in my dictionary\n");
            stioc(output);
         }
         continue;
      }

      // Nothing typed?
      if(number_of_words==0) {
         sprintf(output, "You didn't type anything..\n");
         stioc(output);
         continue;
      }

      // Default
      sprintf(output, "I'm not familiar with that kind of sentence\n");
      stioc(output);
      continue;

    } // main loop

   return 0;

} // main



void error(const char *msg)
{
    perror(msg);
    exit(0);
}






