#include<stdio.h>
#include<malloc.h>
#include<string.h>

#include"My_Link.h"

int Insert_Link(ST_LINK **p, const char *cName)
{
	ST_LINK *Node;
	Node = (ST_LINK *)malloc(sizeof(ST_LINK));
	memset(Node->cMessage, 0, sizeof(128));
	strcpy(Node->cMessage, cName);

	(*p)->next = Node;
	*p = (*p) -> next;
	(*p)->next = NULL;

	return 0;
}
