#include "Flo.h"
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include<qinputdialog.h>
#include<qstring.h>
#include<qlineedit.h>
#pragma execution_character_set("utf-8")
using namespace std;
#define N 210
#define M 1000
struct Edge //�������
{
    int a, b, w;

}edges[M];

static const int INF = 0x3f3f3f3f;
int n, m;//������������
int g[N][N], path[N][N];//gΪ�ڽӾ���path�����ʾ�����յ�����Ҫ�������м��
unordered_map<int, QString> d; //����һ����������֮��ӳ���ɢ�б�

Flo::Flo(QWidget *parent)
	: QMainWindow(parent)
{
    
	ui.setupUi(this);
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(floBackSlot()));
    connect(ui.inButton, SIGNAL(clicked()), this, SLOT(inSlot()));
    connect(ui.searchButton, SIGNAL(clicked()), this, SLOT(searchSlot()));
}

//���������Ϣ
void Flo:: shuru()
{
    ui.textEdit->clear();
    bool flag = false;
    memset(g, 0x3f, sizeof g);

    n=QInputDialog::getInt(this, "�����������������n", "������n", 0, 0, N, 1, &flag);
    if (flag==false)
    {
        return;
    }
    ui.textEdit->insertPlainText("������Ϊ��"+QString::number(n)+"\n");
    m = QInputDialog::getInt(this, "���������������m", "����m", 0, 0, M, 1, &flag);
    if (flag == false)
    {
        return;
    }
    ui.textEdit->insertPlainText("����Ϊ��" + QString::number(m) + "\n");
    ui.textEdit->insertPlainText("������n����������(�����ֱ��)��\n");
    for (int i = 1; i <= n; i++)
    {
        QString cityname;
        cityname = QInputDialog::getText(this, "�������������", "��������",QLineEdit::Normal,"", & flag);
        if (flag == false)
        {
            return;
        }
        ui.textEdit->insertPlainText("("+QString::number(i)+")"+cityname + "\n");

        d[i] = cityname;
    }
    //ui.textEdit->clear();
    ui.textEdit->insertPlainText("��������������a,b,w,��ʾa���к�b����֮�����һ��ȨֵΪw�ıߣ�a,bΪ���б�ţ�\n");
    flag = false;
  
    for (int i = 0; i < m; i++)
    {
        int  a,b, w;
       
        a=QInputDialog::getInt(this, "�������һ������", "��һ������", 0, 0, N, 1, &flag);
        if (flag==false)
        {
            break;
        }
      /*  a = QInputDialog::getText(this, "�������һ������", "��һ������",QLineEdit::Normal,"", & flag);
        if (flag == false)
        {
            break;
        }*/
        
        flag = false;
        b = QInputDialog::getInt(this, "������ڶ�������", "�ڶ�������", 0, 0, N, 1, &flag);
        if (flag == false)
        {
            break;
        }
        flag = false;
        w = QInputDialog::getInt(this, "������Ȩֵw", "Ȩֵw", 0, 0, N, 1, &flag);
        if (flag == false)
        {
            break;
        }
        flag = false;
       
        /*g[a][b] = g[b][a] = min(g[a][b], w);*/
        g[a][b] = min(g[a][b], w); //����������ͼ
        //���������ͼ�Ļ�����д��g[a][b] = g[b][a] = min(g[a][b], w);
        path[a][b] = b; //��path�����е�ֵ��ʼ��Ϊ�յ��ֵ
        edges[i] = { a,b,w };
        //ui.textEdit->insertPlainText(d[a] + "��" + d[b] + "����" + QString::number(w) + "����\n");
    }
    ui.textEdit->clear();
}

//��ӡ������Ϣ
void Flo:: printCityInfo()
{
    
    ui.textEdit->insertPlainText("���е��б����£�����"+QString::number(n)+ "�����У�\n");
   
    for (int i = 1; i <= n; i++)
    {
        
        ui.textEdit->insertPlainText("(" + QString::number(i) + ")"+ d[i] + "   ");
        ui.textEdit->insertPlainText("\n");

    }

    for (int i = 0; i < m; i++)
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        ui.textEdit->insertPlainText(d[a]+"��"+d[b]+"����Ϊ"+ QString::number(w)+ "\n");
    }

}
void Flo:: floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (g[i][j] > g[i][k] + g[k][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                    path[i][j] = path[i][k];
                }
    //g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

void Flo:: query()
{

    ui.textEdit->clear();
 
    bool flag = false;

    for (int i = 1; i <= n; i++)
    {

        ui.textEdit->insertPlainText("(" + QString::number(i) + ")" + d[i] + "   ");
        ui.textEdit->insertPlainText("\n");

    }


    int s1 = QInputDialog::getInt(this, "���������1���", "����1���", 0, 1, n+1, 1, &flag);
    flag = false;
    int s2 = QInputDialog::getInt(this, "���������2���", "����2���", 0, 1, n+1, 1, &flag);
    flag = false;

    const int  num1 = s1;
    const int  num2 = s2;

    if (num1 > n || num1 < 1 || num2 > n || num2 < 1)
    {
        ui.textEdit->insertPlainText("����ĳ��б�Ų����ڣ�\n");
        ui.textEdit->insertPlainText("���б��ֻ����1-"+QString::number(n)+"֮�䣬���������룡\n");
        
    }
    else
    {
        if (num1 == num2)
        {
            g[num1][num2] = 0; //���ǹ涨�����е��Լ��ľ���Ϊ0
        }
        int t = g[num1][num2];
        if (num1 == num2)
        {
            ui.textEdit->insertPlainText(d[num1] + "��" +d[num2]+ "�ľ���Ϊ��"+QString::number(t)+"\n");
           
        }
        else if (t > INF / 2) 
        {
            ui.textEdit->insertPlainText(d[num1] + "��" +d[num2] + "֮�䲻����ͨ·��\n");

        } 
        else
        {
            int z = path[num1][num2];
            ui.textEdit->insertPlainText(d[num1] + "��" + d[num2] + "�����·��Ϊ��" + QString::number(num1));
            //cout << d[num1] << "��" << d[num2] << "�����·��Ϊ��" << num1;
            while (z != num2) //����ת��㲻���յ�ʱ��һֱѭ��
            {
                ui.textEdit->insertPlainText("->" + QString::number(z));
                //cout << "->" << z; //�����ת���
                z = path[z][num2]; //��z���³�z->num2����ת���
            }
            ui.textEdit->insertPlainText("->" + QString::number(num2)+"\n");

            ui.textEdit->insertPlainText(d[num1] + "��" + d[num2] + "�����·������Ϊ��" + QString::number(t)+"\n");

        }
    }
}

void Flo::inSlot()
{
    shuru(); 
    printCityInfo(); 
    floyd(); 
    
}
void Flo::searchSlot()
{
    printCityInfo();
    query();
}
void Flo::floBackSlot()
{
    emit floBackSignal();

}


Flo::~Flo()
{}
