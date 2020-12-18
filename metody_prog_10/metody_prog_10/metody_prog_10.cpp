//tworze dwie tablice o rownej liczbie komorek, reprezentuja cale wyrazenie
	//w pierwszej zapisuje po kolei wszystkie zmienne wyrazenia (np x1,x3,x4; x1,x2,x3)
	//w drugiej zapisuje wartosc odpowiednich zmiennych (x1 = 1, x3 = 1, x4 = 0)

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

ofstream plik("walksat.txt");

void losuj_bez_powtorzen(int* tab, int rozmiar, int x) {
	int counter = 0;
	for (int i = 0; i < rozmiar; i++) {
		tab[i] = 0;
	}
	for (int i = 0; i < rozmiar; i++) {
		do {
			counter = 0;
			tab[i] = (rand() % x) + 1;
			for (int j = 0; j < rozmiar; j++) {
				if (j != i) {
					if (tab[j] == tab[i]) counter++;
				}
			}
		} while (counter != 0);
	}
}

void wypelnij_tablice_zmiennych(int* zmienne, int x, int grupy, int ile) {
	int ileodrzuconych = x - ile;
	int* odrzucone = new int[ileodrzuconych];
	int pozycja = 0;
	int nazwa = 1;
	bool bylo = false;
	bool dodatnia;

	do {
		if (pozycja % ile == 0) { //przejscie na nastepna implicente powoduje wygenerowanie nowych odrzuconych i zerowanie licznika nazw
			losuj_bez_powtorzen(odrzucone, ileodrzuconych, x);
			nazwa = 1;
		}
		for (int i = 0; i < ileodrzuconych; i++) {
			if (nazwa == odrzucone[i]) bylo = true;
		}
		if (bylo == false) {
			dodatnia = rand() % 2;
			if (dodatnia == 1) zmienne[pozycja] = nazwa; //trzeba było poprawić, ale przynajmniej wypisuje w kolejnosci
			else zmienne[pozycja] = -nazwa;
			pozycja++;
		}
		bylo = false;
		nazwa++;
	} while (pozycja < grupy*ile);
	delete[]odrzucone;
}

void wypisz_tablice_zmiennych(int* tab, int grupy, int ile) {
	cout << "(";
	plik << "(";
	for (int i=0; i < grupy - 1; i++){
		for (int j = 0; j < ile-1; j++) {
			if (tab[i*ile + j] > 0) {
				cout << "x" << tab[i*ile + j] << " v ";
				plik << "x" << tab[i*ile + j] << " v ";
			}
			else {
				cout << "-x" << -tab[i*ile + j] << " v ";
				plik << "-x" << -tab[i*ile + j] << " v ";
			}
		}
		if (tab[i*ile + ile - 1] > 0) {
			cout << "x" << tab[i*ile + ile - 1] << ") && (";
			plik << "x" << tab[i*ile + ile - 1] << ") && (";
		}
		else {
			cout << "-x" << -tab[i*ile + ile - 1] << ") && (";
			plik << "-x" << -tab[i*ile + ile - 1] << ") && (";
		}
	}
	for (int i = ile * (grupy - 1); i < ile*grupy-1; i++) {
		if (tab[i] > 0) {
			cout << "x" << tab[i] << " v ";
			plik << "x" << tab[i] << " v ";
		}
		else {
			cout << "-x" << -tab[i] << " v ";
			plik << "-x" << -tab[i] << " v ";
		}
	}
	if (tab[ile*grupy - 1] > 0) {
		cout << "x" << tab[ile*grupy - 1] << ")";
		plik << "x" << tab[ile*grupy - 1] << ")";
	}
	else {
		cout << "-x" << -tab[ile*grupy - 1] << ")";
		plik << "-x" << -tab[ile*grupy - 1] << ")";
	}
}

void losuj_wartosci(int* wartosci, int x) {
	for (int i = 0; i < x; i++) {
		wartosci[i] = rand() % 2;
	}
}

void wypisz_wartosci(int* wartosci, int x) {
	for (int i = 0; i < x; i++) {
		cout << "x" << i + 1 << " = " << wartosci[i] << "   ";
		plik << "x" << i + 1 << " = " << wartosci[i] << "   ";
	}
}

bool sprawdz_implicent(int* zmienne, int* wartosci, int ile) {// przesyłać adres do kontrolowanego elementu
	bool dziala = false;
		for (int i = 0; i < ile; i++) {
			if (zmienne[i] > 0 && wartosci[zmienne[i]] == 1) dziala = true;
			if (zmienne[i] < 0 && wartosci[-zmienne[i]] == 0) dziala = true;
		}
	return dziala;
}

