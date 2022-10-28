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
    ////��������ӱ���ͼ
    ui.pushButton->setShortcut(QKeySequence::InsertParagraphSeparator);  //���ÿ�ݼ�Ϊ���̵ġ��س�����
    ui.lineEdit->setText("admin");
    ui.lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));
    connect(ui.pushButton_2, &QPushButton::clicked, this, &QWidget::close);//�˳���¼����
    connect(ui.pushButton, &QPushButton::clicked, this, &Widget1::judge);//ǰ��menu����
    connect(&m1, SIGNAL(clickButton()), this, SLOT(backMainSlot()));//�ص���¼����
    connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(checkSlot()));
    
}

//void Widget1::paintEvent(QPaintEvent*)
//{
//    //QPainter painter(this);
//    //QPixmap pix;//����QPixmap�������ڼ���ͼƬ
//    //pix.load(":/new/prefix1/XuanWuGate.png");
//    //painter.drawPixmap(0, 0, this->width(), this->height(), pix);
//}

void Widget1::backMainSlot()
{
    m1.close();
    this->close();//����ʱ����menu���棬��ʾ��¼����
}

void Widget1::judge()
{
    //�ж������Ƿ���ȷ�������󵯳�����Ի���
    //QString���trimmed()������ʵ�֣�������ȥ���ַ���ǰ��Ŀհ��ַ���
    if (time==0)
    {
        this->close();
    }
    if (ui.lineEdit_2->text()==code)
    {
        this->hide();//ǰ��menu���棬���ص�¼����
        m1.show();
    }
    else
    {
        QMessageBox::warning(this, QString("���棡"), QString("�������"), QMessageBox::tr("ȷ��"));
        //������ݲ���λ���
        ui.label_3->setText("�㻹��" + QString::number(time) + "�λ��ᣡ");
        time--;
        ui.lineEdit_2->clear();
        ui.lineEdit->setFocus();//�ѹ�궨λ���û�����
    }
}

void Widget1::checkSlot()//�����������Ƿ�ɼ�
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
