#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h> 
#define N 10 //размер игрового поля
#define V 15

struct value
{
	char symbol;
	int x;
	int y;
}; //создание структуры для хранения значения размера островов и их координат

typedef struct value Value;


void creating_field(char** playing_field, int** check_field, Value* islands, int* px, int* py);//функция для создания игрового поля
void game_out(char** playing_field, char** view_field, int* px, int* py);//фунуция для вывода игрового поля 
int checking(char** playing_field, int** check_field, int* px, int* py, int* check_y, int* check_x, int check);//функция для проверки основных правил головоломки

int main()
{
	int check_x[N] = { 3,4,3,7,2,6,9,4,4,10 }; //одномерные массивы, хранящие "код правильно пройденнго уровня"
	int check_y[N] = { 4,4,7,5,4,4,7,3,7,7 };
	char **playing_field = (char **)malloc(N*sizeof(char*)); //двумерный массив игрового поля, хранящий основные значения
	char **view_field = (char **)malloc(N*sizeof(char*)); //двумерный массив, использующийся как поле вывода
	int **check_field = (int **)malloc(N*sizeof(int*)); //двумерный массив, использующийся для создания "кода уровня" 
	Value islands[V]; //структура хранящяя координаты и значения островов
	islands[0].symbol = '1'; islands[0].y = 0; islands[0].x = 2; islands[1].symbol = '2'; islands[1].y = 0; islands[1].x = 7; islands[2].symbol = '2'; islands[2].y = 1; islands[2].x = 1; islands[3].symbol = '1'; islands[3].y = 1; islands[3].x = 4; islands[4].symbol = '3';islands[4].y = 2;islands[4].x = 5;islands[5].symbol = '5';islands[5].y = 2;islands[5].x = 9;islands[6].symbol = '2';islands[6].y = 3;islands[6].x = 2;islands[7].symbol = '1';islands[7].y = 4;islands[7].x = 0;islands[8].symbol = '5';islands[8].y = 4;islands[8].x = 6;islands[9].symbol = '2';islands[9].y = 5;islands[9].x = 1;islands[10].symbol = '1';islands[10].y = 5;islands[10].x = 8;islands[11].symbol = '5';islands[11].y = 6;islands[11].x = 4;islands[12].symbol = '2';islands[12].y = 8;islands[12].x = 0;islands[13].symbol = '3';islands[13].y = 9;islands[13].x = 5;islands[14].symbol = '4';islands[14].y = 9;islands[14].x = 7;
	int x, y;	//координаты для объявления значений игрового поля
	int ox = 0, oy = 0; //координаты курсора
	int nx, ny; //предыдущие координаты курсора
	char key = '0', check = '0', check1 = '0'; //переменные для проверки правильности выполнения головоломки
	int* px = &x, * py = &y; //указатели на переменные координат 
	int* pox = &ox, * poy = &oy; //указатели на переменные координат 
	char* pkey = &key; //указатели на переменные координат 
	
	for (int r = 0; r < N; r++) {
		playing_field[r] = (char*)malloc(N * sizeof(char));
	}
	for (int r = 0; r < N; r++) {
		view_field[r] = (char*)malloc(N * sizeof(char));
	}
	for (int r = 0; r < N; r++) {
		check_field[r] = (int*)malloc(N * sizeof(int));
	}
	setlocale(LC_ALL, "RUS");
	menu();// вызов функции которая открывает меню

	creating_field(playing_field,check_field,islands,px,py); //вызов функции для создания игровогополя 

	do //бесконечный цикл для постоянного ввода значений и перемещения курсора
	{
		game_out(playing_field,view_field,*px,*py);//функция вывода игрового поля 

	
		nx = ox; //координаты курсора до перемещения 
		ny = oy; //координаты курсора до перемещения 
		key = _getch(); //считывание нажания клавиатуры
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

		if (key == 'f')//закрашивание ячеек
		{
			if (playing_field[oy][ox] == '*') playing_field[oy][ox] = '#'; 
			else playing_field[oy][ox] = '*';
		}
		view_field[oy][ox] = '&'; //отображение курсора на текущих координатах
		system("cls"); //очистка экрана
		//вывод массива в консоль посторчно
		for (y = 0; y < N; y++) 
		{
			for (x = 0; x < N; x++)
			{
				printf("%c ", view_field[y][x]);

			}
			printf("\n");
		}
		printf("Для того, чтобы завершить выполнение и перейти к проверке нажмите 'E' \n"); //приглашение к завершению решения головомки

	} while (key != 'e');
	//генерация "карты значений уровня"
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			if (y != 9 && playing_field[y][x] != '#') if (playing_field[y + 1][x] == '*' || ((playing_field[y + 1][x] - '0') > 0)) check_field[y][x] += 1;
			if (y != 0 && playing_field[y][x] != '#') if (playing_field[y - 1][x] == '*' || ((playing_field[y - 1][x] - '0') > 0)) check_field[y][x] += 1;
			if (x != 9 && playing_field[y][x] != '#') if (playing_field[y][x + 1] == '*' || ((playing_field[y][x + 1] - '0') > 0)) check_field[y][x] += 1;
			if (x != 0 && playing_field[y][x] != '#') if (playing_field[y][x - 1] == '*' || ((playing_field[y][x - 1] - '0') > 0)) check_field[y][x] += 1;
			if (playing_field[y][x] == '1') check_field[y][x] = 1;
		}
	}

	checking(playing_field,check_field,px,py,check_y,check_x,check);// вызов функции для создания из "карты уровня" "кода уровня" и их сравнение для определения правильности решения головоломки.
}



