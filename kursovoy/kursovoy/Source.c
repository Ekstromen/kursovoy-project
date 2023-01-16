#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h> 
#define N 10 //������ �������� ����
#define V 15

struct value//�������� ��������� ��� �������� �������� ������� �������� � �� ���������
{
	char symbol; // ������� �������
	int x; // ���������� � �������
	int y; // ���������� � �������
}; 

typedef struct value Value;

int read(struct value* islands); //������� ������ �� ����� ��� ���������� ���������
int create_save(char** playing_field); //������ �������� ���� � ����
int load_save(char** playing_field); //��������� �������� ���� �� ����� 
int creating_field(char** playing_field, int** check_field, Value* islands, int* px, int* py);//������� ��� �������� �������� ����
void game_out(char** playing_field, char** view_field, int* px, int* py);//������� ��� ������ �������� ���� 
int checking(char** playing_field, int** check_field, int* px, int* py, int* check_y, int* check_x);//������� ��� �������� �������� ������ �����������

int main() //������� �������
{
	int check_x[N] = { 3,4,3,7,2,6,9,4,4,10 }; //���������� �������, �������� "��� ��������� ���������� ������"
	int check_y[N] = { 4,4,7,5,4,4,7,3,7,7 };
	char **playing_field = (char **)malloc(N*sizeof(char*)); //��������� ������ �������� ����, �������� �������� ��������
	char **view_field = (char **)malloc(N*sizeof(char*)); //��������� ������, �������������� ��� ���� ������
	int **check_field = (int **)malloc(N*sizeof(int*)); //��������� ������, �������������� ��� �������� "���� ������" 
	for (int r = 0; r < N; r++) playing_field[r] = (char*)malloc(N * sizeof(char)); //��������� ������ ��� ���������� �������
	for (int r = 0; r < N; r++) view_field[r] = (char*)malloc(N * sizeof(char)); //��������� ������ ��� ���������� �������
	for (int r = 0; r < N; r++) check_field[r] = (int*)malloc(N * sizeof(int)); //��������� ������ ��� ���������� �������
	Value islands[V]; //��������� �������� ���������� � �������� ��������
	int x, y;	//���������� ��� ���������� �������� �������� ����
	int ox = 0, oy = 0; //���������� �������
	int nx, ny; //���������� �������� �� �������
	char key = '0'; //���������� ��� �������� ������������ ���������� �����������
	int* px = &x, * py = &y; //��������� �� ���������� ��������� 
	int* pox = &ox, * poy = &oy; //��������� �� ���������� ��������� 
	
	setlocale(LC_ALL, "RUS");
	read(islands); //������ ��������� islands �� �����
	menu();// ����� ������� ������� ��������� ����
	_getch(); //�������� ������ �� �����
	system("cls"); //������� �������
	if (creating_field(playing_field, check_field, islands, px, py) == 0) exit(0); //�������� ����������� �������� �������� ����
	

	do //����������� ���� ��� ����������� ����� �������� � ����������� �������
	{
		
		game_out(playing_field,view_field,*px,*py);//������� ������ �������� ���� 
		nx = ox; //���������� ������� �� ����������� 
		ny = oy; //���������� ������� �� ����������� 
		key = _getch(); //���������� ������� ����������
		if (key == 'w' && (oy > -1 && oy < 10)) oy--; //����������� �����
		if (key == 's' && (oy < 10 && oy > -1)) oy++; //����������� ����
		if (key == 'a' && (ox > -1 && ox < 10)) ox--; //����������� �����
		if (key == 'd' && (ox > -1 && ox < 10)) ox++; //����������� ������
		if (oy == 10) oy = ny; //�������� �� ����� �� ������� �������� ����
		if (oy == -1) oy = ny; //�������� �� ����� �� ������� �������� ����
		if (ox == 10) ox = nx; //�������� �� ����� �� ������� �������� ����
		if (ox == -1) ox = nx; //�������� �� ����� �� ������� �������� ����
		if (playing_field[oy][ox] != '*' && playing_field[oy][ox] != '#'){
			oy = ny; //������ �� ������������ � ������� �� ������ � �������
			ox = nx; //������ �� ������������ � ������� �� ������ � �������
		}
		if (key == 'f')//������������ �����
		{
			if (playing_field[oy][ox] == '*') playing_field[oy][ox] = '#'; //������ ���� �� ����
			else playing_field[oy][ox] = '*'; //������ ���� �� ����
		}
		create_save(playing_field); //�������� �������� ���� � ����
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
		printf("��� ����, ����� ��������� ���������� � ������� � �������� ������� 'E' \n"); //����������� � ���������� ������� ���������
		
	} while (key != 'e');
	//��������� "����� �������� ������"
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			if (y != 9 && playing_field[y][x] != '#') if (playing_field[y + 1][x] == '*' || ((playing_field[y + 1][x] - '0') > 0)) check_field[y][x] += 1;
			if (y != 0 && playing_field[y][x] != '#') if (playing_field[y - 1][x] == '*' || ((playing_field[y - 1][x] - '0') > 0)) check_field[y][x] += 1;
			if (x != 9 && playing_field[y][x] != '#') if (playing_field[y][x + 1] == '*' || ((playing_field[y][x + 1] - '0') > 0)) check_field[y][x] += 1;
			if (x != 0 && playing_field[y][x] != '#') if (playing_field[y][x - 1] == '*' || ((playing_field[y][x - 1] - '0') > 0)) check_field[y][x] += 1;
			if (playing_field[y][x] == '1') check_field[y][x] = 1;
		}
	}

	checking(playing_field,check_field,px,py,check_y,check_x);// ����� ������� ��� �������� �� "����� ������" "���� ������" � �� ��������� ��� ����������� ������������ ������� �����������.
	free(playing_field); //������� ������
	free(check_field); //������� ������
	free(view_field); //������� ������
}

