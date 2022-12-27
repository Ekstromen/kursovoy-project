#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 10 //размер игрового поля
#define V 15

struct value
{
	char symbol;
	int x;
	int y;
}; //создание структуры для хранения значения размера островов и их координат

typedef struct value Value;

int main()
{
	int check_x[N] = {3,4,3,7,2,6,9,4,4,10};
	int check_y[N] = {4,4,7,5,4,4,7,3,7,7};
	char playing_field[N][N]; //игровое поле
	char view_field[N][N]; //поле вывода
	int check_field[N][N]; //поле проверки
	Value islands[V]; //структура хранящяя координаты и значения островов
	int x, y;	//координаты для объявления значений игрового поля
	int ox = 0, oy = 0; //координаты курсора
	int nx, ny; //координаты курсора до перемещения
	char key = '0',check = '0', check1 = '0';

	islands[0].symbol = '1'; //заполнение структуры 
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

	for (y = 0; y < N; y++) //создание игрового поля с помощью двумерного массива
	{
		for (x = 0; x < N; x++)
		{
			playing_field[y][x] = '*';
		
		}
	}

	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			check_field[y][x] = 0;
		}
	}

	for (int i = 0; i < V; i++)
	{
		playing_field[islands[i].y][islands[i].x] = islands[i].symbol;//присваивание значений из структуры к массиву игрового поля 
	}

	do //бесконечный цикл для постоянного ввода значений и перемещения курсора
	{

		for (y = 0; y < N; y++) //создание игрового поля с помощью двумерного массива
		{
			for (x = 0; x < N; x++)
			{
				view_field[y][x] = playing_field[y][x]; //передача значений из массива с данными в массив для вывода на экран

			}
		}

		key = _getch(); //считывание нажания клавиатуры

		nx = ox; //координаты курсора до перемещения 
		ny = oy; //координаты курсора до перемещения 

		if (key == 'w' && (oy > -1 && oy < 10)) oy--; //перемещение вверх
		if (key == 's' && (oy < 10 && oy > -1)) oy++; //перемещение вниз
		if (key == 'a' && (ox > -1 && ox < 10)) ox--; //перемещение влево
		if (key == 'd' && (ox > -1 && ox < 10)) ox++; //перемещение вправо
		if (oy == 10) oy = ny; //проверка на выход за границы игрового поля
		if (oy == -1) oy = ny; //проверка на выход за границы игрового поля
		if (ox == 10) ox = nx; //проверка на выход за границы игрового поля
		if (ox == -1) ox = nx; //проверка на выход за границы игрового поля
		if (playing_field[oy][ox] != '*' && playing_field[oy][ox] != '#')
		{
			oy = ny; //запрет на закрашивание и переход на ячейки с цифрами
			ox = nx; //запрет на закрашивание и переход на ячейки с цифрами
		}

		if (key == 'f') 
		{
			if (playing_field[oy][ox] == '*') playing_field[oy][ox] = '#'; //закрашивание ячеек
			else playing_field[oy][ox] = '*';
		}

		view_field[oy][ox] = '&'; //отображение курсора на текущих координатах
		system("cls"); //очистка экрана
		for (y = 0; y < N; y++) //вывод массива в консоль посторчно
		{
			for (x = 0; x < N; x++)
			{
				printf("%c ", view_field[y][x]);

			}
			printf("\n");
		} 
		printf("%d,%d\n",oy,ox);
		printf("Для того, чтобы завершить выполнение и перейти к проверке нажмите 'E' \n"); //приглашение к завершению решения головомки

	} while (key != 'e');

	//Создание массива с проверкой
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			if (playing_field[y][x] != '#' && (playing_field[y + 1][x] == '*' || ((playing_field[y + 1][x] - '0') > 0)) && y != 9) check_field[y][x] += 1;
			if (playing_field[y][x] != '#' && (playing_field[y - 1][x] == '*' || ((playing_field[y - 1][x] - '0') > 0)) && y != 0) check_field[y][x] += 1;
			if (playing_field[y][x] != '#' && (playing_field[y][x + 1] == '*' || ((playing_field[y][x + 1] - '0') > 0)) && x != 9) check_field[y][x] += 1;
			if (playing_field[y][x] != '#' && (playing_field[y][x - 1] == '*' || ((playing_field[y][x - 1] - '0') > 0)) && x != 0) check_field[y][x] += 1;
			if (playing_field[y][x] == '1') check_field[y][x] = 1;
		}
	}

	for (y = 0; y < N; y++) {
		int summ = 0;
		for (x = 0; x < N; x++) {
			summ += check_field[y][x];
		}
		if (summ != check_y[y]) {
			printf("Неправильно y\n");
			break;
		}
	}

	for (x = 0; x < N; x++) {
		int summ = 0;
		for (y = 0; y < N; y++) {
			summ += check_field[y][x];
		}
		if (summ != check_x[x]) {
			printf("Неправильно x\n");
			break;
		}
	}

	for (y = 0; y < N; y++) //вывод массива в консоль посторчно
	{
		for (x = 0; x < N; x++)
		{
			printf("%d ", check_field[y][x]);

		}
		printf("\n");
	}


	for (y = 0; y < N; y++) //проверка строк на наличие 5 идущих подрял символов #
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

	for (x = 0; x < N; x++)	//проверка столбцов на наличие 5 идущих подрял символов #
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

	



	if (check == 5) printf("Головоломка решена не правильно"); //если проверка не пройдена, то вывести сообщение об этом 

}	
