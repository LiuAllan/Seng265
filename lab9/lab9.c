#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
	char* word;
	struct node_t* next;

}node_t;

node_t* create_node(node_t* prev, char* s)
{
	node_t* n = (node_t*)malloc(sizeof(node_t));
	
	n -> word = s;
	n -> next = NULL;
	
	if(prev) prev->next = n;
	return n;
} 

int main()
{
	node_t *head, *cur;
	head = NULL;
	cur = NULL;

	while(1)
        {
                char* s = (char*)malloc(256*sizeof(char));

                fgets(s, 256, stdin);
                if(s[0] == '\n') break;

                cur = create_node(cur, s);
		if(!head) head = cur;

        }      
	cur = head;
	for(cur = head; cur; cur = cur->next)
		printf("%s\n", cur->word);
	exit(0);
}
/*
Nameval *addfront(Nameval *listp, Nameval *newp)
{
newp->next = listp;
return newp;
}
//usage
Nameval *nvlist = NULL;
...
Nameval *newnode = newitem(string_duplicator("Michael"), 50);
nvlist = addfront(nvlist, newnode);
*/
