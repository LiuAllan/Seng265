/* Name: pirate_password.c
Author: Cap'n Ctrlaltdel
NetLink ID: ctrlaltdel
V#: V00YARRRR 
Description: This be a pirate's code for makin' pirate codes!*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>  
#include <time.h>


/* A note from the Responsible Treasure Hunters Association:
  In real life, you really, really, REALLY shouldn't try and make your own cryptographic
 software. This is mostly because, if you screw up, the consequences could be terrible. */


void add_numbers_to_password(char* password){
	/*this function generates 5 random digits and replaces characters in the password with them!*/
	
	//make a buffer to store temporary digits.
	char* number_temp = (char*) malloc(sizeof(char)*3);
	number_temp[0] = '\0';
	int i;
	int len = strlen(password);
	
	for(i=0; i < 5; i++){
		int randN = abs((int)random()) % 10; /*make a random digit!*/
		sprintf(number_temp, "%d", randN); /*copy the random digit into number_temp. */
		
		int num_loc = abs((int)random()) % len; /*pick a random place in the password to change into the number!*/
		password[num_loc] = number_temp[0]; /*copy the digit's character from number_temp into password at the right place! */
	}
	
	return;
}



void print_password(char* password){
	/*this function prints the password!*/
	

	printf("Today's password is \"%s\", yarr! \n",password);
	
	/*now that the password is shown, get rid of it so it's not in memory any more!*/
	free(password);
	
	return;
}

int main(int argc, char* argv[]){
	/*set up random number generator*/
	time_t seconds = time(NULL); srandom(seconds);


	char* todays_password = malloc(sizeof(char) * 20);

	switch(abs((int)random()) % 3){
		case 0:
			strcpy(todays_password, "Arrrrrrrrrrrr");
		break;
		case 1:
			strcpy(todays_password, "PiecesOf8AndAHalf");
		break;
		case 2:
			strcpy(todays_password, "Pir8ChestJokeHere");
		break;
	}

	/*now we add another word! We might need to resize today's password.*/
	if(strlen(todays_password) + 10 > 20){
		todays_password = (char*) realloc(todays_password, sizeof(todays_password)*2);
	}

	switch(abs((int)random()) % 5){
		case 0:
			strcat(todays_password, "000Plunder");
		break;
		case 1:
			strcat(todays_password, "11MainMast");
		break;
		case 2:
			strcat(todays_password, "2222Sunken");
		break;
		case 3:
			strcat(todays_password, "33Treasure");
		break;
		case 4:
			strcat(todays_password, "444Mystery");
		break;
	}

	add_numbers_to_password(todays_password);

	print_password(todays_password);

	/*now clean everything up! First write over the password, then free it.*/
	strncpy(todays_password, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",20);

	free(todays_password);

}
