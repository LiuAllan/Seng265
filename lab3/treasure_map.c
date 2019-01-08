/* Name: treasure_map.c
Author: Cap'n Ctrlaltdel
NetLink ID: ctrlaltdel
V#: V00YARRRR */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){

	printf("Haharr, you'll never find my %d pieces of gold!\n",10000);

	printf("You'll never find it even if you take...\n");
	
	int steps[15];
	int i;
	int j;
	for(i = 1; i < 15; i++){ 
		/*fill the array with step counts!*/
		steps[i-1] = i;
	}
	
	
	for(j = 0; j < 15; j++){
		printf("%d", steps[j]);

		if(j = 15){
			/*don't print the comma if there's no more loops to go, yarr!
			  instead, print the rest of the line.*/
			printf(" steps south of Crossbones Rock and dig!\n");
		} else {
			printf(', '); /*separate the numbers with a comma!*/
		}
	}

}
