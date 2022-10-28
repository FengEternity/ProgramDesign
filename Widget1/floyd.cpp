#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 210, M = 1000, INF = 0x3f3f3f3f;

int n,m;//城市数，边数
int g[N][N],path[N][N];//g为邻接矩阵，path矩阵表示到达终点所需要经过的中间点
unordered_map<int, string> d; //建立一个序号与城市之间映射的散列表

//函数声明
void shuru(); //输入城市信息
void printCityInfo(); //打印城市信息
void floyd(); //弗洛伊德算法
void query(); //计算任意两个城市之间的最短路径

//用来存边
struct Edge
{
    int a,b,w;

}edges[M];

//输入城市信息
void shuru()
{
    //初始化邻接矩阵
//    for(int i = 1; i <= n; i++)
//        for(int j = 1; j <= n; j++)
//            if(i == j) g[i][j] == 0;
//            else g[i][j] = INF;
    memset(g, 0x3f, sizeof g);

    printf("请输入城市数n和边数m：\n");
    scanf_s("%d%d",&n,&m); //输入城市数,边数


    //请输入n个城市名称，用空格隔开：
    printf("请输入n个城市名称，用空格隔开：\n");
    for(int i = 1; i <= n; i++)
    {
        string cityname;
        cin >> cityname;
        d[i] = cityname;
    }

    printf("接下来的m行：\n");
    printf("请输入三个整数a,b,w,表示a城市和b城市之间存在一条权值为w的边\n");
    //接下来 m 行，每行包含三个整数 u,v,w，表示点 u 和点 v 之间存在一条权值为 w 的边。
    for(int i = 0; i < m; i ++)
    {
        int a,b,w;
        scanf_s("%d%d%d",&a,&b,&w);
        g[a][b] = min(g[a][b], w); //这里是有向图
        //如果是无向图的话可以写成g[a][b] = g[b][a] = min(g[a][b], w);
        path[a][b] = b; //将path矩阵中的值初始化为终点的值
        edges[i] = {a,b,w};
    }

}

//打印城市信息
void printCityInfo()
{
    cout << "城市的列表如下，共有" << n << "个城市：" << endl;
    for(int i = 1; i <= n; i++)
    {
        cout << "(" << i << ")" << d[i] << "    ";
        if(i % 3 == 0) cout << endl;
    }

    for(int i = 0; i < m; i++)
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        cout << d[a] << "到" << d[b] << "距离" << w << "万公里" << endl;
    }

}

//弗洛伊德算法的实现
void floyd()
{
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(g[i][j] > g[i][k] + g[k][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                    path[i][j] = path[i][k];
                }
                //g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

//计算任意两个城市之间的最短路径函数
void query()
{
    cout << "请输入要询问的两个城市的编号，用空格隔开：" << endl;
    int num1 = 0, num2 = 0;
    //用字符串存输入的数据，提高程序鲁棒性
    string str1,str2;
    cin >> str1 >> str2;
    for(int i = 0; i < str1.size(); i++)
    {
        int x = str1[i] - '0';
        num1 = num1 * 10 + x;
    }
    for(int i = 0; i < str2.size(); i++)
    {
        int x = str2[i] - '0';
        num2 = num2 * 10 + x;
    }
    if(num1 > n || num1 < 1 || num2 > n || num2 < 1)
    {
        cout << "输入的城市编号不存在！" << endl;
        cout << "城市编号只能在1-" << n << "之间，请重新输入！" << endl;
    }
    else
    {
        if(num1 == num2)
        {
            g[num1][num2] = 0; //我们规定，城市到自己的距离为0
        }
        int t = g[num1][num2];
        if(num1 == num2)
        {
            cout << d[num1] << "到" << d[num2] << "的距离为：" << t << endl;
        }
        else if(t > INF / 2) cout << d[num1] << "与" << d[num2] << "之间不存在通路！" << endl;
        else
        {
            int z = path[num1][num2];
            cout << d[num1] << "到" << d[num2] << "的最短路径为：" << num1;
            while(z != num2) //当中转结点不是终点时就一直循环
            {
                cout << "->" << z; //输出中转结点
                z = path[z][num2]; //把z更新成z->num2的中转结点
            }
            cout << "->" << num2;
            cout << endl;
            cout << d[num1] << "到" << d[num2] << "的最短路径长度为：" << t << endl;
        }
    }
}

//int main()
//{
//    while(1)
//    {
//        cout << endl;
//        cout << "功能模块：" << endl;
//        cout << "1.输入城市信息" << endl;
//        cout << "2.打印城市信息和城市之间的直接可达距离" << endl;
//        cout << "3.用floyd算法求最短路径并输出最短路径的长度" << endl;
//        cout << "4.退出" << endl;
//
//        while(true)
//        {
//            cout << "请输入您要使用的功能序号:" << endl;
//            //这里巧妙使用string读入数据，再转换成数字，提高程序容错率
//            string str;
//            cin >> str;
//            int num = 0;
//            for(int i = 0; i < str.size(); i++)
//            {
//                int x = str[i] - '0';
//                num = num * 10 + x;
//            }
//            if(num > 4 || num < 1)
//            {
//                cout << "只能输入1-4之间的数，请重新输入！" << endl;
//            }
//            else if(num == 1)
//            {
//                shuru();
//                cout << "输入成功，您现在可以使用2,3功能查看相应结果！" << endl;
//                break;
//            }
//            else if(num == 2)
//            {
//                if(n == 0)
//                {
//                    cout << "您还未输入城市信息，请先输入城市信息！" << endl;
//                }
//                else
//                {
//                    printCityInfo();
//                    cout << endl;
//                }
//                break;
//            }
//            else if(num == 3)
//            {
//                if(n == 0)
//                {
//                    cout << "您还未输入城市信息，请先输入城市信息！" << endl;
//                }
//                else
//                {
//                    floyd();
//                    query();
//                }
//                break;
//
//            }
//            else if(num == 4)
//            {
//                cout << "感谢使用！" << endl;
//                return 0;
//            }
//        }
//    }
//
//    return 0;
//}
