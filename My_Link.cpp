#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

#include"My_Link.h"

#include"my_err.h"

int Insert_Link(ST_LINK **p, const char *cName)
{
	ST_LINK *Node;
	char File_Name[128] = {0};

	strcat(File_Name, cName);

	Node = (ST_LINK *)malloc(sizeof(ST_LINK));
	memset(Node->cMessage, 0, sizeof(128));
	strcpy(Node->cMessage, File_Name);

	(*p)->next = Node;
	*p = (*p) -> next;
	(*p)->next = NULL;

	return 0;
}
