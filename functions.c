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
   //  curently has trouble with: you, crackpot,apple,substance
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

//-------------------------------------------------------------
// Experimental. Not in use.
int tokenize(char* in_string, char* word_array, char delimiter) {

   // input: in_string
   // output: words, number_of_words

   int position = 0;
   int letter_position;
   int word_position;

   for(word_position=1; word_position < MAX_WORDS; word_position++) {
      for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++) {
         // End of in_string?
         if(in_string[position]==0 || position >= 80) {
            ////        word_array[word_position][letter_position] = 0;
            return word_position;
         }

         //end of word?
         if(in_string[position] == delimiter) {
            ////       word_array[word_position][letter_position] = 0;  // terminate the word
            letter_position = 0;  // probably not needed
            position++;  // skip over the delimiter
            break;
         }

         ////     word_array[word_position][letter_position] = in_string[position];
         position++;

      }
   }

}



// new function for chat 10
// compares user input with a sentence template
//
// example:
//  user input: what color is grass?
//  template  : what color is *, color_question, 4
//
// the old way:
//  else if(number_of_words==4 && strcmp(words[1],"what")==0 && strcmp(words[2],"color")==0&& strcmp(words[3],"is")==0){
//     handle_color_question(words[4]);


// number of words: 4
// word 1: what
// word 2: color
// word 3: is

// function: color_question()
// parameter 1: word 4

// new proceedure:
// parse template by comma
// parse template sentence by space
// compare specified words in user sentence with template sentence


/*

  void template_search (void)
  open template.txt

  outer loop
  read template

  inner loop
  tokenize(template, token_array, ',');
  tokenize(token_array[0], word_array, ' ');

  // do the words match?
  for(i=0, i<WORD_MAX, i++){
  if(words!=word_array[i]) break;
  if(w=='*') continue;
  }
*/

//--------------------------------------------------
// This partialy works, but is not currently in use
//  TEMPLATE SEARCH
//
//  inputs
//      what the user typed
//
//  returns
//      the matching template
//      the result code

//  1) opens the tempate file
//  2) gets a line
//  3) extracts the template
//  4) checks the template to see if it's a match

//int template_search(char*user, char*template2)
//int template_search(char*user, char out[MAX_WORDS][MAX_LETTERS]){
int template_search(char*user, template_info_type* template_info) {


#define TEMPLATE_LINE_LENGTH 120

   FILE *template_file_handle;
   int line_position;
   char *status;
   char line[TEMPLATE_LINE_LENGTH];
   char out[MAX_WORDS][MAX_LETTERS];
   char template2[MAX_WORDS][MAX_LETTERS];
   int n;
   int match;
   int number_of_template_words;
   char temp[80];

   //  open template file
   template_file_handle = fopen("templates.txt","r");
   if(template_file_handle == NULL) return CANT_OPEN_FILE;

   // search for template
   while(1) {
      // get a template line
      status = fgets(template_info->line, TEMPLATE_LINE_LENGTH, template_file_handle);

      if (status==0) {
         fclose(template_file_handle);
         return 0;
      }

      // skip the comments
      if (template_info->line[0] == '/' && template_info->line[1] == '/') continue;  // skip comments

      // skip any line that begins with a space or control character
      if(template_info->line[0] <= ' ')continue;

      // extract the template from the line
      line_position = copy_to_delimiter(template_info->line, template_info->template2, ',', 0);

      // separate the words
      number_of_template_words = separate_words(template_info->template2, out);  // 1d 2d

      // check if the number of words are the same
      if(number_of_template_words != number_of_words) continue;

      // check the words one by one
      match = TRUE;
      for(n=1; n<=number_of_template_words; n++) {
         if(strcmp(out[n], "*") == 0) continue;
         if(strcmp(out[n], words[n]) != 0) {
            match = FALSE;
            break;
         }
      }

      if(match == TRUE) {
         break;
      }
   }

   // extract function name
   line_position = copy_to_delimiter(template_info->line, template_info->function_name, ',' ,line_position);

   template_info->parameter1 = 0;
   template_info->parameter2 = 0;

   // extract parameter1

   if(line_position>0) {
      line_position = copy_to_delimiter(template_info->line, temp, ',' ,line_position);
      //sprintf(output, "temp:%s pos: %d", temp, line_position); stioc(output);
      snprintf(template_info->parameter1, sizeof(template_info->parameter1), temp);
   }

   //sprintf(output, "LP: %d", line_position); stioc(output);

   if(line_position>0) {
      // extract parameter2
      line_position = copy_to_delimiter(template_info->line, temp, ',' ,line_position);
      //sprintf(output, "temp:%s pos: %d", temp, line_position); stioc(output);
      snprintf(template_info->parameter2, sizeof(template_info->parameter2), temp);
   }

   fclose(template_file_handle);

   return FOUND;  // (found)

}

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
         if(in[position]==NULL || position >= 200) {
            out[word_position][letter_position] = NULL;
            number_of_words = word_position;
            return number_of_words;
         }

         //end of word?
         if(in[position]==' ') {
            out[word_position][letter_position] = NULL;  // terminate the word
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


// Send to intenet or console
void stioc(char* output_string) {

   char temp_string[80];

   if (irc == TRUE) {
      sprintf(temp_string, "PRIVMSG %s :%s\n",channel, output_string);
      send(socket_desc , temp_string , strlen(temp_string) , 0);

   } else {
      puts(output_string);
   }

}


