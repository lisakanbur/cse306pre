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
#define MAX 1024

#define TRUE 1
#define FALSE 0


int argsCalled[7] = {}; //initializes to 0 which is false. if it's 1 its true
//order of indices is: -f,-r,-h,-max,-min,-mean,-records

char* lines[MAX][MAX] = {};

int lineIdx = 0;

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
            argsCalled[0] = TRUE; //1 means true
        }
        if (strcmp(argv[start], "-r") == 0){
            argsCalled[1] = TRUE;
        }
        if (strcmp(argv[start], "-h") == 0){
            argsCalled[2] = TRUE;
        }
        if (strcmp(argv[start], "-max") == 0){
            argsCalled[3] = TRUE;
        }
        if (strcmp(argv[start], "-min") == 0){
            argsCalled[4] = TRUE;
        }
        if (strcmp(argv[start], "-mean") == 0){
            argsCalled[5] = TRUE;
        }
        if (strcmp(argv[start], "-records") == 0){
            argsCalled[6] = TRUE;
        }
        start = start + 1;
    }

    //parses file


    while (!feof(file)){
      fgets(singleLine, 1024, file); //gets one line

      //no room past 1024
      
      char *original = malloc(sizeof(char)*strlen(singleLine));
      strcpy(original, singleLine);

      char innerArray[MAX][MAX] = {};
 
      char* split = "";

      //puts(singleLine);

      int idx = 0;
     
      //starts with something that does not have a comma
      if (singleLine[0] == '"'){
	split = strtok(singleLine, "\""); //do it twice?

        original = original + strlen(split)+2;
      }
      
      else if (singleLine[0] == ','){ //skip comma
	split = "empty",
	original = original + 1;
      }
      
      else{
	split = strtok(singleLine, ",");
	
         original = original + strlen(split)+1; 
      }

      strcpy(innerArray[idx], split); //adds first value of line to array
      
      

   //Header,"Header, header",header,header,header,header,header,header,header\n

      //test,"test,test","test,test"
            
      while (split != NULL && original != NULL){
	puts(split);

	idx += 1;
   
	if (*original == '"'){

	  split = strtok(original, "\"");

	  if (split == NULL){
	    break;
	  }
		
	  original = original + strlen(split) + 3;

	}
	else if (*original == ','){ //skip the comma
	  split = ""; //empty case
	  original = original + 1;
	}
	
	else{
	  split = strtok(original, ",");
	  
	  if (split == NULL){
	    break;
	   }
	  
	  original = original + strlen(split) + 1;
        }
	
	strcpy(innerArray[idx], split); //adds value of line to inner array

      }
      //at end, add the inner array to the original

      //  memcpy(lines[lineIdx], innerArray, sizeof(innerArray));
      // lines[lineIdx] = innerArray;
      // lineIdx +=1;
    }

    fclose(file);
    
    return 0;
}

