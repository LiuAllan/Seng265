/*
 * Allan Liu
 * V00806981
 *
 * UVic SENG 265, Summer 2018,  A#4
 *
 * This will contain the bulk of the work for the fourth assignment. It
 * provide similar functionality to the class written in Python for
 * assignment #3.
 */
 
 /*GNU extension for getline() because the compiler on lab computers is older version before getline() was standardized in C library.
 */
#define _GNU_SOURCE
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

#define DEFAULT_BUFLEN 80

/*function prototypes*/
void line_spacing();
void margins();
void format(char*);
int check_format(char*);
char **format_file(FILE*);
char **format_line(char**, int);

char *line_string = NULL;
char **result = NULL;
int count;

int chars = 0;
int FT = 0;
int LW = 0;
int LM = 0;
int LS = 0;
int LS_flag = 0;
int LS_changed = 0;
int temp = 0;
int new_paragraph = 0;

/*wrapper function that calls malloc if allocation fails. Reports error and exits. From slides 30*/
void *emalloc(size_t n)
{
	void *p;
	p = malloc(n);
	if (p == NULL) {
		fprintf(stderr, "malloc of %zu bytes failed", n);
		exit(1);
	}
	return p;
}

void format(char *line)
{
	char *t; /*for tokenizing*/
	char *delimiters = " \n";
	char *temp_memory = NULL;
	
	temp_memory = (char*)emalloc(sizeof(char) * (strlen(line)+1));
	strncpy(temp_memory, line, strlen(line)+1);
	
	t = strtok(temp_memory, delimiters);
	/*replace all whitespace and newlines in line with null*/
	while(t)
	{
		int num = strlen(t);
		/*make linespacing if the number of chars exceeds the line width*/
		if(chars + num + 1 > LW)
		{
			strncat(line_string, "\n", 2);
			result[count] = (char*)emalloc(sizeof(char) * (strlen(line_string)+1));
			strncpy(result[count], line_string, strlen(line_string)+1);
			count++;
			/*reset the line_string because start of a new line*/
			strncpy(line_string, "\0", 1);
			line_spacing();
			chars = 0;
		}
		/*adding space between the words unless it is the first word in the line*/
		else if(chars > LM)
		{
			strncat(line_string, " ", 2);
			chars++;
		}
		/*start of a new line*/
		if(chars == 0)
		{
			if (new_paragraph == 1)
			{
				line_spacing();
				new_paragraph = 0;
			}
			margins();
			chars += LM;
		}
		/*add words to the line string*/
		strncat(line_string, t, num + 1);
		chars += num;
		t = strtok(NULL, " \n");
	}
	if (temp_memory)
	{
		free(temp_memory);
	}
}

int check_format(char *line)
{
	int has_format = 0;
	char* next;
	int length = strlen(line)+1;
	/*allocate memory and sets to 0*/
	char *grab = (char*)calloc(length, sizeof(char));
	if(grab == NULL){
		exit(1);
	}
	strncpy(grab, line, length);
	strtok(grab, " \n");
	
	if(!strncmp(grab, ".FT", length))
	{
		next = strtok(NULL, " \n");
		if(!strncmp(next, "on", 3))
		{
			FT = 1;
			has_format = 1;
		}
		else if(!strncmp(next, "off", 3))
		{
			FT = 0;
			has_format = 1;
		}
	}
	
	if(!strncmp(grab, ".LW", length))
	{
		LW = atoi(strtok (NULL, " \n"));
		FT = 1;
		has_format = 1;
	}
	
	if(!strncmp(grab, ".LM", length))
	{
		next = strtok(NULL, " \n");
		if(!strncmp(next, "+", 1))
		{
			next++;
			LM += atoi(next);
		}
		else if(!strncmp(next, "-", 1))
		{
			next++;
			LM -= atoi(next);
		}
		else
		{
			LM = atoi(next);
		}
		if (LM >= LW - 20)
		{
			LM = LW - 20;
		}
		FT = 1;
		has_format = 1;
	}
	
	else if (strncmp(line, ".LS", 3) == 0) 
	{
		//check appropriate line spacing
		if(LS_flag == 1)
		{
			temp = LS;
			LS_changed = 1;
		}
		//t = strtok(line, ".LS ");
		LS = atoi(strtok(line, ".LS "));
		LS_flag = 1;
		FT = 1;
		has_format = 1;
	}
	grab = (char*)realloc(grab, (length+1) * sizeof(char));
	free(grab);
	return has_format;
}

void line_spacing()
{
	//result[count] = (char*)emalloc(sizeof(char)*2);
	/*encounter changed LS*/
	if(LS_changed == 1)
	{
		for(int i = 0; i < temp; i++)
		{
			result[count] = (char*)emalloc(sizeof(char)*2);
			strncpy(result[count], "\n", 2);
			count++;
		}
		LS_flag = 0;
		//LS_changed = 0;
		temp = LS;
	}
	/*encounter no new LS command*/
	else
	{
		for(int i = 0; i < LS; i++)
		{
			result[count] = (char*)emalloc(sizeof(char)*2);
			strncpy(result[count], "\n", 2);
			count++;
		}
	}
}

