ls:Get_Environment.o main.o My_Link.o My_Ls.o
	g++ -o ls Get_Environment.o main.o My_Link.o My_Ls.o my_err.o

main.o:main.cpp My_Ls.h My_Link.h
	g++ -c main.cpp

Get_Environment.o:Get_Environment.cpp My_Link.h my_err.h
	g++ -c Get_Environment.cpp

My_Link.o:My_Link.cpp My_Link.h my_err.h
	g++ -c My_Link.cpp

My_Ls.o:My_Ls.cpp My_Link.h My_Ls.h
	g++ -c My_Ls.cpp

my_err.o:my_err.cpp my_err.h
	g++ -c my_err.cpp
clean:
	rm Get_Environment.o main.o My_Link.o My_Ls.o
