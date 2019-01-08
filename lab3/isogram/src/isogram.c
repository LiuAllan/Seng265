#include <stdio.h>
#include <ctype.h>  //tolower
#include <string.h> //strlen
#include "isogram.h"

bool
is_isogram(const char phrase[])
{
    fprintf(stderr, "phrase='%s'\n", phrase); 
    int i;
    int j;
    for (int i = 0; i < (int)strlen(phrase); i++)
    {
	char character = phrase[i];
	for (int j = 1; j < (int)strlen(phrase); j++)
	{
		char next_character = phrase[j];
		if (character == next_character)
		{
			return 0;
		}
	}
    }
    return true;
}