void margins()
{
	for(int i = 0; i < LM; i++)
	{
		strncat(line_string, " ", 2);
	}
}

char **format_file(FILE *infile) {
	/*initialized to 0 in beginning, will be 1 if line has a formatting command*/
	int has_format = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	count = 0;
	
	/*initialize size of result, size will change as it reads line by line*/
	result = (char**)emalloc(sizeof(char*) * 10000);
	/*allocate memory for the line of string that will be formatted*/
	line_string = (char*)emalloc(sizeof(char) * 120);
	
	/*from slides 34 on dynamic memory, read line by line*/
	while ((read = getline(&line, &len, infile)) != -1) 
	{
		has_format = check_format(line);
		/*has no formatting, "print" the line by adding to the result*/
		if(FT == 0 && has_format != 1)
		{
			result[count] = (char*)emalloc(sizeof(char)*(strlen(line)+1));
			strncpy(result[count], line, strlen(line)+1);
			count++;
		}
		/*line has no new formatting commands but formatting is on, format the line*/
		else if(FT == 1 && has_format != 1)
		{
			/*check for new lines*/
			if(strncmp(line, "\n", 2) == 0)
			//if(strncmp(line, "\n", strlen(line)) == 0)
			{
				/*string is not an empty line*/
				if(strncmp(line_string, "\0", 1) != 0)
				{
					strncat(line_string, "\n", 2);
					result[count] = (char*)emalloc(sizeof(char)*(strlen(line_string)+1));
					
					strncpy(result[count], line_string, strlen(line_string)+1);
					count++;
					chars = 0;
					/*reset the line_string*/
					strncpy(line_string, "\0", 1);
				}
				/*add empty line*/
				result[count] = (char*)emalloc(sizeof(char)*2);
				strncpy(result[count], "\n", 2);
				count++;
				line_spacing();
				new_paragraph = 1;
			}
			format(line);
		}
	}
	/*add the remaining strings to result at the end of the file*/
	if(FT == 1 && new_paragraph != 1)
	{
		strncat(line_string, "\n", 2);
		result[count] = (char*)emalloc(sizeof(char)*(strlen(line_string)+1));
		strncpy(result[count], line_string, strlen(line_string)+1);
		count++;
		chars = 0;
		strncpy(line_string, "\0", 1);
	}
	
	if (line)
	{
		free(line);
	}
	/*end result with null to indicate end*/
	result[count] = NULL;
	return result;
}

/*returns an array of strings*/
char **format_lines(char **lines, int num_lines) {
	int has_format = 0;
	char *line = NULL;
	count = 0;
	
	/*initial size of result, to be adjusted as it read in lines*/
	result = (char**)emalloc(sizeof(char*) * (num_lines*2));
	line_string = (char*)emalloc(sizeof(char) * 120);
	
	for(int i = 0; i<num_lines; i++)
	{
		line = lines[i];
		has_format = check_format(line); //***problem is here causing seg fault
		
		if(FT == 0 && has_format != 1)
		{
			result[count] = (char*)emalloc(sizeof(char)*(strlen(line)+1));
			strncpy(result[count], line, strlen(line)+1);
			count++;
		}
		
		/*line has no new formatting commands but formatting is on, format the line*/
		else if(FT == 1 && has_format != 1)
		{
			/*check for new lines*/
			if(strncmp(line, "\n", 2) == 0)
			{
				/*string is not an empty line*/
				if(strncmp(line_string, "\0", 1) != 0)
				{
					strncat(line_string, "\n", 2);
					result[count] = (char*)emalloc(sizeof(char)*(strlen(line_string)+1));
					
					strncpy(result[count], line_string, strlen(line_string)+1);
					count++;
					chars = 0;
					/*reset the line_string*/
					strncpy(line_string, "\0", 1);
				}
				/*add empty line*/
				result[count] = (char*)emalloc(sizeof(char)*2);
				strncpy(result[count], "\n", 2);
				count++;
				line_spacing();
				new_paragraph = 1;
			}
			format(line);
		}
	}
	if(FT == 1 && new_paragraph != 1)
	{
		strncat(line_string, "\n", 2);
		result[count] = (char*)emalloc(sizeof(char)*(strlen(line_string)+1));
		strncpy(result[count], line_string, strlen(line_string)+1);
		count++;
		chars = 0;
		
		strncpy(line_string, "\0", 1);
	}
	result[count] = NULL;
	
	/*
	if (line)
	{
		free(line);
	}
	*/
	
/*
#ifdef DEBUG
	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL) {
		return NULL;
	}

	result[0] = (char *)malloc(sizeof(char) * DEFAULT_BUFLEN);
	if (result[0] == NULL) {
		return NULL;
	}
	strncpy(result[0], "(machine-like voice) STABLE GENIUS!", 
        DEFAULT_BUFLEN-1);

	result[1] = (char *)malloc(sizeof(char) * 2);
	if (result[1] == NULL) {
		return NULL;
	}
	result[1][0] = '\0';
#endif
*/
	return result;
}