#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h> 
#define N 10 //размер игрового поля
#define V 15

struct value//создание структуры для хранения значения размера островов и их координат
{
	char symbol; // площадь острова
	int x; // координата х острова
	int y; // координата у острова
}; 

typedef struct value Value;

int read(struct value* islands); //функция чтения из файла для заполнения структуры
int create_save(char** playing_field); //запись игрового поля в файл
int load_save(char** playing_field); //загррузка игрового поля из файла 
int creating_field(char** playing_field, int** check_field, Value* islands, int* px, int* py);//функция для создания игрового поля
void game_out(char** playing_field, char** view_field, int* px, int* py);//фунуция для вывода игрового поля 
int checking(char** playing_field, int** check_field, int* px, int* py, int* check_y, int* check_x);//функция для проверки основных правил головоломки

int main() //главная функция
{
	int check_x[N] = { 3,4,3,7,2,6,9,4,4,10 }; //одномерные массивы, хранящие "код правильно пройденнго уровня"
	int check_y[N] = { 4,4,7,5,4,4,7,3,7,7 };
	char **playing_field = (char **)malloc(N*sizeof(char*)); //двумерный массив игрового поля, хранящий основные значения
	char **view_field = (char **)malloc(N*sizeof(char*)); //двумерный массив, использующийся как поле вывода
	int **check_field = (int **)malloc(N*sizeof(int*)); //двумерный массив, использующийся для создания "кода уровня" 
	for (int r = 0; r < N; r++) playing_field[r] = (char*)malloc(N * sizeof(char)); //выделение памяти для двумерного массива
	for (int r = 0; r < N; r++) view_field[r] = (char*)malloc(N * sizeof(char)); //выделение памяти для двумерного массива
	for (int r = 0; r < N; r++) check_field[r] = (int*)malloc(N * sizeof(int)); //выделение памяти для двумерного массива
	Value islands[V]; //структура хранящяя координаты и значения островов
	int x, y;	//координаты для объявления значений игрового поля
	int ox = 0, oy = 0; //координаты курсора
	int nx, ny; //предыдущие координа ты курсора
	char key = '0'; //переменные для проверки правильности выполнения головоломки
	int* px = &x, * py = &y; //указатели на переменные координат 
	int* pox = &ox, * poy = &oy; //указатели на переменные координат 
	
	setlocale(LC_ALL, "RUS");
	read(islands); //чтение структуры islands из файла
	menu();// вызов функции которая открывает меню
	_getch(); //задержка вывода на экран
	system("cls"); //очистка консоли
	if (creating_field(playing_field, check_field, islands, px, py) == 0) exit(0); //проверка возможности создания игрового поля
	

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
		if (playing_field[oy][ox] != '*' && playing_field[oy][ox] != '#'){
			oy = ny; //запрет на закрашивание и переход на ячейки с цифрами
			ox = nx; //запрет на закрашивание и переход на ячейки с цифрами
		}
		if (key == 'f')//закрашивание ячеек
		{
			if (playing_field[oy][ox] == '*') playing_field[oy][ox] = '#'; //замена суши на море
			else playing_field[oy][ox] = '*'; //замена моря на сушу
		}
		create_save(playing_field); //загрузка игрового поля в файл
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

	checking(playing_field,check_field,px,py,check_y,check_x);// вызов функции для создания из "карты уровня" "кода уровня" и их сравнение для определения правильности решения головоломки.
	free(playing_field); //очистка памяти
	free(check_field); //очистка памяти
	free(view_field); //очистка памяти
}

int read(struct value* islands) { //функция чтения
	FILE* f; //открытие файла
	f = fopen("1.txt", "r");
	if (f == NULL) return 0; //проверка файлого потока
	for (int i = 0; i < V; i++) { //считывание файла
		islands[i].symbol = fgetc(f);
		islands[i].y = fgetc(f) - '0';
		islands[i].x = fgetc(f) - '0';

	}
	fclose(f); //закрытие файла
}

int create_save(char** playing_field) { //функция записи в файл
	FILE* fb; //открытие файла
	fb = fopen("buffer.txt", "w");
	if (fb == NULL) return 0; //проверка файлого потока
	else for (int i = 0; i < N; i++) { // запись в файл
		for (int j = 0; j < N; j++) {
			fputc(playing_field[i][j], fb);
		}
	}
	fclose(fb);//закрытие файла
}

int load_save(char** playing_field) { //функция загрузки
	FILE* fb; //открытие файла
	fb = fopen("buffer.txt", "r");
	if (fb == NULL) return 0; //проверка файлого потока
	else {
		for (int i = 0; i < N; i++) { //считывание файла
			for (int j = 0; j < N; j++) {
				playing_field[i][j] = fgetc(fb);
				
			}
		}
	}
	fclose(fb);//закрытие файла
}

