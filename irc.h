#ifndef IRC_H_INCLUDED
#define IRC_H_INCLUDED

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
#include "functions.h"
//#include "main.h"

 int irc;

void irc_init(void);

int irc_io(void);


  struct sockaddr_in server, from;
   char message[2000];
   char server_reply[2000];
char *ret1;
char *ret2;
   char hostname[80];

   char ip[100];
   struct hostent *he;
   struct in_addr **addr_list;
   int i;
int irc;
  char channel[20];
 int socket_desc;
 int n,flags,length, flag;
#endif // IRC_H_INCLUDED
