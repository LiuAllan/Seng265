#include <stdio.h>
#include <string.h>
#include "dump.h"

#define ADDR_SIZE 16

int main () {
   char haystack[40] = "All your bases are belong to us";
   char needle[10] = "bases";
   char buffer[ADDR_SIZE];
   char *ret;
   
   /* Read from stdin example */
   /*
   while (fgets(buffer, ADDR_SIZE, stdin) > 0) {
        printf("stdin:  buffer='%s'\n", buffer);
   }
   */


   /*strncopy example*/ 
   dumpHex(buffer, ADDR_SIZE);
   strncpy(buffer, needle, strlen(needle)+1);
   dumpHex(buffer, ADDR_SIZE);

   /* strstr example */
   dumpHex(haystack, 2*ADDR_SIZE);
   ret = strstr(haystack, needle);
   printf("The substring is: '%s' @ %p\n", ret, ret);
   dumpHex(ret, ADDR_SIZE);

    /* strtok example */
   ret = strtok(haystack, " ");
   dumpHex(haystack, 2*ADDR_SIZE);
   while(ret != NULL) {
        printf("The token is: '%s' @ %p\n", ret, ret);
        ret = strtok(NULL, " ");
        dumpHex(haystack, 2*16);
   }
   
   
   
   return(0);
}
