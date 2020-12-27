#include "handle.h"

void handle_class_statement(char*user_subject, char*user_class)
{
    /*

    example: a cat is an animal(value)


    Posibilities:
                                       db action      user action
        --------------------------     ------------   --------------------------
    2      cat is unknown       	   add to db      "I'll take note of that"
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

//  3)
    if(strcmp(user_class, value) == 0)
    {
        printf("I already know that\n");
        return;
    }

//  lookup "animal"
    strcpy(key, user_class);
    strcat(key," > class");
    class_result = db_lookup(key, value);

// 1)
    if(class_result == NOT_FOUND)
    {
        printf("I'm unfamiliar with %s\n", user_class);
        return;
    }

//  2)
    if(subject_result == NOT_FOUND)
    {
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

void handle_class_question(char* subject)
{

    int result;
    char value[20];
    char key[20];

    strcpy(key, subject);
    result = db_lookup(strcat(key," > class"), value);
    if(result==FOUND) printf("It's a %s\n", value);
    else printf("I've never heard of ""%s""\n", subject);

}





//----------------------------------------------------


void handle_location_question(char* subject)
{

    int result;
    char value[20];
    char key[60];

    // DO WE KNOW THE ANSWER?
    strcpy(key, subject);
    strcat(key, " > location");
    result = db_lookup(key, value);
    if(result==FOUND)
    {
        printf("%s\n", value);
        return;
    }

    // DO WE KNOW THE SUBJECT BUT NOT THE ANSWER?
    strcpy(key, subject);
    strcat(key, " > class");
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

void handle_ability_question(char* key, char* value)
{

    int result;
    char temp[20]=" > ability";

// 0 = match
// 3 = subject not found
// 5 = subject found, no def
// 7 = found, no match
    result = db_root_check(key,"object");
    if(result==3)
    {
        printf(" I never heard of %s\n", key);
        return;
    }
    else if(result!=0)
    {
        printf("code %d",result);
        return;
    }

    if(db_root_check(value,"action")!=0)
    {
        printf("%s is not an action\n",key);
        return;
    }

    strcat(temp, value);
//  result = db_search(key,temp,value);
    //  result = db_get_value(user_words[2],temp,value);

    if(result==0) printf("%s\n", value);
    else printf(" error %d\n", result);

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
    char db_value[20];
    char attribute_name[20];

    printf("   US: %s \n", user_subject);

    //  1) ex: is "grass" in database?
    sprintf(key, "%s > class", user_subject);
    subject_result = db_lookup(key, subject_class);
    if (subject_result == NOT_FOUND)
    {
        printf("I don't know what %s is(h278)\n", user_subject);
        return;
    }

    // 2) is grass an object or substance?
    result1 = db_root_check(user_subject, "object");
    result2 = db_root_check(user_subject, "substance");
    if ((result1 == NOT_FOUND) && (result2 == NOT_FOUND))
    {
        printf("I don't think %s can have such an attribute\n", user_subject);
        return;
    }

    //  3) is green in db?
    sprintf(key, "%s > class", user_attribute);
    result = db_lookup(key, db_class);
    if(result == NOT_FOUND)
    {
        printf("I'm unfamiliar with %s\n", user_attribute);
        return;
    }

    printf("\n[SUB%s ATT%s]\n", user_subject, user_attribute);

    //  4) is "green" an attribute
    result = db_root_check(user_attribute, "attribute");
    if(result == NOT_FOUND)
    {
        printf("%s is not an attribute\n", user_attribute);
        return;
    }

// 5) Already known?

// get attribute_name
    sprintf(key, "%s > class", user_attribute);
    result = db_lookup(key, attribute_name);

    sprintf(key, "%s > %s", user_subject, attribute_name);
    result = db_lookup(key, value);

    if(strcmp(user_attribute, value) == 0)
    {
        printf("I already know that\n");
        return;
    }

//  Lookup subject and attribute_name
    sprintf(key, "%s > %s", user_subject, attribute_name);
    subject_result = db_lookup(key, value);

    // Store the information
    if(subject_result == NOT_FOUND)
    {
        sprintf(key, "%s > %s", user_subject, attribute_name);
        db_add_pair(key, user_attribute);
        printf("I'll take a note of that\n");
        return;
    }


// 4)
    printf("no, it's %s\n", value);


}

//--------------------------------------------------
void handle_attribute_question(char* user_subject,char* attribute_name)
{
    /*
    example: what color is grass

    Posibilities:
    1   grass is unknown                   i dont know what grass is
    2   grass is not an object or substance
    3   color is unknown
    4   color is not an attribute
    5   if known, provide info
    */

    int result;
    int result1;
    int result2;
    char value[20];
    char key[60];
    int subject_result;

    char subject_class[20];
    char db_class[20];
    char db_value[20];
//char attribute_name[20];

    //  1) ex: is "grass" in database?
    sprintf(key, "%s > class", user_subject);
    subject_result = db_lookup(key, subject_class);
    if (subject_result == NOT_FOUND)
    {
        printf("I don't know what %s is(h278)\n", user_subject);
        return;
    }
    // 2) is grass an object or substance?
    result1 = db_root_check(user_subject, "object");
    result2 = db_root_check(user_subject, "substance");
    if ((result1 == NOT_FOUND) && (result2 == NOT_FOUND))
    {
        printf("I don't think %s can have such an attribute\n", user_subject);
        return;
    }

    //  3) is color in db?
    sprintf(key, "%s > class", attribute_name);
    result = db_lookup(key, db_class);
    if(result == NOT_FOUND)
    {
        printf("I'm unfamiliar with %s\n", attribute_name);
        return;
    }

    printf("\n[SUB%s ATT%s]\n", user_subject, attribute_name);

    //  4) is "color" an attribute
    result = db_root_check(attribute_name, "attribute");
    if(result == NOT_FOUND)
    {
        printf("%s is not an attribute\n", attribute_name);
        return;
    }

// 5) Known?

    sprintf(key, "%s > %s", user_subject, attribute_name);
    result = db_lookup(key, value);

    if(result == FOUND)
    {
        printf("%s\n", value);
        return;
    }

    printf("beats me\n");

}

