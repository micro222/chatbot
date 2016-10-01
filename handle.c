#include "handle.h"
#include "functions.h"

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

   // 1 is "animal" in the database?
   if(db_check(user_class) != FOUND) {
      printf("I'm not familiar with %s\n", user_class);
      return;
   }

   //  preparatiom for 2, 3 & 4
//  ex: lookup "cat"
   sprintf(key, "%s > class", user_subject);
   result = db_lookup(key, value);

//  2)
   if(result == NOT_FOUND) {
      sprintf(key, "%s > class", user_subject);
      db_add_pair(key, user_class);
      printf("I'll take a note of that\n");
      return;
   }

//  Note: At this point, "cat" was found in the database.
//  We just need to check if the info matches or not.

//  3) states what already is known
   if(strcmp(user_class, value) == 0) {
      printf("I already know that\n");
      return;
   }

//  4) contradictory info
   else {
      printf("no, it's a %s\n", value);
      return;
   }
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

   if(DEBUG) printf("handle_color  ");

   // 1 is "grass" in the database?
   if(db_check(user_subject) != FOUND) {
      printf("I'm not familiar with %s\n", user_subject);
      return;
   }

   // 2 is "grass" something that can have a color?
   if(db_root_check(user_subject, "substance")!=MATCH && db_root_check(user_subject, "object") != MATCH) {
      printf("I don't think %s can have a color\r\n", user_subject);
      return;
   }

   // 3 is grass already associated with that color? if not, add it
   sprintf(key, "%s > color", user_subject);
   color_result = db_lookup(key, value1);
   if(color_result == NOT_FOUND) {
      sprintf(key, "%s > color", user_subject);
      db_add_pair(key, user_color);
      printf("I'll take a note of that\n");
      return;
   }

   // 4 if already associated with the given color
   if(strcmp(user_color, value1) == 0) {
      printf("I already know that\n");
      return;
   }

   // 5 if associated with a different color
   else printf("no, it's %s\n", value1);
}
//--------------------------------------------------

void handle_class_question(char* subject) {

   int result;
   char value[20];
   char key[20];

   sprintf(key, "%s > class", subject);
   result = db_lookup(key, value);
   if(result==FOUND) printf("It's a %s\n", value);
   else printf("I've never heard of ""%s""\n", subject);

}

//------------------------------------------------------

void handle_color_question(char* subject) {
   int result;
   char value[20];
   char key[60];

   sprintf(key, "%s > color", subject);
   result = db_lookup(key, value);
   if(result == FOUND) {
      printf("%s\n", value);
      return;
   } else {
      printf("I don't know\n");
      return;
   }

   //else if(result==3)printf("I've never heard of %s\n",key);
// else printf(" I don't know (result %d)\n", result);
}

//----------------------------------------------------

void handle_color_confirmation_question(char* subject, char*value1) {

   int result;
   char value[20];
   char key[60];

   sprintf(key, "%s > color", subject);
   db_lookup(key, value);
   result = strcmp(value, value1);
   if (result == 0) {
      printf("yes\n");
   } else printf("no\n");
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

// is the first word the first name of someone we know?
   if(db_get_id(key) == 0) {
      printf("I don't know %s\n", key);
      return;
   }

   if(db_root_check(key,"firstname") == NOT_FOUND){
      printf("%s?\n", key);
// TODO (pi#1#): better reply
      return;
   }

// is the 2nd parameter a known person?
//
   result = db_get_id(parameter2);  // a known entity?
   if(result==FOUND) {
      goto add_info;
   }

   //  Check if the 2nd parameter a object or substance?
   result = db_root_check(parameter2, "object");
   result2 = db_root_check(parameter2, "substance");

   if(result == NOT_FOUND || result2 == NOT_FOUND ) {
      printf("I dont see how %s makes sense\n", parameter2);
      return;
   }

add_info:
   // bob > rating > beer: 7
   sprintf(key,"%s > rating > %s", parameter1, parameter2 );
   db_add_pair(key, rating);

  }

