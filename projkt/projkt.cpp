#include <iostream>
#include <math.h>
using namespace std;

void filing(int** mass, int** spid, int** stoper, int koll) {
	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			mass[i][j] = 0;
	int* lidr;
	lidr = new int[koll];

	for (int i = 0; i < koll; i++)
		lidr[i] = 0;

	for (int i = 0; i < koll; i++) {
		for (int j = 0; j < i; j++) {
			if (i != j) {
				if (lidr[i] < 4 && lidr[j] < 4) {
					lidr[i]++;
					lidr[j]++;
					mass[i][j] = rand() % 100 + 30;
					mass[j][i] = mass[i][j];
					spid[i][j] = rand() % 10 + 1;
					spid[j][i] = spid[i][j];
					stoper[i][j] = rand() % 10;
					stoper[j][i] = stoper[i][j];
				}
			}

		}
		mass[i][i] = 0;
	}
	delete[] lidr;
}//Заполнений матриц
void outer(int** mass, int koll) {
	cout << endl;
	for (int i = 0; i < koll; i++) {
		cout << endl;
		for (int j = 0; j < koll; j++)
			cout << mass[i][j] << " ";
	}
}// Вывод матрицы
void BR(int** mass, int koll) {


	int* help;
	help = new int[koll];	// массив обратных элементов
	for (int i = 0; i < koll; i++)
		help[i] = -1;

	int min = 11;
	//	int ll;
	bool flag = false;
	//	cout << "\n\n";
	for (int i = 0; i < koll; i++) {							// нахождение вершин между которых находятся устраивающие нас пути
		min = 11;
		for (int j = 0; j < koll; j++) {
			if (mass[i][j] != 0) {
				if (i != help[j]) {
					if (i != 0) {
						if (help[i - 1] + 1 != j) {
							//							flag = true;
							if (min > mass[i][j]) {
								min = mass[i][j];
								help[i] = j;
							}
						}
					}
					else
					{
						if (min > mass[i][j]) {
							min = mass[i][j];
							help[i] = j;
						}
					}
				}
			}
		}
		//		cout <<i<<"  " <<help[i] << " / ";
	}


	//	cout << "\n\n";

	for (int i = 0; i < koll; i++)						//Удаление всего лишнего
		for (int j = 0; j < koll; j++) {
			if (i < j) {
				if (mass[i][j] != 0) {
					if (j != help[i] && i != help[j]) {
						mass[i][j] = 0;
						mass[j][i] = 0;
					}
				}
			}
		}
	delete[] help;
}//поиск оптимальной сети
void matrix(int** mass, int** spid, int** stoper, int koll) {
	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			if (mass[i][j] != 0)
				mass[i][j] = mass[i][j] / spid[i][j] + stoper[i][j];
}   //Расчет веса каждого пути зависимости от его длины, скорости и задержки
void kopi(int** mass, int** help, int koll) {
	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			help[i][j] = mass[i][j];
}//Копирование матриц
void minway(int** mass, int koll) {
	double min = 0;
	for (int i = 0; i < koll; i++) {
		min = 6000000;
		for (int j = 0; j < koll; j++) {
			if (mass[i][j] < min && mass[i][j] != 0) {
				min = mass[i][j];
			}
			else {
				mass[i][j] = 0;
				mass[j][i] = 0;
			}
		}
	}
}//Поиск минимального пути
void maxway(int** mass, int koll) {
	double max = 0;
	for (int i = 0; i < koll; i++) {
		max = 0;
		for (int j = 0; j < koll; j++) {
			if (mass[i][j] > max && mass[i][j] != 0) {
				max = mass[i][j];
			}
			else {
				mass[i][j] = 0;
				mass[j][i] = 0;
			}
		}
	}
} //Поиск максимального пути


int main()
{
	setlocale(LC_ALL, "rus");
	int k;
	cout << "Введите размер  ";
	cin >> k;

	int** mass;
	mass = new int* [k];
	for (int j = 0; j < k; j++) {
		mass[j] = new int[k];
		for (int l = 0; l < k; l++)
			mass[j][l] = 0;
	}
	int** spid;
	spid = new int* [k];
	for (int j = 0; j < k; j++) {
		spid[j] = new int[k];
		for (int l = 0; l < k; l++)
			spid[j][l] = 0;
	}
	int** stoper;
	stoper = new int* [k];
	for (int j = 0; j < k; j++) {
		stoper[j] = new int[k];
		for (int l = 0; l < k; l++)
			stoper[j][l] = 0;
	}
	int** helper;
	helper = new int* [k];
	for (int j = 0; j < k; j++) {
		helper[j] = new int[k];
		for (int l = 0; l < k; l++)
			helper[j][l] = 0;
	}

	filing(mass, spid, stoper, k);


	kopi(mass, helper, k);
	matrix(helper, spid, stoper, k);

	outer(helper, k);
	BR(helper, k);
	outer(helper, k);

	kopi(mass, helper, k);
	minway(helper, k);
	outer(helper, k);


	kopi(mass, helper, k);
	maxway(helper, k);
	outer(helper, k);





}