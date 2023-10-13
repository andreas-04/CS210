/*********************************************
 * Id: neac9115
 *
 * Compile: gcc -Wall
 * Run: ./a.out input.txt
 *
 * This code breaks a text file into individual lines
 * and then tokenizes those lines
 *********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 256
// Assign meaning to tokens
void lex(char *, int , int);

// Break the string down into tokens
void tokenize(char *, int);

int main(int argc, char *argv[])
{
   if(argc<2)
   {
      printf("Please specify input file.\n");
      printf("%s /y/shared/Engineering/cs-drbc/assignments/cs210/w01_in1.txt\n", argv[0]);
      return 1;
   }
   FILE * fp;
   char * line = NULL;
   size_t len = 0;
   ssize_t read;

   fp = fopen(argv[1], "r");
   if (fp == NULL){
      printf("Error: Could not open file %s\n", argv[1]);
      exit(EXIT_FAILURE);
  }

   while ((read = getline(&line, &len, fp)) != -1) {
      tokenize(line, read);
   }
   fclose(fp); if (line) { free(line);
   }
   exit(EXIT_SUCCESS);
}

// Assign meaning to tokens
void lex(char *line, int start, int end){
   char token[MAXTOKEN];
   while(start < end && isspace(line[start])){
      start++;
   }
   if((start >= end) || (line[3] != '*') ){
      return;
   }
   if(line[3] == '*' && (end - start) >= 4){
      if(end-start > 5)
      {
         strncpy(token, &line[start], 5);
         token[5] = '\0';
      }
      else{
         strncpy(token, &line[start], end-start);
         token[end-start] = '\0';
      }
      if(token[3] == '*'){
      printf("Token: %s\n", token);
      }
     // printf("Token: one*m\n");
    }
}

// Break the string down into tokens
void tokenize(char *line, int length) {
   int start = 0;
   int end = 0;
   for(end = 0; end < length; end++) {
      if(isspace(line[end])){
        lex(line, start, end);
        start = end;
     }
  }
}
