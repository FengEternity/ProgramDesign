#include "inheritance1.h"
#include<time.h>
#include<qinputdialog.h>
#include<qfile.h>
#include<stdlib.h>
#include<qfiledialog.h>
#pragma execution_character_set("utf-8")
//��Ⱥ����
static int pop[popnum][base_station_num][2];
//����ͼ��ά����
static int area_graph[line_num][row_num];
//��ȡ·������
static int select[popnum][base_station_num][2];
static int t[line_num][2];
static int history_best[base_station_num][2];

inheritance1::inheritance1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	a[0] = 0;
	a[1] = 0;
	b[0] = 0;
	b[1] = 0;
	c[0] = 0;
	c[1] = 0;
	x_line = 1;
	y_row = 1;
	baseNum = 400;
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(startSlot()));
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkSlot()));
	connect(ui.backButton, SIGNAL(clicked()), this, SLOT(inheriBackSlot()));
	connect(ui.outButton, SIGNAL(clicked()), this, SLOT(outSlot()));

}
void inheritance1::init_area(int a[2], int b[2], int c[2])
{

	change_coordinates(a, b, c);
	double k_ab = calculate_k(a, b);
	double k_bc = calculate_k(b, c);
	double k_ac = calculate_k(a, c);
	int i;
	area_graph[a[1]][a[0]] = m_wall;
	area_graph[b[1]][b[0]] = m_wall;
	area_graph[c[1]][c[0]] = m_wall;

	for (i = 0; i < y_row; i++)
	{

		if (i >= (a[0] < b[0] ? a[0] : b[0]) && i <= (a[0] > b[0] ? a[0] : b[0]))
		{
			area_graph[bias(a, k_ab, i)][i] = m_wall;
		}
		if (i >= (b[0] < c[0] ? b[0] : c[0]) && i <= (b[0] > c[0] ? b[0] : c[0]))
		{
			area_graph[bias(b, k_bc, i)][i] = m_wall;
		}
		if (i >= (a[0] < c[0] ? a[0] : c[0]) && i <= (a[0] > c[0] ? a[0] : c[0]))
		{
			area_graph[bias(c, k_ac, i)][i] = m_wall;

		}
	}
	for (i = 0; i < x_line; i++)
	{

		if (i >= (a[1] < b[1] ? a[1] : b[1]) && i <= (a[1] > b[1] ? a[1] : b[1]))
		{
			area_graph[i][re_bias(a, k_ab, i)] = m_wall;
		}
		if (i >= (b[1] < c[1] ? b[1] : c[1]) && i <= (b[1] > c[0] ? b[1] : c[1]))
		{
			area_graph[i][re_bias(b, k_bc, i)] = m_wall;
		}
		if (i >= (a[1] < c[1] ? a[1] : c[1]) && i <= (a[1] > c[1] ? a[1] : c[1]))
		{
			area_graph[i][re_bias(c, k_ac, i)] = m_wall;

		}


	}
	for (size_t i = 0; i < x_line; i++)
	{
		for (size_t j = 0; j < y_row; j++)
		{

			if (i == 0 || i == x_line - 1)
			{
				area_graph[i][j] = t_wall;
			}
			else if (j == 0 || j == y_row - 1)
			{
				area_graph[i][j] = t_wall;
			}


		}
	}

}
void inheritance1::produce()
{
	int i, j;
	srand((unsigned)time(NULL));


	for (i = 0; i < popnum; i++)
	{
		for (j = 0; j < baseNum; j++)
		{
			pop[i][j][0] = rand() % (x_line);

			if (t[pop[i][j][0]][1] - t[pop[i][j][0]][0] <= 1)
			{
				pop[i][j][1] = t[pop[i][j][0]][1];
			}
			else
			{
				pop[i][j][1] = rand() % (t[pop[i][j][0]][1] - t[pop[i][j][0]][0]) + t[pop[i][j][0]][0];
			}


		}
	}



}
double inheritance1::one_AreaCover(int base_station[base_station_num][2])
{
	static int an[line_num][row_num];
	int i, j;
	int num = 0;//���ǵ�����
	double cover_rate;
	int total = 0;

	for (i = 0; i < x_line; i++)//����an�������ͼ����ԭͼ���޸�
	{
		for (j = 0; j < y_row; j++)
		{
			an[i][j] = area_graph[i][j];
		}
	}


	for (i = 0; i < baseNum; i++)//���и���
	{
		an[base_station[i][0]][base_station[i][1]] = Center;
		if (base_station[i][0] + 1 <= y_row)
		{
			an[base_station[i][0] + 1][base_station[i][1]] = c_wall;
		}
		if (base_station[i][0] - 1 >= 0)
		{
			an[base_station[i][0] - 1][base_station[i][1]] = c_wall;
		}
		if (base_station[i][1] + 1 <= x_line)
		{
			an[base_station[i][0]][base_station[i][1] + 1] = c_wall;
		}
		if (base_station[i][1] - 1 >= 0)
		{
			an[base_station[i][0]][base_station[i][1] - 1] = c_wall;
		}
		if (base_station[i][0] - 1 >= 0 && base_station[i][1] - 1 >= 0)
		{
			an[base_station[i][0] - 1][base_station[i][1] - 1] = c_wall;
		}
		if (base_station[i][0] + 1 <= x_line && base_station[i][1] + 1 <= y_row)
		{
			an[base_station[i][0] + 1][base_station[i][1] + 1] = c_wall;
		}
		if (base_station[i][0] + 1 <= x_line && base_station[i][1] - 1 >= 0)
		{
			an[base_station[i][0] + 1][base_station[i][1] - 1] = c_wall;
		}
		if (base_station[i][0] - 1 <= x_line && base_station[i][1] + 1 <= y_row)
		{
			an[base_station[i][0] - 1][base_station[i][1] + 1] = c_wall;
		}


	}

	for (i = 0; i < x_line; i++)//ͳ�Ƹ��ǵ����,ֻͳ����������
	{
		for (j = t[i][0]; j < t[i][1]; j++)
		{
			if (an[i][j] == c_wall || an[i][j] == Center)
			{
				num++;
			}

		}
	}


	for (i = 0; i < x_line; i++)
	{
		total = total + t[i][1] - t[i][0];
	}

	cover_rate = (double)num / (double)total;
	return cover_rate;

}
void inheritance1::choice()
{
	srand((unsigned)time(NULL));
	double fitpro[popnum] = { 0 };//��������
	int i, temp = 0;
	int num = 4;
	int a[4] = { 0 };
	double total = 0;//�ܸ���
	double sum = 0;
	double fit = 0;
	//���̶�
	int max_area_index = max_cover(pop);
	for (size_t i = 0; i < baseNum; i++)//�������Ÿ���
	{
		select[0][i][0] = pop[max_area_index][i][0];
		select[0][i][1] = pop[max_area_index][i][1];
	}

	for (i = 0; i < popnum; i++)
	{

		total += sigmod(one_AreaCover(pop[i]));

	}
	for (i = 0; i < popnum; i++)
	{
		fitpro[i] = sigmod(one_AreaCover(pop[i])) / total;
	}
	for (i = 1; i < popnum; i++)
	{
		double take = ((double)rand()) / RAND_MAX;//����0-1�������

		for (size_t j = 0; j < popnum; j++)
		{
			take = take - fitpro[j];
			if (take <= 0)
			{
				for (size_t k = 0; k < baseNum; k++)
				{
					select[i][k][0] = pop[j][k][0];
					select[i][k][1] = pop[j][k][1];
				}
				break;
			}
		}
	}

	for (size_t i = 0; i < popnum; i++)//������Ⱥ
	{
		for (size_t j = 0; j < baseNum; j++)
		{
			pop[i][j][0] = select[i][j][0];
			pop[i][j][1] = select[i][j][1];
		}
	}
	elitism_save();

}
double inheritance1::sigmod(double a)
{

	return exp(a);

}
void inheritance1::cross()
{
	int crossPossion;//�����
	int select1 = -1, select2 = -1;//���游��
	int i, j, temp;
	double take;
	int cross_time = baseNum / 2;
	int max_index = max_cover(pop);
	for (i = 0; i < cross_time; i++)
	{
		select1 = (int)rand() % (popnum - 1);
		select2 = (int)rand() % (popnum - 1);
		take = ((double)rand()) / RAND_MAX;
		if (take <= cp)
		{
			crossPossion = (int)rand() % (baseNum - 1);
			while (select1 == max_index || select2 == max_index)//������Ⱥ�е�ǰ���Ÿ���
			{
				select1 = (int)rand() % (popnum - 1);
				select2 = (int)rand() % (popnum - 1);
			}

			for (j = 0; j < 2; j++)
			{
				temp = pop[select1][crossPossion][j];
				pop[select1][crossPossion][j] = pop[select2][crossPossion][j];
				pop[select2][crossPossion][j] = temp;
			}

		}
	}


}
void inheritance1::variation()
{
	int select = -1;//ѡ�񸸴�
	int change;//ѡ������
	double take;
	int variation_time = baseNum / 2;
	int max_index = max_cover(pop);
	for (size_t i = 0; i < variation_time; i++)
	{
		/*cout << "var=" << i << endl;*/
		select = (int)rand() % (popnum - 1);
		take = ((double)rand()) / RAND_MAX;
		if (take <= mp)
		{
			while (select == max_index)//������ǰ��Ⱥ���Ÿ���
			{
				select = (int)rand() % (popnum - 1);
			}
			change = (int)rand() % (baseNum - 1);
			pop[select][change][0] = rand() % (x_line - 1);
			//pop[select][change][1] = rand() % (row_num - 1);
			if (t[pop[select][change][0]][1] - t[pop[select][change][0]][0] <= 1)
			{
				pop[select][change][1] = pop[select][change][0];

			}
			else
			{
				pop[select][change][1] = rand() % (t[pop[select][change][0]][1] - t[pop[select][change][0]][0]) + t[pop[select][change][0]][0];
			}
		}
	}

}
int inheritance1::max_cover(int a[popnum][base_station_num][2])
{
	double max = one_AreaCover(a[0]);
	int temp = 0;
	int i;
	for (i = 1; i < popnum; i++)
	{
		if (max < one_AreaCover(a[i]))
		{
			max = one_AreaCover(a[i]);
			temp = i;
		}
	}
	return temp;

}
int inheritance1::min_cover(int a[popnum][base_station_num][2])
{
	double min = one_AreaCover(a[0]);
	int temp = 0;
	int i;
	for (i = 1; i < popnum; i++)
	{
		if (min > one_AreaCover(a[i]))
		{
			min = one_AreaCover(a[i]);
			temp = i;
		}
	}
	return temp;

}
void inheritance1::elitism_save()
{

	int min_index = min_cover(pop);
	int max_index = max_cover(pop);
	for (size_t i = 0; i < baseNum; i++)
	{
		pop[min_index][i][0] = pop[max_index][i][0];
		pop[min_index][i][1] = pop[max_index][i][1];
	}


}
bool inheritance1::show_mine(int i)
{
	int best_one = max_cover(pop);
	ui.textEdit->insertPlainText("\n��" + QString::number(i) + "��\n");
	ui.textEdit->insertPlainText("��ǰ��󸲸���Ϊ:" + QString::number(one_AreaCover(pop[best_one]) * 100) + "%\n");
	
	//cout << "��ǰ��󸲸���Ϊ��" << one_AreaCover(pop[best_one]) * 100 << "%" << endl;
	if (one_AreaCover(pop[best_one]) * 100 >= 95)
	{
		return true;
	}
	return false;
}
void inheritance1::get_boundary()
{
	int i, j;
	int num_in_line = 0;
	int flag = 0;
	for (i = 0; i < x_line; i++)
	{
		num_in_line = 0;
		for (j = 0; j < y_row; j++)
		{
			if (area_graph[i][j] == m_wall)
			{
				num_in_line++;
			}

		}
		for (j = 0; j < y_row; j++)
		{
			if (area_graph[i][j] == m_wall)
			{
				if (flag == 0)
				{
					t[i][0] = j;
				}
				flag++;
				if (flag == num_in_line)
				{
					t[i][1] = j;
				}
			}
		}
		if (flag == 0)
		{
			t[i][1] = t[i][0];
		}
		flag = 0;
	}

}
void inheritance1::rw_file(int area[base_station_num][2])
{
	int i;
	int min_line = min_of_3(a1[1], b1[1], c1[1]);
	int min_row = min_of_3(a1[0], b1[0], c1[0]);
	QString text = "";
	QString path = QFileDialog::getSaveFileName(this, "save", "D:\\", "text(*.txt)");
	QFile file;
	file.setFileName(path);
	file.open(QIODevice::WriteOnly);
	for (size_t i = 0; i < baseNum; i++)
	{
		text = QString::number(area[i][0]+min_row) + "," + QString::number(area[i][1]+min_line)+"\n";
		file.write(text.toUtf8());
		text = "";
	}
	
	file.close();
}
bool inheritance1::getAxis()
{
	bool flag = false;
	ui.textEdit->clear();
	ui.textEdit->insertPlainText("��������x,y\n");
	a[0] = QInputDialog::getInt(this, "�������һ����a�ĺ�����", "��һ����a�ĺ�����", 0, 0, 9999, 1, &flag);
	if (flag==false)
	{
		return false;
	}
	a[1] = QInputDialog::getInt(this, "�������һ����a��������", "��һ����a��������", 0, 0, 9999, 1, &flag);
	if (flag == false)
	{
		return false;
	}
	ui.textEdit->insertPlainText("("+QString::number(a[0])+","+ QString::number(a[1])+")\n");
	b[0] = QInputDialog::getInt(this, "������ڶ�����b�ĺ�����", "�ڶ�����b�ĺ�����", 0, 0, 9999, 1, &flag);
	if (flag == false)
	{
		return false;
	}
	b[1] = QInputDialog::getInt(this, "������ڶ�����b��������", "�ڶ�����b��������", 0, 0, 9999, 1, &flag);
	if (flag == false)
	{
		return false;
	}
	ui.textEdit->insertPlainText("(" + QString::number(b[0]) + "," + QString::number(b[1]) + ")\n");
	c[0] = QInputDialog::getInt(this, "�������������c�ĺ�����", "��������c�ĺ�����", 0, 0, 9999, 1, &flag);
	if (flag == false)
	{
		return false;
	}
	c[1] = QInputDialog::getInt(this, "�������������c��������", "��������c��������", 0, 0, 9999, 1, &flag);
	if (flag == false)
	{
		return false;
	}
	ui.textEdit->insertPlainText("(" + QString::number(c[0]) + "," + QString::number(c[1]) + ")\n");
	baseNum = QInputDialog::getInt(this, "�������վ��Ŀ", "�����վ��Ŀ", 0, 0, 10000, 1, &flag);
	if (flag == false)
	{
		return false;
	}
	ui.textEdit->insertPlainText("��վ��Ŀ=" + QString::number(baseNum) +  "\n");
	generation = QInputDialog::getInt(this, "����������������", "����������", max_generation, 100, 2000, 1, &flag);
	if (flag==false)
	{
		return false;
	}
	ui.textEdit->insertPlainText("(" + QString::number(a[0]) + "," + QString::number(a[1]) + ")");
	for (size_t i = 0; i < 2; i++)
	{
		a1[i] = a[i];
		b1[i] = b[i];
		c1[i] = c[i];
	}
	precision=QInputDialog::getDouble(this, "�����븲������ֵ", "��������ֵ", 95, 0, 99.99, 1, &flag);
	return flag;
}
void inheritance1::judge()
{

	while (x_line > line_num || y_row > row_num || baseNum > base_station_num)
	{
		ui.textEdit->insertPlainText("��ѡ��Χ������վ��Ŀ����,����������");
	}

}
bool inheritance1::TSP()//�������
{
	bool flag;
	int max_index = 0;
	if (getAxis()==false)
	{
		return false;
	}
	judge();
	change_coordinates(a,b,c);
	x_line = lineNum(a, b, c);
	y_row = rowNum(a, b, c);
	init_area(a, b, c);
	get_boundary();
	produce();

	for (size_t i = 0; i < max_generation; i++)
	{
		
		choice();
		cross();
		variation();
		max = max_cover(pop);
		if (i%300==0)
		{
			flag = show_mine(i + 1);
		}
		
		if (one_AreaCover(pop[max]) * 100>precision)
		{
			ui.textEdit->insertPlainText("\n���");
			show_mine(i + 1);
			break;
		}
	}
	return true;
}
double inheritance1::calculate_k(int a[2], int b[2])//б�ʼ���
{
	double k = (double)(a[1] - b[1]) / (a[0] - b[0]);
	return k;
}
int inheritance1::round_up(double x) //����ȡ��
{

	x = (int)(x + 0.5);

	return (int)x;
}
int inheritance1::bias(int a[2], double k, double x)//���������꣬����������
{

	double b = a[1] - k * a[0];
	return round_up(k * x + b);
}
int inheritance1::re_bias(int a[2], double k, double y) //���������꣬����������
{
	double b = a[1] - k * a[0];
	return round_up((y - b) / k);

}
int inheritance1::max_of_3(int a, int b, int c)
{
	int max = a;
	if (c > (b > a ? b : a))
	{
		max = c;
	}
	else
	{
		max = b > a ? b : a;
	}
	return max;
}
int inheritance1::min_of_3(int a, int b, int c)
{
	int min = a;
	if (c < (b < a ? b : a))
	{
		min = c;
	}
	else
	{
		min = b < a ? b : a;
	}
	return min;
}
int inheritance1::lineNum(int a[2], int b[2], int c[2])//��������
{
	int lineN = max_of_3(a[1], b[1], c[1]) - min_of_3(a[1], b[1], c[1]);
	return lineN;

}
int inheritance1::rowNum(int a[2], int b[2], int c[2])//��������
{
	int rowN = max_of_3(a[0], b[0], c[0]) - min_of_3(a[0], b[0], c[0]);
	return rowN;
}
void inheritance1::change_coordinates(int a[2], int b[2], int c[2]) //��������任
{
	int min_line = min_of_3(a[1], b[1], c[1]);
	int min_row = min_of_3(a[0], b[0], c[0]);
	a[0] -= min_row;
	b[0] -= min_row;
	c[0] -= min_row;
	a[1] -= min_line;
	b[1] -= min_line;
	c[1] -= min_line;


}

void inheritance1::startSlot()
{
	if(TSP()==false)
	{
		return;
	}
}
void inheritance1::checkSlot()
{
	QString path_image = "C:\\Users\\86173\\Desktop\\Widget1\\Widget1\\v2.jpg";
	QPixmap img(path_image); 
	QString path = QFileDialog::getSaveFileName(this, "save", "D:\\", "jFiles(*.jpg *.png)");
	
	img.save(path);
}
void inheritance1::outSlot()
{
	rw_file(pop[max]);
}
void inheritance1::inheriBackSlot()
{
	emit inherBackCal();

}
inheritance1::~inheritance1()
{}