int read(struct value* islands) { //������� ������
	FILE* f; //�������� �����
	f = fopen("1.txt", "r");
	if (f == NULL) return 0; //�������� ������� ������
	for (int i = 0; i < V; i++) { //���������� �����
		islands[i].symbol = fgetc(f);
		islands[i].y = fgetc(f) - '0';
		islands[i].x = fgetc(f) - '0';

	}
	fclose(f); //�������� �����
}

int create_save(char** playing_field) { //������� ������ � ����
	FILE* fb; //�������� �����
	fb = fopen("buffer.txt", "w");
	if (fb == NULL) return 0; //�������� ������� ������
	else for (int i = 0; i < N; i++) { // ������ � ����
		for (int j = 0; j < N; j++) {
			fputc(playing_field[i][j], fb);
		}
	}
	fclose(fb);//�������� �����
}

int load_save(char** playing_field) { //������� ��������
	FILE* fb; //�������� �����
	fb = fopen("buffer.txt", "r");
	if (fb == NULL) return 0; //�������� ������� ������
	else {
		for (int i = 0; i < N; i++) { //���������� �����
			for (int j = 0; j < N; j++) {
				playing_field[i][j] = fgetc(fb);
				
			}
		}
	}
	fclose(fb);//�������� �����
}

int creating_field(char **playing_field, int **check_field, Value* islands, int* px, int* py) { //������� �������� �������� ����
	int x = px, y = py; //������� ��������� ����������
	printf("�������: 1) ���� ������ ������ � ������. 2) ���� ������ ��������� ��������� ������������ ������.\n"); //����������� � �����
	char sw = '0'; 
	scanf("%c", &sw); //���� ���������� ��� switch
	FILE* fb; //�������� �����
	fb = fopen("buffer.txt", "r");
	switch (sw)
	{
	case '1':
		for (y = 0; y < N; y++) { //��������� ���������� �������� ����
			for (x = 0; x < N; x++) {
				playing_field[y][x] = '*';
			}
		}
		printf("������� ����� ������� ����� ����������...\n");
		break;

	case '2':
		if (getc(fb) == EOF) {
			for (y = 0; y < N; y++) { //��������� ���������� �������� ����
				for (x = 0; x < N; x++) {
					playing_field[y][x] = '*';
				}
			}
			printf("������! �� ��� �� ������� ������!\n");
			printf("������� ����� ������� ����� ����������...\n");
		}
		else {
			load_save(playing_field);
			printf("������� ����� ������� ����� ����������...\n");
		}
		break;

	default:
		printf("������! ������ �������� ������.\n");
		return 0;
		break;
	}
	
	fclose(fb); //�������� �����
	//��������� ���������� ���� ��������
	for (y = 0; y < N; y++) { //��������� ����������
		for (x = 0; x < N; x++) {
			check_field[y][x] = 0;
		}
	}
	for (int i = 0; i < V; i++) //������������ �������� �� ��������� � ������� �������� ����
	{
		playing_field[islands[i].y][islands[i].x] = islands[i].symbol; 
	}
 }

