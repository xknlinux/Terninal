ls:Get_Environment.o main.o My_Link.o My_Ls.o
	gcc -o ls Get_Environment.o main.o My_Link.o My_Ls.o

main.o:main.c My_Ls.h My_Link.h
	gcc -c main.c

Get_Environment.o:Get_Environment.c My_Link.h
	gcc -c Get_Environment.c

My_Link.o:My_Link.c My_Link.h my_err.h
	gcc -c My_Link.c

My_Ls.o:My_Link.h My_Ls.h
	gcc -c My_Ls.c

clean:
	rm Get_Environment.o main.o My_Link.o My_Ls.o
