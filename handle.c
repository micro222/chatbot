#include "handle.h"
#include "functions.h"
#include "main.h"

void handle_class_statement(char* user_subject, char* user_class) {
   /*
   example: a cat is an animal(value)

   Posibilities:
                                      db action      user action
       --------------------------     ------------   --------------------------
   2   cat is unknown       	        add to db     "I'll take note of that"
   1   animal is unknown                             "what's an animal"
   3   cat is known, class = animal                  "I know"
   4   cat known, class != animal                    "no it's a ____"
   5   info is unknown. Add to db

   // 1 class doesn't exist  	// i dont know what an animal is
   // 2 subject doesnt exist, class exists  	// ill take note of that
   // 3 subject exists, class is the same  	// "i knew that"
   // 4 subject exists, class is different  	// no its not
   */

   char value[20];
   char key[20];
   int result;
   char output[80];

   strcat(debug_string, "class statement\n");  // debug info

   // 1 is "animal" in the database?
   if(db_check(user_class) != FOUND) {
      sprintf(output, "I'm not familiar with %s\n", user_class); stioc(output);
      return;
   }

   //  preparatiom for 2, 3 & 4
//  ex: lookup "cat"
   sprintf(key, "%s > class", user_subject);
   result = db_get_value(key, value);

//  2)
   if(result == NOT_FOUND) {
      sprintf(key, "%s > class", user_subject);
      db_add_pair(key, user_class);
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;
   }

//  Note: At this point, "cat" was found in the database.
//  We just need to check if the info matches or not.

//  3) states what already is known
   if(strcmp(user_class, value) == 0) {
      sprintf(output, "I already know that\n"); stioc(output);
      return;
   }

//  4) contradictory info
   else {
      sprintf(output, "no, %s is a %s\n", user_subject, value); stioc(output);
      return;
   }
}

//--------------------------------------------------

void handle_class_question(char* subject) {

   int result;
   char value[20];
   char key[20];
   char output[80];

   strcat(debug_string, "class question\n");  // debug info

// Replace "you" with the ID of the robot
   if (strcmp(subject,"you")==0) {
      strcpy(subject, "#1");
   }

   sprintf(key, "%s > class", subject);
   result = db_get_value(key, value);
   if(result==FOUND) {
      //  sprintf(output, "%s is a %s\n", subject, value); stioc(output);
      sprintf(output, "a %s\n", value);
      stioc(output);
   } else {
      sprintf(output, "I've never heard of ""%s""\n", subject);
      stioc(output);
   }
}

//--------------------------------------------------

