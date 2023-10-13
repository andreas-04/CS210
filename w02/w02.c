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
void lex(char *, int , int, int);

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
void lex(char *line, int start, int end, int tokenType){
   char token[MAXTOKEN];
   while(start < end && isspace(line[start])){
      start++;
   }
   if(start >= end){
      return;
   }
   strncpy(token, &line[start], end-start);
   token[end-start] = '\0';
   switch(tokenType){
      case 0:
      printf("Token: %s\n", token);
      break;
      case 1:
      printf("String: %s\n", token);
      break;
   }

}

// Break the string down into tokens
void tokenize(char *line, int length) {
   int start = 0;
   int end = 0;

   while (end < length) {
      if (line[end] == '"' && start == end) {
         start = end;
         end++;
         while (end < length && line[end] != '"') {
            end++;
         }
         end++;
         lex(line, start, end, 1);
         start = end;
      }
      else if (isspace(line[end]) || line[end +1] == '"') { 
         if (start != end && isspace(line[end])) {
            lex(line, start, end, 0);
         }
         else{
            lex(line, start, end+1, 0);
         }
         start = end + 1;
         end = start;
      }
      else{
         end++;
      }
   }
   if (start != end) {
      lex(line, start, end,0);
   }
}
