#include "main.h"

void error(const char *);

//-------------------------------------------------------

int main(void)
{

    // Declare vaiables
//   char out[MAX_WORDS][MAX_LETTERS];
    char temp[40][20];
//    char key[80];
//    char buffer[256];
    char output[80];
//  char *output; // this causes a segmentation fault

//    ssize_t ssize;

    irc = TRUE;
    // irc = FALSE;

    // INITIALIZE
    irc_init();
    gender_code = 0;
    strcpy(debug_string, "");
    strcpy(current_user_id_string, "#0");
    strcpy(gender, "unknown");
    strcpy(current_user_name, "unknown");
    expecting_name = FALSE;
    expecting_gender = FALSE;
    time_of_last_input=time(NULL);
    time_of_last_output=time(NULL);


    // THE MAIN LOOP
    while(1)
    {
        // for console I/O
        if(irc == FALSE)
        {
            printf(">"); // user prompt
            get_string(); // get user input from console and store in user_input[]
        }
        // for IRC
        else
        {   // Checks the IRC server for incoming data. Handles pings. Returns 1 if
            // there are words to be processed. Words will be in user_input
            result = irc_io();
            if(result == 0) continue;
        }

        parse(); // separate the sentence into individual words

#if 1
        // word substitutions
        for(n=1; n<=number_of_words; n++)
        {
            //if (strcmp(words[n],"does")==0) strcpy(words[n], "do");
            if (strcmp(words[n],"has")==0)  strcpy(words[n], "have");
            if (strcmp(words[n],"are")==0)  strcpy(words[n], "is");
            if (strcmp(words[n],"wants")==0)strcpy(words[n], "want");
            if (strcmp(words[n],"feels")==0)strcpy(words[n], "feel");
            if (strcmp(words[n],"likes")==0)strcpy(words[n], "like");
            if (strcmp(words[n],"am")==0)	  strcpy(words[n], "is");
            if (strcmp(words[n],"an")==0)	  strcpy(words[n], "a");
            if (strcmp(words[n],"hello")==0)	  strcpy(words[n], "hi");
            if (strcmp(words[n],"hey")==0)	  strcpy(words[n], "hi");
        }
#endif

        //----------------

// The main sentence processing starts here.

        // Help
        if(number_of_words==1 &&
                strcmp(words[1], "help")==0)
        {
            handle_help();
            continue;
        }

        // Show debug info
        if(number_of_words==1 &&
                strcmp(words[1],"d")==0)
        {
            sprintf(output, "%s",debug_string);
            stioc(output);
            continue;
        }
        strcpy(debug_string, "");

        //Dealing with 1 word replies to robot questions
        //expected template: my name is *
        if (expecting_name == TRUE && number_of_words == 1)
        {
            strcpy(temp[1],"my");
            strcpy(temp[2],"name");
            strcpy(temp[3],"is");
            strcpy(temp[4], words[1]);
            memcpy(words, temp, 800);  // MAX_WORDS * MAX_LETTERS
            number_of_words = 4;
        }
        expecting_name = FALSE;

//expected template: my gender is *
        if (expecting_gender == TRUE && number_of_words == 1)
        {
            strcpy(temp[1],"my");
            strcpy(temp[2],"gender");
            strcpy(temp[3],"is");
            strcpy(temp[4], words[1]);
            memcpy(words, temp, 800);  // MAX_WORDS * MAX_LETTERS
            number_of_words = 4;
        }
        expecting_gender = FALSE;

        // Log in?
        // my name is ___
        if(number_of_words==4 &&
                strcmp(words[1],"my")==0 &&
                strcmp(words[2],"name")==0 &&
                strcmp(words[3],"is")==0)
        {
            handle_login(words[4]);
            continue;
        }

        // Hi
        if(number_of_words==1 &&
                strcmp(words[1], "hi")==0)
        {
            handle_greetings();
            continue;
        }

#if 1
        // Logged in? If not, go no further. This can be disabled for testing purposes
        if(strcmp(current_user_id_string, "#0") == 0)
        {
            handle_greetings();
            continue;
        }
#endif

// - - - - MUST BE LOGGED IN TO GET PAST THIS POINT - - - - - - -  - - - - - -

        // A few quick answers. Will be processed normally at some point
        if(strcmp(user_input, "what are you")==0)      {stioc("a robot.\n"); continue;}
        if(strcmp(user_input, "are you human")==0)     {stioc("no"); continue;}
        if(strcmp(user_input, "are you a robot")==0)   {stioc("yes\n"); continue;}
        if(strcmp(user_input, "are you a person")==0)  {stioc("no\n"); continue;}
        if(strcmp(user_input, "where are you")==0)     {stioc("home\n"); continue;}
        if(strcmp(user_input, "who are you")==0)       {stioc("a robot\n"); continue;}
        if(strcmp(user_input, "where is home")==0)     {stioc("canada\n"); continue;}
        if(strcmp(user_input, "how are you")==0)       {stioc("partialy functional\n"); continue;}
        if(strcmp(user_input, "what is your name")==0) {stioc("ivan\n"); continue;}

        //modify_nouns(); // comming soon

        if(number_of_words == 1) {f1(); continue;}

        // Determine if the sentence is a question, statement or command
        if(isquestion())  {handle_question();  continue;}
        if(isstatement()) {handle_statement(); continue;} // 3 or more words needed
        if(iscommand())   {handle_command();   continue;}


// If we haven't figured out the sentence by now, all we can do is make suggestions

        // Too many words?
        if(number_of_words>5)
        {
            sprintf(output, "Try shorter sentences\n");
            stioc(output);
            continue;
        }

        // No verbs?
        if(number_of_words>1)
        {
            flag = 0;
            // check each word to see if it's a verb
            for(i=1; i<=number_of_words; i++)
            {
                if(isverb(words[i]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag==0)
            {
                sprintf(output, "I need complete sentences that include a verb\n");
                stioc(output);
                continue;
            }
        }



        // Nothing typed?
        if(number_of_words==0)
        {
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






