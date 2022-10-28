#pragma once

#include <QMainWindow>
#include "ui_enter1.h"

class enter1 : public QMainWindow
{
	Q_OBJECT

public:
	enter1(QWidget *parent = nullptr);
	~enter1();

private slots:
	void backSlot01();
	void outMinSlot();
	void outAllSlot();
	void anotherSlot();

private:
	Ui::enter1Class ui;
	bool flag = true;

signals:
	void clickBack01();
};
