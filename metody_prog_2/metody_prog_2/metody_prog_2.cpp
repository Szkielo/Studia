// input: liczba n
// output: wygenerowane zbiory w kolejności leksykalnej
// generowanie: start na 1111 dalej 1112 itp, ostatnia cyfra ma być maksymalnie o 1 wieksza od poprzedniej
// wypisanie -> sprawdzenie warunku -> true: "przeskok na następną wartość" false: (ostatnia komórka)++
// wszystko wykonuje się w petli przerwanej gdy counter=n-1 czyli wszystkie wartości spełnią warunek n=[n-1]+1


#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

void wypisz(int * tab, int rozmiar, ofstream& zapis) {
	for (int i = 0; i < rozmiar; i++) {
		cout << tab[i] << " ";
		zapis << tab[i] << " ";
	}
	cout << endl;
	zapis << endl;
}

void check(int* tab, int indeks, int rozmiar, int &swap, int &end, ofstream& zapis) { // indeks = rozmiar-1
	if (end == 1) {}
	else if (indeks - 1 < 0) end = 1;  // warunek konczacy petle (kiedy dotrze do zerowego elementu tablicy)
	else if ((tab[indeks]) == (tab[indeks - 1] + 1)) { //jezeli tab[n] bedzie o jeden wiekszy od tab[n-1], sprawdz poprzedni element
		swap = 1;
		check(tab, indeks - 1, rozmiar, swap, end, zapis);
	}
	else if (swap == 1) { //jezeli swap == 1 (z rekurencji poprzedni el nie jest mniejszy o 1)
		tab[indeks]++;
		for (int i = indeks + 1; i < rozmiar; i++) {
			tab[i] = 1;
		}
		swap = 0;
		wypisz(tab, rozmiar, zapis);
	}
	else {
		tab[indeks]++;
		wypisz(tab, rozmiar, zapis);
	}
}

int main()
{
	int n;
	cout << "\nProgram dokonujacy co najwyzej n-blokowych podzialow zbiorow. Zbiory sa wypisane na ekran oraz do pliku podzialy.txt, w kolejnosci leksykokgraficznej.";
	cout << "\nWprowadz liczbe elementow zbioru: ";
	cin >> n;

	int * tab = new int[n]; // dane przechowywane w tablicy
	for (int i = 0; i < n; i++) {
		tab[i] = 1;
	}
	ofstream zapis("podzialy.txt");
	int end = 0;
	int swap = 0;
	wypisz(tab, n, zapis);
	do {
		check(tab, n - 1, n, swap, end, zapis); //(tablica, sprawdzany indeks, rozmiar tablicy, zmienna konczaca petle, plik do zapisu)
	} while (end != 1);

	zapis.close();
	delete[] tab;
	char pause;
	cin >> pause;
	return 0;
}


