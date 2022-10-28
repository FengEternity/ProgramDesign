#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 210, M = 1000, INF = 0x3f3f3f3f;

int n,m;//������������
int g[N][N],path[N][N];//gΪ�ڽӾ���path�����ʾ�����յ�����Ҫ�������м��
unordered_map<int, string> d; //����һ����������֮��ӳ���ɢ�б�

//��������
void shuru(); //���������Ϣ
void printCityInfo(); //��ӡ������Ϣ
void floyd(); //���������㷨
void query(); //����������������֮������·��

//�������
struct Edge
{
    int a,b,w;

}edges[M];

//���������Ϣ
void shuru()
{
    //��ʼ���ڽӾ���
//    for(int i = 1; i <= n; i++)
//        for(int j = 1; j <= n; j++)
//            if(i == j) g[i][j] == 0;
//            else g[i][j] = INF;
    memset(g, 0x3f, sizeof g);

    printf("�����������n�ͱ���m��\n");
    scanf_s("%d%d",&n,&m); //���������,����


    //������n���������ƣ��ÿո������
    printf("������n���������ƣ��ÿո������\n");
    for(int i = 1; i <= n; i++)
    {
        string cityname;
        cin >> cityname;
        d[i] = cityname;
    }

    printf("��������m�У�\n");
    printf("��������������a,b,w,��ʾa���к�b����֮�����һ��ȨֵΪw�ı�\n");
    //������ m �У�ÿ�а����������� u,v,w����ʾ�� u �͵� v ֮�����һ��ȨֵΪ w �ıߡ�
    for(int i = 0; i < m; i ++)
    {
        int a,b,w;
        scanf_s("%d%d%d",&a,&b,&w);
        g[a][b] = min(g[a][b], w); //����������ͼ
        //���������ͼ�Ļ�����д��g[a][b] = g[b][a] = min(g[a][b], w);
        path[a][b] = b; //��path�����е�ֵ��ʼ��Ϊ�յ��ֵ
        edges[i] = {a,b,w};
    }

}

//��ӡ������Ϣ
void printCityInfo()
{
    cout << "���е��б����£�����" << n << "�����У�" << endl;
    for(int i = 1; i <= n; i++)
    {
        cout << "(" << i << ")" << d[i] << "    ";
        if(i % 3 == 0) cout << endl;
    }

    for(int i = 0; i < m; i++)
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        cout << d[a] << "��" << d[b] << "����" << w << "����" << endl;
    }

}

//���������㷨��ʵ��
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

//����������������֮������·������
void query()
{
    cout << "������Ҫѯ�ʵ��������еı�ţ��ÿո������" << endl;
    int num1 = 0, num2 = 0;
    //���ַ�������������ݣ���߳���³����
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
        cout << "����ĳ��б�Ų����ڣ�" << endl;
        cout << "���б��ֻ����1-" << n << "֮�䣬���������룡" << endl;
    }
    else
    {
        if(num1 == num2)
        {
            g[num1][num2] = 0; //���ǹ涨�����е��Լ��ľ���Ϊ0
        }
        int t = g[num1][num2];
        if(num1 == num2)
        {
            cout << d[num1] << "��" << d[num2] << "�ľ���Ϊ��" << t << endl;
        }
        else if(t > INF / 2) cout << d[num1] << "��" << d[num2] << "֮�䲻����ͨ·��" << endl;
        else
        {
            int z = path[num1][num2];
            cout << d[num1] << "��" << d[num2] << "�����·��Ϊ��" << num1;
            while(z != num2) //����ת��㲻���յ�ʱ��һֱѭ��
            {
                cout << "->" << z; //�����ת���
                z = path[z][num2]; //��z���³�z->num2����ת���
            }
            cout << "->" << num2;
            cout << endl;
            cout << d[num1] << "��" << d[num2] << "�����·������Ϊ��" << t << endl;
        }
    }
}

//int main()
//{
//    while(1)
//    {
//        cout << endl;
//        cout << "����ģ�飺" << endl;
//        cout << "1.���������Ϣ" << endl;
//        cout << "2.��ӡ������Ϣ�ͳ���֮���ֱ�ӿɴ����" << endl;
//        cout << "3.��floyd�㷨�����·����������·���ĳ���" << endl;
//        cout << "4.�˳�" << endl;
//
//        while(true)
//        {
//            cout << "��������Ҫʹ�õĹ������:" << endl;
//            //��������ʹ��string�������ݣ���ת�������֣���߳����ݴ���
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
//                cout << "ֻ������1-4֮����������������룡" << endl;
//            }
//            else if(num == 1)
//            {
//                shuru();
//                cout << "����ɹ��������ڿ���ʹ��2,3���ܲ鿴��Ӧ�����" << endl;
//                break;
//            }
//            else if(num == 2)
//            {
//                if(n == 0)
//                {
//                    cout << "����δ���������Ϣ���������������Ϣ��" << endl;
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
//                    cout << "����δ���������Ϣ���������������Ϣ��" << endl;
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
//                cout << "��лʹ�ã�" << endl;
//                return 0;
//            }
//        }
//    }
//
//    return 0;
//}