//--------------------------------------------------

void handle_help(void)
{
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
printf(" L1 \n");
// Step 1: check if already current user
    if(strcmp(name, current_user_name)==0)
    {
        printf("You told me that already\n");
        known=TRUE;
        return;
    }
//printf(" L2 \n");
// Step #2
    id_number = db_get_id(name);


    if(id_number != 0)
    {
        known=TRUE;
        new = FALSE;
        sprintf(id_string, "#%d", id_number);
printf("\nyour ID number is %d \n", id_number);
    }
    else
    {
        known=FALSE;
    }
//printf(" L3 \n");
// Step 3: add to database
    if(known==FALSE)
    {
        // Get an id number
        id_number = db_next_available_id();
        sprintf(id_string, "#%d", id_number);
        printf("\nyour new ID number is %d \n", id_number);

        // Add the following to the database
        //   #1 > class: person
        //   #1 > firstname:bob
        //   #1 > gender:male

        strcpy(key, id_string);
        strcat(key, " > class");
        // printf("ID STRING: %s\n", id_string);
        //   sprintf(key, "%s > class", id_string);
        db_add_pair(key, "person");

        printf("key: %s\n", key);

        //strcpy(key, id_string);
        //strcat(key, " > firstname");
        sprintf(key, "%s > firstname", id_string);
        db_add_pair(key, name);

        // TEST
        sprintf(key, "%s > gender", id_string);
        gender_code = check_gender_by_name(name);
        switch(gender_code)
        {
        case 1:
            db_add_pair(key, "male");
            break;
        case 2:
            db_add_pair(key, "female");
        }

        known=TRUE;
        new = TRUE;
    }
printf(" L4 \n");
// Step 4:
    strcpy(current_user_name, name);
    current_user_id = id_number;
    if(new == TRUE)
    {
        printf("hello %s\n", current_user_name);
    }
    else
    {
        printf("hi %s\n", current_user_name);
    }
}

