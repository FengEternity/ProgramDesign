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
struct Edge //用来存边
{
    int a, b, w;

}edges[M];

static const int INF = 0x3f3f3f3f;
int n, m;//城市数，边数
int g[N][N], path[N][N];//g为邻接矩阵，path矩阵表示到达终点所需要经过的中间点
unordered_map<int, QString> d; //建立一个序号与城市之间映射的散列表

Flo::Flo(QWidget *parent)
	: QMainWindow(parent)
{
    
	ui.setupUi(this);
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(floBackSlot()));
    connect(ui.inButton, SIGNAL(clicked()), this, SLOT(inSlot()));
    connect(ui.searchButton, SIGNAL(clicked()), this, SLOT(searchSlot()));
}

//输入城市信息
void Flo:: shuru()
{
    ui.textEdit->clear();
    bool flag = false;
    memset(g, 0x3f, sizeof g);

    n=QInputDialog::getInt(this, "请输入请输入城市数n", "城市数n", 0, 0, N, 1, &flag);
    if (flag==false)
    {
        return;
    }
    ui.textEdit->insertPlainText("城市数为："+QString::number(n)+"\n");
    m = QInputDialog::getInt(this, "请输入请输入边数m", "边数m", 0, 0, M, 1, &flag);
    if (flag == false)
    {
        return;
    }
    ui.textEdit->insertPlainText("边数为：" + QString::number(m) + "\n");
    ui.textEdit->insertPlainText("请输入n个城市名称(用数字编号)：\n");
    for (int i = 1; i <= n; i++)
    {
        QString cityname;
        cityname = QInputDialog::getText(this, "请输入城市名称", "城市名称",QLineEdit::Normal,"", & flag);
        if (flag == false)
        {
            return;
        }
        ui.textEdit->insertPlainText("("+QString::number(i)+")"+cityname + "\n");

        d[i] = cityname;
    }
    //ui.textEdit->clear();
    ui.textEdit->insertPlainText("请输入三个整数a,b,w,表示a城市和b城市之间存在一条权值为w的边（a,b为城市编号）\n");
    flag = false;
  
    for (int i = 0; i < m; i++)
    {
        int  a,b, w;
       
        a=QInputDialog::getInt(this, "请输入第一个城市", "第一个城市", 0, 0, N, 1, &flag);
        if (flag==false)
        {
            break;
        }
      /*  a = QInputDialog::getText(this, "请输入第一个城市", "第一个城市",QLineEdit::Normal,"", & flag);
        if (flag == false)
        {
            break;
        }*/
        
        flag = false;
        b = QInputDialog::getInt(this, "请输入第二个城市", "第二个城市", 0, 0, N, 1, &flag);
        if (flag == false)
        {
            break;
        }
        flag = false;
        w = QInputDialog::getInt(this, "请输入权值w", "权值w", 0, 0, N, 1, &flag);
        if (flag == false)
        {
            break;
        }
        flag = false;
       
        /*g[a][b] = g[b][a] = min(g[a][b], w);*/
        g[a][b] = min(g[a][b], w); //这里是有向图
        //如果是无向图的话可以写成g[a][b] = g[b][a] = min(g[a][b], w);
        path[a][b] = b; //将path矩阵中的值初始化为终点的值
        edges[i] = { a,b,w };
        //ui.textEdit->insertPlainText(d[a] + "到" + d[b] + "距离" + QString::number(w) + "万公里\n");
    }
    ui.textEdit->clear();
}

//打印城市信息
void Flo:: printCityInfo()
{
    
    ui.textEdit->insertPlainText("城市的列表如下，共有"+QString::number(n)+ "个城市：\n");
   
    for (int i = 1; i <= n; i++)
    {
        
        ui.textEdit->insertPlainText("(" + QString::number(i) + ")"+ d[i] + "   ");
        ui.textEdit->insertPlainText("\n");

    }

    for (int i = 0; i < m; i++)
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        ui.textEdit->insertPlainText(d[a]+"到"+d[b]+"距离为"+ QString::number(w)+ "\n");
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


    int s1 = QInputDialog::getInt(this, "请输入城市1编号", "城市1编号", 0, 1, n+1, 1, &flag);
    flag = false;
    int s2 = QInputDialog::getInt(this, "请输入城市2编号", "城市2编号", 0, 1, n+1, 1, &flag);
    flag = false;

    const int  num1 = s1;
    const int  num2 = s2;

    if (num1 > n || num1 < 1 || num2 > n || num2 < 1)
    {
        ui.textEdit->insertPlainText("输入的城市编号不存在！\n");
        ui.textEdit->insertPlainText("城市编号只能在1-"+QString::number(n)+"之间，请重新输入！\n");
        
    }
    else
    {
        if (num1 == num2)
        {
            g[num1][num2] = 0; //我们规定，城市到自己的距离为0
        }
        int t = g[num1][num2];
        if (num1 == num2)
        {
            ui.textEdit->insertPlainText(d[num1] + "到" +d[num2]+ "的距离为："+QString::number(t)+"\n");
           
        }
        else if (t > INF / 2) 
        {
            ui.textEdit->insertPlainText(d[num1] + "与" +d[num2] + "之间不存在通路！\n");

        } 
        else
        {
            int z = path[num1][num2];
            ui.textEdit->insertPlainText(d[num1] + "到" + d[num2] + "的最短路径为：" + QString::number(num1));
            //cout << d[num1] << "到" << d[num2] << "的最短路径为：" << num1;
            while (z != num2) //当中转结点不是终点时就一直循环
            {
                ui.textEdit->insertPlainText("->" + QString::number(z));
                //cout << "->" << z; //输出中转结点
                z = path[z][num2]; //把z更新成z->num2的中转结点
            }
            ui.textEdit->insertPlainText("->" + QString::number(num2)+"\n");

            ui.textEdit->insertPlainText(d[num1] + "到" + d[num2] + "的最短路径长度为：" + QString::number(t)+"\n");

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
