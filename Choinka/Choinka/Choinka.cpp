//Visual Studio 2017 community (c++17)

#include "pch.h"
#include <iostream>

using namespace std;

//dla rozmiaru segmentu = 5, pierwszy segment wygl¹da 1, 3, 5 czyli ma wysokosc 3. Kazda z lini ma promien wiekszy o 1. Kazdy z segmentow jest dluzszy od poprzedniego o 2.
//segment 1 zaczyna sie od 1, segment 2 i 3 od 3 (dla nieparzystych)
//dla choinki o szer 5: wysokoœci - 3, 4, 6

//pierwszy segment ma wysokosc n/2+1, drugi jest wyzszy o 1, trzeci jest wyzszy o 2 (³¹cznie 3)
//dla wiekszej liczby segmentow chyba wprowadzic dynamiczna tab segmentow z counterem, ktory bedzie proporcjonalnie dodawal wysokosci seg (w konstruktorze)
class Choinka {
private:
	bool ** tablica;
	int seg1width;
	int wys_tab;
	int szer_tab;
	int seg1h, seg2h, seg3h; //height
	bool nieparzysty = false;

public:
	Choinka(int seg1width);
	~Choinka();
	void buildChoinka();
	void printChoinka();
};

Choinka::Choinka(int seg1width) { //tworzenie tablicy dobrych rozmiarów
	this->seg1width = seg1width;
	if (seg1width % 2 != 0) nieparzysty = true;
	if (nieparzysty) { //nieparzyste
		seg1h = seg1width / 2 + 1; 
		seg2h = seg1h + 1;
		seg3h = seg1h + 3;

		szer_tab = 1 + seg3h * 2; //szerokosc pnia 3
	}

	else { //parzyste
		seg1h = seg1width / 2;
		seg2h = seg1h + 1;
		seg3h = seg1h + 3;

		szer_tab = seg3h * 2; //szerokosc pnia 2
	}
	wys_tab = seg1h + seg2h + seg3h + 1; //+1 bo pien na samym dole

	tablica = new bool*[wys_tab];
	for (int i = 0; i < wys_tab; i++) {
		tablica[i] = new bool[szer_tab]{};
	}

}

Choinka::~Choinka() {
	for (int i = 0; i < wys_tab; i++) {
		delete[] tablica[i];
	}
	delete[] tablica;
}


void Choinka::buildChoinka() { //wypelnianie tablicy (pod inna ilosc segmentow trzeba troche przerobic)
	int threshold;
	
	//segment 1
	if (nieparzysty) threshold = szer_tab / 2;
	else threshold = szer_tab / 2 - 1;
	
	for (int i = 0; i < seg1h; i++) {
		for (int j = 0; j < szer_tab; j++) {
			if ((j > threshold) && (j < (szer_tab - threshold))) tablica[i][j] = true;
		}
		threshold--;
	}

	//segment 2
	if (nieparzysty) threshold = szer_tab / 2 - 1;
	else threshold = szer_tab / 2 - 2;

	for (int i = 0; i < seg2h; i++) {
		for (int j = 0; j < szer_tab; j++) {
			if (j > threshold && j < (szer_tab - threshold)) tablica[i+seg1h][j] = true;
		}
		threshold--;
	}

	//segment 3
	if (nieparzysty) threshold = szer_tab / 2 - 1;
	else threshold = szer_tab / 2 - 2;

	for (int i = 0; i < seg3h; i++) {
		for (int j = 0; j < szer_tab; j++) {
			if (j > threshold && j < (szer_tab - threshold)) tablica[i+seg1h+seg2h][j] = true;
		}
		threshold--;
	}

	// pien
	if (nieparzysty) threshold = szer_tab / 2 - 1;
	else threshold = szer_tab / 2 - 2;

	for (int j = 0; j < szer_tab; j++) {
		if (j > threshold && j < (szer_tab - threshold)) tablica[seg1h + seg2h + seg3h][j] = true;
	}
}

void Choinka::printChoinka() { //wypisywanie talbicy (rozbudowywalne o znak choinki)
	for (int i = 0; i < wys_tab; i++) {
		for (int j = 0; j < szer_tab; j++) {
			if (tablica[i][j] == true) cout << "*";
			else cout << " ";
		}
		cout << endl;
	}
}

int main()
{
	cout << "\nPodaj rozmiar pierwszego segmentu choinki (nie mniejszy niz 3): ";
	int rozmiar;
	cin >> rozmiar;
	while (rozmiar < 3) {
		cout << "\nSprobuj jeszcze raz! :";
		cin >> rozmiar;
	}
	Choinka najladniejsza(rozmiar + 1);
	najladniejsza.buildChoinka();
	najladniejsza.printChoinka();
	char pause;
	cin >> pause;
	return 0;
}


