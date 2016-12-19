#include "fa.h"

int f1(void)
{

    char output[80];

// Log out
    if(strcmp(words[1],"bye")==0)
    {
        sprintf(output, "talk to you later %s\r\n\r\n",current_user_name);
        stioc(output);
//       current_user_name[20]="unknown";
        strcpy(current_user_name, "unknown");
        strcpy(current_user_id_string, "#0");
        //current_user_id = 0;
        gender_code = 0;
        strcpy(gender, "unknown");
        return 1;
    }

    // Get ID number
    if(strcmp(words[1],"id")==0)
    {
        {
            sprintf(output, "%s\n",current_user_id_string);
            stioc(output);
        }
        return 1;
    }

    // Get gender code
    if(strcmp(words[1],"g")==0)
    {
        {
            sprintf(output, "%s\n",gender);
            stioc(output);
        }
        return 1;

    }

// and if input was not understood...

    // A single verb?
    if(isverb(words[1]) == 0)
    {
        sprintf(output, "is a verb\n");
        stioc(output);
        return 1;
    }

    // Single word
    sprintf(key, "%s > class", words[1]);  // assemble a key
//        if(db_lookup(key, value) == FOUND) {
    if(db_get_value(key, value) == FOUND)
    {
        sprintf(output, "That's a %s\n", value);
        stioc(output);
        return 1;
    }
    if(isword(words[1])==0)
    {
        sprintf(output, "%s is in my dictionary, but I'm not familiar with it\n", words[1]);
        stioc(output);
    }
    else
    {
        sprintf(output, "That's not in my dictionary\n");
        stioc(output);
    }
    return 1;
}

int f2(void)
{
    char output[80];

    // Template: list <class>
    // Example: list action
    if(strcmp(words[1],"list")==0)
    {
        handle_list_question(words[2]);
        return 1;
    }
return 0;

}

