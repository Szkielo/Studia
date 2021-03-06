#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	////////////////////////////////////////// pobieranie danych
	int n, skierowany, wierzch;
	cout << "Program sluzacy do generowania grafow R-MAT" << endl;
	cout << "\nPodaj typ grafu jaki chcesz stworzyc: \n1. skierowany \n2. nieskierowany" << endl;
	cin >> skierowany;
	cout << "\nPodaj liczbe wierzcholkow grafu (zostanie wygenerowane 2^n wierzcholkow): ";
	cin >> n;
	wierzch = pow(2, n);
	int cw1, cw2, cw3, cw4;
	cout << "Podaj prawdopodobienstwo dla 1 cwiartki: ";
	cin >> cw1;
	cout << "Podaj prawdopodobienstwo dla 2 cwiartki: ";
	cin >> cw2;
	cout << "Podaj prawdopodobienstwo dla 3 cwiartki: ";
	cin >> cw3;
	cout << "Podaj prawdopodobienstwo dla 4 cwiartki: ";
	cin >> cw4;

	int gestosc;
	cout << "\nPodaj gestosc zapelnienia grafu (0 - 100): ";
	cin >> gestosc;
	
	////////////////////////////////////////// tablica i warunek
	int ** tab = new int* [wierzch];
	for (int i = 0; i < wierzch; i++) {
		tab[i] = new int[wierzch] {0};
	}

	int x, y, wys, szer, warunek; //x, y to wspolzedne
	int counter = 0;
	if (skierowany == 1)
		warunek = wierzch * wierzch * gestosc / 100;
	else
		warunek = wierzch * wierzch / 2 * gestosc / 100;
	
	////////////////////////////////////////// wypelnienie tablic
	srand(time(NULL));
	int random;
	do {
		wys = wierzch;
		szer = wierzch;
		x = 0;
		y = 0;
		do {
			random = rand() % (cw1+cw2+cw3+cw4); // zabezpieczenie przed prawdopodobienstwem > 100%
			szer /= 2;
			wys /= 2;
			if (random <= cw1) {}
			else if (random > cw1 && random <= (cw1 + cw2))
				y += wys;
			else if (random > (cw1 + cw2) && random <= (cw1 + cw2 + cw3))
				x += szer;
			else
			{
				x += szer;
				y += wys;
			}
		} while (szer > 1);

		if (tab[x][y] != 1)
		{
			tab[x][y] = 1;
			if (skierowany == 2) tab[y][x] = 1; //odbicie symetryczne dla nieskierowanych
			counter++;
		}
	} while (counter < warunek);

	//////////////////////////////////////////////// wypisanie na ekran i do pliku
	
	ofstream plik;
		plik.open("r-mat.txt");
	for (int i = 0; i < wierzch; i++) {
		for (int j = 0; j < wierzch; j++) {
			cout << tab[i][j] << " ";
			plik << tab[i][j] << " ";
		}
		cout << endl;
		plik << endl;
	}
	plik.close();
	
	//////////////////////////////////////////////// delete tab + pause
	char pauza;
	cin >> pauza;
	for (int i = 0; i < wierzch; i++) {
		delete[] tab[i];
	}
	delete[] tab;
	return 0;
}

