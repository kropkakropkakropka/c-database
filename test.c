#include<stdlib.h>
#include<stdio.h>
#include<string.h> 



int main(){
    int id;
    char line[1024] = {0,};
    char c;
    FILE *fpointer;
    fpointer = fopen("ksiazki.txt", "r");
    
    if(fpointer == NULL){
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }   

    fclose(fpointer);
    return 0;
}