#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
/*int main() will work too */
{
	char *text = "world";
	fprintf(stderr, "debugging");
	printf("Hello %s\n", text);
	return 0;

}
