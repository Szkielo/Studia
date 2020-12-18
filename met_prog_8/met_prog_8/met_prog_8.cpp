//program decydujący o kolejności wykonywania działań na macierzach
//plan: podaj liczbe macierzy (n), utwórz n-wymiarową tablice, wpisuj rozmiary kolejnych macierzy
//poprawność sprawdzam porównując wartości w tablicy
//obliczam najkrótszą drogę (przy mnożeniu M na N * N na K liczbą mnożeń jest iloczyn M*N*K)
// --- alg. obliczania drogi ---
//wyświetlam wynik

#include "pch.h"
#include <iostream>
#include <limits.h> //dla zmiennej min

using namespace std;

void wypisz (int i, int j, int** poz, char& macierz){
	if (i == j) cout << macierz++;
	else {
		cout << "(";
		wypisz(i, poz[i][j], poz, macierz);
		wypisz(poz[i][j] + 1, j, poz, macierz);
		cout << ")";
	}
}

int main()
{
	cout << "Program sluzacy do okreslenia optymalnej kolejnosci dzialania na macierzach.";
	cout << "\nMnozenie mozna wykonac gdy liczba kolumn macierzy po lewej stronie mnozenia, jest rowna liczbie wierszy macierzy po prawej stronie." << endl;
	cout << "\nPodaj liczbe macierzy, ktore chcesz wymnozyc: ";
	int rozmiary; //liczba macierzy + 1 (ostatnia komórka to liczba kolumn, pozostałe to liczba wierszy)
	cin >> rozmiary;
	rozmiary++;
	int * tab_rozm = new int[rozmiary];
	for (int i = 0; i < rozmiary-1; i++) { //pętla bez ostatniej komórki
			cout << "\nPodaj liczbe wierszy " << i + 1 << " macierzy: ";
			cin >> tab_rozm[i];
	}
	cout << "\nPodaj liczbe kolumn " << rozmiary-1 << " macierzy: ";
	cin >> tab_rozm[rozmiary-1];

	//-----------obliczanie najkrótszej drogi--------------
	//tworzę dwie nowe dwuwymiarowe tablice o rozmiarze równym ilosci macierzy + 1, jedna przechowuje koszty mnożenia a druga wybór nawiasowanych macierzy (a konkretnie punkt rozdzielenia nawiasami)
	//(wykład 5 - problem tworzenia iloczynu łańcucha macierzy 2)

	int** cost = new int* [rozmiary];
	for (int i = 0; i < rozmiary; i++) {
		cost[i] = new int[rozmiary]{};
	}
	int** poz = new int*[rozmiary];
	for (int i = 0; i < rozmiary; i++) {
		poz[i] = new int[rozmiary]{};
	}
	
	int i, j, d, min, temp; //i-wiersze, j-kolumny, d-przesuniecie na nastepna diagonalę
	for (d = 1; d < rozmiary - 1; d++) { // d=1 bo główna diagonala ma same zera
		for (i = 1; i < rozmiary - d; i++) {
			j = i + d;
			min = INT_MAX;
			for (int k = i; k < j; k++) { //petla wybiera minimalny koszt i podaje jego pozycje (gdy wariantów jest kilka)
				temp = cost[i][k] + cost[k + 1][j] + tab_rozm[i - 1] * tab_rozm[k] * tab_rozm[j]; // koszt całkowity to suma kosztów obliczenia podmacierzy oraz kosztu pomnożenia macierzy wynikowych
				if (temp < min) {
					min = temp;
					poz[i][j] = k;
				}
			}
			cost[i][j] = min; //zapis kolejnej wartości minimalnej
		}
	}

	// wyswietlanie wyniku (w tablicy poz indeks poczatkowy jest rowny 1)
	char nazwa_macierzy = 'A';
	cout << "\nOptymalna kolejnosc wykonywania mnozenia: " << endl;
	wypisz(1, rozmiary - 1, poz, nazwa_macierzy);
	cout << endl << "\nIlosc wykonanych operacji: " << cost[1][rozmiary - 1];
	
	// czyszczenie pamięci
	for (int i = 0; i < rozmiary; i++) {
		delete[] cost[i];
	}
	delete[] cost;

	for (int i = 0; i < rozmiary; i++) {
		delete[] poz[i];
	}
	delete[] poz;
	delete[] tab_rozm;

	//pauza na końcu
	char pause;
	cin >> pause;
	return 0;
}