void zamien(int* zmienne, int* wartosci, int grupy, int ile, int x, bool* implicenty) {
	int a, b, c;
	do {
		a = rand() % grupy; //wybieram implicent, który się zeruje
		if (implicenty[a] == false) {
			b = rand() % ile; // wybieram zmienna do zanegowania
			c = zmienne[a*ile + b];
			int test;
			
			if (c > 0 && wartosci[c - 1] == 1) {
				wartosci[c - 1] = 0; //negacja
				cout << "\nZanegowano zmienna: x" << c;
				plik << "\nZanegowano zmienna: x" << c;
			}
			else if (c > 0 && wartosci[c - 1] == 0) {
				wartosci[c - 1] = 1;
				cout << "\nZanegowano zmienna: x" << c;
				plik << "\nZanegowano zmienna: x" << c;
			}
			else if (c < 0 && wartosci[(-c) - 1] == 1) {
				wartosci[(-c) - 1] = 0;
				cout << "\nZanegowano zmienna: x" << -c;
				plik << "\nZanegowano zmienna: x" << -c;
			}
			else if (c < 0 && wartosci[(-c) - 1] == 0) {
				wartosci[(-c) - 1] = 1;
				cout << "\nZanegowano zmienna: x" << -c;
				plik << "\nZanegowano zmienna: x" << -c;
			}
			cout << endl;
			plik << endl;
			wypisz_wartosci(wartosci, x);
			break;
		}
	} while (true);
}

void walk(int* zmienne, int* wartosci, int grupy, int ile, int x) {
	int liczba_zerowych = 0;
	int counter_zamian = 0;
	bool* implicenty = new bool[grupy];//tablica na implicenty które dają 0
	do {
		liczba_zerowych = 0;
		for (int i = 0; i < grupy; i++) {
			implicenty[i] = true;
		}
		for (int i = 0; i < grupy; i++) {
			if (sprawdz_implicent(&zmienne[i*ile], wartosci, ile) == false) {
				liczba_zerowych++;
				implicenty[i] = false;
			}
		}
		if (liczba_zerowych == 0) break;
		else {
			zamien(zmienne, wartosci, grupy, ile, x, implicenty);
			counter_zamian++;
		}

	} while (true);
	delete[]implicenty;
	cout << endl << endl << "Wartosci koncowe zmiennych: ";
	plik << endl << endl << "Wartosci koncowe zmiennych: ";
	wypisz_wartosci(wartosci, x);
	cout << "\nRozwiazanie znalezione w " << counter_zamian << " krokach.";
	plik << "\nRozwiazanie znalezione w " << counter_zamian << " krokach.";
}


int main()
{
	//przyjmowanie zmiennych
	cout << "Program demonstrujacy dzialanie algorytmu WalkSat";
	cout << "\nWyrazenia logiczne sa generowane w sposob losowy, biorac pod uwage parametry podane przez uzytkownika";
	cout << "\nGdy zmiennych jest wiecej niz miesci jeden implicent, sa one rowniez losowo przydzielane.";
	cout << "\nWynik dzialania programu jest zapisywany do pliku walksat.txt";
	cout << "\nPodaj ilosc zmiennych: ";
	int x;
	cin >> x;
	plik << "\nPodaj ilosc zmiennych: " << x;
	cout << "\nPodaj ilosc implicentow: ";
	int grupy;
	cin >> grupy;
	plik << "\nPodaj ilosc implicentow: "<< grupy;
	cout << "\nPodaj ilosc zmiennych na implicent (nie wiecej niz " << x << "): ";
	int ile;
	cin >> ile;
	cout << "\nPodaj ilosc zmiennych na implicent: " << ile;

	//tworzenie tablic i losowanie wyrazenia
	srand(time(NULL));
	int* zmienne = new int[grupy*ile];
	int* wartosci = new int[x];


	wypelnij_tablice_zmiennych(zmienne, x, grupy, ile);
	cout << "\nWygenerowane losowe wyrazenie: ";
	plik << "\nWygenerowane losowe wyrazenie: ";
	wypisz_tablice_zmiennych(zmienne, grupy, ile);
	losuj_wartosci(wartosci, x);
	cout << "\nWylosowane wartosci poczatkowe zmiennych: " << endl;
	plik << "\nWylosowane wartosci poczatkowe zmiennych: " << endl;
	wypisz_wartosci(wartosci, x);
	
	walk(zmienne, wartosci, grupy, ile, x);

	

	delete[]zmienne;
	delete[]wartosci;
	char znak;
	cin >> znak;
	return 0;
}