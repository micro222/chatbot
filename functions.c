#include "functions.h"



void get_string(void) {

   int position;

   for(position = 0; position <= 78; position++) {
      user_input[position] = getchar();
      if(user_input[position]==10)break; // CR
      if(user_input[position]==13)break; // LF
   }
   user_input[position] = 0;

}

//--------------------------------------------------------------

void parse(void) {

   // input: user_input
   // output: words, number_of_words

   int position = 0;
   int letter_position;
   int word_position;
   //while(1);
   for(word_position=1; word_position < MAX_WORDS; word_position++) {
      for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++) {

         // End of user input?
         if(user_input[position]==0 || position >= 80) {
            words[word_position][letter_position] = 0;
            number_of_words = word_position;
            return;
         }

         //end of word?
         if(user_input[position]==' ') {
            words[word_position][letter_position] = 0;  // terminate the word
            letter_position = 0;  // probably not needed
            position++;  // skip over the space
            break;
         }

         //
         words[word_position][letter_position] = user_input[position];
         position++;
      }
   }

}
//------------------------------------------------------------------

int isvowel(char c1) {

   char vowels[6]="aeiouy";
   int i;

   for(i=0; i<6; i++) {
      if(c1 == vowels[i])return 0;
   }
   return 1;

}

//---------------------------------------

int isconsonant(char c1) {

   char consonants[20]="bcdfghjklmnpqrstvwxz";
   int i;

   for(i=0; i<20; i++) {
      if(c1 == consonants[i]) return 0;
   }
   return 1;

}

//-----------------------------------------------------------------------

int is_nonsense_word(char* s1) {
   //
   //  curently has trouble with: you, crackpot, apple, substance
   //
   //

   // 3 vowels in a row?
   int i,inarow;
   int j;
   char *list_nonsense[] = {"ch", "gh", "sc", "sp", "th", "ck", "pp", "tt"};
char output[80];

   inarow=0;
   for(i=0; i<80-3; i++) {
      if(user_input[i]==0) break;
      if(isvowel(user_input[i])==0) inarow++;
      else inarow=0;
      if(inarow>=4) break;
   }
   if(inarow>=3)sprintf(output, "  3 vowels in a row  \n"); stioc(output);
   // replace all occurances of CH GH SC SP TH CK PP ST with vowels
   for(i=0; i<80-3; i++) {
      if(user_input[i]==0) break;
      for (j=0; j<sizeof(list_nonsense); j++) {
         if(strncmp(&user_input[i], "ch", 2))
            strncpy(&user_input[i], "aa", 2);
      }
   }

   // 3 consonants in a row?
   inarow=0;
   for(i=0; i<80-3; i++) {
      if(user_input[i]==0) break;
      if(isconsonant(user_input[i])==0) inarow++;
      else inarow=0;
      if(inarow>=4) break;
   }
   if(inarow>=4)sprintf(output, "  that's jiberish\n"); stioc(output);

}

//--------------------------------------------------------

int isword(char*word_to_lookup) {
   FILE *general;

   int result = 1;
   char word_from_list[80];
   char *status;
char output[80];

   //  open word list
   general = fopen("word100k.txt","r");
   if(general == NULL) {
      sprintf(output, "fopen failed while trying to open word100k.txt\n"); stioc(output);
   }

   while(1) {
      status = fgets(word_from_list,40,general);
      if (status==0)break;
      // remove the newline character
      word_from_list[strlen(word_from_list)-1] = '\0';

      if (strcmp(word_to_lookup, word_from_list) == 0) {
         result = 0;
         break;
      }

   }// end of while

   fclose(general);
   return result;

}
//--------------------------------------------------------

int isverb(char* word_to_lookup){
   FILE *verbs;
   int result = 0;
   char word_from_list[80];
   char *status;
   char output[80];

   //  open word list
   verbs = fopen("verbs.txt","r");
   if(verbs == NULL) {
      sprintf(output, "fopen failed while trying to open verbs.txt\n"); stioc(output);
   }

   while(1) {
      status = fgets(word_from_list,40,verbs);
      if (status==0)break;
      // remove the newline character
      word_from_list[strlen(word_from_list)-1] = '\0';

      if (strcmp(word_to_lookup, word_from_list) == 0) {
         return 1;
         break;
      }

   }// end of while

   fclose(verbs);
   return 0;

}

