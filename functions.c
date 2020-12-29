#include "functions.h"
#include "main.h"

// Global in this file
int line_position;


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

   for(word_position=1; word_position < MAX_WORDS; word_position++) {
      for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++) {

         // End of user input?
         if(user_input[position]==0 || position >= 80) {
            user_words[word_position][letter_position] = 0;
            number_of_words = word_position;
            return;
         }

         //end of word?
         if(user_input[position]==' ') {
            user_words[word_position][letter_position] = 0;  // terminate the word
            letter_position = 0;  // probably not needed
            position++;  // skip over the space
            break;
         }

         //
         user_words[word_position][letter_position] = user_input[position];
         position++;
      }
   }

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
         return;
      }
      from++;
   }
}

//=========================

int check_gender_by_name(char* name)
{

    #define LINE_LENGTH 20
    FILE *male;
    FILE *female;
    char *status;
    char line[LINE_LENGTH];
    int n, i;

    //  open male file
    male = fopen("male_names.txt","r");
    if(male == NULL) return CANT_OPEN_FILE;

    for(n=0; n<1000; n++)
    {
        // get a line
        status = fgets(line, LINE_LENGTH, male);
        if (status==0)
        {
            fclose(male);
            break;
        }

        // teminate the word
        for(i=0; i<LINE_LENGTH; i++)
        {
            if(line[i] == 10)
            {
                line[i] = 0;
                break;
            }
        }

        if(strcmp(name, line) == 0)
        {
            fclose(male);
            return 1;
        }

    }

    //  open female file
    female = fopen("female_names.txt","r");
    if(female == NULL) return CANT_OPEN_FILE;

    for(n=0; n<1000; n++)
    {
        // get a line
        status = fgets(line, LINE_LENGTH, female);
        if (status==0)
        {
            fclose(female);
            break;
        }

        // teminate the word
        for(i=0; i<LINE_LENGTH; i++)
        {
            if(line[i] == 10)
            {
                line[i] = 0;
                break;
            }
        }

        if(strcmp(name, line) == 0)
        {
            fclose(female);
            return 2;
        }



    }
return 3;
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
   if(inarow>=3)sprintf(output, "  3 vowels in a row  \n"); puts(output);
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
   if(inarow>=4)sprintf(output, "  that's jiberish\n"); puts(output);

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
      sprintf(output, "fopen failed while trying to open word100k.txt\n"); puts(output);
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
      sprintf(output, "fopen failed while trying to open verbs.txt\n"); puts(output);
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

//------------------------------------------------------------------------------

int isquestion(void){

   // If the first word is one of the 9 listed below , the sentence is a question

   int i;
   char w[10][6] = {"who", "what", "where", "when", "why", "how", "is", "do", "can"};

   for(i=0; i<9; i++){
      if(strcmp(user_words[1], w[i]) == 0) return i+1;
   }
   return 0;
}

//------------------------------------------------------------------------------

int isstatement(void)
{
    // If the second or third word is a verb, the sentence is a statement

    if(number_of_words < 3) return 0; // at least 3 words are needed
    if(isverb(user_words[2])) return 1;
    if(isverb(user_words[3])) return 1;
    return 0;

}

//----------------------------------------------------------------------

int iscommand(void)
{
    // If the first word is a verb, the sentence is a command

    if(isverb(user_words[1]))return 1;
    else return 0;
}


//-------------------------------------------------------------
