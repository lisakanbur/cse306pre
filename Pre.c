#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Added define statements for each flag for later use and checks*/

#define MAX 1024

#define TRUE 1
#define FALSE 0


int argsCalled[7] = {}; //initializes to 0 which is false. if it's 1 its true
//order of indices is: -f,-r,-h,-max,-min,-mean,-records



char* lineParser(FILE *file, int argc, char* argv[]){
  //parses file

  char *output = malloc(sizeof(char)*1024); //this will be the string that at the end concatenates
  //all of the args etered
    
  char singleLine[MAX];


    
  /* THIS IS WHAT YOU WILL BE MODIFYING */

  char *f = ""; //string for -f value
  char *r = ""; //string for -r value
  char max_field[MAX] = "-1"; //int for max field
  char min_field[MAX] = "2147483647"; //string for min field
  char *mean_field = ""; //string for mean field
  char *records = ""; //string for records field value
  char sum[MAX] = "0"; //Start the sum at zero and go up from there
  char count[MAX]= "0"; // counter used to for calcuating mean
  char temporaryMeanBuffer[MAX];
  char mean[MAX];

  /* THIS IS WHAT YOU WILL BE MODIFYING */


    
  while (!feof(file)){
    fgets(singleLine, 1024, file); //gets one line
      
    char *original = malloc(sizeof(char)*strlen(singleLine));
    strcpy(original, singleLine);

    char innerArray[MAX][MAX] = {};
 
    char* split = "";

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
      
            
    while (split != NULL && original != NULL){
      //puts(split);

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

    //at this point, the whole line is filled i believe
    if (argsCalled[2] == TRUE){ //need to skip header line
      argsCalled[2] = FALSE;
      continue;
    }

    //now we loop through argv to get the order of the commands

    
    for (int i = 1; i < argc; i++){
      if (strcmp(argv[i], "-h") == 0){
	continue;
      }
      if (strcmp(argv[i], "-f") == 0){ //0 means it matched
            
      }
      if (strcmp(argv[i], "-r") == 0){
            
      }
      if (strcmp(argv[i], "-max") == 0){ //FIX LATER - doesn't account for "ref_date"
	//display the max value in the field
	//assuming number for now - NEED TO ADD EXIT IF NON NUMERICAL NUMBER

	char* field = argv[i+1]; //"0"
	int fieldIDX = atoi(field); //0

	
      if (atof(innerArray[fieldIDX]) > atof(max_field)){
	  strcpy(max_field, innerArray[fieldIDX]); //copies max into max_field
      }
	  
      }
      if (strcmp(argv[i], "-min") == 0){ //FIX LATER - doesn't account for "ref_date"
	//display min value in field
	//assuming number for now - NEED TO ADD EXIT IF NON NUMERICAL NUMBER

	char* field = argv[i+1];
	int fieldIDX = atoi(field);

	if (atof(innerArray[fieldIDX]) < atof(min_field)){
	  strcpy(min_field, innerArray[fieldIDX]);
	}
            
      }
      if (strcmp(argv[i], "-mean") == 0){
          char temporaryFinalBuffer[MAX];
          char temporaryAddedBuffer[MAX];
          char temporaryCountedBuffer[MAX];
          char* input = argv[i + 1];

          int inputIdx = atoi(input);
          double added = atof(sum) + atof(innerArray[inputIdx]);
          int counted = atoi(count) + 1;

          sprintf(temporaryAddedBuffer, "%f", added);
          strcpy(sum, temporaryAddedBuffer);
          sprintf(temporaryCountedBuffer, "%d", counted);
          strcpy(count, temporaryCountedBuffer);
          
      }
      if (strcmp(argv[i], "-records") == 0){
           
      }
    } //end for loop
	
  } //end while loop i think

   if(atoi(count) > 0){
       double placeholderMean = atof(sum) / atof(count);
       sprintf(temporaryMeanBuffer, "%f", placeholderMean);
       strcpy(mean, temporaryMeanBuffer);
   }

  
  //now we need to loop thru argv again and merge to output

    
  for (int i = 1; i < argc; i++){
    if (strcmp(argv[i], "-h") == 0){
      continue;
    }
    if (strcmp(argv[i], "-f") == 0){ //0 means it matched
      //add the f value to output         
    }
    if (strcmp(argv[i], "-r") == 0){
      //add the r value to output          
    }
    if (strcmp(argv[i], "-max") == 0){
      //add the max value to output
       strcat(output, max_field);
    }
    if (strcmp(argv[i], "-min") == 0){
      //add the min value to output
      strcat(output, min_field);
    }
    if (strcmp(argv[i], "-mean") == 0){
      //add the mean value to output
    }
    if (strcmp(argv[i], "-records") == 0){
      //add the records value to output
    }
  } //end for loop

    

    //strcpy(output, max_field);
	
    return output;
}




int main(int argc, char *argv[]){

  if(argc == 0 || argc == 1){ // there are wrong number of arguments
    return 1;
  }

  FILE *file =  fopen((argv[argc-1]), "r");

  if (file == NULL){
    return 1;
  }


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

  char* out = lineParser(file, argc, argv);
  puts(out);

  fclose(file);
    
  return 0;
}
