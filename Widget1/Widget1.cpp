#include "Widget1.h"
#include"qpushbutton.h"
#include <QMessageBox>
#include<qpainter.h>
#include<qlabel.h>
Widget1::Widget1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //setWindowIcon(QIcon(":/new/prefix1/biaozhi_PNG.png"));
    ////给窗口添加背景图
    ui.pushButton->setShortcut(QKeySequence::InsertParagraphSeparator);  //设置快捷键为键盘的“回车”键
    ui.lineEdit->setText("admin");
    ui.lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));
    connect(ui.pushButton_2, &QPushButton::clicked, this, &QWidget::close);//退出登录界面
    connect(ui.pushButton, &QPushButton::clicked, this, &Widget1::judge);//前往menu界面
    connect(&m1, SIGNAL(clickButton()), this, SLOT(backMainSlot()));//回到登录界面
    connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(checkSlot()));
    
}

//void Widget1::paintEvent(QPaintEvent*)
//{
//    //QPainter painter(this);
//    //QPixmap pix;//创建QPixmap对象，用于加载图片
//    //pix.load(":/new/prefix1/XuanWuGate.png");
//    //painter.drawPixmap(0, 0, this->width(), this->height(), pix);
//}

void Widget1::backMainSlot()
{
    m1.close();
    this->close();//返回时隐藏menu界面，显示登录界面
}

void Widget1::judge()
{
    //判断密码是否正确，若错误弹出警告对话框
    //QString类的trimmed()函数来实现，它可以去除字符串前后的空白字符。
    if (time==0)
    {
        this->close();
    }
    if (ui.lineEdit_2->text()==code)
    {
        this->hide();//前往menu界面，隐藏登录界面
        m1.show();
    }
    else
    {
        QMessageBox::warning(this, QString("警告！"), QString("密码错误！"), QMessageBox::tr("确定"));
        //清空内容并定位光标
        ui.label_3->setText("你还有" + QString::number(time) + "次机会！");
        time--;
        ui.lineEdit_2->clear();
        ui.lineEdit->setFocus();//把光标定位至用户名处
    }
}

void Widget1::checkSlot()//设置密码栏是否可见
{
    if (ui.checkBox->checkState())
    {
        ui.lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui.lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}


Widget1::~Widget1()
{}