//--------------------------------------------------


void handle_location_question(char* subject) {

   int result;
   char value[20];
   char key[60];

   // DO WE KNOW THE ANSWER?
//    strcpy(key, subject);
//    strcat(key, " > location");
   sprintf(key, "%s > location", subject);
   result = db_lookup(key, value);
   if(result==FOUND) {
      printf("%s\n", value);
      return;
   }

   // DO WE KNOW THE SUBJECT BUT NOT THE ANSWER?
   //strcpy(key, subject);
   //strcat(key, " > class");
   sprintf(key, "%s > class", subject);
   result = db_lookup(key, value);
   if(result==FOUND) {
      printf(" I don't know where %s is\n", subject);
      return;
   }

   // WE DON'T KNOW THE SUBJECT
   printf(" I never heard of %s\n", key);
   return;

}

//-------------------------------------------------------

void handle_ability_question(char* subject, char* action) {

//   int result;
   char key[40];
   char value[20];

   // Is suject in the database?
   if(db_check(subject) == NOT_FOUND) {
      printf(" I never heard of %s\n", subject);
      return;
   }
//--
   // Is subject an object?
   if(db_root_check(subject, "object") == NOT_FOUND) {
      printf("%s is not an object\n", subject);
      return;
   }

   // Is action really an action?
   if(db_root_check(action, "action") == NOT_FOUND) {
      printf("%s is not an action\n", action);
      return;
   }

   // Look up ability
   sprintf(key,"%s > ability > %s", subject, action);
   db_lookup(key, value);
   printf("RESULT: %s\n", value);
// TODO (pi#1#): improve the output

}

//------------------------------------------------------
// key is someones first name
// p is what the rating is of
//
void handle_rating_question(char* key, char* p) {

   int result;
   char value[20];
//   char id[20];
   char temp[20]="rating-";

   result = db_get_id(key);
   //printf("result %d %s %s %s      ", result, key, p, id);
   //return;

   if(result !=0) {
      printf("I dont know %s\n", key);
      return;
   }

//printf("result %d     ", result);
//  return;

//check if the subject of rating is known

//   result = db_subject_search(p);
   if(result!=0) {
      printf("What is %s?\n", key);
      return;
   }

// get rating if any
   strcat(temp, p);
//  result = db_search(key,temp,value);

   if(result==0) printf("%s\n", value);
   else printf("I dont know (code:%d)\n", result);

}

//----------------------------------------

void handle_list_question(char* subject) {

// WORK IN PROGRESS

}

//--------------------------------------------------

void handle_attribute_statement(char* user_subject,char* user_attribute) {
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

   // 1) ex: is "grass" in database?
   if(db_check(user_subject) == NOT_FOUND) {
      printf("I'm unfamiliar with %s\n", user_subject);
      return;
   }

   // 2) Is grass an object or substance?
   result1 = db_root_check(user_subject, "object");
   result2 = db_root_check(user_subject, "substance");
   if ((result1 == NOT_FOUND) && (result2 == NOT_FOUND)) {
      printf("I don't think %s can have such an attribute\n", user_subject);
      return;
   }

   // 3) is green in db?
   sprintf(key, "%s > class", user_attribute);
   if(db_lookup(key, db_class) == NOT_FOUND) {
      printf("I'm unfamiliar with %s\n", user_attribute);
      return;
   }

   // 4) is "green" an attribute
   if(db_root_check(user_attribute, "attribute") == NOT_FOUND) {
      printf("%s is not an attribute\n", user_attribute);
      return;
   }

   // Preparation for 5, 6 and 7

   // Get the type of the attribute. ex: "green is a color"
   sprintf(key, "%s > class", user_attribute);  // assemble key, ex: "green > class"
   db_lookup(key, attribute_type);  // ex: returns "color"

   // Get the attribute from db if any
   sprintf(key, "%s > %s", user_subject, attribute_type);  // assemble key, ex: "green > color"
   result = db_lookup(key, db_attribute);  // ex: returns "green"

   // 5) Is the attribute already known?
    if(strcmp(user_attribute, db_attribute) == 0) {   // compare "green"(what the user typed) with green(from db)
      printf("I already know that\n");
      return;
   }

   // 6 Check if the attrubute contradicts what's in the db
   if(result == FOUND) {
      printf("no, it's %s\n", db_attribute);
      return;
   }

   // 7 Since posiblities 1 to 6 have been eliminated, it's ok to add the info to the db
   // Determine attribute type

   // Add to db


//   sprintf(key, "%s > %s", user_subject, attribute_type);  // assemble key, ex: grass > color
//   db_add_pair(key, user_attribute);
db_add_pair2(user_subject, attribute_type, user_attribute);

   printf("I'll take a note of that\n");
   return;

}

