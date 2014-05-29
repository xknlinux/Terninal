#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

#include"My_Link.h"
#include"My_Ls.h"

int PARAMETER_MARK;

ST_LINK *ST_Head_Name = (ST_LINK *)malloc(sizeof(ST_LINK));
int iNumber; //目录下的文件总数

int Run_Function(int argc, char *argv[]) 			//根据参数执行不同的函数
{
	ST_LINK *p;
	
	Get_Parameter(argc, argv);  //Get the Parameter
	Before_Running();       //set PARAMETER_MARK

	p = ST_Head_Path->next;

	if(p == NULL)
		Display_File("./");
	while(p != NULL)
	{
		Display_File(p->cMessage);
		p = p->next;
	}

	printf("\n");
	return TRUE;
}

int Display_File(const char *cPath)  				//读取目录下的文件
{
	DIR *dFd;
	struct dirent *ST_Ptr;

	ST_LINK *p = ST_Head_Name;
	char File_Name[128] = {0};
	iNumber = 0; //文件数量清零

	if((dFd = opendir(cPath)) == NULL)
	{
		my_err("opendir", __LINE__);
	}
	while((ST_Ptr = readdir(dFd)) != NULL) 	//读取一个目录下的所有文件信息
	{
		strcat(File_Name, cPath);
		strcat(File_Name, ST_Ptr->d_name);

		Insert_Link(&p, ST_Ptr->d_name);
		iNumber++;
		
		if(-1 == stat(File_Name,&(p->buf)))
			my_err("stat", __LINE__);

		 memset(File_Name, 0, 128);
	}

	My_Sort_Pre(); 	//按--参数后的要求进行排序

	Switch_Function(cPath);
	return 0;
}

void My_Sort_Pre() 	//按要求进行排序
{

	int (*My_Strcmp)(ST_LINK*, ST_LINK*);
	if(ST_Head_Parameter_Sort[0] == '\0')
	{
		My_Strcmp = Cmp_Name;
	}
	else if(strcmp(ST_Head_Parameter_Sort, "help") == 0)
	{
		readme();
		exit(0);
	}
	else if(strcmp(ST_Head_Parameter_Sort, "size") == 0)
	{
		My_Strcmp = Cmp_Size;
	}
	else if(strcmp(ST_Head_Parameter_Sort, "name") == 0)
		My_Strcmp = Cmp_Name;
	else
	{
		printf("Try './ls --help' for more information.\n");
		exit(0);
	}

	My_Sort(My_Strcmp);
}

void readme()
{
	system("cat readme");
}

int Switch_Function(const char *cPath) 	//根据PARAMETER_MARK选择不同的执行策略
{
	ST_LINK *p;


	if((PARAMETER_MARK & D_PARAMETER) == D_PARAMETER) 			//有-d选项
		Display_DD(cPath);
	
	else if((PARAMETER_MARK & L_PARAMETER) == L_PARAMETER) 		//有-l选项
	{
		if(ST_Head_Path->next!=NULL && ST_Head_Path->next->next != NULL)
			printf("%s:\n",cPath);
		printf("total %d\n", iNumber); 		//输出文件总数

		p = ST_Head_Name->next;
		while(p != NULL)
		{
			if(p->cMessage[0] == '.')
			{
				if((PARAMETER_MARK & A_PARAMETER) == A_PARAMETER)
					Display_LL(p->buf,p);
			}
			else
				Display_LL(p->buf, p);
			p = p->next;
		}
	}
	else 										//没有-l -d选项
		Out_Put();
	return TRUE;
}

int Display_DD(const char *cPath) //显示-d参数
{
	ST_LINK *p;
	if((PARAMETER_MARK & L_PARAMETER) != L_PARAMETER)
	{
		if(ST_Head_Path->next == NULL)
			printf("\033[;34m.\033[0m\n");
		else
			printf("\033[;34m%s\033[0m   ", cPath);
	}
	else
	{
		p = (ST_LINK *)malloc(sizeof(ST_LINK));
		strcpy(p->cMessage, ".");
		if(ST_Head_Path->next == NULL)
		{
			if(-1 == stat(".", &(p->buf)))
				my_err("stat", __LINE__);
			Display_LL(p->buf, p);
		}
		else
			Display_LL(p->buf, p);
	}
	return 0;
}