//-------------------------------------------------------------


//-----------------------------------------------------

int separate_words(char* in, char out[MAX_WORDS][MAX_LETTERS]) {

   // input:
   // output: out, number_of_words

   int position = 0;
   int letter_position;
   int word_position;
   int number_of_words = 0;

   for(word_position=1; word_position < MAX_WORDS; word_position++) {
      for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++) {

         // End of sentence?
         if(in[position]=='\0' || position >= 200) {
            out[word_position][letter_position] = '\0';
            number_of_words = word_position;
            return number_of_words;
         }

         //end of word?
         if(in[position]==' ') {
            out[word_position][letter_position] = '\0';  // terminate the word
            letter_position = 0;  // probably not needed
            position++;  // skip over the space
            break;
         }

         out[word_position][letter_position] = in[position];
         position++;
      }
   }
   return 0;
}

//------------------------------------------------------------
/*
int check_gender_by_name(char* name, char* gender2) {

#define LINE_LENGTH 20
   FILE *male;
   FILE *female;
   char *status;
   char line[LINE_LENGTH];
   int n, i;

   //  open male file
   male = fopen("male_names.txt","r");
   if(male == NULL)
      return CANT_OPEN_FILE;

   for(n=0; n<1000; n++) {
      // get a line
      status = fgets(line, LINE_LENGTH, male);
      if (status==0) {

         break;
      }

      // teminate the word
      for(i=0; i<LINE_LENGTH; i++) {
         if(line[i] == 10) {
            line[i] = 0;
            break;
         }
      }

      if(strcmp(name, line) == 0) {
         strcpy(gender2, "male");
         fclose(male);
         return FOUND;
      }

   }

   fclose(male);

   //  open female file
   female = fopen("female_names.txt","r");
   if(female == NULL)

      return NOT_FOUND;

   for(n=0; n<1000; n++) {
      // get a line
      status = fgets(line, LINE_LENGTH, female);
      if (status==0) {

         break;
      }

      // teminate the word
      for(i=0; i<LINE_LENGTH; i++) {
         if(line[i] == 10) {
            line[i] = 0;
            break;
         }
      }

      if(strcmp(name, line) == 0) {
         fclose(female);
         strcpy(gender2, "female");
         return FOUND;
      }

   }

   fclose(female);
   return NOT_FOUND;
}
*/
//-------------------------------------------------------------

// Send to intenet or console
void stioc(char* output_string) {

   char temp_string[300];

   puts(output_string);
 }

//------------------------------------------------------------------------------

int isquestion(void){

   // If the first word is one of the 9 listed below , the sentence is a question

   int i;
   char w[10][6] = {"who", "what", "where", "when", "why", "how", "is", "do", "can"};

   for(i=0; i<9; i++){
      if(strcmp(words[1], w[i]) == 0) return i+1;
   }
   return 0;
}

//------------------------------------------------------------------------------

int isstatement(void)
{
    // If the second or third word is a verb, the sentence is a statement

    if(number_of_words < 3) return 0; // at least 3 words are needed
    if(isverb(words[2])) return 1;
    if(isverb(words[3])) return 1;
    return 0;

}

//----------------------------------------------------------------------

int iscommand(void)
{
    // If the first word is a verb, the sentence is a command

    if(isverb(words[1]))return 1;
    else return 0;
}

//=========================

