/*
lookup value (key, value)
add pair (key, value)
change value (key, value)
remove pair (key)
*/

#include "db.h"

//--------------------------------------------------
//
//  GET VALUE FROM GENERAL DATABASE
//
//  inputs
//    key, value
//
//  returns
//  FOUND or NOT_FOUND
//
//  1) opens the database
//  2) gets a line
//  3) extracts the key
//  4) checks the key to see if it's the one we're looking for
//  5) goes to step 2 if not
//  6) returns value
//
int db_get_value(char*target_key, char*db_value){

    FILE *general;
    int linepos;
    char *status;
    char line[80];
    char db_key[60];

   //  open general knowlege database
    general = fopen("general.txt","r");
    if(general == NULL) return CANT_OPEN_FILE;

    // search for key
    while(1){
	   // get a line
	   status = fgets(line,80,general);
       if (status==0){
    	  fclose(general);
          return NOT_FOUND;
       }

     // get the key
       linepos =  copy_to_delimiter(line, db_key, ':', 0);
       // is it the key we're looking for?
       // if not, get another line

       if(strcmp(target_key, db_key) != 0) continue;
       break;
	} // end of key search

    // get value
    db_copy_word(line, linepos, db_value);

    fclose(general);

    return FOUND;  // (found)

}


//-------------------------------------------------------------------
//
//   example:  db_add_pair("grass > color","green");
//
//
int db_add_pair(char*key, char*value){

    FILE *general;

   //open
	  general = fopen("general.txt","a");
	  if(general == NULL) {printf("fopen failed while trying to open general.txt");}

   //add key and value
	  fprintf(general, "%s:%s\n", key, value);

   // close
	  fclose(general);

	  return 1;

}


//-------------------------------------------------------------------
//
//   example:  db_add_pair2("grass", "color", "green");
//
//
int db_add_pair2(char*key1, char*key2, char*value){

    FILE *general;

   //open
	  general = fopen("general.txt","a");
	  if(general == NULL) {printf("fopen failed while trying to open general.txt");}

   //add key and value
	  fprintf(general, "%s > %s:%s\n", key1, key2, value);

   // close
	  fclose(general);

	  return 1;

}


//--------------------------------
//    look up a first name and return the id number
//    returns 0 if error
//
//
int db_get_id(char* firstname)
{

    int id;
    char id_string[20], name[20];
    char key[80];
    int result;

    for(id=1; id<1000; id++)
    {
        snprintf (id_string, sizeof(id_string), "%d",id); // convert id number from integer to string (integer, string, base)
        sprintf(key, "#%s > firstname", id_string);
        result = db_get_value(key, name);

        // look up the first name
        if(result==FOUND)
        {
            result = strcmp(name, firstname);
            if(result==0)
            {
                // That's the entity we're looking for
                return id;
            }
            // That's not the entity we're looking for, so try again
            else {
                continue;
            }
        }
    }

    return 0; // database size limit reached (DGI)

}


//--------------------------------------------------------
//
// looks for the specified key and changes its value
//
//

int db_change_value(char*key, char*value){
    FILE *general;
    FILE *temp;

    char *status;
    char line[80];
    char db_key[60];

    //open files
   	general = fopen("general.txt","r");
	   if(general == NULL) {
       printf("DB: can't open general.txt");
       return 2;
    }
	temp = fopen("temp.txt","w");
   	if(temp == NULL) {
       printf("DB: can't open temp.txt");
       fclose(general);
       return 2;
    }

    // search for a key, copy each line
    while(1){
	      // get a line
	      status = fgets(line,80,general);
       if (status==0){
          fclose(general);
          fclose(temp);
          return 1;  //(key not found)
	      }

       db_copy_word(line,1, db_key);
       // is it the key we're looking for?
       // if not, get another line
       if(strcmp(key, db_key)==0) {
         fprintf(temp, "%s", line); // copy line to temp file
         break;
       }
    }  // end of subject search

    //add key and value
	   fprintf(temp, "%s: %s\n", key, value);


    // copy remainder of file
    //   fprintf(temp, "%s", line); // copy line to temp file
    while(1){
        // get another line
		     status = fgets(line,80,general);
		     if (status==0) break;
 	        fprintf(temp, "%s", line); // copy line to temp file
       }

    // close
	   fclose(general);
	   fclose(temp);

   	if(remove("general.txt") != 0) {printf("oops, file error ""%s"" \n", strerror(1));}
	   if(rename("temp.txt","general.txt") != 0) {printf("file error ""%s"" \n", strerror(1));}

	   return 0;  // (success)

}





//--------------------------------------------------------

int db_next_available_id(void){

   int i;
   char value[20];
   int result;
   char key[20], id_string[20];

   for(i=1; i<1000; i++){
      // look for id
      snprintf(key, sizeof(key), "#%d > class", i); // ex: "#23 > class"
      if(db_get_value(key,value) != FOUND){
          return i;
      }
   }
   printf("error in function DNAI");
   return 0;
}

//----------------------------------------------------------
//
//
//
//
//
int db_copy_word(char* line, int position, char* value)
{

    int i;

    for(i=0; i<MAX_LETTERS-2; i++)
    {
        //skip over leading spaces and tabs
        if(line[position]==' ') position++;
        if(line[position]==' ') position++;
        if(line[position]==' ') position++;
        if(line[position]=='\t') position++;
        if(line[position]=='\t') position++;
        if(line[position]=='\t') position++;

        if ((isalpha(line[position])==0) && (isdigit(line[position])==0))
        {
            value[i]=0;

            return position;
        }
        else
        {
            value[i]=line[position];
            position++;
        }
    }

    return position;

}

//------------------------------
//
// COPIES A STRING UP TO THE DELIMITER
//
// parameters: from, to
//
// returns: the position after the delimiter
//
// usualy the copy then gets compared to a key that's being searched for
//
int copy_to_delimiter(char* from, char* to, char delimiter, int start){

   int i;

   for(i=0; i<80; i++){
      if (from[i+start] == delimiter){
         to[i] = NULL; //
         return i + 1 + start;
      }
      else if (from[i+start] == 10 || from[i+start] == 13){
         to[i] = NULL; //
         return 0;
      }
      else{
         to[i] = from[i+start];
      }
   }
   i++;
   to[i+start] = NULL;
return i;
}


//-----------------------------------------------------------------------
//
// ex: is cat a creature?
// db_root_check("cat", "creature");
//
int db_root_check(char* startingwith, char* lookingfor){
                      //  animal              creature
   int result;
   int n;
   char subject[60];
   char key[60];
   char value[20];

   strcpy(subject, startingwith);
   for(n=0; n<5; n++){
       sprintf(key, "%s > class", subject);
       result = db_get_value(key, value); // lookup
       if(result == NOT_FOUND) return NOT_FOUND; // if not in database at all, exit
       if(strcmp(value,lookingfor)==0)return FOUND;  // is it what we're looking for?
       if(strcmp(value,"root")==0)return NOT_FOUND; // has it reached to root?
       strcpy(subject,value); // if no luck so far, the value becomes the subject
   }
  return NOT_FOUND;  // not found
}

//-----------------------------------------------------------------------
//
// ex:
// db_check("cat");
//
int db_check(char* subject){

   char key[60];
   char value[20];

   sprintf(key, "%s > class", subject);
   return db_get_value(key, value); // lookup

}




