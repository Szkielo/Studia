// Drzewa t-narne
//

#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;


void wypisz(int * Z, int* X, int link, int wezly, ofstream& zapisX, ofstream& zapisZ) {
	cout << "";
	for (int i = 0; i < link; i++) {
		cout << Z[i] << " ";
		zapisZ << Z[i] << " ";
	}
	cout << "                               ";
	for (int i = 0; i < wezly; i++) {
		cout << X[i];
		zapisX << X[i];
	}
	cout << endl;
	zapisZ << endl;
	zapisX << endl;
}

void resetZ(int* Z, int link, int kids, int wezly, int& step, bool& end) {
	if (link - 1 == 0) end = true;
	else if (Z[link - 1] == (wezly - step)) {
		step += kids;
		resetZ(Z, link - 1, kids, wezly, step, end);
		Z[link - 1] = Z[link - 2] + 1;
	}
	else {
		Z[link - 1]++;
	}
}

void genX(int* Z, int * X, int link, int wezly) {
	for (int i = 0; i < wezly; i++) {
		X[i] = 0;
	}
	for (int i = 0; i < link; i++) {
		X[Z[i] - 1] = 1;
	}
}

void generate(int * Z, int* X, int link, int kids, int wezly, ofstream& zapisX, ofstream& zapisZ, int& gencount) { // go up to slots from poprzedni el + 1, then add 1 to one before, go again... maksymalnie (wierzcholki) razy
	int step = 0;
	bool end = false;
	do {
			for (int i = Z[link - 1]; i <= wezly; i++) {
				Z[link - 1] = i;
				genX(Z, X, link, wezly);
				wypisz(Z, X, link, wezly, zapisX, zapisZ);
				gencount++;
			}
			resetZ(Z, link, kids, wezly, step, end); // petla przeszla, trzeba dodać do poprzedniego i zresetować
			step = 0;
	} while (end == false);
}


int main()
{
	cout << "Program generujacy Z-sekwencje i X-sekwencje dla drzew t-narnych.";
	cout << "\nWyniki zostana zapisane do dwoch roznych plikow.";
	cout << "\nPodaj liczbe potomkow na wierzcholek: ";
	int link, kids;
	cin >> kids;
	cout << "\nPodaj liczbe wierzcholkow obdarzonych potomkami: ";
	cin >> link;

	int wezly = (link - 1) * kids + 1; // pomijamy niemajace potomkow, +1 z korzenia
	int * X = new int[wezly] {};
	int * Z = new int[link] {};
	for (int i = 0; i < link; i++) {
		Z[i] = i + 1;
	}
	int gencount = 0;

	ofstream zapisX("listaX.txt");
	ofstream zapisZ("listaZ.txt");
	//---------
	cout << endl;
	cout << "\nZ-sekwencje:                       X-sekwencje:" << endl;
	generate(Z, X, link, kids, wezly, zapisX, zapisZ, gencount);
	//---------
	cout << "\nLiczba wygenerowanych sekwencji: " << gencount;
	zapisZ << "\nLiczba wygenerowanych sekwencji: " << gencount;
	zapisX << "\nLiczba wygenerowanych sekwencji: " << gencount;
	zapisX.close();
	zapisZ.close();
	delete[]X;
	delete[]Z;
	char pause;
	cin >> pause;
	return 0;
}

