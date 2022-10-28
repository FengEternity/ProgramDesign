#include "Tree.h"
#include<qinputdialog.h>
#include<iostream>
#include<qstring.h>
#include<qdebug.h>
#pragma execution_character_set("utf-8")
using namespace std;

struct EdgeType                                     //关于图中边的信息的结构体
{
	int from, to;
	int Weight;
};
struct EdgeGraph                                    //关于整个图中顶点、边的所有信息，需要将前面边的结构体内容导入此结构体
{
	int Vertex[100];                            //顶点数组，假设最大顶点数和边数不超过100
	EdgeType Edge[100];                         //边信息的结构体数组
	int VertexNum, EdgeNum;                     //顶点数、边数
};

Tree::Tree(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.start, SIGNAL(clicked()), this, SLOT(Link()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(toCal()));

}




//void Tree::Create(struct EdgeGraph* MyEdgeGraph);        //构造图的函数函数
//void WayToAchieve(struct EdgeGraph* MyEdgeGraph);   //算法实现函数
//int FindRoot(int Parent[], int v);                   //寻找各连通分量根的函数

void Tree::Link()
{
	init();
	Create(MyEdgeGraph1);         //构造图的函数函数
	WayToAchieve(MyEdgeGraph1);
	//int FindRoot(int Parent[], int v);                   //寻找各连通分量根的函数
}



void Tree::Create(struct EdgeGraph* MyEdgeGraph)
{
	int Vertex, Edge, Weight;
	bool flag = false;

	Vertex = QInputDialog::getInt(this, "请输入无向图的顶点数", "无向图的顶点数", 0, 0, 100, 1, &flag);
	if (flag == false)
	{
		return;
	}

	Edge = QInputDialog::getInt(this, "请输入无向图的边数", "无向图的边数", 0, 0, 100, 1, &flag);
	if (flag == false)
	{
		return;
	}

	EdgeType* MyEdge = new EdgeType[Edge];             //申请用户要求数量的边信息结构体数组
	if (!MyEdge)
	{
		exit(100);
	}
	for (int i = 0; i < Edge; i++) {                   //边结构体数组的初始化
		MyEdge[i].from = QInputDialog::getInt(this, "请输入节点1", "节点1", 0, 0, 100, 1, &flag);
		if (flag==false)
		{
			return;
		}
		MyEdge[i].to = QInputDialog::getInt(this, "请输入节点2", "节点2", 0, 0, 100, 1, &flag);
		if (flag == false)
		{
			return;
		}
		MyEdge[i].Weight = QInputDialog::getDouble(this, "请输入其权重", "权重", 0, 0, 9999999, 1, &flag);
		if (flag == false)
		{
			return;
		}
		ui.textEdit->insertPlainText(QString::number(MyEdge[i].from)+"<->"+ QString::number(MyEdge[i].to)+"权值为："+ QString::number(MyEdge[i].Weight) + "\n");
	}
	for (int i = 0; i < Edge; i++) {                   //依据各边的权值进行重新排序
		for (int j = i + 1; j < Edge; j++) {
			if (MyEdge[i].Weight > MyEdge[j].Weight) {
				EdgeType Temp;
				Temp = MyEdge[i];
				MyEdge[i] = MyEdge[j];
				MyEdge[j] = Temp;
			}
		}
	}
	(*MyEdgeGraph).VertexNum = Vertex;
	(*MyEdgeGraph).EdgeNum = Edge;
	for (int i = 0; i < Edge; i++) {
		(*MyEdgeGraph).Edge[i] = MyEdge[i];                //将边的信息结构体导入图的信息结构体
	}
	for (int i = 0; i < Vertex; i++) {
		(*MyEdgeGraph).Vertex[i] = i;                     //初始化图结构体的顶点数组
	}
}

void Tree::WayToAchieve(struct EdgeGraph* MyEdgeGraph)
{
	ui.textEdit->clear();
	int num = 0, i = 0, v1, v2;
	QString out="";
	int* root = new int[(*MyEdgeGraph).VertexNum];        //创建辅助函数并初始化
	for (int i = 0; i < (*MyEdgeGraph).VertexNum; i++) {
		root[i] = -1;
	}
	ui.textEdit->insertPlainText("该最小代价生成树为：\n");
	for (num = 0, i = 0; i < (*MyEdgeGraph).EdgeNum; i++) {      //依次对每个边进行遍历，num记录输出边的个数
		v1 = FindRoot(root, (*MyEdgeGraph).Edge[i].from);    //分别寻找v1,v2所在连通分量的根
		v2 = FindRoot(root, (*MyEdgeGraph).Edge[i].to);
		if (v1 != v2) {                                     //如果所在不同的连通分量就合并
			
			out = "(" + QString::number((*MyEdgeGraph).Edge[i].from) + "," + QString::number((*MyEdgeGraph).Edge[i].to) + ")\n";
			ui.textEdit->insertPlainText(out);
			root[v2] = v1;                                 //合并
			num++;                                         //记录选择边的个数
			if (num == (*MyEdgeGraph).VertexNum - 1) {     //如果选择的边次数等于顶点数-1则证明最小树已经生成，结束函数调用
				return;
			}
		}
	}
}

void Tree::init()
{
	MyEdgeGraph1 = new EdgeGraph;
}

int Tree::FindRoot(int Parent[], int v)
{
	int v1 = v;
	while (Parent[v1] > -1) {         //不停循环找根
		v1 = Parent[v1];
	}
	return v1;
}




void Tree::toCal()
{
	emit clickBackCal();
}



Tree::~Tree()
{}
