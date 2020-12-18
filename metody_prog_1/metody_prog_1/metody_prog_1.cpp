// input: n; output: wszystkie permutacje zbioru n-liczbowego w kolejnopsci leksykograficznej
// kontrola bledow: backtracking spowoduje wywołanie się wszystkich możliwych kombinacji
// 

#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

void wypisz(int * tab, int rozmiar, ofstream& plik1) {
	for (int i = 0; i < rozmiar + 1; i++) { // +1 kompensuje input w main
		cout << tab[i] << " ";
		plik1 << tab[i] << " ";
	}
	plik1 << endl;
	cout << endl;
}
void nieporzadki(int * tab, int rozmiar, ofstream& plik2, int& niepcount) {
	int counter = 0;
	for (int i = 0; i < rozmiar + 1; i++) {
		if (tab[i] != i + 1) counter++;
	}
	if (counter == rozmiar + 1) {
		for (int i = 0; i < rozmiar + 1; i++) {
			plik2 << tab[i];
		}
		plik2 << endl;
		niepcount++;
	}
}

void swap(int &a, int &b) { // zamienia dwie wartości miejscami
	int c = b;
	b = a;
	a = c;
}

void permutacja(int * tab, int x, int n, ofstream& plik1, ofstream& plik2, int& permcount, int& niepcount){
	if (x == n){
		wypisz(tab, n, plik1);
		permcount++;
		nieporzadki(tab, n, plik2, niepcount);
	}
	else
	{
		for (int i = x; i <= n; i++)
		{
			swap(tab[x], tab[i]);
			permutacja(tab, x + 1, n, plik1, plik2, permcount, niepcount); //rekurencja
			swap(tab[x], tab[i]); // powrót do oryginalnej wartości
		}
	}
}

int main()
{
	int n; // wczytanie n z klawiatury, utworzenie tablicy [1,2,3,4....]
	cout << "Program pobiera liczbe elementow zbioru oraz wypisuje na ekran wszystkie permutacje tego zbioru.";
	cout << "\nProgram tworzy rowniez dwa pliki: permutacje.txt do ktorego zapisywane sa wygenerowane permutacje oraz nieporzadki.txt gdzie zapisywane sa same nieporzadki";
	cout << "\nWprowadz liczbe elementow zbioru: ";
	cin >> n;
	int * tab = new int[n];
	for (int i = 0; i < n; i++) {
		tab[i] = i + 1;
	}
	cout << endl;
	int permcount = 0;
	int niepcount = 0;
	ofstream plik1("permutacje.txt");
	ofstream plik2("nieporzadki.txt");

	permutacja(tab, 0, n-1, plik1, plik2, permcount, niepcount); // przekazujemy tablice, oraz indeks poczatku i konca, indeks koncowy jest przekazywany również do funkcji wypisz() więc tam trzeba dodać 1
	
	cout << "\nLiczba wygenerowanych permutacji: " << permcount;
	cout << "\nLiczba wygenerowanych nieporzadkow: " << niepcount;
	plik1 << "\nLiczba wygenerowanych permutacji: " << permcount;
	plik2 << "\nLiczba wygenerowanych nieporzadkow: " << niepcount;
	plik1.close();
	plik2.close();
	delete[] tab;
	char pause;
	cin >> pause;
	return 0;
}