//--------------------------------------------------
// handle hi, hello
//
//
void handle_greetings(void) {
   // if not logged in
   if(current_user_id == 0) {
      printf("hi, what is your name?\r\n");
      expecting_name = TRUE;
   }
   // if logged in
   else {
      printf("hi %s\r\n", current_user_name);
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
      printf("I'm not familiar with %s\n", user_class);
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
      printf("I'll take a note of that\n");
      return;
   }

//  Note: At this point, "cat" was found in the database.
//  We just need to check if the info matches or not.

//  3) states what already is known
   if(strcmp(user_class, value) == 0) {
      printf("I already know that\n");
      return;
   }

//  4) contradictory info
   else {
      printf("no, it's a %s\n", value);
      return;
   }
}
*/

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
   int id2;

//   int subject_result;
//   char subject_class[20];
   char db_class[20];

   // is dog in db? no
   sprintf(key, "%s > class", parameter2);
   if(db_lookup(key, db_class) == NOT_FOUND) {
      printf("I'm unfamiliar with %s\n", parameter2);
      return;
   }

   // is "dog" a condition? no
   if(db_root_check(parameter2, "condition") == FOUND) {
      db_add_pair2(parameter1, "condition", parameter2); // new function
 //  #17 > condition: toothache
      printf("I'll take a note of that\n");
      return;
   }

   //  is "dog" a relation? no
   if(db_root_check(parameter2, "relation") == FOUND) {
      sprintf(key, "%s > %s", parameter1, "condition");  // assemble key
      db_add_pair(key, parameter2);
      printf("I'll take a note of that\n");
      return;
   }

   //  is "dog" a pet? yes
   if(db_root_check(parameter2, "creature") == FOUND) {
      //  sprintf(key, "%s > %s", parameter1, "pet");  // assemble key
      //  db_add_pair(key, parameter2);

      id2 = db_next_available_id(); // get an unused ID# for the dog
      sprintf(key1, "#%d", current_user_id); // convert id# to db string
      sprintf(key2, "#%d", id2); // convert id# to db string
      db_add_pair2(key2, "class", parameter2); // ex: #125 > class: dog
      db_add_pair2(key2, "owner", key1); // ex: #125 > owner: #17
      db_add_pair2(key1, "pet", key2); // ex: #17 > pet: #125
      printf("I'll take a note of that\n");
      return;

   }
   //  is "dog" a posession
   if(db_root_check(parameter2, "object") == FOUND) {
      id2 = db_next_available_id(); // get an unused ID# for the posession
      sprintf(key1, "#%d", current_user_id); // convert id# to db string
      sprintf(key2, "#%d", id2); // convert id# to db string
      //printf("1:%s, 2:%s", key1, key2);
      db_add_pair2(key2, "class", parameter2); // ex: #125 > class: car
      db_add_pair2(key2, "owner", key1); // ex: #125 > owner: #17
      db_add_pair2(key1, "posession", key2); // ex: #17 > posession: #125
      printf("I'll take a note of that\n");
      return;

   }


   printf("I don't know how you can have a %s\n", parameter2);
   return;

}

