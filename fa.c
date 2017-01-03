#include "fa.h"

int f1(void)
{

    char output[80];

    strcat(debug_string, " f1 ");  // debug info
// Log out
    if(strcmp(words[1],"bye")==0)
    {
        sprintf(output, "talk to you later %s\r\n",current_user_name);
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

    // Get gender
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
    if(isverb(words[1]) == 1)
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



// none of the above
int fnota(void)
{
    char output[80];
return 0;

}


//=================================================
