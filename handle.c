#include "handle.h"

void handle_class_statement(char*user_subject, char*user_class){
  /*

  example: a cat is an animal(value)


  Posibilities:
                                     db action      user action
      --------------------------     ------------   --------------------------
2      cat is unknown       	         add to db      "I'll take note of that"
1     animal is unknown                             "what's an animal"
3     cat is known, class = animal                  "I know"
4     cat known, class != animal                    "no it's a ____"


// 1 class doesn't exist  	// i dont know what an animal is
// 2 subject doesnt exist, class exists  	// ill take note of that
// 3 subject exists, class is the same  	// "i knew that"
// 4 subject exists, class is different  	// no its not

  */

  char value[20];
  char key[20];
  int subject_result, class_result, comparison_result;

//  ex: lookup "cat"
    strcpy(key, user_subject);
    strcat(key," > class");
    subject_result = db_lookup(key, value);
      printf("DEBUG: %s\n", value);


//  3)
    if(strcmp(user_class, value) == 0){
        printf("I already know that\n");
        return;
    }



//  lookup "animal"
    strcpy(key, user_class);
    strcat(key," > class");
    class_result = db_lookup(key, value);

// 1)
    if(class_result == NOT_FOUND) {
       printf("I'm unfamiliar with %s\n", user_class);
       return;
    }

//  2)
    if(subject_result == NOT_FOUND) {
       strcpy(key, user_subject);
       strcat(key," > class");
       db_add_pair(key, user_class);
       printf("I'll take a note of that\n");
       return;
    }


// 4)
    printf("no, it's a %s\n", value);

}

//--------------------------------------------------
void handle_color_statement(char* user_subject,char* user_color){
  /*
  example: grass is green

  Posibilities:
  1   grass is unknown                   i dont know what grass is
  2   grass known, color is unknown     add color
  3   grass known, color = green      i know
  4   grass known, color not green    is not
  */

char key[20];
char value[20];
int subject_result;
char user_class;
int class_result;

//  ex: lookup "grass"
    strcpy(key, user_subject);
    strcat(key," > class");
    subject_result = db_lookup(key, value);

//  lookup "green"
    strcpy(key, user_class);
    strcat(key," > color");
    class_result = db_lookup(key, value);

// 1)
    if(class_result == NOT_FOUND) {
       printf("I'm unfamiliar with %s\n", user_class);
       return;
    }

//  2)
    if(subject_result == NOT_FOUND) {
       strcpy(key, user_subject);
       strcat(key," > color");
       db_add_pair(key, user_color);
       printf("I'll take a note of that\n");
       return;
    }

//  3)
    if(strcmp(user_class, value) == 0){
        printf("I already know that\n");
        return;
    }

// 4)
    printf("no, it's a %s\n", value);


}
//--------------------------------------------------

void handle_class_question(char* subject){

  int result;
  char value[20];
  char key[20];

  strcpy(key, subject);
  result = db_lookup(strcat(key," > class"), value);
  if(result==FOUND) printf("It's a %s\n", value);
  else printf("I've never heard of ""%s""\n", subject);

}

//------------------------------------------------------

void handle_color_question(char* subject){
  int result;
  char value[20];
  char key[60];

  strcpy(key, subject);
  strcat(key, " > color");
  result = db_lookup(key, value);
  if(result == FOUND){
    printf("%s\n", value);
    return;
  }
   else{
     printf("I don't know\n");
     return;
   }

  //else if(result==3)printf("I've never heard of %s\n",key);
 // else printf(" I don't know (result %d)\n", result);
}

//----------------------------------------------------

void handle_color_confirmation_question(char* subject, char*value1){

  int result;
  char value[20];
  char key[60];

    strcpy(key, subject); // prepare to lookup
       strcat(key," > color"); // prepare to lookup
       db_lookup(key, value); // lookup
       result = strcmp(value, value1);
        if (result == 0){
            printf("yes\n");
        }
        else printf("no\n");
}

//----------------------------------------------------

void handle_opinion_statement(char* key, char* s2, char* opinion){
//
// in: firstname, firstname or object or substance, rating:0-9
//
//  examples:
//  i like beer
//     1) i'll take note of that
//     2) what is beer?
//     3) i already knew that
//     4) but I thought you hated beer
//  i like jane
//     1) opinion added
//     2) i know nothing of this "jane" you speak of
//  jane likes beer
//     1) opinion added
//     2) i know nothing of this "jane" you speak of
//     3) i know nothing of this "beer" you speak of
//     4)
//
 // Problem: will make multiple entries

// second parameter
//
//  known person?    add info
//  unknown person?  dont know this person
//  known object?    add info
//  known substance? add info
//  unknown

  char pn[20]="opinion-";
 // char value[20];
  int result, result2;
  char id1[20],id2[20];
  int person = FALSE;

// So, take example 2. At this point we know that neither of the words have been checked.
// We'll start by seeing if the first word is the first name of someone we know.
// We can use the get id function for that
// If known, take note that this is a person and continue on, if not, send a message and exit

   result = db_get_id(key);

   if(result != FOUND){

      result = db_root_check(key,"firstname");

      if(result==FOUND) printf("I don't know%s\n", key);
      else printf("%s?\n", key);

      return;
   }
// Next we'll look at the 2nd parameter and see if it's a known person
//
   result = db_get_id(s2);  // a known entity?
   result2 = db_root_check(s2,"firstname");  // a person?

   if(result==FOUND && result2==FOUND){
      person = TRUE;
      goto add_info;
   }

   if(result!=FOUND && result2==FOUND){
      printf("I don't know %s\n", s2);
      return;
   }

    //  Check if the 2nd parameter a object or substance?
    result = db_root_check(s2, "object");
    result2 = db_root_check(s2, "substance");

    if(result == 3){
      printf("I don't know what %s is\n", s2);
      return;
   }
    printf("*%d*\n", result);
    if(result != FOUND && result2 != FOUND){
      printf("I dont see how %s makes sense\n", s2);
      return;
    }
//---
// If we've made if this far we have a valid sentence and we can store
// the info

add_info:

   if(person==TRUE)strcat(pn, id2);
   else strcat(pn, s2);

//  result = db_lookup(id1, pn, value);

//if(result == SUBJECT_NOT_FOUND){
//     db_add_subject_and_property(id1,pn,opinion);
//     db_add_property(id1,"firstname",key);
//     printf("name and opinion added\n");
//  }
// else
  if(result==5){

//     db_add_property(id1, pn, opinion);
     printf("opinion added\n");
  }
  else if(result == FOUND) printf("I already know that\n");
  else printf("error, result code:%d\n",result);
}

