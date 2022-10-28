#pragma once

#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include "ui_find1.h"

class find1 : public QMainWindow
{
	Q_OBJECT

public:
	find1(QWidget *parent = nullptr);
	
	~find1();
	

private slots:
	void backSlot02();
	void judge02();
	void totalSlot();
	void baseSlot();
	void lineSlot();

private:
	Ui::find1Class ui;
	int baseNum = 223349;
	double baseMoney = 40 * baseNum;//万元
	int minlen = 635;
	double lineMoney = minlen * 0.0960;//万元
	double totalMoney = baseMoney+ lineMoney;
	QString Name[10] = { "南京","镇江","扬州","淮安","马鞍山","滁州","芜湖","宣城","溧阳","金坛" };
	int Dt[10][10] = { { 0,61,69,209,51,53,86,141,120,84 },
						{ 61,0,130,270,112,114,147,202,181,145 },
						{ 69,130,0,140,120,122,155,210,189,153 },
						{ 209,270,140,0,260,262,295,350,329,293 },
						{ 51,112,120,260,0,104,137,192,171,135 },
						{ 53,114,122,262,104,0,139,194,173,137 },
						{ 86,147,155,295,137,139,0,55,206,170 },
						{ 141,202,210,350,192,194,55,0,261,225 },
						{ 120,181,189,329,171,173,206,261,0,36 },
						{ 84,145,153,293,135,137,170,225,36,0 } };
	

signals :
	void clickBack02();
};
