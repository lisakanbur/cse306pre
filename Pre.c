#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*Added define statements for each flag for later use and checks*/

#define MAX 1024

#define TRUE 1
#define FALSE 0


int argsCalled[7] = {}; //initializes to 0 which is false. if it's 1 its true
//order of indices is: -f,-r,-h,-max,-min,-mean,-records


int integerTest(char* num){ //a value of 1 will indicate true meaning it is an integer
  int decCount = 0; //if this exceeds 1, not valid float cuz two decimals

  for (int i = 0; i < strlen(num); i++){
    if (decCount > 1){
      return FALSE;
    }
    
    if (num[i] == '.'){ //technically decimal is valid for float
      decCount+=1;
      continue;
    }
    int result = isdigit(num[i]);

    if (result==0){ //a character is not a numeric character
      return FALSE;
    }
  }
  
  return TRUE; //otherwise, everything worked
}


int findHeaderFieldIdx(char headerLine[MAX][MAX], char* userInput, int len){
  //if found it, return a number, else return a -1 and abort
  
  int field = -1;
  
  for (int i = 0; i < len; i++){

    if (strncmp(headerLine[i], userInput, strlen(userInput)) == 0){ //match
      field = i;
      break;
    }
  }

  if (field == -1){ //check if its a regular integer. this funct above only works on strings
    if (integerTest(userInput) == TRUE){
      return atoi(userInput);
    }
  }

  return field;
  
}


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
  char mean_field[MAX] = "0"; //string for mean field
  float count = 0;
  char *records = ""; //string for records field value

  char headerLine[MAX][MAX] = {}; //stores header line
  int headerLength = 0; //calculates length of header
  

  int h = FALSE; // other flag to see if -h has been used

  /* THIS IS WHAT YOU WILL BE MODIFYING */

  int firstLine = TRUE;
  int firstTracker = -1;
    
  while (!feof(file)){
    fgets(singleLine, 1024, file); //gets one line

    char *temp;
    if((temp=strchr(singleLine, '\n')) != NULL){
      *temp = '\0';
    }
      
    char *original = malloc(sizeof(char)*strlen(singleLine));
    strcpy(original, singleLine);

    char innerArray[MAX][MAX] = {};
 
    char* split = "";

    int idx = 0;

    firstTracker+=1;
    
    if (firstTracker > 0){
      firstLine = FALSE;
    }
     
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
    
    if (firstLine){
      strcpy(headerLine[idx], split);
      headerLength+=1;
    }
      
            
    while (split != NULL && original != NULL){
      // puts(split);
    
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
      
      
      if (firstLine){//writes to header
	strcpy(headerLine[idx], split);
	headerLength+=1;
      }
    }

  
    
    //at this point, the whole line is filled i believe
    if (argsCalled[2] == TRUE){ //need to skip header line but store it
      argsCalled[2] = FALSE;
      h = TRUE; //-h has been specified. flag so mean and max and min dont break
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
	
	if (!h){ //this means -h is not specified & we cant take max with strings
	  strcpy(output, "error"); //exit because string value - cant take max
	  return output; //exit because string value - cant take max
	}

	char* field = argv[i+1]; //"0"

	//need to test if the field given was 0 or "Ref_Date"

	int fieldIDX = findHeaderFieldIdx(headerLine, field, headerLength); //will translate to inde
	
	if (fieldIDX == -1){ //there is an error and we must abort
	  strcpy(output, "error"); //exit because string value - cant take max
	  return output;
	}



	//!!!!!!!!!!!!!!!!! FAILING HERE!!!!!!!!!!!

	/*
	  if (integerTest(innerArray[fieldIDX]) == FALSE){//then current value is NONVALID
	 
	  strcpy(output, "error");
	  return output;
	  }
	*/
	
	
	if (atof(innerArray[fieldIDX]) > atof(max_field)){
	  strcpy(max_field, innerArray[fieldIDX]); //copies max into max_field
	}
	  
      }
      if (strcmp(argv[i], "-min") == 0){ //FIX LATER - doesn't account for "ref_date"
	//display min value in field
	//assuming number for now - NEED TO ADD EXIT IF NON NUMERICAL NUMBER

	if (!h){
	  strcpy(output, "error"); //exit because string value - cant take max
	  return output; //exit because string value - cant take max
	}

	char* field = argv[i+1]; //"0"

	//need to test if the field given was 0 or "Ref_Date"

	int fieldIDX = findHeaderFieldIdx(headerLine, field, headerLength); //will translate to inde
	
	if (fieldIDX == -1){ //there is an error and we must abort
	  strcpy(output, "error"); //exit because string value - cant take max
	  return output;
	}

	if (atof(innerArray[fieldIDX]) < atof(min_field)){
	  strcpy(min_field, innerArray[fieldIDX]);
	}

	//need to add integer test
            
      }
      if (strcmp(argv[i], "-mean") == 0){

	if (!h){
	  strcpy(output, "error"); //exit because string value - cant take max
	  return output;
	}
	
	char *field = argv[i+1];
	int fieldIDX = findHeaderFieldIdx(headerLine, field, headerLength);

	if (fieldIDX == -1){ //there is an error and we must abort
	  strcpy(output, "error"); //exit because string value - cant take max
	  return output;
	}
	
	float prevNum = atof(mean_field);
	float newNum = atof(innerArray[fieldIDX]);
	float newSum = prevNum + newNum;

	char buffer[MAX];
	sprintf(buffer, "%f", newSum);
	strcpy(mean_field, buffer);
	
	count = count + 1;
           
      }
      if (strcmp(argv[i], "-records") == 0){
           
      }
    } //end for loop
	
  } //end while loop i think

  
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
      float finalSum = atof(mean_field);
      float finalMean = finalSum/count;

      char temp[MAX];
      sprintf(temp, "%f", finalMean);

      strcat(output, temp);
 
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

  if (strcmp(out, "error") == 0){ //error occurred
    return 1;
  }
  puts(out);

  fclose(file);
    
  return 0;
}
