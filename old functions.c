/*
void get_string(void){

   int position;

   for(position = 0; position <= 78; position++){
      user_input[position] = getchar();
      if(user_input[position]==10)break; // CR
      if(user_input[position]==13)break; // LF
   }
   user_input[position] = 0;

}

//--------------------------------------------------------------

void parse(void){

// input: user_input
// output: words, number_of_words

  int position = 0;
  int letter_position;
  int word_position;
  //while(1);
  for(word_position=1; word_position < MAX_WORDS; word_position++) {
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){

      // End of user input?
      if(user_input[position]==0 || position >= 80){
        user_words[word_position][letter_position] = 0;
        number_of_words = word_position;
        return;
      }

      //end of word?
      if(user_input[position]==' '){
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

//------------------------------------------------------------------

int isvowel(char c1){

  char vowels[6]="aeiouy";
  int i;

  for(i=0;i<6;i++){
    if(c1 == vowels[i])return 0;
  }
  return 1;

}

//---------------------------------------

int isconsonant(char c1){

  char consonants[20]="bcdfghjklmnpqrstvwxz";
  int i;

  for(i=0;i<20;i++){
    if(c1 == consonants[i]) return 0;
  }
  return 1;

}

//-----------------------------------------------------------------------

int is_nonsense_word(char* s1){
//
//  curently has trouble with: you, crackpot,apple,substance
//
//

// 3 vowels in a row?
int i,inarow;

inarow=0;
for(i=0;i<80-3;i++){
  if(user_input[i]==0) break;
  if(isvowel(user_input[i])==0) inarow++;
  else inarow=0;
  if(inarow>=4) break;
}
if(inarow>=3)printf("  3viar  \n");  // (3 vowels in arow)

// replace all occurances of CH GH SC SP TH CK PP ST with vowels
for(i=0;i<80-3;i++){
  if(user_input[i]==0) break;
  if((user_input[i]== 'c' && user_input[i+1]== 'h') ||
     (user_input[i]== 'g' && user_input[i+1]== 'h') ||
     (user_input[i]== 's' && user_input[i+1]== 'c') ||
     (user_input[i]== 's' && user_input[i+1]== 'p') ||
     (user_input[i]== 's' && user_input[i+1]== 't') ||
     (user_input[i]== 'p' && user_input[i+1]== 'p') ||
     (user_input[i]== 'c' && user_input[i+1]== 'k') ){
    user_input[i]='a'; user_input[i+1]='a';
  }
}

// 3 consonants in a row?
inarow=0;
for(i=0;i<80-3;i++){
  if(user_input[i]==0) break;
  if(isconsonant(user_input[i])==0) inarow++;
  else inarow=0;
  if(inarow>=4) break;
}
if(inarow>=4)printf("  pile of garbage!  \n");

}

//--------------------------------------------------------

int isword(char*word_to_lookup){
   FILE *general;

	int result = 1;
    char word_from_list[80];
    char *status;

	//  open word list
	general = fopen("word100k.txt","r");
	if(general == NULL) {printf("fopen failed while trying to open word100k.txt\n");}

	while(1){

		status = fgets(word_from_list,40,general);
		if (status==0)break;
		// remove the newline character
		word_from_list[strlen(word_from_list)-1] = '\0';

		if (strcmp(word_to_lookup, word_from_list) == 0){
			result = 0;
			break;
		}

	}// end of while

	fclose(general);
	return result;

}
*/


/*
int tokenize(char* in_string, char* word_array, char delimiter){

// input: in_string
// output: words, number_of_words

  int position = 0;
  int letter_position;
  int word_position;

  for(word_position=1; word_position < MAX_WORDS; word_position++) {
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){
      // End of in_string?
      if(in_string[position]==0 || position >= 80){
////        word_array[word_position][letter_position] = 0;
        return word_position;
      }

      //end of word?
      if(in_string[position] == delimiter){
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

/*

// new function for chat 10
// compares user input with a sentence template
//
// example:
//  user input: what color is grass?
//  template  : what color is *, color_question, 4
//
// the old way:
  //  else if(number_of_words==4 && strcmp(user_words[1],"what")==0 && strcmp(user_words[2],"color")==0&& strcmp(user_words[3],"is")==0){
  //     handle_color_question(user_words[4]);


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
/*
//--------------------------------------------------
//
//  TEMPLATE SEARCH
//
//  inputs
//
//
//  returns
//
//
//  1) opens the tempate file
//  2) gets a line
//  3) extracts the template
//  4) checks the template to see if it's a match

int template_search(char*user, char*template2)
{

#define TEMPLATE_LINE_LENGTH 120
    FILE *templatex;
    int linepos;
    char *status;
    char line[TEMPLATE_LINE_LENGTH];
    char out[MAX_WORDS][MAX_LETTERS];
    int n;
    int match;
    int number_of_words2;



    //  open template file
    templatex = fopen("templates.txt","r");
    if(templatex == NULL) return CANT_OPEN_FILE;

    // search for template
    while(1)
    {
        // get a template line
        status = fgets(line, TEMPLATE_LINE_LENGTH, templatex);
        if (status==0)
        {
            fclose(templatex);
            return 0;
        }

        if (line[0] == '/' && line[1] == '/') continue;  // skip comments
        if(line[0] <= ' ')continue; // skip any line that begins with a space or control character

        // extract the template
        linepos = copy_to_delimiter(line, template2, ',');
        number_of_words2 = separate_words(template2, out);

        if(number_of_words2 != number_of_words) continue;

#if 1
        match = TRUE;
        for(n=1; n<=number_of_words2; n++)
        {
            if(strcmp(out[n], "*") == 0) continue;
            if(strcmp(out[n], user_words[n]) != 0)
            {
                match = FALSE;
                // printf("NO MATCH: %s, %s\r\n\n", out[n], user_words[n]);
                break;
            }
        }

#endif

        if(match == TRUE) printf("template match: %s\r\n\n", template2);

    }
    fclose(templatex);

    return template2;  // (found)

}
*/
