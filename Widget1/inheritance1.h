#pragma once

#include <QWidget>
#include "ui_inheritance1.h"

//���ͼ����
#define line_num 500
//���ͼ����
#define row_num  500
//�������
#define cp 0.95
//�������
#define mp 0.45
//��վ����
#define base_station_num 2000
//��Ⱥ����
#define popnum 100
//����������
#define max_generation 3000
//���α߽�ֵ
#define t_wall 5
//��ͼ�߽�ֵ
#define m_wall 1
//����ֵ
#define c_wall 2
//��վԲ�ĸ���ֵ
#define Center 9

class inheritance1 : public QWidget
{
	Q_OBJECT
	

public:
	inheritance1(QWidget *parent = nullptr);
	//������Ⱥ����
	void produce();
	//����һ�������ܸ������
	double one_AreaCover(int base_station[base_station_num][2]);
	//�����
	double sigmod(double a);
	//��ʼ��ͼ
	void init_area(int a[2], int b[2], int c[2]);
	//ѡ�����,���̶�
	void choice();
	//����
	void cross();
	//����
	void variation();
	//�ҵ���󸲸��ʸ�����±�
	int max_cover(int a[popnum][base_station_num][2]);
	//�ҵ���С�����ʸ�����±�
	int min_cover(int a[popnum][base_station_num][2]);
	//��Ӣ��������
	void elitism_save();
	//��ȡ������ÿһ�еı߽�
	void get_boundary();
	//�����󸲸���
	bool show_mine(int i);
	//���պ���
	bool TSP();
	//��д�ļ�
	void rw_file(int area[base_station_num][2]);
	//������������
	bool getAxis();
	//�ж��������ͻ�վ���Ƿ����
	void judge();
	int round_up(double x);
	int bias(int a[2], double k, double x);
	int re_bias(int a[2], double k, double y);
	double calculate_k(int a[2], int b[2]);
	int rowNum(int a[2], int b[2], int c[2]);
	int max_of_3(int a, int b, int c);
	int min_of_3(int a, int b, int c);
	int lineNum(int a[2], int b[2], int c[2]);
	void change_coordinates(int a[2], int b[2], int c[2]);
	int max=0;
	~inheritance1();

private:
	Ui::inheritance1Class ui;
	int a[2] = {0,0};
	int b[2] = {0,0};
	int c[2] = {0,0};
	int a1[2];
	int b1[2];
	int c1[2];
	int x_line=1;
	int y_row=1;
	int baseNum = 400;
	int generation = max_generation;
	double precision = 95;


public slots:
	void startSlot();
	void checkSlot();
	void outSlot();
	void inheriBackSlot();

signals:
	void inherBackCal();
};
