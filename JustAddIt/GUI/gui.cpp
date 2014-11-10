//@author A0116781A
#include "gui.h"

using namespace std;

const QString GUI::WINDOW_ICON = "JustAddIt/JustAddIt_small.ico";
const QString GUI::TITLE = "JustAddIt";
const QString GUI::STYLESHEET_PUSHBUTTON = "QPushButton { border: 1px solid grey; border-radius: 5px; padding: 3px; background-color: #EFF8FF; color: black; }";
const QString GUI::STYLESHEET_LINEEDIT = "QLineEdit { border: 1px solid grey; border-radius: 5px; background-color: #EFF8FF; color: black; }";
const QString GUI::STYLESHEET_LINEEDIT_PLACEHOLDER = "QLineEdit { border: 1px solid grey; border-radius: 5px; background-color: #EFF8FF; color: blue; }";
const QString GUI::STYLESHEET_TEXTEDIT = "QTextEdit { border: 1px solid grey; border-radius: 5px; background-color: #EFF8FF; color: black; }";
const QString GUI::PLACEHOLDER_LINEEDIT = "add {task details}, search {keyword}, export, undo, redo, home, exit";

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//this->setWindowFlags(Qt::FramelessWindowHint);
	QIcon* icon = new QIcon(WINDOW_ICON);
	this->setWindowIcon(*icon);

	this->setWindowTitle(TITLE);

	ui.pushButton->setStyleSheet(STYLESHEET_PUSHBUTTON);
	ui.lineEdit->setStyleSheet(STYLESHEET_LINEEDIT_PLACEHOLDER);
	ui.textEdit->setStyleSheet(STYLESHEET_TEXTEDIT);

	ui.textEdit->setReadOnly(true);

	connect(ui.lineEdit, SIGNAL(textChanged()), ui.lineEdit, SLOT(setLineEditStyleSheet()));

	ui.lineEdit->setPlaceholderText(PLACEHOLDER_LINEEDIT);
	ui.lineEdit->setFocus();

	initProg();
}

GUI::~GUI()
{

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

void GUI::updateDisplay(vector<string> output) {
	ui.textEdit->clear();
	for(vector<string>::iterator iter = output.begin(); iter != output.end(); iter++) {
		QString string = QString::fromStdString(*iter);
		ui.textEdit->append(string);
	}
	return;
}

void GUI::setLineEditStyleSheet() {
	QString lineEditText = ui.lineEdit->text();

	if(isTextPlaceholder(lineEditText)) {
		ui.lineEdit->setStyleSheet(STYLESHEET_LINEEDIT_PLACEHOLDER);
	} else {
		ui.lineEdit->setStyleSheet(STYLESHEET_LINEEDIT);
	}
}

bool GUI::isTextPlaceholder(QString string) {
	if(string == PLACEHOLDER_LINEEDIT) {
		return true;
	}
	return false;
}
