#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#define N 10 //размер игрового поля
#define V 15

struct value
{
	char symbol;
	int x;
	int y;
}; //создание структуры для хранения значения размера островов и их координат

typedef struct value Value;

int array(int* array_x, int* array_y, int new_x, int new_y, int count);
int delete(int* ptr_array, int size);
int sort_array(int* array_x, int* array_y, int count);

int main()
{
	int array_x[100000];
	int array_y[100000];
	int count_array = 0;

	char playing_field[N][N]; //игровое поле
	char view_field[N][N]; //поле вывода
	Value islands[V]; //объявление структуры
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

	//проверка условия головоломки(не работает)
	for (y = 0; y < N; y++)
	{
		for (x = 0; x < N; x++) //построчная проверка на наличие цифры в ячейке массива
		{
			if (playing_field[y][x] != '*' && playing_field[y][x] != '#' && playing_field[y][x] != '1')
			{
				count_array = 0;
				for (int y1 = y; y1 < N; y1 += 1)
				{
					for (int x1 = x; x1 < N; x1 += 1)
					{
						if (playing_field[y - 1][x] == '*' || (playing_field[y - 1][x] == playing_field[y][x])) {
							array(array_x[count_array], array_y[count_array], x1, y1, count_array);
							count_array++;
							y1 -= 1;
						}
						else {
							if (playing_field[y][x - 1] == '*' || (playing_field[y][x - 1] == playing_field[y][x])) {
								array(array_x[count_array], array_y[count_array], x1, y1, count_array);
								count_array++;
								x1 -= 1;
							}
							else {
								if (playing_field[y][x + 1] == '*' || (playing_field[y][x + 1] == playing_field[y][x])) {
									array(array_x[count_array], array_y[count_array], x1, y1, count_array);
									count_array++;
									x1 += 1;
								}
								else {
									y1 = y;
									x1 = x;
								}
							}
						}

						if (playing_field[y][x - 1] == '*' || (playing_field[y][x - 1] == playing_field[y][x])) {
							array(array_x[count_array], array_y[count_array], x1, y1, count_array);
							count_array++;
							x1 -= 1;
						}
						else {
							if (playing_field[y - 1][x] == '*' || (playing_field[y - 1][x] == playing_field[y][x])) {
								array(array_x[count_array], array_y[count_array], x1, y1, count_array);
								count_array++;
								y1 -= 1;
							}
							else {
								if (playing_field[y + 1][x] == '*' || (playing_field[y + 1][x] == playing_field[y][x])) {
									array(array_x[count_array], array_y[count_array], x1, y1, count_array);
									count_array++;
									y1 += 1;
								}
								else {
									y1 = y;
									x1 = x;
								}
							}
						}

						if (playing_field[y][x + 1] == '*' || (playing_field[y][x + 1] == playing_field[y][x])) {
							array(array_x[count_array], array_y[count_array], x1, y1, count_array);
							count_array++;
							x1 += 1;
						}
						else {
							if (playing_field[y - 1][x] == '*' || (playing_field[y - 1][x] == playing_field[y][x])) {
								array(array_x[count_array], array_y[count_array], x1, y1, count_array);
								count_array++;
								y1 -= 1;
							}
							else {
								if (playing_field[y + 1][x] == '*' || (playing_field[y + 1][x] == playing_field[y][x])) {
									array(array_x[count_array], array_y[count_array], x1, y1, count_array);
									count_array++;
									y1 += 1;
								}
								else {
									y1 = y;
									x1 = x;
								}
							}
						}

						if (playing_field[y + 1][x] == '*' || (playing_field[y + 1][x] == playing_field[y][x])) {
							array(array_x[count_array], array_y[count_array], x1, y1, count_array);
							count_array++;
							y1 += 1;
						}
						else {
							if (playing_field[y][x - 1] == '*' || (playing_field[y][x - 1] == playing_field[y][x])) {
								array(array_x[count_array], array_y[count_array], x1, y1, count_array);
								count_array++;
								x1 -= 1;
							}
							else {
								if (playing_field[y][x + 1] == '*' || (playing_field[y][x + 1] == playing_field[y][x])) {
									array(array_x[count_array], array_y[count_array], x1, y1, count_array);
									count_array++;
									x1 += 1;
								}
								else {
									y1 = y;
									x1 = x;
								}
							}

							

						}

					}
				}
				sort_array(array_x, array_y, count_array);
				if ((int)count_array != playing_field[y][x] - '0')
				{
					printf("Ошибка");
					break;
				}
			}
		}

	}

	/*for (int i = 0; i < 15; i++)
	{
		int count1 = 0;
		int count2 = 0;
		for (int j = islands[i].y; j < 10; j++) {
			for (int l = islands[i].x; l < 10; l++) {
				if (playing_field[j][l] == '*' && ())
			}
		}
	}*/
	

	if (check == 5) printf("Головоломка решена не правильно"); //если проверка не пройдена, то вывести сообщение об этом 

}	

int array(int* array_x, int* array_y, int new_x, int new_y, int count)
{
	array_x[count] = new_x;
	array_y[count] = new_y;
}

int sort_array(int* array_x, int* array_y, int count) {
	for (int i = 0; i < count; i++) {
		int duble_x = array_x[i];
		int duble_y = array_y[i];
		for (int l = 0; l < count; l++) {
			for (int j = i + 1; j < count; j++) {

				if (duble_x == array_x[j] && duble_y == array_y[j]) {
					delete(array_x, count, j);
					delete(array_y, count, j);
				}
			}
		}
	}
}

int delete(int* ptr_array, int size, int i) {

	for (; i < size; i++)
	{
		ptr_array[i] = ptr_array[i + 1];
	}
}