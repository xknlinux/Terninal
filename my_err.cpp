#include<stdio.h>
#include<stdlib.h>

#include"my_err.h"

void my_err(const char *err_string, int line)
{
	fprintf(stderr, "line: %d", line);
	perror("opendir");
	exit(1);
}

