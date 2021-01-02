#include "template_functions.h"

int search_template_file(void){

    #define MAX 150
    int n;
    FILE *templates;
   // char output[80];
   // int status;
    char* file_status;
    int index;
    int length;

// open file
    templates = fopen("templates2.txt","r");
    if(templates == NULL) printf("fopen failed while trying to open templates2.txt\n");

// search line by line
    while(1)    {
        // read a line
        file_status = fgets(template_line, 100, templates);
        if (file_status==0){return 0;}
        remove_comments();
        length = extract_template(); // gets stored in templates1
        if (length == 0) continue;   // if there was no template, move on to the next line
        split_template();            // results are put in template_words
        match = compare_template();  // compares user_words with template_words
        if(match == 1) break;
    } // get another template if there's no match
    fclose(templates);
    extract_function_name();
    extract_arg1();
    extract_arg2();
    index = atoi(arg1);
    if(index > 0){strcpy(arg1, user_words[index]);}    // if a number is specified, replace with the appropriate word
    index = atoi(arg2);
    if(index > 0){strcpy(arg2, user_words[index]);}    // if a number is specified, replace with the appropriate word
    return 1;
}
////////////////////////////////

int extract_template(void)
{
    int letter_position;
    line_position =0;

    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){
        // End of template_line?
        if(template_line[line_position]==0 ){
            template1[letter_position] = 0;
            return 0;
        }
        if(line_position >=  0x10|| line_position >= 0x13){
            template1[letter_position] = 0;
            return 0;
        }
        //end of word?
        if(template_line[line_position] == ','){
            template1[letter_position] = 0;  // terminate the word
            line_position++;
            return letter_position;
        }
        template1[letter_position] = template_line[line_position];
        line_position++;
     }
    return 0;
}

void split_template(){

    int letter_position = 0;
    int word_position = 1;
    int n;

    for(line_position = 0; line_position < sizeof(template1); line_position++){

        if(template1[line_position]==0){
            template_words[word_position][letter_position] = 0;
            numberoftemplatewords = word_position ;
            return;
        }

        if(template1[line_position] == ' '){
            template_words[word_position][letter_position] = 0;  // terminate the word
            word_position++;
            letter_position = 0;
            continue;
        }
        template_words[word_position][letter_position] = template1[line_position];
        letter_position++;
    }
}

int compare_template()
{
    int n;
    //match = 1; // match
    if(number_of_words != numberoftemplatewords) return 0;

    for(n=1; n<=numberoftemplatewords; n++)
    {
        if(strcmp(user_words[n], template_words[n] ) == 0 ||
                (strcmp(template_words[n], "*") == 0))
        {
        }
        else{
             return 0;
        }
    }
    return 1; // match
}


void remove_comments(void){

    int n;

    for(n=0; n< MAX; n++){
        if(template_line[n] == '/'){
            template_line[n] = 0;    // terminate the string
            return;
        }
        else if(template_line[n] == 0){
            return;
        }
    }
}


void extract_function_name(void)
{

    int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the comma
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        //end of function name?
        if(template_line[line_position] == ','){
            function_name[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        function_name[letter_position] = template_line[line_position];
        line_position++;
    }
}


void extract_arg1(void)
{
    int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the space
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        //end of arg1?
        if(template_line[line_position] == ','){
            arg1[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        arg1[letter_position] = template_line[line_position];
        line_position++;
    }
}


void extract_arg2(void){
    int letter_position;
    if(template_line[line_position] == ',' ) line_position++; // skip over the space
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){
        //end of arg2?
        if(template_line[line_position] == ' ' || template_line[line_position] == 0  ){
            arg2[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        arg2[letter_position] = template_line[line_position];
        line_position++;
    }
    printf("ea2 error\n");
}
/*
int str_to_int(char* s)
{
    if (s[0] < '0' || s[0] > '9') return 0;
    return s[0] - '0';
}
*/
/////////////////////////////////