void  (char* user_subject,char* user_attribute) {
   /*
   example: grass is green

   Posibilities:
   1   grass is unknown                      "reply: "i dont know what grass is"
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
//   char value[20];
   char key[60];
//   int subject_result;
//   char subject_class[20];
   char db_class[20];
   char attribute_type[20];
   char db_attribute[20];
   char id3[20];
char output[80];

strcat(debug_string, "attribute statement\n");  // debug info

   if (strcmp(user_subject,"i")==0)  {
      strcpy(user_subject, current_user_id_string);
      goto skip400;
   }
   else if (strcmp(user_subject,"you")==0) {
      strcpy(user_subject, "#1");
      goto skip400;
   }

   // known person or robot
   result = db_get_id_string2(user_subject, id3);
   if (result == FOUND){
        strcpy(user_subject, id3);
   }

skip400:

   // 1) ex: is "grass" in database?
   if(db_check(user_subject) == NOT_FOUND) {
      sprintf(output, "I'm unfamiliar with %s\n", user_subject); stioc(output);
      return;
   }

   // 2) Is grass an object or substance?
   result1 = db_root_check(user_subject, "object");
   result2 = db_root_check(user_subject, "substance");
   if ((result1 == NOT_FOUND) && (result2 == NOT_FOUND)) {
      sprintf(output, "I don't think %s can have such an attribute\n", user_subject); stioc(output);
      return;
   }

   // 3) is green in db?
   sprintf(key, "%s > class", user_attribute);
   if(db_get_value(key, db_class) == NOT_FOUND) {
      sprintf(output, "I'm unfamiliar with %s\n", user_attribute); stioc(output);
      return;
   }

   // 4) is "green" an attribute
   if(db_root_check(user_attribute, "attribute") == NOT_FOUND) {
      sprintf(output, "%s is not an attribute\n", user_attribute); stioc(output);
      return;
   }

   // Preparation for 5, 6 and 7

   // Get the type of the attribute. ex: "green is a color"
   sprintf(key, "%s > class", user_attribute);  // assemble key, ex: "green > class"
   db_get_value(key, attribute_type);  // ex: returns "color"

   // Get the attribute from db if any
   sprintf(key, "%s > %s", user_subject, attribute_type);  // assemble key, ex: "green > color"
   result = db_get_value(key, db_attribute);  // ex: returns "green"

   // 5) Is the attribute already known?
    if(strcmp(user_attribute, db_attribute) == 0) {   // compare "green"(what the user typed) with green(from db)
      sprintf(output, "I already know that\n"); stioc(output);
      return;
   }

   // 6 Check if the attrubute contradicts what's in the db
   if(result == FOUND) {
      sprintf(output, "no, %s is a %s\n", user_subject, db_attribute); stioc(output);
      return;
   }

   // 7 Since posiblities 1 to 6 have been eliminated, it's ok to add the info to the db
   // Determine attribute type

   // Add to db


//   sprintf(key, "%s > %s", user_subject, attribute_type);  // assemble key, ex: grass > color
//   db_add_pair(key, user_attribute);
db_add_pair2(user_subject, attribute_type, user_attribute);

   sprintf(output, "I'll take a note of that\n"); stioc(output);
   return;

}

//---------------------------------------------------------

void handle_have_statement(char* parameter1, char* parameter2){

/*
IN DEVELOPMENT, PARTIALLY WORKING

Examples
   i have a dog (pet, opposite: owner)
   my dog has fleas
   i have a daughter
   i have a cold
   i have influenza
   i have a sore toe
   my daughter has a bad attitude
   i have 3 dogs
   i have 2 thumbs
   i have a * in my *
   i have some *

Options
   1) condition (fleas, asthma, toothache)
   2) posession (pizza, car, hammer)
   3) relation (father, wife)
   4) pet (dog, cat)

Relations
   parent, offspring (son/daughter, mother/father)
   siblings? (brother/sister), aunt/uncle, (do this later)
   spouse  (wife/husband), friend, boyfriend/girlfriend

"i have a dog"
   create database entries
      #125 > class: dog
      #125 > first_name: spot
      #125 > gender: male
      #125 > owner: #17
      #17 > pet: #125

"i have a toothache"
   create a database entry
      #17 > condition: toothache

"i have a car"
     create database entries
        #200 > class: car
        #200 > owner: #17

"i have a daughter"
    create database entries
        #250 > class: person
        #250 > gender: female
        #250 > parent: #17
        #17 > offspring: #250

i have a dog
   check if dog is known
   determine whether dog is a condition, posession, relation or pet
   already known?
   contradictory info?

*/

// taken fom other function
//   int result;
//   int result1;
//   char value[20];
   char key[60];
   char key1[20];
   char key2[20];
   char id3[20];
char output[80];

//   int subject_result;
//   char subject_class[20];
   char db_class[20];

strcat(debug_string, "have statement\n");  // debug info

   if (strcmp(parameter1,"i")==0)  {
      strcpy(parameter1, current_user_id_string);
      goto skip297;
   }
   else if (strcmp(parameter1,"you")==0) {
      strcpy(parameter1, "#1");
      goto skip297;
   }

   // known person or robot
   result = db_get_id_string2(parameter1, id3);
   if (result == FOUND){
        strcpy(parameter1, id3);
   }
   else{
      sprintf(output, "%s is not a known specific entity\n", parameter1); stioc(output);
      return;
   }

skip297:

   // is dog in db? no
   sprintf(key, "%s > class", parameter2);
   if(db_get_value(key, db_class) == NOT_FOUND) {
      strcat(debug_string, "class\n");  // debug info
      sprintf(output, "I'm unfamiliar with %s\n", parameter2); stioc(output);
      return;
   }

   // is "dog" a condition? no
   if(db_root_check(parameter2, "condition") == FOUND) {
      strcat(debug_string, "condition\n");  // debug info
      db_add_pair2(parameter1, "condition", parameter2); // new function
 //  #17 > condition: toothache
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;
   }

   //  is "dog" a relation? no
   if(db_root_check(parameter2, "relation") == FOUND) {
      strcat(debug_string, "relation\n");  // debug info
      sprintf(key, "%s > %s", parameter1, "condition");  // assemble key
      db_add_pair(key, parameter2);
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;
   }

   //  is "dog" a pet? yes
   if(db_root_check(parameter2, "creature") == FOUND) {
      //  sprintf(key, "%s > %s", parameter1, "pet");  // assemble key
      //  db_add_pair(key, parameter2);
      strcat(debug_string, "pet\n");  // debug info
      db_next_available_id_string(key2); // get an unused ID# for the dog
      db_add_pair2(key2, "class", parameter2); // ex: #125 > class: dog
      db_add_pair2(key2, "owner", parameter1); // ex: #125 > owner: #17
      db_add_pair2(parameter1, "pet", key2); // ex: #17 > pet: #125
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;

   }
   //  is "dog" a posession
   if(db_root_check(parameter2, "object") == FOUND) {
      strcat(debug_string, "possession\n");  // debug info
      db_next_available_id_string(key2); // get an unused ID# for the posession
      db_add_pair2(key2, "class", parameter2); // ex: #125 > class: car
      db_add_pair2(key2, "owner", parameter1); // ex: #125 > owner: #17
      db_add_pair2(parameter1, "posession", key2); // ex: #17 > posession: #125
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;

   }

   sprintf(output, "I don't know how you can have a %s\n", parameter2); stioc(output);
   return;

}

