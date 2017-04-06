/*
 Allan Liu
 V00806981
 Assignment1
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IN_LINES 300
#define MAX_IN_CHARS 132

/* global variables */
char output[MAX_IN_LINES * MAX_IN_CHARS];
char processed[MAX_IN_CHARS];  /* when the string is formated */
int line_size = 0;             /* keeps track of the line size that has been formated */

/* flagged within the input file with .FT, .LM, .LW, .LS */
int FT = 0;
int LM = 0;
int LW = 0;
int LS = 0;

void read_in (char* line) {
  /* split the list into tokens */
  char* word = strtok (line, " \n"); /* the current token */
  
  /* checks if a new line is needed for each word, then set margins, and cat it. */
  while (word) {
    if (line_size + strlen (word) >= LW) { /* if .FT is 1 then .LM is also */
      strncat (processed, "\n", 1);
      line_size = 0;
      if (LM) { /* check if margin is needed */
        while (line_size < LM) { /* make as many margin spaces specified in the formating command */
          strncat (processed, " ", 1);
          line_size++;
        }
      }
    }
    /* add a space */
    else if (line_size >= LM+1) {
      line_size++;
      strncat (processed, " ", 1);
    }
    line_size += strlen (word);
    strncat (processed, word, MAX_IN_CHARS);
    word = strtok (NULL, " \n");
  }

  return;
}

int which_format (char* line) {
  /* makes a copy of the string */
  char copy[MAX_IN_CHARS];
  strncpy (copy, line, MAX_IN_CHARS);
  /* tokenize the string. */
  strtok (copy, " \n");
  /* detect a formating command */
  if ( !strncmp(copy, ".FT", MAX_IN_CHARS) ) {
    char* opt = strtok (NULL, " \n"); /* (from Lab4 Slides) gets more tokens from that same string */
    if ( !strncmp(opt, "on", 3) ) {
      FT = 1;
    }
    else {
      FT = 0;
    }
    return 1;
  }
  if ( !strncmp(copy, ".LM", MAX_IN_CHARS) ) {
    int opt = atoi( strtok (NULL, " \n") );
    LM = opt;
    return 1;
  }
  if ( !strncmp(copy, ".LW", MAX_IN_CHARS) ) {
    int opt = atoi( strtok (NULL, " \n") );
    LW = opt;
    FT = 1;
    return 1;
  }
if ( !strncmp(copy, ".LS", MAX_IN_CHARS) ) {
    int opt = atoi( strtok (NULL, "\n") );
	LS = opt;
	return 1;
  }

  return 0;
}

int main (int argc, char** args) {
  /* variables */
  FILE* file;
  char line[MAX_IN_CHARS]; 
  
  /* return an error if file is invalid */
  file = fopen (args[1], "r");
  if (file == NULL) {
    return -1;
  }
  
  /* read each line and stop at the end */
  while ( fgets (line, MAX_IN_CHARS, file) ) {
    /* check for the formating commands */
    if ( which_format (line) ) {
      continue;
    }
    
    if (LM) {
      /* make as many margin spaces as needed */
      while (line_size < LM) {
        strncat (processed, " ", 1);
        line_size++; /* adjust line size. */
      }
    }

    if (LS) {
      /* make a linespacing if .LS set to 1 */
     strncat (processed "\n", " ", 1);
    }


    /* format or don't based on the formating commands */
    if (FT && !strncmp (line, "\n", 1) ) {
      strncat (output, "\n\n", MAX_IN_CHARS);
      line_size = 0;
    }
    if (FT) {
      read_in (line);
      strncat (output, processed, MAX_IN_CHARS);
      strncpy (processed, "", MAX_IN_CHARS);
    }
    else {
      strncat (output, line, MAX_IN_CHARS);
    }
  }
  
  if (FT) {
    strncat (output, "\n", MAX_IN_CHARS);
  }
  
  printf("%s", output);
  
  return 0;
}
