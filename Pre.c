#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if(argc == 0 || argc == 1){
        return -1;
    }
    
    FILE *file;
    file = fopen((argv[argc-1]), "r"); 
    
    return 0;
}
