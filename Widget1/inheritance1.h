#pragma once

#include <QWidget>
#include "ui_inheritance1.h"

//面积图行数
#define line_num 500
//面积图列数
#define row_num  500
//交叉概率
#define cp 0.95
//变异概率
#define mp 0.45
//基站总数
#define base_station_num 2000
//种群个数
#define popnum 100
//进化最大代数
#define max_generation 3000
//矩形边界值
#define t_wall 5
//地图边界值
#define m_wall 1
//覆盖值
#define c_wall 2
//基站圆心覆盖值
#define Center 9

class inheritance1 : public QWidget
{
	Q_OBJECT
	

public:
	inheritance1(QWidget *parent = nullptr);
	//产生种群函数
	void produce();
	//计算一个个体总覆盖面积
	double one_AreaCover(int base_station[base_station_num][2]);
	//激活函数
	double sigmod(double a);
	//初始化图
	void init_area(int a[2], int b[2], int c[2]);
	//选择操作,轮盘赌
	void choice();
	//交叉
	void cross();
	//变异
	void variation();
	//找到最大覆盖率个体的下标
	int max_cover(int a[popnum][base_station_num][2]);
	//找到最小覆盖率个体的下标
	int min_cover(int a[popnum][base_station_num][2]);
	//精英保留策略
	void elitism_save();
	//获取三角形每一行的边界
	void get_boundary();
	//输出最大覆盖率
	bool show_mine(int i);
	//最终函数
	bool TSP();
	//读写文件
	void rw_file(int area[base_station_num][2]);
	//输入三点坐标
	bool getAxis();
	//判断行列数和基站数是否过大
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
