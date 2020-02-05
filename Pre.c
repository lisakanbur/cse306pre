#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Added define statements for each flag for later use and checks*/
#define f false
#define h false
#define r false
#define maxField false
#define minField false
#define meanField false
#define recordsFieldValue false

#define TRUE 1
#define FALSE 0


int argsCalled[7] = {}; //initializes to 0 which is false. if it's 1 its true
//order of indices is: -f,-r,-h,-max,-min,-mean,-records

int main(int argc, char *argv[]){

    if(argc == 0 || argc == 1){ // there are wrong number of arguments
        return 1;
    }

    FILE *file =  fopen((argv[argc-1]), "r");

    if (file == NULL){
      return 1;
    }

    char singleLine[1024];

    int start = 1;
    
    //tests the arguments provided ---> -h hello.csv would mean argc = 3
    while(start < argc-1){ //argc-1 because the last specified thing is the file
        if (strcmp(argv[start], "-f") == 0){ //0 means it matched
            argsCalled[0] = 1; //1 means true
        }
        if (strcmp(argv[start], "-r") == 0){
            argsCalled[1] = 1;
        }
        if (strcmp(argv[start], "-h") == 0){
            argsCalled[2] = 1;
        }
        if (strcmp(argv[start], "-max") == 0){
            argsCalled[3] = 1;
        }
        if (strcmp(argv[start], "-min") == 0){
            argsCalled[4] = 1;
        }
        if (strcmp(argv[start], "-mean") == 0){
            argsCalled[5] = 1;
        }
        if (strcmp(argv[start], "-records") == 0){
            argsCalled[6] = 1;
        }
        start = start + 1;
    }

    //parses file

    char* split = "";
    int flag = FALSE;
  
    while (!feof(file)){
      fgets(singleLine, 1024, file); //gets one line
      split = strtok(singleLine, ",");
      
      while (split!=NULL){ 
	if (split[0] == '"'){
	    puts("executed");
	    flag = TRUE; //we found
	    split = strtok(NULL, '"');
	    printf("%s\n", split);
	    flag = FALSE;

	    continue;
	  }
	  
	  if (flag == FALSE){
	     printf("%s\n", split);
             split = strtok(NULL, ",");
	   }
        }
      // puts(singleLine);
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
