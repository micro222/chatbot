#include "template_functions.h"

int search_file(void)
{
    /*
    search file for matching template
     read line, if EOL return fail
     remove comments
     extract template
     split template
     check template for match
    extract info
     extract function_name
     extract arg1
     extract arg2
     change arguments if they are integers
    return success
    call function
    */
#define MAX 150
    int n;
    int numberofwords;
    FILE *templates;
    char output[80];
    int status;
    char* file_status;
    int index;
    int length;

// open file
    templates = fopen("templates2.txt","r");
    if(templates == NULL)
    {
        sprintf(output, "fopen failed while trying to open templates2.txt\n");
        puts(output);
    }

// search line by line
    while(1){
        // read a line
        file_status = fgets(template_line, 100, templates);
        if (file_status==0){printf("\nEOF"); return 0;}
        remove_comments();
        length = extract_template();
        if (length == 0) continue; // get the next line
        split_template();  // results are put in template_words
        match = compare_template();
  //       if(match == 1) printf("\nMATCH\n  ");
        if(match == 1) break;
    } // get another template if there's no match
    fclose(templates);
//if(match == 0) return;
//    printf("Template words:");
    for(n=1; n<=numberoftemplatewords; n++) printf("%s ", template_words[n]);
    extract_function_name();           //    printf(" func: %s ", function_name);
    extract_arg1();                    //    printf(" arg1: %s ", arg1);
    extract_arg2();                    //    printf(" arg2: %s ", arg2);

 index = atoi(arg1);
 if(index > 0){strcpy(arg1, user_words[index]); }
 //printf(" arg1b: %s ", arg1);

 index = atoi(arg2);
 if(index > 0){strcpy(arg2, user_words[index]); }
 //printf(" arg2b: %s \n", arg2);

 return 1;

}
////////////////////////////////

int extract_template(void)
{
    int letter_position;
    line_position =0;

    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)

    {
        // End of template_line?

        if(template_line[line_position]==0 )
        {
            template1[letter_position] = 0;
         //   printf("null:%s\n", template1);
            return 0;
        }
        if(line_position >=  0x10|| line_position >= 0x13)
        {
            template1[letter_position] = 0;
    //        printf("crlf:%s\n", template1);
            return 0;
        }
        //end of word?
        if(template_line[line_position] == ',')
        {
            template1[letter_position] = 0;  // terminate the word
            line_position++;
             //printf("105:%s\n", template1);////////////////////////////
            return letter_position;
        }
        template1[letter_position] = template_line[line_position];
        line_position++;
    //    printf("110:%s\n", template1);
    }
    return 0;
}

void split_template()
{

    int letter_position = 0;
    int word_position = 1;
    int n;

    for(line_position = 0; line_position < sizeof(template1); line_position++)
    {

        if(template1[line_position]==0)
        {
            template_words[word_position][letter_position] = 0;
            numberoftemplatewords = word_position ;

#if 0
printf("user words: ");
for(n=1;n<=number_of_words;n++) printf(" %s ", user_words[n]);
printf("\ntemplate words: ");
for(n=1;n<=numberoftemplatewords;n++) printf(" %s ", template_words[n]);
printf("\n\n");
#endif

            return;
        }

        if(template1[line_position] == ' ')
        {
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
  // printf("num %d\n", numberoftemplatewords);/////
  if(number_of_words != numberoftemplatewords) return 0;

    for(n=1; n<=numberoftemplatewords; n++)
    {

//printf("N:%d\n", n);
//printf("tem: %s\n", template_words[n]);
//printf("user: %s\n", user_words[n]);/////////////
//printf("\n");

        if(strcmp(user_words[n], template_words[n] ) == 0 ||
                (strcmp(template_words[n], "*") == 0))        {
  //         printf("same\n");
        }
        else {
    //        printf("different\n");
            return 0;
        }
    }
  //  printf("default\n");
    return 1; // match
}


void remove_comments(void)
{
//        status = 1;
    int n;

    for(n=0; n< MAX; n++)
    {
        if(template_line[n] == '/')
        {
            template_line[n] = 0;    // terminate the string
            return;
        }
        else if(template_line[n] == 0)
        {
            //              status = 0;
            return;
        }
    }

}


void extract_function_name(void){

    int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the comma
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){
        //end of function name?
  //        printf(" LP:%d",letter_position);

        if(template_line[line_position] == ','){
            function_name[letter_position] = 0;  // terminate the word


            line_position++; // skip over the comma
            return;
        }
        function_name[letter_position] = template_line[line_position];
        line_position++;
    }
}


void extract_arg1(void){
    int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the space
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        //end of arg1?
        if(template_line[line_position] == ',')
        {
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
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        //end of arg2?
        if(template_line[line_position] == ' '  )
        {
            arg2[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        arg2[letter_position] = template_line[line_position];
        line_position++;
    }
}

int str_to_int(char* s){
  if (s[0] < '0' || s[0] > '9') return 0;
  return s[0] - '0';
}

/////////////////////////////////