//--------------------------------------------------


void handle_location_question(char* subject){

  int result;
  char value[20];
  char key[60];

  // DO WE KNOW THE ANSWER?
  strcpy(key, subject);
  strcat(key, " > location");
  result = db_lookup(key, value);
  if(result==FOUND) {
        printf("%s\n", value);
        return;
  }

  // DO WE KNOW THE SUBJECT BUT NOT THE ANSWER?
  strcpy(key, subject);
  strcat(key, " > class");
  result = db_lookup(key, value);
  if(result==FOUND){
    printf(" I don't know where %s is\n", subject);
    return;
  }

  // WE DON'T KNOW THE SUBJECT
  printf(" I never heard of %s\n", key);
  return;

}

//-------------------------------------------------------

void handle_ability_question(char* key, char* value){

  int result;
  char temp[20]=" > ability";

// 0 = match
// 3 = subject not found
// 5 = subject found, no def
// 7 = found, no match
   result = db_root_check(key,"object");
   if(result==3) {printf(" I never heard of %s\n", key); return;}
   else if(result!=0){ printf("code %d",result); return;}

   if(db_root_check(value,"action")!=0){printf("%s is not an action\n",key); return;}

  strcat(temp, value);
//  result = db_search(key,temp,value);
  //  result = db_get_value(user_words[2],temp,value);

  if(result==0) printf("%s\n", value);
  else printf(" error %d\n", result);

}

//------------------------------------------------------
// key is someones first name
// p is what the opinion is of
//
void handle_opinion_question(char* key, char* p){

  int result;
  char value[20];
  char id[20];
  char temp[20]="opinion-";

  result = db_get_id(key);
  //printf("result %d %s %s %s      ", result, key, p, id);
  //return;

if(result !=0){
printf("I dont know %s\n", key);
return;
}

//printf("result %d     ", result);
//  return;

//check if the subject of opinion is known

//   result = db_subject_search(p);
   if(result!=0) {
      printf("What is %s?\n", key);
      return;
   }

// get opinion if any
  strcat(temp, p);
//  result = db_search(key,temp,value);

  if(result==0) printf("%s\n", value);
  else printf("I dont know (code:%d)\n", result);

}

//----------------------------------------

void handle_list_question(char* subject){

}

//--------------------------------------------------

void handle_attribute_statement(char* user_subject,char* user_attribute){
  /*
  example: grass is green

  Posibilities:
  1   grass is unknown                   i dont know what grass is
  2   grass is not an object or substance
  3   green is unknown
  4   green is not an attribute
  5   info already known
  6   info is contradictory
  7   ok to add to db
  */

  int result;
  int result1;
  int result2;
  char value[20];
  char key[60];
  int subject_result;
  char subject_class[20];
  char db_class[20];
  char user_color[20];
    //  1) ex: is "grass" in database?
    strcpy(key, user_subject);
    strcat(key," > class");
    subject_result = db_lookup(key, subject_class);
    // if subject_result === UNKNOWN, I don't know what %s is

    // 2) is grass an object or substance?
    result1 = db_root_check(user_subject, "object");
    result2 = db_root_check(user_subject, "substance");
    if ((result1 == NOT_FOUND) && (result2 == NOT_FOUND)){
        printf("I don't think %s can have such an attribute\n", user_subject);
        return;
    }

    //  3) is green in db?
    strcpy(key, user_attribute);
    strcat(key," > class");
    result = db_lookup(key, db_class);
    if(result == NOT_FOUND) {
       printf("I'm unfamiliar with %s\n", user_attribute);
       return;
    }

    //  4) is "green" an attribute
    result = db_root_check(user_attribute, "attribute");
    if(result == NOT_FOUND) {
        printf("%s is not an attribute\n", user_attribute);
        return;
    }

// 5) already known
// green
    strcpy(key, user_subject);
    strcat(key," > class");
    result = db_lookup(key, value);
// color

    strcpy(key, user_subject);
    strcat(key," > ");
    strcat(key, value);
// green
    result = db_lookup(key, value);

    if(strcmp(user_attribute, value) == 0){
        printf("I already know that\n");
        return;
    }

//  ex: lookup "grass"
    strcpy(key, user_subject);
    strcat(key," > ");
    subject_result = db_lookup(key, value);


    if(subject_result == NOT_FOUND) {
       strcpy(key, user_subject);
       strcat(key," > color");
       db_add_pair(key, user_color);
       printf("I'll take a note of that\n");
       return;
    }


// 4)
    printf("no, it's a %s\n", value);


}

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

//--------------------------------------------------

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


