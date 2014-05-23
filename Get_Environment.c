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
	p1 = ST_Head_Path;
	p2 = ST_Head_Parameter;
	while(argv[i] != NULL)
	{
		i++;
		stat(argv[i], argv[i]);
		if(S_ISDIR(argv[i].st_mode))
		{
			ST_Node = malloc(sizeof(ST_Node));
			srtcpy(ST_Node -> cMessage, argv[i]);
			p1->next = ST_Node;
			p1 = p1 -> next;
			continue;
			
		}
		if(argv[i][0] == '-')
		{
			j=0;
			ST_Node = malloc(sizeof(ST_Node));
			while(j < strlen(argv[i]) -1)
			{
				argv[i][j] = argv[i][j+1];
				j++;
			}
			srtcpy(ST_Node -> cMessage, argv[i]);
			p2->next = ST_Node;
			P2 = P2 -> next;

		}
		else
			printf("ls: cannot access %s: No such file or directory\n", argv[i]);
	}

	return TRUE;
}
