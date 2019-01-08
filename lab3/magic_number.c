#include <stdlib.h>
#include <stdio.h>

/*This program is supposed to take the magic number, add 3, and then multiply by 2. It repeats those two steps several times, then outputs the number!*/

int main(int argc, char* argv[]){

	printf("The magic numbers are... ");
	
	int magic_number = 1;
	int i;
	for(i = 0; i < 15; i++){	
		magic_number = (magic_number+3)*2;
		
		if(i == 12 || i == 13){ /*third-last and second-last*/
			printf("%d, ", magic_number);
		}
		if(i == 14){ /*last one*/
			printf("and %d!\n", magic_number);
		}
	}

    return 0;
}

/*if my calculations are right, the magic numbers should be 57338, 114682, and 229370. */
