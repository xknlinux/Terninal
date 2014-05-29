#ifndef MY_LS_
#define MY_LS_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include"My_Link.h"

#define TRUE 0
#define FAILURE -1

#define NO_PARAMETER 0
#define L_PARAMETER 1
#define A_PARAMETER 2
#define D_PARAMETER 4

extern int PARAMETER_MARK;

void my_err(const char *err_string, int line);
int Display_File(const char *cPath);
int Run_Function();
int Before_Running();
void My_Sort_Pre();
void Out_Put();
void My_Sort(int (*My_Strcmp)(ST_LINK*, ST_LINK*));
void print(ST_LINK *Node);
int Display_LL(struct stat buf, ST_LINK *p);
int Run_Function(int argc, char *argv[]);
int Switch_Function(const char *cPath);
int Display_DD(const char *cPath);

int Cmp_Name(ST_LINK *p1, ST_LINK *p2);
int Cmp_Size(ST_LINK *p1, ST_LINK *p2);

void readme();
#endif
