/*
Allan Liu
V00806981
Assignment 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IN_LINES 500
#define MAX_IN_CHARS 132

/* Global Variables */
char output[MAX_IN_LINES * MAX_IN_CHARS];
char *delimiters = " \n";
int line_size = 0;
char processed_string[MAX_IN_CHARS];

/* Flags, determines which format to use after reading in file */
int FT = 0;
int LM = 0;
int LW = 0;
int LS = 0;

/* Defining Functions */
int which_format(char *buffer);
void line_width(char *buffer);
void make_margin();
void extra_line(char *buffer);

void make_margin(void)
{
	while(line_size < LM)
	{
		strncat(processed_string, " ", 1);
		line_size++;
	}
}

/* Function to pass tests 8 and 9. Did not have time to finish */
void extra_line(char *buffer)
{
	/*
	int extra;
	char *last;
	char *wrd = strtok(buffer, delimiters);
	while(wrd)
	{
		
		last = wrd[strlen(wrd)-1];
		extra = strncmp(last, "\n", 1);
		if(extra != 0)
		{
			continue;
		}
		exit(1);
	}
	*/
}

int which_format(char *buffer)
{
	char word[MAX_IN_CHARS];
	strncpy(word, buffer, MAX_IN_CHARS);
	strtok(word, delimiters);
	
	/* Compare the word with .FT. If it does have .FT, check if it is on, else it is off*/
	if (!strncmp(word, ".FT", MAX_IN_CHARS))
	{
		/* if matches .FT, then the next word must be the options to be formatted with */
		char *options = strtok(NULL, delimiters);
		if(!strncmp(options, "on", 3))
		{
			FT = 1;
		}
		else
		{
			FT = 0;
		}
		return 1;
	}
	if (!strncmp(word, ".LM", MAX_IN_CHARS)) 
	{
		/* Converts the tokenized string to an integer and set LM to the specified integer
 		https://stackoverflow.com/questions/27937148/strtok-reading-the-spaces-at-the-end-of-string-and-not-returning-null */
		int opt = atoi(strtok (NULL, delimiters));
		LM = opt;
		return 1;
   	}
	
	if (!strncmp(word, ".LW", MAX_IN_CHARS)) 
	{
		int opt = atoi(strtok (NULL, delimiters));
		LW = opt;
		FT = 1;
		return 1;
   	}
	
	if (!strncmp(word, ".LS", MAX_IN_CHARS)) 
	{
		int opt = atoi(strtok (NULL, delimiters));
		LS = opt;
		//printf("%d", LS);
		return 1;
   	}
	
	return 0;
}

void line_width(char *buffer)
{
	char *word = strtok(buffer, delimiters);
	while(word)
	{
		/* If the word I am trying to catenate with the line exceeds the LW, start a new line.*/
		if (line_size + strlen(word) >= LW)
		{
			strncat(processed_string, "\n", 1);
			line_size = 0;
			
			if (LS)
			{
				int i;
				for (i = 0; i < LS; i++)
				{
					strncat(processed_string, "\n", 1);
					line_size = 0;
				}
			}
			 
			if (LM)
			{
				make_margin();
			}
		}

		/* Catenate a space to each word. line_size should always be larger than LM unless it is the first word of the line. 
 		* When it is the beginning of a new line, the line_size is set to 0, indicating start of a line.*/
		else if (line_size >= LM+1)
		{
			line_size++;
			strncat(processed_string, " ", 1);
		}
		
		line_size += strlen(word);
		strncat(processed_string, word, MAX_IN_CHARS);
		word = strtok(NULL, delimiters);

	}
	
	return;
}

int main(int argc, char *argv[])
{
	char buffer[MAX_IN_CHARS];
	
	/* From slides 78 */
	FILE *file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("Please input an existing file");
		return -1;
	}
	
	while (fgets(buffer, MAX_IN_CHARS, file))
	{
		if (which_format(buffer))
		{
			//printf("%d\n", LW);
			//printf("%d\n", FT);
			continue;
		}
		
		if (LM)
		{
			make_margin();
		}
		/* Start of a new line of a new paragraph*/
		if (FT && !strncmp(buffer, "\n", 1))
		{
			strncat(output, "\n\n", MAX_IN_CHARS);
			line_size = 0;
		}	
		
		if (LS && !strncmp(buffer, "\n", 1))
		{
			strncat(output, "\n\n", MAX_IN_CHARS);
			line_size = 0;
		}	
		
		if (FT)
		{
			/* Append it to output, but copy the processed string for new line*/
			line_width(buffer);
			strncat(output, processed_string, MAX_IN_CHARS);
			strncpy(processed_string, "", MAX_IN_CHARS);
		}
		
		else
		{
			strncat(output, buffer, MAX_IN_CHARS);
		}
	}
	
	/* Creates a new line or won't pass test on lab computers */
	if (FT)
	{
		//extra_line(buffer);
		int extra;
		extra = strncmp(buffer, "\0", 1);
		if (extra == 0)
		{
			//printf("hi\n");
		}		

		strncat(output, "\n", MAX_IN_CHARS);
	}
	
	printf("%s", output);
	return 0;
}
