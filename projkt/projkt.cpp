#include <iostream>
using namespace std;

void filing(double** mass, int **graf, int koll) {
	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			mass[i][j] = 0;

	for (int i = 0; i < koll; i++) {
		for (int j = 0; j < i; j++) {
					mass[i][j] = rand() % 10;
					mass[j][i] = mass[i][j];
					if (mass[i][j] != 0) {
						graf[i][j] = (rand() % 9)+1;
						graf[j][i] = graf[i][j];
					}
				}
			
		mass[i][i] = 0;
		graf[i][i] = 0;
	}
		
}

void timert(double ** mass, int** graf, int koll) {
	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			mass[i][j] = mass[i][j] / graf[i][j];

}


int liner(int** mass, int koll) {
	int lin = 0;
	for (int i = 0; i < koll; i++) {
		for (int j = 0; j < i; j++)
			if (mass[i][j] != 0)
				lin++;
	}
	return(lin);
}
	
void KP(int** mass, int koll) {
	int lin = liner(mass,koll);
	int min = 3;

	int** help;
	help = new int* [3];
	for (int i = 0; i < min; i++)
		help[i] = new int[300];

	min = 11;
	int ll = 0;
	int* mm = new int[lin];
	for (int i = 0; i < lin; i++)
		mm[i] = 0;
	int fix = lin;

	for (int i = 0; i < koll; i++)					//массив длин и точек
		for (int j = 0; j < i; j++) {
			if (mass[i][j] != 0)
			{
				help[0][ll] = mass[i][j];
				help[1][ll] = i;
				help[2][ll] = j;
				ll++;
			}
		}

	for (int i = 0; i < lin; i++)					//Сортировка массива по возрастанию
		for (int j = 0; j < lin; j++)
			if (help[0][i] < help[0][j]) {
				ll = help[0][i];
				help[0][i] = help[0][j];
				help[0][j] = ll;

				ll = help[1][i];
				help[1][i] = help[1][j];
				help[1][j] = ll;


				ll = help[2][i];
				help[2][i] = help[2][j];
				help[2][j] = ll;
			}


	int mirt = 0;

	while (fix != 0) {										//Очищение основной матрици
		if (mirt == ll)
			break;

		if (mm[help[1][mirt]] < 2 && mm[help[2][mirt]] < 2) {
			mm[help[1][mirt]]++;
			mm[help[2][mirt]]++;
		}
		else {
			mass[help[1][mirt]][help[2][mirt]] = 0;
			mass[help[2][mirt]][help[1][mirt]] = 0;
		}
		mirt++;
		fix--;
	}

	delete[] help;
	delete[] mm;


}









int main()
{

	setlocale(LC_ALL, "rus");

	int k = 0;
	cout << "Введите разрешение матрицы  ";

	cin >> k;

	cout << "\n\n\nМатрица   " << k << " х " << k;
	double** mass;
	mass = new double* [k];
	for (int j = 0; j < k; j++) {
		mass[j] = new double[k];
		for (int l = 0; l < k; l++)
			mass[j][l] = 0;
	}
	int** graf;
	graf = new int* [k];
	for (int j = 0; j < k; j++) {
		graf[j] = new int[k];
		for (int l = 0; l < k; l++)
			graf[j][l] = 0;
	}

	double* way = new double[k];


	filing(mass,graf, k);
	for (int i = 0; i < k; i++) {
		cout << endl;
		for (int j = 0; j < k; j++)
			cout << mass[i][j] << "  ";
	}
	cout << endl; cout << endl;
	for (int i = 0; i < k; i++) {
		cout << endl;
		for (int j = 0; j < k; j++)
			cout << graf[i][j] << "  ";
	}
	cout << endl; cout << endl;

	timert(mass, graf, k);

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			graf[i][j] = mass[i][j];
	cout << "g";
	KP(graf,k);

	cout << "g";
	for (int i = 0; i < k; i++) {
		cout << endl;
		for (int j = 0; j < k; j++)
			if (i == j)
				cout << graf[i][j] << "  ";
			else
				cout << "0  ";
	}
	cout << endl; cout << endl;













	for (int i = 0; i < k; i++)
		delete[] mass[i];
	delete[] mass;
	for (int i = 0; i < k; i++)
		delete[] graf[i];
	delete[] graf;

	
}