//----------------------------------------------------

void handle_color_confirmation_question(char* subject, char*value1) {

   int result;
   char value[20];
   char key[60];
char output[80];

strcat(debug_string, "color confirmation question\n");  // debug info

   sprintf(key, "%s > color", subject);
   result = db_get_value(key, value);
   if(result == NOT_FOUND){
      sprintf(output, "I do not have that information\n"); stioc(output);
   }
   result = strcmp(value, value1);
   if (result == 0) {
      sprintf(output, "yes\n"); stioc(output);
   } else {sprintf(output, "no\n"); stioc(output);}
}

//----------------------------------------------------

void handle_rating_statement(char* parameter1, char* parameter2, char* rating) {
// UNDER RENOVATIONS
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
//     1) rating added
//     2) i know nothing of this "jane" you speak of
//  jane likes beer
//     1) rating added
//     2) i know nothing of this "jane" you speak of
//     3) i know nothing of this "beer" you speak of
//     4)
//
// TODO (pi#1#):
// Problem: will make multiple entries

// second parameter
//
//  known person?    add info
//  unknown person?  dont know this person
//  known object?    add info
//  known substance? add info
//  unknown
   int result, result2;
   char key[60];
   char id3[60];
   char output[80];

   strcat(debug_string, "rating statement\n");  // debug info

   if (strcmp(parameter1,"i")==0)  {
      strcpy(parameter1, current_user_id_string);
      goto skip436;
   } else if (strcmp(parameter1,"you")==0) {
      strcpy(parameter1, "#1");
      goto skip436;
   }

   // known person or robot
   result = db_get_id_string2(parameter1, id3);
   if (result == FOUND) {
      strcpy(parameter1, id3);
   } else{
      sprintf(output, "%s is not a known specific entity\n", parameter1);
      stioc(output);
      return;
   }

skip436:


// is the 2nd parameter a known person?
//
   result = db_get_id(parameter2);  // a known entity?
   if(result==FOUND) {
      goto add_info;
   }

   //  Check if the 2nd parameter a object or substance?
   result = db_root_check(parameter2, "object");
   result2 = db_root_check(parameter2, "substance");

   if(result == NOT_FOUND && result2 == NOT_FOUND ) {
      sprintf(output, "I dont see how %s makes sense\n", parameter2);
      stioc(output);
      return;
   }

add_info:
   // bob > rating > beer: 7
   sprintf(key,"%s > rating > %s", parameter1, parameter2 );
   db_add_pair(key, rating);
   sprintf(output, "I'll take note of that\n");
   stioc(output);
  }

//--------------------------------------------------


void handle_location_question(char* subject) {

   int result;
   char value[20];
   char key[60];
char output[80];
char id[60];

strcat(debug_string, "location question\n");  // debug info

   // DO WE KNOW THE ANSWER?
//    strcpy(key, subject);
//    strcat(key, " > location");
   sprintf(key, "%s > location", subject);
   result = db_get_value(key, value);
   if(result==FOUND) {
      sprintf(output, "%s\n", value); stioc(output);
      return;
   }

//
result = db_get_id_string2(subject, id);
if(result == FOUND){
   sprintf(output, "%s\n", subject); stioc(output);
      return;
}


   // DO WE KNOW THE SUBJECT BUT NOT THE ANSWER?
   //strcpy(key, subject);
   //strcat(key, " > class");
   sprintf(key, "%s > class", subject);
   result = db_get_value(key, value);
   if(result==FOUND) {
      sprintf(output, " I don't know where %s is\n", subject); stioc(output);
      return;
   }

   // WE DON'T KNOW THE SUBJECT
   sprintf(output, " I never heard of %s\n", subject); stioc(output);
   return;

}

