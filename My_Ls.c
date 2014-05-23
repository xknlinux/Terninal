#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>

#include"My_Ls.h"
#include"Get_Environment.h"

int PARAMETER_MARK;

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		PARAMETER_MARK = NO_PARAMETER;
		Run_Function();
	}

	Get_Parameter(argc, argv); 	//Get the Parameter

	return TRUE;
}

int Run_Function()
{

	switch(PARAMETER_MARK)
	{
		case NO_PARAMETER:
			Display_File("./");
			break;
		default:
			break;

	}


	return TRUE;
}

int Display_File(char *cPath)
{
	DIR *dFd;
	struct dirent *ST_Ptr;


	if((dFd = opendir("./")) == NULL)
	{
		my_err("opendir", __LINE__);
	}
	while((ST_Ptr = readdir(dFd)) != NULL)
	{
		printf("%s  ", ST_Ptr->d_name);
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
