# include <iostream>
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
void Create(struct EdgeGraph *MyEdgeGraph);         //����ͼ�ĺ�������
void WayToAchieve(struct EdgeGraph *MyEdgeGraph);   //�㷨ʵ�ֺ���
int FindRoot(int Parent[],int v);                   //Ѱ�Ҹ���ͨ�������ĺ���
void main()
{
	EdgeGraph MyEdgeGraph;
	Create(&MyEdgeGraph);
	WayToAchieve(&MyEdgeGraph);
	system("pause");
	return;
}
void Create(struct EdgeGraph *MyEdgeGraph)
{
	int Vertex, Edge, Weight;
	cout << "����������ͼ�Ķ�������" << endl;
	cin >> Vertex;
	cout << "����������ͼ�ı�����" << endl;
	cin >> Edge;
	cout << "����������ÿ��������������������ͱߵ�Ȩֵ��" << endl;
	EdgeType *MyEdge = new EdgeType[Edge];             //�����û�Ҫ�������ı���Ϣ�ṹ������
	for (int i = 0; i < Edge; i++) {                   //�߽ṹ������ĳ�ʼ��
		cin >> MyEdge[i].from >> MyEdge[i].to >> MyEdge[i].Weight;
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
void WayToAchieve(struct EdgeGraph *MyEdgeGraph)
{
	int num = 0, i = 0,v1,v2;
	int *root = new int[(*MyEdgeGraph).VertexNum];        //����������������ʼ��
	for (int i = 0; i < (*MyEdgeGraph).VertexNum; i++) {
		root[i] = -1;
	}
	for (num = 0, i = 0; i < (*MyEdgeGraph).EdgeNum; i++) {      //���ζ�ÿ���߽��б�����num��¼����ߵĸ���
		v1 = FindRoot(root,(*MyEdgeGraph).Edge[i].from);    //�ֱ�Ѱ��v1,v2������ͨ�����ĸ�
		v2 = FindRoot(root, (*MyEdgeGraph).Edge[i].to);
		if (v1 != v2) {                                     //������ڲ�ͬ����ͨ�����ͺϲ�
			cout << "("<<(*MyEdgeGraph).Edge[i].from<<(*MyEdgeGraph).Edge[i].to<<")" << endl;
			root[v2] = v1;                                 //�ϲ�
			num++;                                         //��¼ѡ��ߵĸ���
			if (num == (*MyEdgeGraph).VertexNum - 1) {     //���ѡ��ıߴ������ڶ�����-1��֤����С���Ѿ����ɣ�������������
				return;
			}
		}
	}
}
int FindRoot(int Parent[], int v)
{
	int v1 = v;
	while (Parent[v1] > -1) {         //��ͣѭ���Ҹ�
		v1 = Parent[v1];
	}
	return v1;
}