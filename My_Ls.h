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

#define FILE_ 1
#define DIR_ 2
#define LINK_ 3
#define BLOCK_ 4
#define FIFO_ 5
#define SOCKET_ 6



int PARAMETER_MARK;

void my_err(const char *err_string, int line);
void Display_File();
int Display_File_Data(const char *cPath);
int Run_Function();
int Before_Running();
void Shine_Upon(char cCharacter);
void Out_Put();
void My_Sort();
void print(ST_LINK *Node);
void D_NoL();
int Da_Xiao();
int Display_LL(struct stat buf, ST_LINK *p);

#endif
