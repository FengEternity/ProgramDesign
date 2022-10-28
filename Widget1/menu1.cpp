#include "menu1.h"

menu1::menu1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(changeSlot()));//返回登录界面

	connect(ui.pushButton, &QPushButton::clicked, this, &menu1::toEnterSlot);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &menu1::toFindSlot);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &menu1::toCalSlot);

	connect(&e1, SIGNAL(clickBack01()), this, SLOT(toMenuSlot01()));
	connect(&f1, SIGNAL(clickBack02()), this, SLOT(toMenuSlot02()));
	connect(&c1, SIGNAL(clickBack03()), this, SLOT(toMenuSlot03()));
}

void menu1::changeSlot()
{
	emit clickButton();//发出返回登录界面的信号
}

void menu1::toEnterSlot()
{
	this->hide();//隐藏menu界面，显示Enter界面
	e1.show();
}

void menu1::toFindSlot()
{
	this->hide();//隐藏menu界面，显示Find界面
	f1.show();
}

void menu1::toCalSlot()
{
	this->hide();//隐藏menu界面，显示Calculation界面
	c1.show();
}

void menu1::toMenuSlot01() 
{
	e1.hide();
	this->show();
}

void menu1::toMenuSlot02()
{
	f1.hide();
	this->show();
}

void menu1::toMenuSlot03()
{
	c1.hide();
	this->show();
}

menu1::~menu1()
{}
