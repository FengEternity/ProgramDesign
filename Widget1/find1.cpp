#include "find1.h"
#include<QmessageBox>
#include<qdebug.h>
#include<qtextedit.h>
find1::find1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(backSlot02()));

    connect(ui.pushButton_2, &QPushButton::clicked, this, &find1::judge02);

    connect(ui.pushButton_5, &QPushButton::clicked, this, &find1::totalSlot);

    connect(ui.pushButton_3, &QPushButton::clicked,this, &find1::baseSlot);

    connect(ui.pushButton_4, &QPushButton::clicked, this, &find1::lineSlot);
}

void find1::judge02()
{
   
    ui.textEdit->clear();
    int index1 = -1;
    int index2 = -1;
    int money=0;
    QString city1 = ui.comboBox_1->currentText();
    QString city2 = ui.comboBox_2->currentText();
    for (size_t i = 0; i < 10; i++)
    {
        if (city1==Name[i])
        {
            index1 = i;
        }
        if (city2 == Name[i])
        {
            index2 = i;
        }

    }
    ui.textEdit->insertPlainText(city1+"��"+city2+"����Ϊ:"+QString::number(Dt[index1][index2])+"����\n");
    ui.textEdit->insertPlainText(city1+"��" + city2 + "�������Ϊ��" + QString::number((double)Dt[index1][index2] * 960/10000) + "��Ԫ\n");



  
}

void find1::backSlot02()
{
	emit clickBack02();
}
void find1::totalSlot()
{
    ui.textEdit->clear();
    ui.textEdit->insertPlainText("�Ͼ�����Ȧ���˺�5G��վ�����Ϊ��"+QString::number(totalMoney/10000)+"��Ԫ\n");

}
void find1::baseSlot()
{
    ui.textEdit->clear();
    ui.textEdit->insertPlainText("�Ͼ�����Ȧ5G��վ����Ϊ��" + QString::number(baseNum) + "��\n");
    ui.textEdit->insertPlainText("�Ͼ�����Ȧ5G��վ�����Ϊ��" + QString::number(baseMoney/10000) + "��Ԫ\n");


}
void find1::lineSlot()
{
    ui.textEdit->clear();
    ui.textEdit->insertPlainText("�Ͼ�����Ȧ���������Ϊ��"+ QString::number(lineMoney)+"��Ԫ");
}

find1::~find1()
{}
