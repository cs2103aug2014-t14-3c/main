#include "gui.h"

using namespace std;

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//this->setWindowFlags(Qt::FramelessWindowHint);

	ui.pushButton->setStyleSheet("QPushButton { border: 1px solid white; border-radius: 5px; padding: 3px; background-color: #EFF8FF; color: black; }");
	ui.lineEdit->setStyleSheet("QLineEdit { border: 1px solid white; border-radius: 5px; background-color: #EFF8FF; color: black; }");
	ui.textEdit->setStyleSheet("QTextEdit { border: 1px solid black; border-radius: 5px; background-color: #EFF8FF; color: black; }");

	ui.textEdit->setReadOnly(true);

	ui.lineEdit->setFocus();

	initProg();
}

GUI::~GUI()
{

}

void GUI::updateDisplay(vector<string> output) {
	ui.textEdit->clear();
	for(vector<string>::iterator iter = output.begin(); iter != output.end(); iter++) {
		QString string = QString::fromStdString(*iter);
		ui.textEdit->append(string);
	}
	return;
}

void GUI::initProg() {
	vector<string> output = IReceiver::initialise();

	updateDisplay(output);
}

void GUI::on_pushButton_clicked() {
	QString qs = ui.lineEdit->text();
	string str = qs.toLocal8Bit().constData();

	if(qs == "exit") {
		exit(0);
	}
	
	vector<string> output;
	output.clear();

	output = IReceiver::receive(str);

	updateDisplay(output);
	
	ui.lineEdit->clear();

}