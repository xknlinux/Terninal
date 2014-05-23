#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	struct stat p;
	stat(argv[1],&p);
	if(S_ISDIR(p.st_mode))
	{
		printf("Dir\n");
	}
	if(S_ISREG(p.st_mode))
	{
		printf("file\n");
	}
}