//-------------------------------------------------------

void handle_ability_question(char* subject, char* action) {

//   int result;
   char key[40];
   char value[20];
char output[80];

   // Is suject in the database?
   if(db_check(subject) == NOT_FOUND) {
      sprintf(output, " I never heard of %s\n", subject); stioc(output);
      return;
   }
//--
   // Is subject an object?
   if(db_root_check(subject, "object") == NOT_FOUND) {
      sprintf(output, "%s is not an object\n", subject); stioc(output);
      return;
   }

   // Is action really an action?
   if(db_root_check(action, "action") == NOT_FOUND) {
      sprintf(output, "%s is not an action\n", action); stioc(output);
      return;
   }

   // Look up ability
   sprintf(key,"%s > ability > %s", subject, action);
   db_get_value(key, value);
   sprintf(output, "RESULT: %s\n", value); stioc(output);
// TODO (pi#1#): improve the output

}

//------------------------------------------------------
// key is someones first name
// p is what the rating is of
//
void handle_rating_question(char* key, char* p) {
char output[80];

   int result;
   char value[20];
//   char id[20];
   char temp[20]="rating-";

   result = db_get_id(key);
   //sprintf(output, "result %d %s %s %s      ", result, key, p, id); stioc(output);
   //return;

   if(result !=0) {
      sprintf(output, "I dont know %s\n", key); stioc(output);
      return;
   }

//sprintf(output, "result %d     ", result); stioc(output);
//  return;

//check if the subject of rating is known

//   result = db_subject_search(p);
   if(result!=0) {
      sprintf(output, "What is %s?\n", key); stioc(output);
      return;
   }

// get rating if any
   strcat(temp, p);
//  result = db_search(key,temp,value);

   if(result==0) {
      sprintf(output, "%s\n", value); stioc(output);
   }
   else sprintf(output, "I dont know (code:%d)\n", result); stioc(output);

}

//----------------------------------------

void handle_list_question(char* subject) {

// WORK IN PROGRESS

}

//--------------------------------------------------
// handle hi, hello
//
//
void handle_greetings(void) {

char output[80];

strcat(debug_string, "greetings\n");  // debug info
   // if not logged in
   if(strcmp(current_user_id_string, "#0") == 0) {
      sprintf(output, "hi, what is your name?\r\n"); stioc(output);
      expecting_name = TRUE;
   }
   // if logged in
   else {
      sprintf(output, "hi %s\r\n", current_user_name); stioc(output);
   }
}

 /*
void handle_is_statement(char*user_subject, char*user_attribute) {

   UNDER CONSTRUCTION, will likely be abandoned


   example: a cat is an animal(value)

   Posibilities:
                                      db action      user action
       --------------------------     ------------   --------------------------
      cat is unknown       	        add to db     "I'll take note of that"
      animal is unknown                             "what's an animal"
      cat is known, class = animal                  "I know"
      cat known, class != animal                    "no it's a ____"

   //  class doesn't exist  	// i dont know what an animal is
   //  subject doesnt exist, class exists  	// ill take note of that
   //  subject exists, value is the same  	// "i knew that"
   //  subject exists, value is different  	// no its not

   At some point we need to figure out if this is a class or an attribute.
   The syntax tells us what to expect, then we have to verify it.


   class or attribute?
   B)if(root_check(p1) == attribute) deal with it, goto label1
   A)if(p1 is in db) it's a class so deal with it,
   if yes to both,


   label1:





   cat in db?




   char value[20];
   char key[20];
   int result;

   // 1 is "animal" in the database?
   if(db_check(user_class) != FOUND) {
      sprintf(output, "I'm not familiar with %s\n", user_class); stioc(output);
      return;
   }

   //2,3&4
//  ex: lookup "cat"
   sprintf(key, "%s > class", user_subject);
   result = db_lookup(key, value);

//  2)
   if(result == NOT_FOUND) {
      sprintf(key, "%s > class", user_subject);
      db_add_pair(key, user_class);
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;
   }

//  Note: At this point, "cat" was found in the database.
//  We just need to check if the info matches or not.

//  3) states what already is known
   if(strcmp(user_class, value) == 0) {
      sprintf(output, "I already know that\n"); stioc(output);
      return;
   }

//  4) contradictory info
   else {
      sprintf(output, "no, it's a %s\n", value); stioc(output);
      return;
   }
}
*/


