#include "calculation1.h"
#include<QMessageBox>

calculation1::calculation1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(backSlot03()));

    connect(ui.pushButton_2, &QPushButton::clicked, this, &calculation1::toTreeSlot);

    connect(ui.pushButton_3, &QPushButton::clicked, this, &calculation1::toFloSlot);
    
    connect(ui.pushButton_4, &QPushButton::clicked, this, &calculation1::toInheritanceSlot);

    connect(&t1, SIGNAL(clickBackCal()), this, SLOT(backCalSlot()));

    connect(&f1, SIGNAL(floBackSignal()), this, SLOT(fbackCalSlot()));

    connect(&inher1, SIGNAL(inherBackCal()), this, SLOT(ibackCalSlot()));
}

void calculation1::toTreeSlot()
{

    this->hide();//隐藏calculation界面，显示Tree界面
    t1.show();
}

void calculation1::toFloSlot()
{
    this->hide();//隐藏calculation界面，显示Flo界面
    f1.show();
    
}


void calculation1::toInheritanceSlot()
{
    this->hide();
    inher1.show();

}
void calculation1::backCalSlot()
{
    t1.hide();
    this->show();
}
void calculation1::fbackCalSlot()
{
    f1.hide();
    this->show();

}
void calculation1::ibackCalSlot()
{
    inher1.hide();
    this->show();
}







void calculation1::backSlot03()
{
	emit clickBack03();
}

calculation1::~calculation1()
{}
