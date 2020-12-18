// odcinanie alfa-beta
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <limits.h>

using namespace std;

void wypisz(int tab[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		cout << tab[i] << " ";
	}
}

int alfa_beta(int tab1[], int index, int t, int alfa, int beta, int obecna_wysokosc, int tab2[]) {
	if (tab1[index] != 0) return tab1[index];
	int v, temp;

	if (obecna_wysokosc % 2 == 0) { // szukamy maksimum
		v = INT_MIN;
		for (int i = 1; i <= t; i++) {
			temp = alfa_beta(tab1, index * t + i, t, alfa, beta, obecna_wysokosc + 1, tab2);
			if (temp > v) v = temp;
			if (v > beta) {//odcinanie beta
				for (; i < t; i++) {
					tab2[index * t + i] = -1;
				}
				break;
			}
			if (v > alfa) alfa = v;
		}
	}
	else { // szukamy minimum
		v = INT_MAX;
		for (int i = 1; i <= t; i++) {
			temp = alfa_beta(tab1, index * t + i, t, alfa, beta, obecna_wysokosc + 1, tab2);
			if (temp < v) v = temp;
			if (v < alfa) {//odcinanie alfa
				for (; i < t; i++) {
					tab2[index * t + i] = 1;
				}
				break;
			}
			if (v < beta) beta = v;
		}
	}
	tab1[index] = v;
	return v;
}

int main()
{
	//tworzenie i wypelnienie drzewa
	cout << "\nProgram demonstrujacy dzialanie algorytmu Min-Max z odcinaniem Alfa-Beta.";
	cout << "\nPodaj wysokosc drzewa (4-6): ";
	int h, t;
	cin >> h;
	cout << "\nPodaj liczbe potomkow kazdego wierzcholka w drzewie (2-3): ";
	cin >> t;
	// kazdy kolejny poziom ma poprzedni*t wierzchołków
	int liscie = 1;
	int wierzcholki = 1;
	for (int i = 0; i < h; i++) {
		liscie *= t;
		wierzcholki += liscie;
	}

	srand(time(NULL));
	int* tab1 = new int[wierzcholki];//wejscie
	for (int i = 0; i < wierzcholki; i++) {
		tab1[i] = 0;
	}
	int* tab2 = new int[wierzcholki];//wynik
	for (int i = 0; i < wierzcholki; i++) {
		tab2[i] = 0;
	}

	for (int i = 0; i < liscie; i++) {
		tab1[wierzcholki - i - 1] = rand() % 8 + 1;
	}
	

	cout << "\nTablica z wygenerowanymi wartosciami lisci: " << endl;
	wypisz(tab1, wierzcholki);

	// odcinanie alfa-beta (dla alfa 1, dla beta -1), preorder
	int alfa = INT_MIN;
	int beta = INT_MAX;
	int indeks = 0;
	int obecna_wysokosc = 0;

	alfa_beta(tab1, indeks, t, alfa, beta, obecna_wysokosc, tab2);
	cout << "\nTablica po uzyciu algorytmu min-max z odcinaniem alfa-beta (wierzcholki drzewa uzupelnione wartosciami): " << endl;
	wypisz(tab1, wierzcholki);

	cout << "\nTablica z zaznaczonymi odcieciami (1 dla alfa, -1 dla beta): " << endl;
	wypisz(tab2, wierzcholki);

	char pauza;
	cin >> pauza;
	delete[] tab1;
	delete[] tab2;
	return 0;
}
