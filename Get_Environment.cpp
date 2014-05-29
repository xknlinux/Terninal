#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include"My_Link.h"
#include"my_err.h"

ST_LINK *ST_Head_Path;
ST_LINK *ST_Head_Parameter;
char ST_Head_Parameter_Sort[128];

int Get_Parameter(int argc, char **argv)
{
	int i=0;
	unsigned int j;
	struct stat p;
	ST_LINK *ST_Node, *p1, *p2;
	ST_Head_Path = (ST_LINK *)malloc(sizeof(ST_LINK));
	ST_Head_Parameter = (ST_LINK *)malloc(sizeof(ST_LINK));

	p1 = ST_Head_Path;
	p2 = ST_Head_Parameter;
	while(argv[++i] != NULL)
	{
		memset(&p, 0, sizeof(struct stat));
		stat(argv[i], &p);
		if(S_ISDIR(p.st_mode)) 		//获取路径
		{
			ST_Node = (ST_LINK *)malloc(sizeof(ST_Node));
			Insert_Link(&p1, argv[i]);

			if(p1->cMessage[strlen(p1->cMessage) - 1] != '/')
				p1->cMessage[strlen(p1->cMessage)] = '/';
			if(-1 == stat(argv[i], &(p1->buf)))
				my_err("stat", __LINE__);
			continue;
		}
		else if(argv[i][0] == '-' && argv[i][1] == '-') //获取--参数
		{
			j=0;
			ST_Node = (ST_LINK *)malloc(sizeof(ST_Node));
			while(j<(strlen(argv[i]) - 2))
			{
				argv[i][j] = argv[i][j+2];
				j++;
			}
			argv[i][j]='\0';
			strcpy(ST_Head_Parameter_Sort, argv[i]);
		}
		else if(argv[i][0] == '-') //获取-参数
		{
			j=0;
			ST_Node = (ST_LINK *)malloc(sizeof(ST_Node));
			while(j < (strlen(argv[i]) -1))
			{
				argv[i][j] = argv[i][j+1];
				j++;
			}
			Insert_Link(&p2, argv[i]);
		}
		else
			printf("ls: cannot access %s: No such file or directory\n", argv[i]);
	}

	return TRUE;
}
