#pragma once
#include <QMainWindow>
#include "ui_Flo.h"

class Flo : public QMainWindow
{
	Q_OBJECT

public:
	Flo(QWidget *parent = nullptr);
	void shuru(); //输入城市信息
	void printCityInfo(); //打印城市信息
	void floyd(); //弗洛伊德算法
	void query(); //计算任意两个城市之间的最短路径
	~Flo();

private:
	
	Ui::FloClass ui;

public slots:
	void inSlot();
	void searchSlot();
	void floBackSlot();
signals:
	void floBackSignal();
		
};


