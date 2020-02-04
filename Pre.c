#include <stdio.h>
#include <stdlib.h>


/*Added define statements for each flag for later use and checks*/
#define frh = false;
#define maxField = false;
#define minField = false;
#define meanField = false;
#define recordsFieldValue = false;

int main(int argc, char *argv[]){

    if(argc == 0 || argc == 1){ // there are wrong number of arguments
        return 1;
    }

    FILE *file =  fopen((argv[argc-1]), "r");


    if (file == NULL){
      return 1;
    }

    char singleLine[1024];

    while (!feof(file)){
      fgets(singleLine, 1024, file); //gets one line
      puts(singleLine);
    }

    

    fclose(file);
    return 0;
}

/*
 * Display the number of records in the first field of file
 */

//temporarily commented out because errors

/*
char[] field_count(FILE *file){
  //use fgets() or gets() to read line from csv
  //attempting fgets()
  
  char str_buf[1024];
  fgets(str_buf, 1024, *file);
  //if you print str_buf then it should be the first record in the file
  return char[];
  
}

*/
