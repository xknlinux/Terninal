#include<QApplication>

#include"Terminal.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Terminal *a = new Terminal();
	a->show();

	return app.exec();
}
