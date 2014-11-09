//@author A0116781A
//
//-----------------------------------------------
//This is the GUI class. It is responsible for 
//the user interface of JustAddIt.
//
//Whenever the return key is pressed, the command
//typed in the command line will be sent to the 
//logic components to be parsed and executed.
//The output returned by the command execution is
//then displayed in the main text box.
//
//-----------------------------------------------

#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QWidget>
#include "ui_gui.h"
#include "stdafx.h"
#include "Executor.h"

class GUI : public QWidget
{
	Q_OBJECT
		
public:
	GUI(QWidget *parent = 0);
	~GUI();

private:
	Ui::GUIClass ui;
	
	static const QString title;

	void initProg(); 
	void updateDisplay(vector<string> output);

private slots:
	void on_pushButton_clicked();
};

#endif // GUI_H
