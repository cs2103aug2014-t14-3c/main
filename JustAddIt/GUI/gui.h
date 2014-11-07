#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QWidget>
#include "ui_gui.h"
#include "stdafx.h"
#include "IReceiver.h"

class GUI : public QWidget
{
	Q_OBJECT
		
public:
	GUI(QWidget *parent = 0);
	~GUI();

private:
	Ui::GUIClass ui;

	void initProg(); 
	void updateTextEdit(std::vector<std::string> output);

private slots:
	void on_pushButton_clicked();
};

#endif // GUI_H