int Display_LL(struct stat buf, ST_LINK *p) 	//显示-l参数
{

	char buf_time[32];
	struct passwd *psd; //从该结构体中获取文件所有者的用户名
	struct group *grp; 	//从该结构体中获取文件所有者属组的组名

	if(S_ISLNK(buf.st_mode)) 	//打印文件类型
		printf("l");
	else if(S_ISREG(buf.st_mode))
		printf("-");
	else if(S_ISDIR(buf.st_mode))
		printf("d");
	else if(S_ISCHR(buf.st_mode))
		printf("c");
	else if(S_ISBLK(buf.st_mode))
		printf("b");
	else if(S_ISFIFO(buf.st_mode))
		printf("f");
	else if(S_ISSOCK(buf.st_mode))
		printf("s");

	if(buf.st_mode & S_IRUSR) 	//所有者对文件读取权限
		printf("r");
	else
		printf("-");
	if(buf.st_mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	if(buf.st_mode & S_IXUSR)
		printf("x");
	else
		printf("-");

	if(buf.st_mode & S_IRGRP) 	//所有者同组对文件读取权限
		printf("r");
	else
		printf("-");
	if(buf.st_mode & S_IWGRP)
		printf("w");
	else
		printf("-");
	if(buf.st_mode & S_IXGRP)
		printf("x");
	else
		printf("-");

	if(buf.st_mode & S_IROTH) 	//其他用户对文件读取权限
		printf("r");
	else
		printf("-");
	if(buf.st_mode & S_IWOTH)
		printf("w");
	else
		printf("-");
	if(buf.st_mode & S_IXOTH)
		printf("x");
	else
		printf("-");

	printf("  ");
	//根据UID和GID获取所有者的用户名与组名
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);

	printf("%4d ",(int) buf.st_nlink); 	//打印文件连接数
	printf("%-8s", psd->pw_name);
	printf("%-8s", grp->gr_name);

	printf("%6d", (int)buf.st_size); 	//打印文件大小

 	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = '\0';
	printf("  %s", buf_time);

	printf("  ");

	print(p);

	printf("\n");

	return 0;
}

int Before_Running() //设置PARAMETER_MARK
{
	ST_LINK *p;
	p = ST_Head_Parameter;
	int i;
	char cCharacter;
	while(p->next != NULL)
	{
		i=0;
		p = p -> next;
		while(p->cMessage[i] != '\0')
		{
			cCharacter = p->cMessage[i];
			if(cCharacter == 'l')
			{
				PARAMETER_MARK |= L_PARAMETER; 
			}
			else if(cCharacter == 'a')
			{
				PARAMETER_MARK |= A_PARAMETER;
			}
			else if(cCharacter == 'd')
			{
				PARAMETER_MARK |= D_PARAMETER;
			}
			i++;
		}
	}
	return TRUE;
}



void Out_Put() 				//输出+布局
{
	ST_LINK *w = ST_Head_Name->next;

	while(w != NULL)
	{
		if(w->cMessage[0] == '.')
		{
			if((PARAMETER_MARK & A_PARAMETER) == A_PARAMETER)
				print(w);
			w = w->next;
		}
		else
		{
			print(w);
			w = w->next;
		}
	}
	printf("\n\n");
}

//30: 黑 31: 红  32: 绿 33: 黄 34: 蓝 35: 紫 36: 深绿 37: 白色

void print(ST_LINK *Node) 			//带有颜色的输出
{
	if(S_ISREG(Node->buf.st_mode))
		printf("\033[;33m%s\033[0m   ", Node->cMessage);
	else if(S_ISDIR(Node->buf.st_mode))
		printf("\033[;34m%s\033[0m   ", Node->cMessage);
	else if(S_ISLNK(Node->buf.st_mode))
		printf("\033[;36m%s\033[0m   ", Node->cMessage);
	else if(S_ISBLK(Node->buf.st_mode))
		printf("\033[;37m%s\033[0m   ", Node->cMessage);
	else if(S_ISFIFO(Node->buf.st_mode))
		printf("\033[;31m%s\033[0m   ", Node->cMessage);
	else if(S_ISSOCK(Node->buf.st_mode))
		printf("\033[;35m%s\033[0m   ", Node->cMessage);
	else
		printf("%s   ", Node->cMessage);
}

void My_Sort(int (*My_Strcmp)(ST_LINK*, ST_LINK*)) 			//冒泡排序
{
	int i;
	ST_LINK *p, *s;
	ST_LINK *ST_Temp = NULL;
	ST_LINK *ST_Swap_Temp = NULL;
	for(i = 0; i < iNumber; i++)
	{
		s = ST_Head_Name;
		for(p = s->next; p->next != ST_Temp; s = s->next)
		{
			if(My_Strcmp(p, p->next) > 0)
			{
				ST_Swap_Temp = p;
				s->next = p->next;
				ST_Swap_Temp->next = p->next->next;
				s->next->next= ST_Swap_Temp;
			}
			else
				p = p->next;
		}
		ST_Temp  = p;
	}
}

int Cmp_Name(ST_LINK *p1, ST_LINK *p2)
{
	char *str1 = (char *)malloc(128); 
	char *str2 = (char *)malloc(128); 
	memset(str1, 0, 128);
	memset(str2, 0, 128);
	strcpy(str1, p1->cMessage);
	strcpy(str2, p2->cMessage);
	while(*str1 != '\0' && *str2 != '\0')
	for(;str1 !='\0' && str2!= '\0'; str1++, str2++)
	{
		if(((*str1>=65 && *str1 <=90) && (*str2>=97 && *str2<=122)))
		{
			return 1;
		}
		else if((*str1>=97 && *str1 <=122) && (*str2>=65 && *str2<=90))
				return -1;
		else if(*str1 > *str2)
			return 1;
		else if(*str1 < *str2)
			return -1;
		else
			continue;
	}
	if(*str1 == '\0' && *str2 != '\0')
		return -1;
	else if(*str1 != '\0' && *str2 == '\0')
		return 1;
	else
		return 0;
}

int Cmp_Size(ST_LINK *p1, ST_LINK *p2)
{
	if(p1->buf.st_size > p2->buf.st_size)
		return 1;
	else
		return 0;
}
