//@author A0116781A
#include "gui.h"

using namespace std;

const QString GUI::TITLE = "JustAddIt";
const QString GUI::STYLESHEET_PUSHBUTTON = "QPushButton { border: 1px solid grey; border-radius: 5px; padding: 3px; background-color: #EFF8FF; color: black; }";
const QString GUI::STYLESHEET_LINEEDIT = "QLineEdit { border: 1px solid grey; border-radius: 5px; background-color: #EFF8FF; color: black; }";
const QString GUI::STYLESHEET_TEXTEDIT = "QTextEdit { border: 1px solid grey; border-radius: 5px; background-color: #EFF8FF; color: black; }";

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowTitle(TITLE);

	ui.pushButton->setStyleSheet(STYLESHEET_PUSHBUTTON);
	ui.lineEdit->setStyleSheet(STYLESHEET_LINEEDIT);
	ui.textEdit->setStyleSheet(STYLESHEET_TEXTEDIT);

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
	vector<string> output = Executor::initialise();
	//RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 'J');
	updateDisplay(output);
}

void GUI::on_pushButton_clicked() {
	QString qs = ui.lineEdit->text();
	string str = qs.toLocal8Bit().constData();
	
	vector<string> output;
	output.clear();

	output = Executor::execute(str);

	updateDisplay(output);
	
	ui.lineEdit->clear();

}