//------------------------------------------------------


void handle_login(char* name) {
   int result;
   int known=FALSE;
   int new2 = TRUE;
 //  char first_name[20]
   char id_string[20];
   //char s2[20];
   char value[20];
   char key[80];
   int id_number;

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
      printf("You told me that already\n");
      known=TRUE;
      return;
   }

   // Step #2
   id_number = db_get_id(name);
   if(id_number != 0) {
      known=TRUE;
      new2 = FALSE;
      // get gender
      sprintf(key,"#%d > gender", id_number);
      result = db_lookup(key, value);
      if(result != FOUND) {
         gender_code=0;
      }
      if(strcmp(value, "male")==0) {
         gender_code=1;
      }
      if(strcmp(value, "female")==0) {
         gender_code=2;
      }
   } else {
      known=FALSE;
   }

   // Step 3: add user to database
   if(known==FALSE) {
      // Get an id number
      id_number = db_next_available_id();

      // Add the following to the database
      //   #1 > class: person
      //   #1 > firstname:bob
      //   #1 > gender:male
      snprintf (id_string, sizeof(id_string), "%d",id_number);
      sprintf(key, "#%s > class", id_string);
      db_add_pair(key, "person");
      sprintf(key,"#%s > firstname", id_string);
      db_add_pair(key, name);
      sprintf(key,"#%s > gender", id_string);
      gender_code = check_gender_by_name(name);
      switch(gender_code) {
      case 1:
         db_add_pair(key, "male");
         break;
      case 2:
         db_add_pair(key, "female");
      }
      known=TRUE;
      new2 = TRUE;
   }

   // Step 4:
   strcpy(current_user_name, name);
   current_user_id = id_number;
   if(new2 == TRUE) {
      printf("hello %s\n", current_user_name);
   } else {
      printf("hi %s\n", current_user_name);
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
   printf("I can handle the following sentences\r\n\r\n");
   printf(" my name is ___\n");
   printf(" what is my name\n");
   printf(" what is my gender\n");
   printf(" I am male\n");
   printf(" I am female\n");
   printf(" my gender is male\n");
   printf(" my gender is female\n");
   printf(" say my name\n");
   printf(" what color is ___, ex: what color is grass\n");
   printf(" is <subject> <color>, ex: is grass green\n" );
   printf(" where is <object>\n" );
   printf(" can ___ ___, ");
   printf(" what are ___\n" );
   printf(" what is a ___\n" );
   printf(" what is ___\n" );
   printf(" a <object> is a ___, ex: a cat is an animal\n" );
   printf(" ___ is <color>\n" );
   printf(" ___ like ___, ex: I like pizza\n" );
   printf(" ___ hate ___\n" );
   printf(" ___ love ___\n" );
   printf(" ___ dont like ___\n" );
   printf(" do you like ___\n" );
   //printf("who am i, ");
   //printf("i am ___\r\n");
   printf("bye\r\n");
   //printf("is ___ ___, ");
   //printf("what is ___, ");
   //printf("have you heard of ___, ");
   //printf("___ is ___\r\n");
   //printf("can ___ ___, ");
   //printf("do ___ ___, ");
   //printf("___ can ___\r\n");
   //printf("___ like ___, ");
   //printf("do ___ like ___\r\n");
   //printf("___ hates ___, ");
   //printf("do ___ hate ___\r\n");
   //printf("___ is in ___, ");
   //printf("where is ___\r\n");
   //printf("how old is/are ___\r\n");
   //printf("do ___ feel ___, ");
   //printf("___ feels ___\r\n");
   //printf("do ___ want ___, ");
   //printf("___ want _\r\n");
   //printf("do ___ have ___\r\n");
   //printf("what is the ___ of ___, ___ is the ___ of___\r\n");
   //printf("what time is it\r\n");
   //printf("lookup ___\r\n");
   // continue;
}

