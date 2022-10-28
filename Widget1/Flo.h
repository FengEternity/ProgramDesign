#pragma once
#include <QMainWindow>
#include "ui_Flo.h"

class Flo : public QMainWindow
{
	Q_OBJECT

public:
	Flo(QWidget *parent = nullptr);
	void shuru(); //���������Ϣ
	void printCityInfo(); //��ӡ������Ϣ
	void floyd(); //���������㷨
	void query(); //����������������֮������·��
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


