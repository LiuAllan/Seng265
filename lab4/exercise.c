#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define MAX_WORDS 100
#define MAX_WORD_LEN 20

int main(int argc, char* argv[]){

	char* delimiters = " .?!\n";			// delimiters for strtok()
	
	char *words[MAX_WORDS][MAX_WORD_LEN];	// array to store each word
	char *buffer[MAX_LINE_LEN];				//buffer for fgets

	// Loop through each line of stdin with fgets
	// For each line use strtok to parse each word into the words array
	
	// Once you've finished reading stdin, print each word of the 
	// words array and its length using strlen()
	
	while(fgets(&buffer, MAX_LINE_LEN, stdin))
	{
		char *word = strtok(&buffer, delimiters);
		//printf("Word is: %s", *word);
		while(word)
		{
			printf("%s \n", word);
			word = strtok(NULL, delimiters);
		}	
	}

	return 0;
}
