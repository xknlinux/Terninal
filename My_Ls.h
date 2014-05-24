#ifndef MY_LS_
#define MY_LS_

#define TRUE 0
#define FAILURE -1

#define NO_PARAMETER 0
#define L_PARAMETER 1
#define A_PARAMETER 2
#define D_PARAMETER 4

void my_err(const char *err_string, int line);
void Display_File();
int Display_File_Data(const char *cPath);
int Run_Function();
int Before_Running();
void Shine_Upon(char cCharacter);
void Out_Put();

#endif
