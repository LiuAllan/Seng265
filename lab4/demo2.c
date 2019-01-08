#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dump.h"

#define ADDR_SIZE 16 

//What happens if I pass my char array to a function
void myfunc(char foo[]) //What if I tried to pass foo[3]?
{
    //The compiler no longer knows how big the array is!
    //This is passed by reference (ie. the memory address)
    printf("myfunc(bar);\n");
    printf("sizeof(foo)    = ? \n");
    wait();
    printf("sizeof(foo)    = %d\n", (int)sizeof(foo));
    wait();
}

int 
main(int argc, char* argv[]){
    
    char* foo = "abc";
    printf("char* foo      = \"%s\"\n", foo);
    dumpHex(foo, ADDR_SIZE);
   
    //Get the length of the string .. does it work? 
    printf("sizeof(foo)    = ? \n");
    wait();
    printf("sizeof(foo)    = %d\n", (int)sizeof(foo));
    wait();
    
    //Oh, char* is a memory address so we get the size of the
    //memory address which is N bytes.  Okay, let's just get
    //the first index, that's not a address.
    printf("sizeof(foo[0]) = ? \n");
    wait(); 
    printf("sizeof(foo[0]) = %d\n", (int)sizeof(foo[0]));
    wait();
   
    //Oops, that's a char. So how do we did it? 
    printf("strlen(foo)    = ?\n");
    wait();
    printf("strlen(foo)    = %d\n", (int)strlen(foo));
    wait();
    
    //That seems like a hassle, I'd rather use sizeof. 
    //Let's just use an char array instead. 
    { //<-- This just creates a locality so I can reuse the variables 
        char bar[3];
        bar[0] = 'a';
        bar[1] = 'b';
        bar[2] = 'c';
        printf("char bar[3]; \nbar[0] = 'a'; \nbar[1] = 'b'; \nbar[2] = 'c';\n");
        dumpHex(bar, ADDR_SIZE);
    
        //Get the length of the string .. does it work? 
        printf("sizeof(bar)    = ? \n");
        wait();
        printf("sizeof(bar)    = %d\n", (int)sizeof(bar));
        wait();
   
        //There are fixed ... but what if? 
        myfunc(bar);
    }

    
    
    //Or what if ...? 
    { 
        char bar[10];
        memset(bar,'$',10); //This is to simulate stale data 
        bar[0] = 'a';
        bar[1] = 'b';
        bar[2] = 'c';
        printf("char bar[10]; \nbar[0] = 'a'; \nbar[1] = 'b'; \nbar[2] = 'c';\n");
        dumpHex(bar, ADDR_SIZE);
    
        //Get the length of the string .. does it work? 
        printf("sizeof(bar)    = ? \n");
        wait();
        printf("sizeof(bar)    = %d\n", (int)sizeof(bar));
        wait();

        //Okay, I'll just use strlen()
        printf("strlen(bar)    = %d\n", (int)strlen(bar));
        wait();

        //Oops, forgot the NULL
        bar[3] = '\0';
        printf("bar[3] = '\\0';\n");
        printf("strlen(bar)    = %d\n", (int)strlen(bar));
        wait();
    }
    
}
