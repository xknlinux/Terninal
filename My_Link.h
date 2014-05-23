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
}ST_LINK;

ST_LINK *ST_Head_Path;
ST_LINK *ST_Head_Parameter;

#endif
