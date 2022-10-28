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
	void backSlot03();//返回

	void toTreeSlot();//去最小代价生成树

	void toFloSlot();//去最短路径

	void toInheritanceSlot();//去覆盖率

	void backCalSlot();

	void fbackCalSlot();

	void ibackCalSlot();
signals:
	void clickBack03();

};
