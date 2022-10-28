#pragma once

#include <QMainWindow>
#include "ui_Tree.h"

class Tree : public QMainWindow
{
	Q_OBJECT

public:
	Tree(QWidget *parent = nullptr);
	void Create(struct EdgeGraph* MyEdgeGraph);
	void WayToAchieve(struct EdgeGraph* MyEdgeGraph);   //算法实现函数
	void init();
	int FindRoot(int Parent[], int v);                   //寻找各连通分量根的函数
	~Tree();

private:
	Ui::TreeClass ui;
	EdgeGraph* MyEdgeGraph1;
	
private slots:
	void Link();
	
	void toCal();

signals:
	void clickBackCal();
};
