#include "irc.h"

void irc_init(void){

 char output[80];

      strcpy(hostname, "chat.freenode.net");
      strcpy(channel, "#chatbot");

   // Look up the IP address
   if ( (he = gethostbyname( hostname ) ) == NULL) {
      herror("gethostbyname"); //gethostbyname failed
      return ;
   }

   //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
   addr_list = (struct in_addr **) he->h_addr_list;

   for(i = 0; addr_list[i] != NULL; i++) {
      //Return the first one;
      strcpy(ip , inet_ntoa(*addr_list[i]) );
   }

   sprintf(output, "%s resolved to : %s" , hostname , ip);
    puts(output);
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

      flags = fcntl(socket_desc,F_GETFL,0); // return the flags
   assert(flags != -1); // quit if the above failed
   fcntl(socket_desc, F_SETFL, flags | O_NONBLOCK); // set the non blocking flag

   flags = fcntl(socket_desc, F_GETFL, 0);
   if ((flags & O_NONBLOCK) == O_NONBLOCK) {
     printf("nonblocking\n");
   }
   else {
     printf("blocking.\n");
   }

   }

int irc_io(void) {

   char output[80];

   //Receive a reply from the server
   bzero(server_reply, 2000); // clear the buffer
   length = recv(socket_desc, server_reply , 2000 , 0);
   if (length <  0) {
      if(strcmp(current_user_id_string, "#0") != 0 &&
            time(NULL) > time_of_last_input + 200 &&
            +           time(NULL) > time_of_last_output + 9) {
         sprintf(output, "it looks like %s has wandered off somewhere\n", current_user_name);
         stioc(output);
         strcpy(current_user_id_string, "#0");
         strcpy(current_user_name, "unknown");
         strcpy(gender, "unknown");
         time_of_last_output = time(NULL);
      }
      return 0;
   }
   puts(server_reply);
   // Handle pings
   if(!strncmp(server_reply, "PING ", 5)) {
      server_reply[1] = 'O';  // turn a ping into a pong
      send(socket_desc , server_reply , strlen(server_reply) , 0);  // send pong
      printf("%s\n", server_reply);
      return 0;
   }
   ret1 = strstr(server_reply, "PRIVMSG");
   if(ret1 == NULL) return 0; // if it's not a message, go back to the top of the loop
   ret2 = strstr(ret1, ":"); // get rid of everything before the :
   ret2++; // move past the :
   *(ret2 + strlen(ret2) - 2) = 0; // get rid of the CR at the end
   strcpy(user_input, ret2);
   printf("extracted message: %s\r\n", user_input); // show the extracted message
   time_of_last_input = time(NULL);
   return 1; //
}

