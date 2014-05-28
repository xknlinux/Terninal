#ifndef MY_LINK_
#define MY_LINK_

#include<stdio.h>
#include<malloc.h>


#define TRUE 0
#define FAILURE -1


typedef struct Link
{
	char cMessage[128];
	struct Link *next;
	int iSign; 			//标记颜色
}ST_LINK;

ST_LINK *ST_Head_Path;
ST_LINK *ST_Head_Parameter;
int Get_Parameter(int argc, char **argv);
int Insert_Link(ST_LINK **p, const char *cName, int SIGN);

#endif
