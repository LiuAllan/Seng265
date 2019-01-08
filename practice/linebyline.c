/* echo the contents of file specified as the first argument, line by line. */
#include <stdio.h>
#include <stdlib.h>
#define BUFLEN 100
int main(int argc, char *argv[]) {
	char buffer[BUFLEN];
	int num_lines;
	if (argc < 2) {
		fprintf(stderr, "You must provide a filename\n");
		exit(1);
	}
	FILE *data_fp = fopen(argv[1], "r");
	if (data_fp == NULL) {
		fprintf(stderr, "unable to open %s\n", argv[1]);
		exit(1);
	}
	num_lines = 0;
	while (fgets(buffer, sizeof(char) * BUFLEN, data_fp)) {
		num_lines++;
		printf("%d: %s", num_lines, buffer);
	}
	fclose(data_fp); /* There is a little bug in the loop! */
	return 0;
}


FILE *file = fopen(argv[1], "r");

while(fgets(buffer, MAX_LEN_CHAR, file)
{



}
