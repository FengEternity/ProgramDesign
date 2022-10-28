#include "enter1.h"
#include<qfiledialog.h>
enter1::enter1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QString path = "C:\\Users\\86173\\Desktop\\Widget1\\Widget1\\all.jpg";  // 定义图片的路径
	QPixmap img(path); // 实例化一个img
	ui.label->setPixmap(img); // 在label中添加img
	ui.label->resize(img.width(), img.height());  // 使用图片尺寸设置label大小
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(backSlot01()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(outMinSlot()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(outAllSlot()));
	connect(ui.another, SIGNAL(clicked()), this, SLOT(anotherSlot()));

}

void enter1::backSlot01()
{
	emit clickBack01();
}


void enter1::outMinSlot()
{
	QString path_image = "C:\\Users\\86173\\Desktop\\Widget1\\Widget1\\min.jpg";
	QPixmap img(path_image);
	QString path = QFileDialog::getSaveFileName(this, "save", "D:\\", "jFiles(*.jpg *.png)");
	img.save(path);

}
void enter1::outAllSlot()
{
	QString path_image = "C:\\Users\\86173\\Desktop\\Widget1\\Widget1\\all.jpg";
	QPixmap img(path_image);
	QString path = QFileDialog::getSaveFileName(this, "save", "D:\\", "jFiles(*.jpg *.png)");
	img.save(path);
}
void enter1::anotherSlot()
{
	if (flag==true)
	{
		QString path = "C:\\Users\\86173\\Desktop\\Widget1\\Widget1\\min.jpg";  
		QPixmap img(path);
		ui.label->setPixmap(img); 
		ui.label->resize(img.width(), img.height());
		flag = false;
	}
	else
	{
		QString path = "C:\\Users\\86173\\Desktop\\Widget1\\Widget1\\all.jpg";
		QPixmap img(path);
		ui.label->setPixmap(img);
		ui.label->resize(img.width(), img.height());
		flag = true;
	}
	
}

enter1::~enter1()
{}
