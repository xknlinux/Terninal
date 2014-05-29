#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QDialog>

class QLabel;
class QLineEdit;

class Terminal:public QDialog
{
	Q_OBJECT
	
	public:
		Terminal();
	private:
		void CreateAction();
		void Setup_Layout();
		void Run_Ls();

		QLabel *DisplayWindow;
		QLineEdit *InputWindow;
};


#endif