void creating_field(char **playing_field, int **check_field, Value* islands, int* px, int* py) {
	int x = px, y = py; //функция принимает координаты
	for (y = 0; y < N; y++) //первичное заполнение игрового поля
	{
		for (x = 0; x < N; x++)
		{
			playing_field[y][x] = '*';

		}
	}
	//первичное заполнение поля проверки
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			check_field[y][x] = 0;
		}
	}
	//присваивание значений из структуры к массиву игрового поля
	for (int i = 0; i < V; i++)
	{
		playing_field[islands[i].y][islands[i].x] = islands[i].symbol; 
	}
 }

void game_out(char** playing_field, char** view_field, int* px, int* py) {
	int x = px, y = py;//функция принимает координаты
	for (y = 0; y < N; y++) 
	{
		for (x = 0; x < N; x++)
		{
			view_field[y][x] = playing_field[y][x]; //передача значений из массива с данными в массив для вывода на экран

		}
	}
}

int checking(char** playing_field, int** check_field, int* px, int* py, int* check_y, int* check_x, int check) {
	int x = px, y = py;//функция принимает координаты
	//цикл суммирует значения в строках и в столбцах тем самым коздавая "код уровня"
	for (y = 0; y < N; y++) {
		int summ = 0;
		for (x = 0; x < N; x++) {
			summ += check_field[y][x];
		}
		if (summ != check_y[y]) { //если значения не совпадают то головоломка решена не правильно
			check == 5;
			break;
		}
	}

	for (x = 0; x < N; x++) {
		int summ = 0;
		for (y = 0; y < N; y++) {
			summ += check_field[y][x];
		}
		if (summ != check_x[x]) {//если значения не совпадают то головоломка решена не правильно
			check == 5;
			break;
		}
	}
	
	for (y = 0; y < N; y++) //проверка строк в игровом поле на наличие 5 идущих подрял символов #
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

	for (x = 0; x < N; x++)	//проверка столбцов в игровом поле на наличие 5 идущих подрял символов #
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
	printf("\n");
	if (check == 5) printf("Головоломка решена не правильно.\n"); //если проверка не пройдена, то вывести сообщение об этом 
	else printf("Головоломка решена правильно!\n");//если проверка пройдена, то вывести сообщение об этом 
}

int menu() { //функция которая выводит на экран приглашение к введению гроловоломки
	printf("Вас приветствует головоломка 'Нурикабе-линия' !\n");
	printf("На экране у вас появиться игровое поле на котором будут символы '*', которые обозначают сушу, а также на игровом поле будут цифры, которые обозначают площадь острова включая клетку с самой цифрой.\n");
	printf("Задача игрока: поставить клетки моря '#' так, чтобы острова соответствовали площади прилежащих к ним цифр, при этом соблюдая правила головоломки.\n");
	printf("Правила: пять клеток '#' не должны стоять в ряд; область размером 2 x 2 клетки может состоять из '#'.\n");
	printf("Пример решеной головоломки:\n");
	printf("# * * # * 3 # #\n");
	printf("* # * # * # 6 *\n");
	printf("3 # * # # # * *\n");
	printf("* # 5 # # # * *\n");
	printf("# # # * * 3 # #\n");
	printf("# * # # # # * 6\n");
	printf("# 2 # # # # * *\n");
	printf("# # 2 * # # * *\n");
	printf("Для перемещения используй клавиши 'wasd', для замены символов используй клавишу 'f', для завершения игры 'e' (Символы должны быть строчные и на английской раскладке).\n");
	printf("Нажмите любую клавишу чтобы продолжить...\n");
}
