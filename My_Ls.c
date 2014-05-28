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


extern ST_LINK *ST_Head_Path;
extern ST_LINK *ST_Head_Parameter;
ST_LINK *ST_Head_Name;
int iNumber; //目录下的文件总数

int Display_LL(struct stat buf, ST_LINK *p)
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

	printf("%4d ", buf.st_nlink); 	//打印文件连接数
	printf("%-8s", psd->pw_name);
	printf("%-8s", grp->gr_name);

	printf("%6d", buf.st_size); 	//打印文件大小

 	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = '\0';
	printf("  %s", buf_time);

	printf("  ");

	print(p);

	printf("\n");
}

void D_NoL() 		//有-d选项没有-l选项
{
	ST_LINK *p;
	p = ST_Head_Path->next;
	while(p != NULL)
	{
		printf("\033[;34m%s\033[0m   ", p->cMessage);
		p = p->next;
	}
}

int Before_Running() //设置PARAMETER_MARK
{
	ST_LINK *p;
	p = ST_Head_Parameter;
	int i;
	while(p->next != NULL)
	{
		i=0;
		p = p -> next;
		while(p->cMessage[i] != '\0')
		{
			Shine_Upon(p->cMessage[i]);
			i++;
		}
	}
	return TRUE;
}

void Shine_Upon(char cCharacter) //PARAMETER_MARK设置
{
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
}

void Display_File()  				//判断是否为本目录
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

int Display_File_Data(const char *cPath)  				//读取目录下的文件
{
	DIR *dFd;
	struct stat buf;
	struct dirent *ST_Ptr;
	ST_Head_Name = (ST_LINK *)malloc(sizeof(ST_LINK));
	ST_LINK *p = ST_Head_Name;
	char File_Name[128] = {0};
	int iSign = 0; //是否有-a参数
	iNumber = 0; //文件数量清零
	
	if((PARAMETER_MARK & 2) == 2)
		iSign = 1; // 有-a参数

	if((dFd = opendir(cPath)) == NULL)
	{
		my_err("opendir", __LINE__);
	}
	while((ST_Ptr = readdir(dFd)) != NULL)
	{
		Insert_Link(&p, ST_Ptr->d_name, 0);
		iNumber++;

		strcat(File_Name, cPath); 		//接下来就是设置iSign文件类型标志位
		strcat(File_Name, ST_Ptr->d_name);

		if(-1 == stat(File_Name, &buf))
			my_err("stat", __LINE__);

		if(S_ISREG(buf.st_mode))
			p->iSign = FILE_;
		else if(S_ISDIR(buf.st_mode))
			p->iSign = DIR_;
		else if(S_ISLNK(buf.st_mode))
			p->iSign = LINK_;
		else if(S_ISBLK(buf.st_mode))
			p->iSign = BLOCK_;
		else if(S_ISFIFO(buf.st_mode))
			p->iSign = FIFO_;
		else if(S_ISSOCK(buf.st_mode))
			p->iSign = SOCKET_;
		else
			p->iSign = 0;

		memset(File_Name, 0, 128);

	}
	
	My_Sort(); 	//对读取的文件进行排序

	if(ST_Head_Path->next!=NULL && ST_Head_Path->next->next != NULL)
		printf("%s:\n",cPath);
	
	if((PARAMETER_MARK & L_PARAMETER) == L_PARAMETER) 		//有-l选项
	{
		p = ST_Head_Name->next;
		while(p != NULL)
		{
			strcat(File_Name, cPath);
			strcat(File_Name, p->cMessage);
			
			if(-1 == stat(File_Name, &buf))
				my_err("stat", __LINE__);
			

			if(p->cMessage[0] == '.')
			{
				if(iSign == 1)
					Display_LL(buf, p);
			}
			else
				Display_LL(buf, p);
			p = p->next;
			memset(File_Name, 0, 128);
		}
	}
	else 										//没有-l选项
		Out_Put();
	printf("\n");
	return TRUE;
}

void Out_Put() 				//输出
{
	int iMax = 70; //一行最多25个字符
	int iSign = 0; //标志是否有-a参数
	if((PARAMETER_MARK & 2) == 2)
		iSign = 1; // 有-a参数
	
	ST_LINK *w = ST_Head_Name->next;

	while(w != NULL)
	{
		iMax -= strlen(w->cMessage);
		if(iMax < 0)
		{
			printf("\n");
			iMax = 70;
		}
		if(w->cMessage[0] == '.')
		{
			if(iSign == 1)
				print(w);
			w = w->next;
		}
		else
		{
			print(w);
			w = w->next;
		}
		
	}
	printf("\n");
}

//30: 黑 31: 红  32: 绿 33: 黄 34: 蓝 35: 紫 36: 深绿 37: 白色

void print(ST_LINK *Node) 			//带有颜色的输出
{
	if(Node->iSign == FILE_)
		printf("\033[;33m%s\033[0m   ", Node->cMessage);
	else if(Node->iSign == DIR_)
		printf("\033[;34m%s\033[0m   ", Node->cMessage);
	else if(Node->iSign == LINK_)
		printf("\033[;35m%s\033[0m   ", Node->cMessage);
	else if(Node->iSign == BLOCK_)
		printf("\033[;32m%s\033[0m   ", Node->cMessage);
	else if(Node->iSign == FIFO_)
		printf("\033[;37m%s\033[0m   ", Node->cMessage);
	else if(Node->iSign == SOCKET_)
		printf("\033[;31m%s\033[0m   ", Node->cMessage);
	else
		printf("%s   ", Node->cMessage);
}

void My_Sort() 			//冒泡排序
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
			if(strcmp(p->cMessage, p->next->cMessage) > 0)
			{
				if(Da_Xiao(p->cMessage, p->next->cMessage))
					goto DAXIAO2;
DAXIAO1:
				ST_Swap_Temp = p;
				s->next = p->next;
				ST_Swap_Temp->next = p->next->next;
				s->next->next= ST_Swap_Temp;
			}
			else
			{
				if(Da_Xiao(p->cMessage, p->next->cMessage))
					goto DAXIAO1;
DAXIAO2:
				p = p->next;
			}
		}
		ST_Temp  = p;
	}
}

int Da_Xiao(const char *str1, const char *str2)
{
	while(*str1 != '\0' && *str2 != '\0')
	for(;str1 !='\0' && str2!= '\0'; str1++, str2++)
	{
		if(((*str1>=65 && *str1 <=90) && (*str2>=97 && *str2<=122)) || ((*str1>=97 && *str1 <=122) && (*str2>=65 && *str2<=90)))
				return 1;
		else if(*str1 == *str2)
			continue;
		else
			return 0;
	}
}
