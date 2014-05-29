#ifndef MY_LINK_
#define MY_LINK_

#include<stdio.h>
#include<malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



#define TRUE 0
#define FAILURE -1


typedef struct Link
{
	char cMessage[128];
	struct stat buf;
	struct Link *next;
}ST_LINK;

extern ST_LINK *ST_Head_Path;
extern ST_LINK *ST_Head_Parameter;
extern char ST_Head_Parameter_Sort[128];
int Get_Parameter(int argc, char **argv);
int Insert_Link(ST_LINK **p, const char *cName);

#endif
