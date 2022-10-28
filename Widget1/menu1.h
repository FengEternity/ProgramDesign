#pragma once

#include <QMainWindow>
#include "ui_menu1.h"
#include"enter1.h"
#include"find1.h"
#include"calculation1.h"

class menu1 : public QMainWindow
{
	Q_OBJECT

public:
	menu1(QWidget *parent = nullptr);
	enter1 e1;
	find1 f1;
	calculation1 c1;
	~menu1();

private:
	Ui::menu1Class ui;
private slots:
	void changeSlot();

	void toEnterSlot();
	void toFindSlot();
	void toCalSlot();

	void toMenuSlot01();
	void toMenuSlot02();
	void toMenuSlot03();

signals:
	void clickButton();
};
