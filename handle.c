#include "handle.h"

void handle_class_statement(char*user_subject, char*user_class)
{
    /*
    example: a cat is an animal(value)

    Posibilities:
                                       db action      user action
        --------------------------     ------------   --------------------------
    2   cat is unknown       	        add to db     "I'll take note of that"
    1   animal is unknown                             "what's an animal"
    3   cat is known, class = animal                  "I know"
    4   cat known, class != animal                    "no it's a ____"

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

    //2,3&4
//  ex: lookup "cat"
    sprintf(key, "%s > class", user_subject);
    result = db_lookup(key, value);

//  2)
    if(result == NOT_FOUND)
    {
        sprintf(key, "%s > class", user_subject);
        db_add_pair(key, user_class);
        printf("I'll take a note of that\n");
        return;
    }

//  Note: At this point, "cat" was found in the database.
//  We just need to check if the info matches or not.

//  3) states what already is known
    if(strcmp(user_class, value) == 0)
    {
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
void handle_color_statement(char* user_subject,char* user_color)
{
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
    char value1[20];char value2[20];
    int subject_result;
    char user_class;
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
    if(color_result == NOT_FOUND)
    {
        sprintf(key, "%s > color", user_subject);
        db_add_pair(key, user_color);
        printf("I'll take a note of that\n");
        return;
    }

    // 4 if already associated with the given color
    if(strcmp(user_color, value1) == 0)
    {
        printf("I already know that\n");
        return;
    }

    // 5 if associated with a different color
    else printf("no, it's %s\n", value1);
}
//--------------------------------------------------

void handle_class_question(char* subject)
{

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
    }
    else {
        printf("I don't know\n");
        return;
    }

    //else if(result==3)printf("I've never heard of %s\n",key);
// else printf(" I don't know (result %d)\n", result);
}

//----------------------------------------------------

void handle_color_confirmation_question(char* subject, char*value1)
{

    int result;
    char value[20];
    char key[60];

    sprintf(key, "%s > color", subject);
    db_lookup(key, value);
    result = strcmp(value, value1);
    if (result == 0)
    {
        printf("yes\n");
    }
    else printf("no\n");
}

//----------------------------------------------------

void handle_rating_statement(char* key, char* s2, char* rating)
{
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
// Problem: will make multiple entries

// second parameter
//
//  known person?    add info
//  unknown person?  dont know this person
//  known object?    add info
//  known substance? add info
//  unknown

    char pn[20]="rating-";
// char value[20];
    int result, result2;
    char id1[20],id2[20];
    int person = FALSE;

// So, take example 2. At this point we know that neither of the words have been checked.
// We'll start by seeing if the first word is the first name of someone we know.
// We can use the get id function for that
// If known, take note that this is a person and continue on, if not, send a message and exit

    result = db_get_id(key);

    if(result != FOUND)
    {

        result = db_root_check(key,"firstname");

        if(result==FOUND) printf("I don't know%s\n", key);
        else printf("%s?\n", key);

        return;
    }
// Next we'll look at the 2nd parameter and see if it's a known person
//
    result = db_get_id(s2);  // a known entity?
    result2 = db_root_check(s2,"firstname");  // a person?

    if(result==FOUND && result2==FOUND)
    {
        person = TRUE;
        goto add_info;
    }

    if(result!=FOUND && result2==FOUND)
    {
        printf("I don't know %s\n", s2);
        return;
    }

    //  Check if the 2nd parameter a object or substance?
    result = db_root_check(s2, "object");
    result2 = db_root_check(s2, "substance");

    if(result == NO_MATCH)
    {
        printf("I don't know what %s is\n", s2);
        return;
    }
    printf("*%d*\n", result);
    if(result != FOUND && result2 != FOUND)
    {
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
//     db_add_subject_and_property(id1,pn,rating);
//     db_add_property(id1,"firstname",key);
//     printf("name and rating added\n");
//  }
// else
    if(result==5)
    {

//     db_add_property(id1, pn, rating); // change this
        printf("rating added\n");
    }
    else if(result == FOUND) printf("I already know that\n");
    else printf("error, result code:%d\n",result);
}

//--------------------------------------------------


void handle_location_question(char* subject)
{

    int result;
    char value[20];
    char key[60];

    // DO WE KNOW THE ANSWER?
//    strcpy(key, subject);
//    strcat(key, " > location");
    sprintf(key, "%s > location", subject);
    result = db_lookup(key, value);
    if(result==FOUND)
    {
        printf("%s\n", value);
        return;
    }

    // DO WE KNOW THE SUBJECT BUT NOT THE ANSWER?
    //strcpy(key, subject);
    //strcat(key, " > class");
    sprintf(key, "%s > class", subject);
    result = db_lookup(key, value);
    if(result==FOUND)
    {
        printf(" I don't know where %s is\n", subject);
        return;
    }

    // WE DON'T KNOW THE SUBJECT
    printf(" I never heard of %s\n", key);
    return;

}

//-------------------------------------------------------

void handle_ability_question(char* key, char* value) {

    int result;
    char* temp[40];
    char value2[20];

    result = db_root_check(key,"object");
    if(result == NOT_FOUND) {
        printf(" I never heard of %s\n", key);
        return;
    }

    if(result != MATCH) {
        printf("%s is not an object\n", key);
        return;
    }

    if(db_root_check(value,"action")!= MATCH) {
        printf("%s is not an action\n",key);
        return;
    }

    sprintf(temp,"%s > ability > %s", key, value);
    result = db_lookup(temp, value2);
    printf("RESULT: %d\r\n", result);
}

//------------------------------------------------------
// key is someones first name
// p is what the rating is of
//
void handle_rating_question(char* key, char* p)
{

    int result;
    char value[20];
    char id[20];
    char temp[20]="rating-";

    result = db_get_id(key);
    //printf("result %d %s %s %s      ", result, key, p, id);
    //return;

    if(result !=0)
    {
        printf("I dont know %s\n", key);
        return;
    }

//printf("result %d     ", result);
//  return;

//check if the subject of rating is known

//   result = db_subject_search(p);
    if(result!=0)
    {
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

void handle_list_question(char* subject)
{

}

//--------------------------------------------------

void handle_attribute_statement(char* user_subject,char* user_attribute)
{
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
    //strcpy(key, user_subject);
    //strcat(key," > class");
    sprintf(key, "%s > class", user_subject);
    subject_result = db_lookup(key, subject_class);
    // if subject_result === UNKNOWN, I don't know what %s is

    // 2) is grass an object or substance?
    result1 = db_root_check(user_subject, "object");
    result2 = db_root_check(user_subject, "substance");
    if ((result1 == NOT_FOUND) && (result2 == NOT_FOUND))
    {
        printf("I don't think %s can have such an attribute\n", user_subject);
        return;
    }

    //  3) is green in db?
    //strcpy(key, user_attribute);
    //strcat(key," > class");
    sprintf(key, "%s > class", user_attribute);
    result = db_lookup(key, db_class);
    if(result == NOT_FOUND)
    {
        printf("I'm unfamiliar with %s\n", user_attribute);
        return;
    }

    //  4) is "green" an attribute
    result = db_root_check(user_attribute, "attribute");
    if(result == NOT_FOUND)
    {
        printf("%s is not an attribute\n", user_attribute);
        return;
    }

// 5) already known
// green
    //strcpy(key, user_subject);
    //strcat(key," > class");
    sprintf(key, "%s > class", user_subject);
    result = db_lookup(key, value);
// color

    strcpy(key, user_subject);
    strcat(key," > ");
    strcat(key, value);
    //sprintf(key, "%s > class", user_subject);
// green
    result = db_lookup(key, value);

    if(strcmp(user_attribute, value) == 0)
    {
        printf("I already know that\n");
        return;
    }

//  ex: lookup "grass"
    strcpy(key, user_subject);
    strcat(key," > ");
//        sprintf(key, "%s > class", user_subject);
    subject_result = db_lookup(key, value);


    if(subject_result == NOT_FOUND)
    {
     //   strcpy(key, user_subject);
     //   strcat(key," > color");
            sprintf(key, "%s > color", user_subject);
        db_add_pair(key, user_color);
        printf("I'll take a note of that\n");
        return;
    }


// 4)
    printf("no, it's a %s\n", value);


}
//--------------------------------------------------
// WORK IN PROGRESS
//
// handle hi, hello
//
//
void handle_greetings(void)
{
    // if not logged in
    if(current_user_id == 0){
        printf("hi, what is your name?\r\n");
    }
    // if logged in
    else{
        printf("hi %s\r\n", current_user_name);
    }
}


