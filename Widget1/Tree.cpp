#include "Tree.h"
#include<qinputdialog.h>
#include<iostream>
#include<qstring.h>
#include<qdebug.h>
#pragma execution_character_set("utf-8")
using namespace std;

struct EdgeType                                     //����ͼ�бߵ���Ϣ�Ľṹ��
{
	int from, to;
	int Weight;
};
struct EdgeGraph                                    //��������ͼ�ж��㡢�ߵ�������Ϣ����Ҫ��ǰ��ߵĽṹ�����ݵ���˽ṹ��
{
	int Vertex[100];                            //�������飬������󶥵����ͱ���������100
	EdgeType Edge[100];                         //����Ϣ�Ľṹ������
	int VertexNum, EdgeNum;                     //������������
};

Tree::Tree(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.start, SIGNAL(clicked()), this, SLOT(Link()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(toCal()));

}




//void Tree::Create(struct EdgeGraph* MyEdgeGraph);        //����ͼ�ĺ�������
//void WayToAchieve(struct EdgeGraph* MyEdgeGraph);   //�㷨ʵ�ֺ���
//int FindRoot(int Parent[], int v);                   //Ѱ�Ҹ���ͨ�������ĺ���

void Tree::Link()
{
	init();
	Create(MyEdgeGraph1);         //����ͼ�ĺ�������
	WayToAchieve(MyEdgeGraph1);
	//int FindRoot(int Parent[], int v);                   //Ѱ�Ҹ���ͨ�������ĺ���
}



void Tree::Create(struct EdgeGraph* MyEdgeGraph)
{
	int Vertex, Edge, Weight;
	bool flag = false;

	Vertex = QInputDialog::getInt(this, "����������ͼ�Ķ�����", "����ͼ�Ķ�����", 0, 0, 100, 1, &flag);
	if (flag == false)
	{
		return;
	}

	Edge = QInputDialog::getInt(this, "����������ͼ�ı���", "����ͼ�ı���", 0, 0, 100, 1, &flag);
	if (flag == false)
	{
		return;
	}

	EdgeType* MyEdge = new EdgeType[Edge];             //�����û�Ҫ�������ı���Ϣ�ṹ������
	if (!MyEdge)
	{
		exit(100);
	}
	for (int i = 0; i < Edge; i++) {                   //�߽ṹ������ĳ�ʼ��
		MyEdge[i].from = QInputDialog::getInt(this, "������ڵ�1", "�ڵ�1", 0, 0, 100, 1, &flag);
		if (flag==false)
		{
			return;
		}
		MyEdge[i].to = QInputDialog::getInt(this, "������ڵ�2", "�ڵ�2", 0, 0, 100, 1, &flag);
		if (flag == false)
		{
			return;
		}
		MyEdge[i].Weight = QInputDialog::getDouble(this, "��������Ȩ��", "Ȩ��", 0, 0, 9999999, 1, &flag);
		if (flag == false)
		{
			return;
		}
		ui.textEdit->insertPlainText(QString::number(MyEdge[i].from)+"<->"+ QString::number(MyEdge[i].to)+"ȨֵΪ��"+ QString::number(MyEdge[i].Weight) + "\n");
	}
	for (int i = 0; i < Edge; i++) {                   //���ݸ��ߵ�Ȩֵ������������
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
		(*MyEdgeGraph).Edge[i] = MyEdge[i];                //���ߵ���Ϣ�ṹ�嵼��ͼ����Ϣ�ṹ��
	}
	for (int i = 0; i < Vertex; i++) {
		(*MyEdgeGraph).Vertex[i] = i;                     //��ʼ��ͼ�ṹ��Ķ�������
	}
}

void Tree::WayToAchieve(struct EdgeGraph* MyEdgeGraph)
{
	ui.textEdit->clear();
	int num = 0, i = 0, v1, v2;
	QString out="";
	int* root = new int[(*MyEdgeGraph).VertexNum];        //����������������ʼ��
	for (int i = 0; i < (*MyEdgeGraph).VertexNum; i++) {
		root[i] = -1;
	}
	ui.textEdit->insertPlainText("����С����������Ϊ��\n");
	for (num = 0, i = 0; i < (*MyEdgeGraph).EdgeNum; i++) {      //���ζ�ÿ���߽��б�����num��¼����ߵĸ���
		v1 = FindRoot(root, (*MyEdgeGraph).Edge[i].from);    //�ֱ�Ѱ��v1,v2������ͨ�����ĸ�
		v2 = FindRoot(root, (*MyEdgeGraph).Edge[i].to);
		if (v1 != v2) {                                     //������ڲ�ͬ����ͨ�����ͺϲ�
			
			out = "(" + QString::number((*MyEdgeGraph).Edge[i].from) + "," + QString::number((*MyEdgeGraph).Edge[i].to) + ")\n";
			ui.textEdit->insertPlainText(out);
			root[v2] = v1;                                 //�ϲ�
			num++;                                         //��¼ѡ��ߵĸ���
			if (num == (*MyEdgeGraph).VertexNum - 1) {     //���ѡ��ıߴ������ڶ�����-1��֤����С���Ѿ����ɣ�������������
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
	while (Parent[v1] > -1) {         //��ͣѭ���Ҹ�
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
