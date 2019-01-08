/*
 * UVic SENG 265, Summer 2018, A#4
 *
 * This will contain a solution to uvroff2.c. In order to complete the
 * task of formatting a file, it must open the file and pass the result
 * to a routine in formatter.c.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

FILE *input;
char **result;

//Needs to open the file, then pass to formatter.c via format_file If *not* a file, count lines, then pass to formatter.c via format_lines 


int main(int argc, char *argv[]) {
	input = fopen(argv[1], "r");

	if (input == NULL) {
		char* my_string = (char*) malloc (sizeof(char)*argc);
		for (int j = 1; j < argc; j++){
			my_string[j-1] = *argv[j];
		}
		char* super_string = my_string;
		result = format_lines((char**)super_string, argc);
		//printf("%s does nothing right now.\n", argv[0]);
	}
	else{
		result = format_file(input);
		//printf("%s does nothing right now.\n", argv[0]);
	}
	
	int i = 0;
	while(result[i] != NULL)
	{
		printf("%s", result[i]);
		free(result[i]);
		i++;
	}
	
	free(result);
	free(input);
	
#ifdef DEBUG
	//printf("%s does nothing right now.\n", argv[0]);
#endif
	exit(0);
}
