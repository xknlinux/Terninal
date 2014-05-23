#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include"Get_Environment.h"
#include"My_Link.h"


int Get_Parameter(int argc, char **argv)
{
	int i=0,j;
	struct stat p;
	ST_LINK *ST_Node, *p1, *p2;
	ST_Head_Path = (ST_LINK *)malloc(sizeof(ST_LINK));

	ST_Head_Path = (ST_LINK *)malloc(sizeof(ST_LINK));
	ST_Head_Parameter = (ST_LINK *)malloc(sizeof(ST_LINK));

	p1 = ST_Head_Path;
	p2 = ST_Head_Parameter;
	while(argv[++i] != NULL)
	{
		memset(&p, 0, sizeof(struct stat));
		stat(argv[i], &p);
		if(S_ISDIR(p.st_mode))
		{
			ST_Node = (ST_LINK *)malloc(sizeof(ST_Node));
			memset(ST_Node->cMessage, 0, 128);
			strcpy(ST_Node -> cMessage, argv[i]);
			p1->next = ST_Node;
			p1 = p1 -> next;
			p1->next = NULL;
			continue;
			
		}
		else if(argv[i][0] == '-')
		{
			j=0;
			ST_Node = (ST_LINK *)malloc(sizeof(ST_Node));
			while(j < strlen(argv[i]) -1)
			{
				argv[i][j] = argv[i][j+1];
				j++;
			}
			memset(ST_Node->cMessage, 0, 128);
			strcpy(ST_Node -> cMessage, argv[i]);
			p2->next = ST_Node;
			p2 = p2 -> next;
			p2->next = NULL;
		}
		else
			printf("ls: cannot access %s: No such file or directory\n", argv[i]);
	}

	return TRUE;
}