int creating_field(char **playing_field, int **check_field, Value* islands, int* px, int* py) { //функция создания игрового поля
	int x = px, y = py; //функция принимает координаты
	printf("Введите: 1) Если хотите начать с начала. 2) Если хотите загрузить последние сохранненные данные.\n"); //приглашение к вводу
	char sw = '0'; 
	scanf("%c", &sw); //ввод переменной для switch
	FILE* fb; //открытие файла
	fb = fopen("buffer.txt", "r");
	switch (sw)
	{
	case '1':
		for (y = 0; y < N; y++) { //первичное заполнение игрового поля
			for (x = 0; x < N; x++) {
				playing_field[y][x] = '*';
			}
		}
		printf("Нажмите любую клавишу чтобы продолжить...\n");
		break;

	case '2':
		if (getc(fb) == EOF) {
			for (y = 0; y < N; y++) { //первичное заполнение игрового поля
				for (x = 0; x < N; x++) {
					playing_field[y][x] = '*';
				}
			}
			printf("Ошибка! Вы еще не вводили данные!\n");
			printf("Нажмите любую клавишу чтобы продолжить...\n");
		}
		else {
			load_save(playing_field);
			printf("Нажмите любую клавишу чтобы продолжить...\n");
		}
		break;

	default:
		printf("Ошибка! Введен неверный символ.\n");
		return 0;
		break;
	}
	
	fclose(fb); //закрытие файла
	//первичное заполнение поля проверки
	for (y = 0; y < N; y++) { //первичное заполнение
		for (x = 0; x < N; x++) {
			check_field[y][x] = 0;
		}
	}
	for (int i = 0; i < V; i++) //присваивание значений из структуры к массиву игрового поля
	{
		playing_field[islands[i].y][islands[i].x] = islands[i].symbol; 
	}
 }

void game_out(char** playing_field, char** view_field, int* px, int* py) { //функция вывода игрового поля на экран
	int x = px, y = py;//функция принимает координаты
	for (y = 0; y < N; y++) 
	{
		for (x = 0; x < N; x++)
		{
			view_field[y][x] = playing_field[y][x]; //передача значений из массива с данными в массив для вывода на экран

		}
	}
}

int checking(char** playing_field, int** check_field, int* px, int* py, int* check_y, int* check_x) { //функция проверки решения
	int x = px, y = py;//функция принимает координаты
	char check = '0';

	for (y = 0; y < N; y++) {//цикл суммирует значения в строках тем самым создавая "код уровня"
		int summ = 0;
		for (x = 0; x < N; x++) {
			summ += check_field[y][x];
		}
		if (summ != check_y[y]) { //если значения не совпадают то головоломка решена не правильно
			check = 5; //присваивание значения при котором все последующие циклы прервутся
			break;	//выход из цикла
		}
	}

	for (x = 0; x < N; x++) { //цикл суммирует значения в столбцах тем самым создавая "код уровня"
		int summ = 0;
		for (y = 0; y < N; y++) {
			summ += check_field[y][x];
		}
		if (summ != check_x[x]) {//если значения не совпадают то головоломка решена не правильно
			check = 5; //присваивание значения при котором все последующие циклы прервутся
			break; //выход из цикла
		}
	}
	
	for (y = 0; y < N; y++) //проверка строк в игровом поле на наличие 5 идущих подрял символов #
	{
		for (x = 0; x < N; x++)
		{
			if (check == 5) break;
			if (playing_field[y][x] == '#') check += 1; 
			else check = 0; //обнуление переменной тк последовательность нарушена
		}
		if (check == 5) break;
		check = 0;	//обнуление переменной тк последовательность нарушена
	}

	for (x = 0; x < N; x++)	//проверка столбцов в игровом поле на наличие 5 идущих подряд символов #
	{
		for (y = 0; y < N; y++)
		{
			if (check == 5) break;
			if (playing_field[y][x] == '#') check += 1;
			else check = 0; //обнуление переменной тк последовательность нарушена
		}
		if (check == 5) break;
		check = 0; //обнуление переменной тк последовательность нарушена
	}

	printf("\n"); //пропуск строки
	if (check == 5) printf("Головоломка решена неправильно.\n"); //если проверка не пройдена, то вывести сообщение об этом 
	else {
		printf("Головоломка решена правильно!\n");//если проверка пройдена, то вывести сообщение об этом 
		//обнуление файла 
		FILE* file = fopen("buffer.txt", "w"); //открытие файла в режиме чтения
		fclose(file); //закрытие файла
	}
}

int menu() { //функция которая выводит на экран приглашение к введению головоломки
	
	FILE* file = fopen("menu.txt", "r+"); //открытие файла в режиме чтения
	for (int i = 0; i < 18; i++) {
		char* buffer = (char*)malloc(1000 * sizeof(char));
		buffer = fgets(buffer, 1000, file);
		printf("%s", buffer);
	}
	fclose(file); //закрытие файла
}