#include<QMainWindow>
#include<QLabel>
#include<QLineEdit>
#include<QVBoxLayout>

#include"Terminal.h"

Terminal::Terminal()
{
	CreateAction();
	Setup_Layout();

	this -> setFixedSize(800,600);
	Run_Ls();
}

void Terminal::Run_Ls()
{

}

void Terminal::CreateAction()
{
	DisplayWindow = new QLabel();

	InputWindow = new QLineEdit;
}

void Terminal::Setup_Layout()
{
	QVBoxLayout *Window = new QVBoxLayout;
	Window->addWidget(InputWindow);
	Window->addWidget(DisplayWindow);

	setLayout(Window);
}