//-------------------------------------------------------------------

void handle_have_statement(char* user_subject, char* user_x)
{
    /*
       USER WORDS                                          Database entry
    -----------------   -------------------------------  --------------------
    I have a daughter   relation                         #4 > daughter:#15
    I have a car        possession(object or substance or animal)  #4 > possession:#17
    I have covid        condition                        #4 > condition:covid

    check user_subject,  errors: unknown, not a person
    check user_x,        errors: unknown, not an object or substance
    condition, relation or possession,  errors: not a relation

    If condition, add #4 > condition:covid

    If relation, add #15 > class:person, #15 gender:female, #5 > daughter:#15
    (want to know name)

    If possession, add #17 > class:car, #5 > possession:#17

    */
    char db_result[20];
    char id_string[20];
    char id_number;
    int result;

    printf("\nHAVE STATEMENT\n");

    //  1) ex: is subject in the database?
    sprintf(key, "%s > class", user_subject);
    result = db_lookup(key, db_result);
    if (result == NOT_FOUND){

    //        printf("\nUS%s RE%d K%s DBR%s\n", user_subject, result, key, db_result);



        printf("I don't know what %s is.\n", user_subject);
        return;
    }
  //  printf("\nH2\n");
    // 2) is subject a person?
    result = db_root_check(user_subject, "person");
    if (result == NOT_FOUND)
    {
        printf("I would think the first word would be a person\n");
        return;
    }
//printf("\nH3\n");
    //  3) is x in db?
    sprintf(key, "%s > class", user_x);
    result = db_lookup(key, db_result);
    if(result == NOT_FOUND)
    {
        printf("I'm unfamiliar with %s\n", user_x);
        return;
    }

 //   printf("\n[SUB: %s, X: %s]\n", user_subject, user_x);
//printf("\nH4\n");
    //  4) is x a condition
    result = db_root_check(user_x, "condition");
    if(result != NOT_FOUND)
    {

  //  printf("\n[RESULT: %d]\n", result);
        // I'd like to check if the info exists but I dont know how to deal with multiple entries
        // Store the information
        sprintf(key, "%s > condition", user_subject);
        db_add_pair(key, user_x);
        printf("I'll take a note of that [condition]\n");
        return;
    }

 //   printf("\nH5\n");
    //  4) is x a relation
    result = db_root_check(user_x, "relation");
    if(result == NOT_FOUND)
    {
        printf("%s is not a relation\n", user_x);
        return;
    }

    else {

 //--- construction
        printf("%s is a relation\n", user_x);
  //printf("\nH6\n");
// 6) Already known?

    sprintf(key, "%s > %s", user_subject, user_x);
    result = db_lookup(key, value);

    //  If relation, add #15 > class:person, #15 gender:female, #5 > daughter:#15

// Get an ID for this person
      id_number = db_next_available_id();   // get next id
      sprintf(id_string, "#%d", id_number);

// add to DB
        sprintf(key, "%s > class", id_string);
        db_add_pair(key, "person");

// add relationship
        sprintf(key, "%s > %s", user_subject, user_x);
        db_add_pair(key, id_string);

// add gender
        sprintf(key, "%s > gender", user_x );
        result = db_lookup(key, db_result);
        if(result == FOUND){
           sprintf(key, "%s > gender", id_string);
           db_add_pair(key, db_result);
        }
        printf("I'll take a note of that [3 entries created]\n");
        return;

// 7)
printf("\nH7\n");
    printf("no, it's %s\n", value);

 //-----


    }
printf("\nH2\n");
    //  4) is x a possession
    result = db_root_check(user_x, "possession");
    if(result == NOT_FOUND)
    {
        printf("%s is not an possession\n", user_x);
        return;
    }

}

void handle_have_question(char*x,char*y)
{

}





