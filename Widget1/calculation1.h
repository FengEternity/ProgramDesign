#pragma once
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "ui_calculation1.h"
#include"Tree.h"
#include "Flo.h"
#include"inheritance1.h"
class calculation1 : public QMainWindow
{
	Q_OBJECT

public:
	calculation1(QWidget *parent = nullptr);
	Tree t1;
	Flo f1;
	inheritance1 inher1;
	~calculation1();

private:
	Ui::calculation1Class ui;

private slots:
	void backSlot03();//����

	void toTreeSlot();//ȥ��С����������

	void toFloSlot();//ȥ���·��

	void toInheritanceSlot();//ȥ������

	void backCalSlot();

	void fbackCalSlot();

	void ibackCalSlot();
signals:
	void clickBack03();

};