//------------------------------------------------------


void handle_login(char* name) {
   int result;
   int known=FALSE;
   int new2 = TRUE;
 //  char first_name[20]
   char id_string[20];
   //char s2[20];
   char value[20];
   char gender2[10];
   char key[80];
   int id_number;
char output[80];

strcat(debug_string, "login\n");  // debug info
   // Proceedure
   //
   // 1 is the person the current user?
   // 2 is this person known? (search for first name in database)
   // 3 if not known, create new entry in database
   // 4 update user_id, user_name, gender)
   //
   ////////////////////////////////////////////////////////////

   // Step 1: check if already current user
   if(strcmp(name, current_user_name)==0) {
      sprintf(output, "You told me that already\n"); stioc(output);
      known=TRUE;
      return;
   }

   // Step #2
   result = db_get_id_string2(name, id_string);
   if(result == FOUND){
      known = TRUE;
      new2 = FALSE;
      // get gender
      sprintf(key,"%s > gender", id_string);
      result = db_get_value(key, value);
      if(result == NOT_FOUND) {
         strcpy(gender, "unknown");
      }
      else{
      check_gender_by_name(name, value);
         strcpy(gender, value);
      }

   }
   else {

        known = FALSE;
   }

   // Step 3: add user to database
   if(known==FALSE) {
      // Get an id number
      db_next_available_id_string(id_string);

      // Add the following to the database
      //   #1 > class: person
      //   #1 > firstname:bob
      //   #1 > gender:male
      sprintf(key, "%s > class", id_string);
      db_add_pair(key, "person");
      sprintf(key,"%s > firstname", id_string);
      db_add_pair(key, name);
      result = check_gender_by_name(name, gender2);
      if(result == FOUND){
         sprintf(key,"%s > gender", id_string);
         db_add_pair(key, gender2);
         strcpy(gender, gender2);
      }
      // TO DO
      // if not found, say that the name is unusual and ask their gender. Allow a 1 word answer. Allow a non-answer
      else{
         sprintf(output, "I haven't heard of that name before. Are you male or female?\n");
         stioc(output);
         expecting_gender = TRUE;
      }

      known = TRUE;
      new2 = TRUE;
   }

   // Step 4:
   strcpy(current_user_name, name);
   strcpy(current_user_id_string, id_string);

   if(expecting_gender == TRUE) return;

   if(new2 == TRUE) {
      sprintf(output, "hello %s\n", current_user_name); stioc(output);
   } else {
      sprintf(output, "hi %s\n", current_user_name); stioc(output);
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

void handle_help(void) {

char output[300];

 sprintf(output, "I've been programmed for simple questions and statements based on the words what, is, are, have, and like. If i don't know something, you can always try explaining. Just keep it really simple. \n"); stioc(output);
/*




   sprintf(output, "I can handle the following sentences\r\n\r\n"); stioc(output);
   sprintf(output, " my name is ___\n"); stioc(output);
   sprintf(output, " what is my name\n"); stioc(output);
   sprintf(output, " what is my gender\n"); stioc(output);
   sprintf(output, " I am male\n"); stioc(output);
   sprintf(output, " I am female\n"); stioc(output);
   sprintf(output, " my gender is male\n"); stioc(output);
   sprintf(output, " my gender is female\n"); stioc(output);
   sprintf(output, " say my name\n"); stioc(output);
   sprintf(output, " what color is ___, ex: what color is grass\n"); stioc(output);
   sprintf(output, " is <subject> <color>, ex: is grass green\n" ); stioc(output);
   sprintf(output, " where is <object>\n" ); stioc(output);
   sprintf(output, " can ___ ___, "); stioc(output);
   sprintf(output, " what are ___\n" ); stioc(output);
   sprintf(output, " what is a ___\n" ); stioc(output);
   sprintf(output, " what is ___\n" ); stioc(output);
   sprintf(output, " a <object> is a ___, ex: a cat is an animal\n" ); stioc(output);
   sprintf(output, " ___ is <color>\n" ); stioc(output);
   sprintf(output, " ___ like ___, ex: I like pizza\n" ); stioc(output);
   sprintf(output, " ___ hate ___\n" ); stioc(output);
   sprintf(output, " ___ love ___\n" ); stioc(output);
   sprintf(output, " ___ dont like ___\n" ); stioc(output);
   sprintf(output, " do you like ___\n" ); stioc(output);
 */
   //sprintf(output, "who am i, "); stioc(output);
   //sprintf(output, "i am ___\r\n"); stioc(output);
   //sprintf(output, "bye\r\n"); stioc(output);
   //sprintf(output, "is ___ ___, "); stioc(output);
   //sprintf(output, "what is ___, "); stioc(output);
   //sprintf(output, "have you heard of ___, "); stioc(output);
   //sprintf(output, "___ is ___\r\n"); stioc(output);
   //sprintf(output, "can ___ ___, "); stioc(output);
   //sprintf(output, "do ___ ___, "); stioc(output);
   //sprintf(output, "___ can ___\r\n"); stioc(output);
   //sprintf(output, "___ like ___, "); stioc(output);
   //sprintf(output, "do ___ like ___\r\n"); stioc(output);
   //sprintf(output, "___ hates ___, "); stioc(output);
   //sprintf(output, "do ___ hate ___\r\n"); stioc(output);
   //sprintf(output, "___ is in ___, "); stioc(output);
   //sprintf(output, "where is ___\r\n"); stioc(output);
   //sprintf(output, "how old is/are ___\r\n"); stioc(output);
   //sprintf(output, "do ___ feel ___, "); stioc(output);
   //sprintf(output, "___ feels ___\r\n"); stioc(output);
   //sprintf(output, "do ___ want ___, "); stioc(output);
   //sprintf(output, "___ want _\r\n"); stioc(output);
   //sprintf(output, "do ___ have ___\r\n"); stioc(output);
   //sprintf(output, "what is the ___ of ___, ___ is the ___ of___\r\n"); stioc(output);
   //sprintf(output, "what time is it\r\n"); stioc(output);
   //sprintf(output, "lookup ___\r\n"); stioc(output);
   // continue;
}
void handle_have_question(char* p1, char* p2) {
// WORK IN PROGRESS
   int r;
   char id3[20];
   char value2[30];
char output[80];

   strcat(debug_string, "have question\n");  // debug info
//

   if (strcmp(p1,"i")==0)  {
      strcpy(p1, current_user_id_string);
      goto skip840;
   }
   else if (strcmp(p1,"you")==0) {
      strcpy(p1, "#1");
      goto skip840;
   }

   // known person or robot
   result = db_get_id_string2(p1, id3);
   if (result == FOUND){
        strcpy(p1, id3);
   }
   else{
      sprintf(output, "%s is not a known specific entity\n", p1); stioc(output);
      return;
   }

skip840:

//
   sprintf(key, "%s > condition", p1);  // assemble key
   if(db_check_pair(key, p2) == FOUND) {
      strcat(debug_string, "condition\n");  // debug info
      sprintf(output, "yes\n"); stioc(output);
      return;
   }

   //  is "dog" a relation? no
   sprintf(key, "%s > relation", p1);  // assemble key
   if(db_check_pair(key, p2) == FOUND) {
      strcat(debug_string, "relation\n");  // debug info
      sprintf(output, "yes\n"); stioc(output);
      return;
   }

   //  is "dog" a pet? yes
   sprintf(key, "%s > pet", p1);  // assemble key
   if(db_check_pair(key, p2) == FOUND) {
      strcat(debug_string, "pet\n");  // debug info
      sprintf(output, "yes\n"); stioc(output);
      return;

   }

   //  is "dog" a posession
   sprintf(key, "%s > possession", p1);  // assemble key
   if(db_get_value(key, value2) == FOUND) {
      sprintf(output, "%s,%s,%s\n",p1,p2,value2); stioc(output);
      strcat(debug_string, "possession\n");  // debug info
      sprintf(key, "%s > class", value2);  // assemble key
      if(db_check_pair(key, p2) == FOUND){
         sprintf(output, "yes\n"); stioc(output);
         return;
      }
   }
   sprintf(output, "not that I know about"); stioc(output);
   return;

}


//--------------------------------------------------
void handle_color_statement(char* user_subject,char* user_color) {
   /*
   example: grass is green

   Posibilities:
   1   grass is unknown                "I dont know what grass is"
   2   grass can't have a color
   3   grass is known. no color is listed
   4   grass is known and already associated with the given color
   5   grass is known, but a different color is listed

   */

   char key[20];
   char value1[20];
//   char value2[20];
//   int subject_result;
//   char user_class;
   int color_result;
char output[80];

strcat(debug_string, "color statement\n");  // debug info

   // 1 is "grass" in the database?
   if(db_check(user_subject) != FOUND) {
      sprintf(output, "I'm not familiar with %s\n", user_subject); stioc(output);
      return;
   }

   // 2 is "grass" something that can have a color?
   if(db_root_check(user_subject, "substance")!=MATCH && db_root_check(user_subject, "object") != MATCH) {
      sprintf(output, "I don't think %s can have a color\r\n", user_subject); stioc(output);
      return;
   }

   // 3 is grass already associated with that color? if not, add it
   sprintf(key, "%s > color", user_subject);
   color_result = db_get_value(key, value1);
   if(color_result == NOT_FOUND) {
      sprintf(key, "%s > color", user_subject);
      db_add_pair(key, user_color);
      sprintf(output, "I'll take a note of that\n"); stioc(output);
      return;
   }

   // 4 if already associated with the given color
   if(strcmp(user_color, value1) == 0) {
      sprintf(output, "I already know that\n"); stioc(output);
      return;
   }

   // 5 if associated with a different color
   else {sprintf(output, "no, it's %s\n", value1); stioc(output);}
}

//------------------------------------------------------

void handle_color_question(char* subject) {
   int result;
   char value[20];
   char key[60];
char output[80];

strcat(debug_string, "color question\n");  // debug info

   sprintf(key, "%s > color", subject);
   result = db_get_value(key, value);
   if(result == FOUND) {
      sprintf(output, "%s\n", value); stioc(output);
      return;
   } else {
      sprintf(output, "I don't know\n"); stioc(output);
      return;
   }

   //else if(result==3)sprintf(output, "I've never heard of %s\n",key); stioc(output);
// else sprintf(output, " I don't know (result %d)\n", result); stioc(output);
}

void handle_pronouns(void){

int i;
// - - IN PROGRESS - - -
int verb_position;
int shifting_needed;
// i
   for(i=1; i<+number_of_words; i++) {
      if (strcmp(words[i],"i")==0)  {
         strcpy(words[i], current_user_id_string);
      }
   }

// you
   for(i=1; i<+number_of_words; i++) {
      if (strcmp(words[i],"you")==0) {
         strcpy(words[i], "#1");
      }
   }

// my
//   verb_position = find_verb();
   for(i=1; i<=number_of_words; i++){
      if(strcmp(words[i],"my")!=0) continue;
      // is there a verb on the left? can only check if verb_position > 1
      if(i-1 == verb_position) {
      // get id words[i+1]
      // put id in words[i], store and get an id if needed
      shifting_needed = TRUE;
      // shift remaining words left

      }
   if(shifting_needed == TRUE) number_of_words++;
   shifting_needed = FALSE;

   }


// your



   // known person or robot
 //  result = db_get_id_string2(p1, id3);
   if (result == FOUND){
 //       strcpy(p1, id3);
   }
   else{
  //    sprintf(output, "%s is not a known specific entity\n", p1); stioc(output);
      return;
   }

//skip840:


}

void handle_attribute_question(char* p1, char* p2){

// what is your name
// what color is chocolate
//
// p1 is chocolate
// p2 is color

  int r;
  char id3[20];
  char value2[30];
  char output[80];

  strcat(debug_string, "attribute question\n");  // debug info
//

   if (strcmp(p1,"i")==0)  {
      strcpy(p1, current_user_id_string);
      goto skip1100;
   }
   else if (strcmp(p1,"you")==0) {
      strcpy(p1, "#1");
      goto skip1100;
   }
/*
   // known person or robot
   result = db_get_id_string2(p1, id3);
   if (result == FOUND){
        strcpy(p1, id3);
   }
   else{
      sprintf(output, "%s is not a known specific entity\n", p1); stioc(output);
      return;
   }
*/
skip1100:

//
   sprintf(key, "%s > %s", p1, p2);  // assemble key
   if(db_get_value(key, value2) == FOUND) {
      sprintf(output, "%s\n", value2); stioc(output);
      return;
   }
   sprintf(output, "I don't know"); stioc(output);
   return;



}







