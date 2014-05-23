#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>

#include"My_Link.h"
#include"My_Ls.h"
#include"Get_Environment.h"

int PARAMETER_MARK;

extern ST_LINK *ST_Head_Path;
extern ST_LINK *ST_Head_Parameter;
int main(int argc, char *argv[])
{

	Get_Parameter(argc, argv); 	//Get the Parameter
	Before_Running();
	Run_Function();

	return TRUE;
}

int Before_Running() //设置PARAMETER_MARK
{
	ST_LINK *p;
	p = ST_Head_Parameter;
	int i=0;
	while(p->next != NULL)
	{
		p = p -> next;
		while(p->cMessage[i] != '\0')
		{
			Shine_Upon(p->cMessage[i]);
			i++;
		}
	}

	return TRUE;
}

void Shine_Upon(char cCharacter)
{
	if(cCharacter == 'l')
	{
		PARAMETER_MARK &= L_PARAMETER; 
	}
	else if(cCharacter == 'a')
	{
		PARAMETER_MARK &= A_PARAMETER;
	}
	else if(cCharacter == 'd')
	{
		PARAMETER_MARK &= D_PARAMETER;
	}
}

int Run_Function() 			//根据参数执行不同的函数
{

	switch(PARAMETER_MARK)
	{
		case NO_PARAMETER:
			Display_File();
			break;
		default:
			break;
	}

	return TRUE;
}

void Display_File()
{
	ST_LINK *p;
	p = ST_Head_Path->next;
	if(p == NULL)
		Display_File_Data("./");
	else
	{
		while( p != NULL)
		{
			Display_File_Data(p->cMessage);
			p = p->next;
		}
	}
}

int Display_File_Data(const char *cPath)
{
	DIR *dFd;
	struct dirent *ST_Ptr;

	if((dFd = opendir(cPath)) == NULL)
	{
		my_err("opendir", __LINE__);
	}
	while((ST_Ptr = readdir(dFd)) != NULL)
	{
		printf("%s  ", ST_Ptr->d_name);
		ST_Ptr = NULL;
	}

	printf("\n");
	return TRUE;
}

void my_err(const char *err_string, int line)
{
	fprintf(stderr, "line: %d", line);
	perror("opendir");
	exit(1);
}
