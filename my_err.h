#ifndef ERROR_
#define ERROR_

#include<stdio.h>
#include<stdlib.h>


void my_err(const char *err_string, int line)
{
	fprintf(stderr, "line: %d", line);
	perror("opendir");
	exit(1);
}


#endif
