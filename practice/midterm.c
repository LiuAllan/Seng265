#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
void swap(int *c, int *d);

void swap(int *c, int *d)
{
	int temp = *c;
	*c = *d;
	*d = temp;
//	return temp;	

}
*/
int main()
{
	char string[] = "the quick brown foo jumped over bar";
	char *word = strtok(string, " ");

	while(word)
	{
		printf("The word is: %s\n", word);
		word = (strtok(NULL, " "));
	}
	
	return 0; 
}