int f3(void)
{
    char output[80];
    // what is ___
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"is")==0)
    {
        handle_class_question(words[3]);
        return 1;
    }

    // what are ___
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"are")==0)
    {
        handle_class_question(words[3]);
        return 1;
    }
    // where is ___
    if(strcmp(words[1],"where")==0 &&
            strcmp(words[2],"is")==0 )
    {
        handle_location_question(words[3]);
        //   handle_attribute_question(words[3], "location");
        return 1;
    }

    // ___ is ___
    // this needs to be placed after "what is ___"
    if(strcmp(words[2],"is")==0)
    {
        handle_attribute_statement(words[1],words[3]);
        return 1;
    }

    if(strcmp(words[2],"is")==0 )
    {
        handle_class_statement(words[1],words[3]);
        return 1;
    }

    // is ___ <color>?
    if(strcmp(words[1],"is")==0 &&
            db_root_check(words[3],"color")==FOUND)
    {
        handle_color_confirmation_question(words[2],words[3]);
        return 1;
    }

    // where is ___
    if(strcmp(words[1],"where")==0 &&
            strcmp(words[2],"is")==0)
    {
        handle_location_question(words[3]);
        return 1;
    }

    // - - - - - - - - - - - - - - - - - - - - - -
    // ABILITY
    // can <subject> <action>
    if(strcmp(words[1],"can")==0 )
    {
        handle_ability_question(words[2],words[3]);
        return 1;
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
    if(strcmp(words[2],"like")==0)
    {
        handle_rating_statement(words[1], words[3], "7");
        return 1;
    }

    // Template: <person> hate __
    // Example: i hate beer
    if(strcmp(words[2],"hate")==0)
    {
        handle_rating_statement(words[1], words[3], "0");
        return 1;
    }

    // <creature> love ___
    // conditions: 3 words, middle word is "love"
    if(strcmp(words[2],"love")==0)
    {
        handle_rating_statement(words[1], words[3], "10");
        return 1;
    }

    // Template: i have *
    // Example: i have rabies
    if(strcmp(words[2],"have")==0 )
    {
        handle_have_statement(words[1], words[3]);
        return 1;
    }

    // "say my name"
    if(strcmp(words[1],"say")==0 &&
            strcmp(words[2],"my")==0 &&
            strcmp(words[3],"name")==0)
    {
        sprintf(output, "%s\n",current_user_name);
        stioc(output);
        return 1;
    }

    /*
     // ___ is <color>
     // conditions: 3 words, middle word is "is"
     if(number_of_words==3 &&
     strcmp(words[2],"is")==0 &&
     db_root_check(words[3],"color")==FOUND) {
        handle_color_statement(words[1],words[3]);
        return 1;
     }
    */
    return 0;
}
int f4(void)
{
    char output[80];


    // what is a ___
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"is")==0 &&
            strcmp(words[3],"a")==0)
    {
        handle_class_question(words[4]);
        return 1;
    }



    if(strcmp(words[2],"is")==0 &&
            strcmp(words[3],"a")==0)
    {
        handle_class_statement(words[1],words[4]);
        return 1;
    }

    // does jane have acne
    if(strcmp(words[1],"does")==0 &&
            strcmp(words[3],"have")==0)
    {
        handle_have_question(words[2],words[4]);
        return 1;
    }

    // - - - - - - COLORS - - - - - - - - - - - - - - - -
    //
    // what color is ___
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"color")==0&&
            strcmp(words[3],"is")==0)
    {
        handle_attribute_question(words[4], words[2]);
        return 1;
    }

    // ___ dont like ___
    if(strcmp(words[2],"dont")==0 &&
            strcmp(words[3],"like")==0)
    {
        handle_rating_statement(words[1], words[3], "3");
        return 1;
    }

    // Template: does <person> like <subject>
    // Example: does fred like beer
    if(strcmp(words[1],"does")==0 &&
            strcmp(words[3],"like")==0 )
    {
        handle_rating_question(words[2], words[4]);
        return 1;
    }


    // Template: i have a *
    // Example: i have a dog
    if(strcmp(words[2],"have")==0 &&
            strcmp(words[3],"a")==0 )
    {
        handle_have_statement(words[1], words[4]);
        return 1;
    }


    // - - - - - - - - - - - - - - - - - - - - - -
    // "what is my name"
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"is")==0 &&
            strcmp(words[3],"my")==0 &&
            strcmp(words[4],"name")==0)
    {
        sprintf(output, "%s\n",current_user_name);
        stioc(output);
        return 1;
    }

    // "what is my gender"
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"is")==0 &&
            strcmp(words[3],"my")==0 &&
            strcmp(words[4],"gender")==0)
    {
        sprintf(output, "%s\n", gender);
        stioc(output);
        return 1;
    }
    // "what is my *"
    if(strcmp(words[1],"what")==0 &&
            strcmp(words[2],"is")==0 &&
            strcmp(words[3],"your")==0 )
    {
        handle_attribute_question("#1", words[4]);
        //stioc(output);
        return 1;
    }

    // my gender is male
    if(strcmp(words[1],"my")==0 &&
            strcmp(words[2],"gender")==0 &&
            strcmp(words[3],"is")==0 &&
            strcmp(words[4],"male")==0 )
    {
        sprintf(key, "%s > gender", current_user_id_string);
        strcpy(gender, "male");
        db_add_pair(key, "male");
        return 1;
    }

    // my gender is female
    if(strcmp(words[1],"my")==0 &&
            strcmp(words[2],"gender")==0 &&
            strcmp(words[3],"is")==0 &&
            strcmp(words[4],"female")==0 )
    {
        sprintf(key, "%s > gender", current_user_id_string);
        strcpy(gender, "female");
        db_add_pair(key, "female");
        return 1;
    }

    /*
          // what color is ___
          if(strcmp(words[1],"what")==0 &&
          strcmp(words[2],"color")==0&&
          strcmp(words[3],"is")==0) {
             handle_color_question(words[4]);
             return 1;
          }
    */
return 0;
}
int f5(void)
{
    char output[80];

    // a __ is a __
    // ex: a cat is an animal
    if(strcmp(words[1],"a")==0 &&
            strcmp(words[3],"is")==0 &&
            strcmp(words[4],"a")==0
      )
    {
        handle_class_statement(words[2],words[5]);
        return 1;
    }

    // does jane have a dog
    if(strcmp(words[1],"does")==0 &&
            strcmp(words[3],"have")==0 &&
            strcmp(words[4],"a")==0)
    {
        handle_have_question(words[2],words[5]);
        return 1;
    }
return 1;
}

// none of the above
int fnota(void)
{
    char output[80];
return 0;

}
