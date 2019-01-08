#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dump.h"

#define ADDR_SIZE 16


int 
main(int argc, char* argv[]){
    //Create two char arrays and display code for demo purposes 
    char test1[10] = {'a','b','c', '\0'};
    char test2[10] = {'d','e','f', '\0'};
    printf("char test1[10] = \"%s\"\n", test1);
    printf("char test2[10] = \"%s\"\n", test2);
    printf("\n");

    //Print out the contents of 16 bytes of memory
    //start at the memory address of test1 and test2
    //then wait for a keypress
    dumpHex(&test1, ADDR_SIZE);
    dumpHex(&test2, ADDR_SIZE);
    wait();

    //Update index 16 of test1 with the char 'g'
    //Notice, no errors are produced even though we're out of bounds!
    char g = 'g';
    test1[14]='g';
    printf("test1[16] = \'%c\'\n", g);
    dumpHex(&test1, ADDR_SIZE);
    wait();

    //Update offset 2 of test1 with the char 'h'
    //An index is just the offset of the memory address for the variable
    char h = 'h';
    printf("*(test1+2) = \'%c\'\n", h);
    *(test1+2) = 'h'; 
    dumpHex(&test1, ADDR_SIZE);

    char x = 'x';
    printf("test2[2] = \'%c\'\n", x);
    test2[2] = x; 
    dumpHex(&test2, ADDR_SIZE);
    wait();

   
    //Create a char array using a string literal
    //Notice the other memory contents, it's code! 
    char* foo = "abc"; //Adds in a \0 by default
    printf("char* foo = \"%s\"\n", foo);
    dumpHex(foo, ADDR_SIZE);
    wait();

    //You can still you the same types of indexing
    //as with the other char array declaration
    char bar1 = *(foo+2);
    char bar2 = foo[2];
    printf("char bar1 = *(foo+2);\n");
    printf("     bar1 = \"%c\"\n", bar1);
    printf("char bar2 = foo[2];\n");
    printf("     bar2 = \"%c\"\n", bar2);
    wait();

    //However, remember what Mike said about string literals and 
    //code data?  What if we tried to modify the data?
    printf("What's going to happen when we try to run this code?\n");
    printf("foo[0] = \'%c\'\n", 'X');
    wait();
    
    foo[0] = 'X';
}