void game_out(char** playing_field, char** view_field, int* px, int* py) { //������� ������ �������� ���� �� �����
	int x = px, y = py;//������� ��������� ����������
	for (y = 0; y < N; y++) 
	{
		for (x = 0; x < N; x++)
		{
			view_field[y][x] = playing_field[y][x]; //�������� �������� �� ������� � ������� � ������ ��� ������ �� �����

		}
	}
}

int checking(char** playing_field, int** check_field, int* px, int* py, int* check_y, int* check_x) { //������� �������� �������
	int x = px, y = py;//������� ��������� ����������
	char check = '0';

	for (y = 0; y < N; y++) {//���� ��������� �������� � ������� ��� ����� �������� "��� ������"
		int summ = 0;
		for (x = 0; x < N; x++) {
			summ += check_field[y][x];
		}
		if (summ != check_y[y]) { //���� �������� �� ��������� �� ����������� ������ �� ���������
			check = 5; //������������ �������� ��� ������� ��� ����������� ����� ���������
			break;	//����� �� �����
		}
	}

	for (x = 0; x < N; x++) { //���� ��������� �������� � �������� ��� ����� �������� "��� ������"
		int summ = 0;
		for (y = 0; y < N; y++) {
			summ += check_field[y][x];
		}
		if (summ != check_x[x]) {//���� �������� �� ��������� �� ����������� ������ �� ���������
			check = 5; //������������ �������� ��� ������� ��� ����������� ����� ���������
			break; //����� �� �����
		}
	}
	
	for (y = 0; y < N; y++) //�������� ����� � ������� ���� �� ������� 5 ������ ������ �������� #
	{
		for (x = 0; x < N; x++)
		{
			if (check == 5) break;
			if (playing_field[y][x] == '#') check += 1; 
			else check = 0; //��������� ���������� �� ������������������ ��������
		}
		if (check == 5) break;
		check = 0;	//��������� ���������� �� ������������������ ��������
	}

	for (x = 0; x < N; x++)	//�������� �������� � ������� ���� �� ������� 5 ������ ������ �������� #
	{
		for (y = 0; y < N; y++)
		{
			if (check == 5) break;
			if (playing_field[y][x] == '#') check += 1;
			else check = 0; //��������� ���������� �� ������������������ ��������
		}
		if (check == 5) break;
		check = 0; //��������� ���������� �� ������������������ ��������
	}

	printf("\n"); //������� ������
	if (check == 5) printf("����������� ������ �����������.\n"); //���� �������� �� ��������, �� ������� ��������� �� ���� 
	else {
		printf("����������� ������ ���������!\n");//���� �������� ��������, �� ������� ��������� �� ���� 
		//��������� ����� 
		FILE* file = fopen("buffer.txt", "w"); //�������� ����� � ������ ������
		fclose(file); //�������� �����
	}
}

int menu() { //������� ������� ������� �� ����� ����������� � �������� �����������
	
	FILE* file = fopen("menu.txt", "r+"); //�������� ����� � ������ ������
	for (int i = 0; i < 18; i++) {
		char* buffer = (char*)malloc(1000 * sizeof(char));
		buffer = fgets(buffer, 1000, file);
		printf("%s", buffer);
	}
	fclose(file); //�������� �����
}