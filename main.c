#include<stdio.h>
#include<string.h>

#include"My_Ls.h"
#include"My_Link.h"


int Run_Function() 			//根据参数执行不同的函数
{
	struct stat buf;
	ST_LINK *p;
	if((PARAMETER_MARK & D_PARAMETER) == D_PARAMETER)
	{
		if((PARAMETER_MARK & L_PARAMETER) != L_PARAMETER)
		{
			if(ST_Head_Path->next == NULL)
				printf("\033[;34m.\033[0m\n");
			else
			{
				D_NoL();
				printf("\n");
			}
		}
		else
		{
			p = (ST_LINK *)malloc(sizeof(ST_LINK));
			strcpy(p->cMessage, ".");
			if(ST_Head_Path->next == NULL)
			{
				if(-1 == stat(".", &buf))
					my_err("stat", __LINE__);
				Display_LL(buf, p);
			}
			else
			{
				p = ST_Head_Path->next;
				if(-1 == stat(".", &buf))
					my_err("stat", __LINE__);

				while(p != NULL)
				{
					Display_LL(buf, p);
					p = p->next;
				}
			}
		}
	}
	else
		Display_File();

	return TRUE;
}

int main(int argc, char *argv[])
{

	Get_Parameter(argc, argv); 	//Get the Parameter
	Before_Running(); 		//set PARAMETER_MARK
	Run_Function();

	return TRUE;
}
