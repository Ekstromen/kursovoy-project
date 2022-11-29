#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#define N 10 //������ �������� ����
#define V 15

struct value
{
	char symbol;
	int x;
	int y;
}; //�������� ��������� ��� �������� �������� ������� �������� � �� ���������

typedef struct value Value;

int main()
{

	char playing_field[N][N]; //������� ����
	char view_field[N][N]; //���� ������
	Value islands[V]; //���������� ���������
	int x, y;	//���������� ��� ���������� �������� �������� ����
	int ox = 0, oy = 0; //���������� �������
	int nx, ny; //���������� ������� �� �����������
	char key = '0',check = '0', check1 = '0';

	islands[0].symbol = '1'; //���������� ��������� 
	islands[0].y = 0;
	islands[0].x = 2;
	islands[1].symbol = '2';
	islands[1].y = 0;
	islands[1].x = 7;
	islands[2].symbol = '2';
	islands[2].y = 1;
	islands[2].x = 1;
	islands[3].symbol = '1';
	islands[3].y = 1;
	islands[3].x = 4;
	islands[4].symbol = '3';
	islands[4].y = 2;
	islands[4].x = 5;
	islands[5].symbol = '5';
	islands[5].y = 2;
	islands[5].x = 9;
	islands[6].symbol = '2';
	islands[6].y = 3;
	islands[6].x = 2;
	islands[7].symbol = '1';
	islands[7].y = 4;
	islands[7].x = 0;
	islands[8].symbol = '5';
	islands[8].y = 4;
	islands[8].x = 6;
	islands[9].symbol = '2';
	islands[9].y = 5;
	islands[9].x = 1;
	islands[10].symbol = '1';
	islands[10].y = 5;
	islands[10].x = 8;
	islands[11].symbol = '5';
	islands[11].y = 6;
	islands[11].x = 4;
	islands[12].symbol = '2';
	islands[12].y = 8;
	islands[12].x = 0;
	islands[13].symbol = '3';
	islands[13].y = 9;
	islands[13].x = 5;
	islands[14].symbol = '4';
	islands[14].y = 9;
	islands[14].x = 7;

	setlocale(LC_ALL, "RUS");

	for (y = 0; y < N; y++) //�������� �������� ���� � ������� ���������� �������
	{
		for (x = 0; x < N; x++)
		{
			playing_field[y][x] = '*';
		
		}
	}

	for (int i = 0; i < V; i++)
	{
		playing_field[islands[i].y][islands[i].x] = islands[i].symbol;//������������ �������� �� ��������� � ������� �������� ���� 
	}

	do //����������� ���� ��� ����������� ����� �������� � ����������� �������
	{

		for (y = 0; y < N; y++) //�������� �������� ���� � ������� ���������� �������
		{
			for (x = 0; x < N; x++)
			{
				view_field[y][x] = playing_field[y][x]; //�������� �������� �� ������� � ������� � ������ ��� ������ �� �����

			}
		}

		key = _getch(); //���������� ������� ����������

		nx = ox; //���������� ������� �� ����������� 
		ny = oy; //���������� ������� �� ����������� 

		if (key == 'w' && (oy > -1 && oy < 10)) oy--; //����������� �����
		if (key == 's' && (oy < 10 && oy > -1)) oy++; //����������� ����
		if (key == 'a' && (ox > -1 && ox < 10)) ox--; //����������� �����
		if (key == 'd' && (ox > -1 && ox < 10)) ox++; //����������� ������
		if (oy == 10) oy = ny; //�������� �� ����� �� ������� �������� ����
		if (oy == -1) oy = ny; //�������� �� ����� �� ������� �������� ����
		if (ox == 10) ox = nx; //�������� �� ����� �� ������� �������� ����
		if (ox == -1) ox = nx; //�������� �� ����� �� ������� �������� ����
		if (playing_field[oy][ox] != '*' && playing_field[oy][ox] != '#')
		{
			oy = ny; //������ �� ������������ � ������� �� ������ � �������
			ox = nx; //������ �� ������������ � ������� �� ������ � �������
		}

		if (key == 'f') 
		{
			if (playing_field[oy][ox] == '*') playing_field[oy][ox] = '#'; //������������ �����
			else playing_field[oy][ox] = '*';
		}

		view_field[oy][ox] = '&'; //����������� ������� �� ������� �����������
		system("cls"); //������� ������
		for (y = 0; y < N; y++) //����� ������� � ������� ���������
		{
			for (x = 0; x < N; x++)
			{
				printf("%c ", view_field[y][x]);

			}
			printf("\n");
		} 
		printf("%d,%d\n",oy,ox);
		printf("��� ����, ����� ��������� ���������� � ������� � �������� ������� 'E' \n"); //����������� � ���������� ������� ���������

	} while (key != 'e');

	for (y = 0; y < N; y++) //�������� ����� �� ������� 5 ������ ������ �������� #
	{
		for (x = 0; x < N; x++)
		{
			if (check == 5) break;
			if (playing_field[y][x] == '#') check += 1;
			else check = 0;
			

		}
		if (check == 5) break;
		check = 0; 
	}

	for (x = 0; x < N; x++)	//�������� �������� �� ������� 5 ������ ������ �������� #
	{
		for (y = 0; y < N; y++)
		{
			if (check == 5) break;
			if (playing_field[y][x] == '#') check += 1;
			else check = 0;
			

		}
		if (check == 5) break;
		check = 0; 
	}

	for (int i = 0; i < V; i++)
	{

	}
	//�������� ������� �����������(�� ��������)
	/*for (y = 0; y < N; y++)
	{
		int count = 0;
		for (x = 0; x < N; x++) //���������� �������� �� ������� ����� � ������ �������
		{
			if (playing_field[y][x] != '*' && playing_field[y][x] != '#' && playing_field[y][x] != '1')
			{
				for (int y1 = y; y1 < N; y1 += 1) 
				{
					for (int x1 = x; x1 < N; x1 += 1)
					{
						if (playing_field[y - 1][x] == '*' || (playing_field[y - 1][x] == playing_field[y][x])) //������� �� ������ ������ ��� �������� ������� ���� #
						{
							count += 1;
							y1 -= 1;
						}
						if (playing_field[y + 1][x] == '*' || (playing_field[y + 1][x] == playing_field[y][x]))	//������� �� ������ ����� ��� �������� ������� ���� #
						{
							count += 1;
							y1 += 1;
						}
						if (playing_field[y][x - 1] == '*' || (playing_field[y][x - 1] == playing_field[y][x]))	//������� �� ������ ����� ��� �������� ������� ���� #
						{
							count += 1;
							x1 -= 1;
						}
						if (playing_field[y][x + 1] == '*' || (playing_field[y][x + 1] == playing_field[y][x]))	//������� �� ������ ������ ��� �������� ������� ���� #
						{
							count += 1;
							x1 += 1;
						}
					}
				}
				if ((int)count != playing_field[y][x] - '0')
				{
					printf("������");
					break;
				}
			}
		}
		
	}*/

	if (check == 5) printf("����������� ������ �� ���������"); //���� �������� �� ��������, �� ������� ��������� �� ���� 


	
}

