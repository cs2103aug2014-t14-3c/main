#include "gui.h"

using namespace std;

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::FramelessWindowHint);
	this->resize(700, 500);

	ui.lineEdit->setStyleSheet("QLineEdit { border: 1px solid white; border-radius: 5px; background-color: black; color: white; }");
	ui.textEdit->setStyleSheet("QTextEdit { border: 1px solid white; border-radius: 5px; background-color: black; color: white; }");

	ui.textEdit->setReadOnly(true);

	ui.lineEdit->setFocus();

	initProg();
}

GUI::~GUI()
{

}

void GUI::updateTextEdit(vector<string> output) {
	ui.textEdit->clear();
	for(vector<string>::iterator iter = output.begin(); iter != output.end(); iter++) {
		QString string = QString::fromStdString(*iter);
		ui.textEdit->append(string);
	}
	return;
}

void GUI::initProg() {
	vector<string> output = IReceiver::initialise();

	updateTextEdit(output);
}

void GUI::on_pushButton_clicked() {
	QString qs = ui.lineEdit->text();
	string str = qs.toLocal8Bit().constData();

	if(!qs.isEmpty()) {
		if(qs == "exit") {
			exit(0);
		}

		vector<string> output = IReceiver::receive(str);

		updateTextEdit(output);
	
		ui.lineEdit->clear();
	}
}