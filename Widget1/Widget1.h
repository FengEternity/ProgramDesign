#pragma once

#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_Widget1.h"
#include"menu1.h"
class Widget1 : public QMainWindow
{
    Q_OBJECT

public:
    Widget1(QWidget *parent = nullptr);
    menu1 m1; //����menu��Ķ���
    //void paintEvent(QPaintEvent*);//����Event�¼����Ʊ���ͼ

    ~Widget1();

private:
    Ui::Widget1Class ui;
    QString code = "123456";
    int time = 5;

private slots:
    void backMainSlot();
    void judge();
    void checkSlot();

};