void normalize(void) {

   int from = 0;
   int to = 0;
   char buffer[80];

   // Skip past leading whitespaces
   while(user_input[from] == ' ') from++;

   while(1) {

      // If lower case
      if(user_input[from] >= 'a' && user_input[from] <= 'z') {
         buffer[to++] = user_input[from++];
         continue;
      }

      // If upper case
      if(user_input[from] >= 'A' && user_input[from] <= 'Z') {
         buffer[to++] = user_input[from++] + 32;
         continue;
      }

      // If number
      if(user_input[from] >= '0' && user_input[from] <= '9') {
         buffer[to++] = user_input[from++];
         continue;
      }


      // If multiple whitespaces
      //   if(user_input[from] == ' ' && user_input[from-1] == ' ' && from > 0) {
      if(user_input[from] == ' ' && buffer[to - 1] == ' ' && to > 0) {
         from++;
         continue;
      }
      // If normal whitespace
      if(user_input[from] == ' ') {
         buffer[to++] = user_input[from++];
         continue;
      }

      // If null
      if(user_input[from] == 0) {
         buffer[to++] = user_input[from++];
         strcpy(user_input, buffer);
         //puts(buffer); // DEBUG
         return;
      }

      from++;
   }
}

//=========================


#include "stdlib.h"
#include "string.h"
#include <ctype.h>
#include <stdio.h>

#define MAX_WORDS 80
#define MAX_LETTERS 79


// function list
int tokenize(char[100], char*[100], char);
void search_file(void);
void extract_template(void);
void split_template(void);
int compare_template(void);
void remove_comments(void);
void extract_function_name(void);
void extract_arg1(void);
void extract_arg2(void);
int str_to_int(char*);

// global variables
char user_words[40] [40];
char template_line[100];
char template_line_segments[80][100];
char template_segments[80][100];
char template_words[80][100];
char function_name[100];
char template1[100];
char arg1[40];
char arg2[40];
int line_position = 0;
int numberoftemplatewords;
int match;

void search_file(void)
{
#define MAX 150
    int n;
    int numberofwords;
    FILE *templates;
    char output[80];
    int status;
    char* file_status;
    int result;

// open file
    templates = fopen("templates2.txt","r");
    if(templates == NULL)
    {
        sprintf(output, "fopen failed while trying to open templates2.txt\n");
        puts(output);
    }

// search line by line
    while(1)
    {
        // read a line
        file_status = fgets(template_line, 100, templates);
        if (file_status==0){printf("\nEOF"); return;}
        remove_comments();
        extract_template();
        split_template();
        match = compare_template();
        if(match == 1)printf("\nMATCH\n  ");
        if(match == 1) break;
    } // get another template if there's no match

    fclose(templates);
    for(n=0; n<numberoftemplatewords; n++) printf("TW%s ", template_words[n]);
    extract_function_name();               printf(" func: %s ", function_name);
    extract_arg1();                        printf(" arg1: %s ", arg1);
    extract_arg2();                        printf(" arg2: %s ", arg2);

 result = atoi(arg1);
 if(result > 0){strcpy(arg1, user_words[result-1]); }
 printf(" arg1b: %s ", arg1);

 result = atoi(arg2);
 if(result > 0){strcpy(arg2, user_words[result-1]); }
 printf(" arg2b: %s ", arg2);

 return;

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



}
////////////////////////////////

void extract_template(void)
{
    int letter_position;
    line_position =0;

    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        // End of template_line?

        if(template_line[line_position]==0 )
        {
            template1[letter_position] = 0;
            return;
        }
        if(line_position >= 80)
        {
            template1[letter_position] = 0;
            return;
        }
        //end of word?
        if(template_line[line_position] == ',')
        {
            template1[letter_position] = 0;  // terminate the word
            line_position++;
            return;
        }
        template1[letter_position] = template_line[line_position];
        line_position++;
    }
}

void split_template()
{

    int letter_position = 0;
    int word_position = 0;

    for(line_position = 0; line_position < sizeof(template1); line_position++)
    {

        if(template1[line_position]==0)
        {
            template_words[word_position][letter_position] = 0;
            numberoftemplatewords = word_position +1;
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
    for(n=0; n<numberoftemplatewords; n++)
    {
        if(strcmp(user_words[n], template_words[n] ) == 0 ||
                (strcmp(template_words[n], "*") == 0))        {
        }
        else return 0;
    }
    return 1;
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


