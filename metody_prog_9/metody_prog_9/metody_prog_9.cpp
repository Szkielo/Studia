#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <limits.h>
#include <string>

using namespace std;

struct wezel
{
	wezel * lewy;
	wezel * prawy;
	int znak = -1; //pozycja ASCII
	int wartosc = 0; //czestosc
};

struct wezel* nowy_wezel() {
	struct wezel* wezel = new struct wezel;
	wezel->lewy = NULL;
	wezel->prawy = NULL;
	return wezel;
}

struct wezel* nowy_wezel(int znak, int wartosc) {//overload
	struct wezel* wezel = new struct wezel;
	wezel->znak = znak;
	wezel->wartosc = wartosc;
	wezel->lewy = NULL;
	wezel->prawy = NULL;
	return wezel;
}

int searchminindex1(int tab[]) {//funkcja zwraca indeks najmniejszego elementu z pierwszej tablicy, -1 gdy nie ma
	int minval = INT_MAX;
	int minindex = -1;
	for (int i = 0; i < 128; i++) {
		if (tab[i] != 0) {
			if (tab[i] < minval) {
				minval = tab[i];
				minindex = i;
			}
		}
	}
	return minindex;
}

int searchminindex2(int tab[]) {//funkcja zwraca indeks najmniejszego elementu z drugiej tablicy
	int minval = INT_MAX;
	int minindex = -1;
	for (int i = 0; i < 128; i++) {
		if (tab[i] != 0) {
			if (tab[i] < minval) {
				minval = tab[i];
				minindex = i;
			}
		}
	}
	return minindex;
}

bool checkifjednodrzewo(int tab2[]) {
	int counter = 0;
	for (int i = 0; i < 128; i++) {
		if (tab2[i] != 0) counter++;
	}
	if (counter == 1) return true;
	else return false;
}


wezel* tworz_drzewo(int tab1[]) {//funkcja zwraca adres korzenia wygenerowanego drzewa
	//tworze dwie tablice, w jednej przechowuje adresy utworzonych drzew, w drugiej wartosci (czestosc), spójne indeksy - pamietac o zerowaniu obu
	wezel* tab2adr[128]{ 0 };
	int tab2war[128]{ 0 };
	//wyciagam 2 indeksy (z najmniejszymi wartosciami) w danym momencie (niezerowe), robie z nich drzewo, zeruje miejsca skad wzialem, odkładam do tab2
	//żeby wyciągnąć dwa na raz, muszę je tymczasowo wyzerować, wartości zapisuję w roocie, którego jeszcze nie ma w tablicy2 (czyli nie może być znaleziony)
	int index1, index2;

	do {

		struct wezel *root = nowy_wezel();// tworzę nowy korzeń
		// lewo
		index1 = searchminindex1(tab1);
		index2 = searchminindex2(tab2war);
		if ((searchminindex1(tab1) == -1) && (checkifjednodrzewo(tab2war) == true)) break; //warunek konczacy petle
		
		if ((index1 != -1) && (index2 != -1)) {
			if (tab1[index1] <= tab2war[index2]) {//tab1 wygrywa, czyli dopisujemy znak do drzewa
				root->lewy = nowy_wezel(index1, tab1[index1]);//parametry (znak, wystapienia)
				root->wartosc += tab1[index1]; //dodaje wartość do korzenia obecnego drzewa
				tab1[index1] = 0; //zeruję tablicę, żeby nie użyć drugi raz
			}
			else {//tab2 wygrywa, czyli wpisujemy do lewej gałęzi adres drzewa, które wygenerowaliśmy wcześniej
				root->lewy = tab2adr[index2];
				root->wartosc += tab2war[index2];
				//zerujemy wpisy w obu tablicach
				tab2adr[index2] = 0;
				tab2war[index2] = 0;
			}
		}
		else if ((index1 == -1) && (index2 != -1)) {
			root->lewy = tab2adr[index2];
			root->wartosc += tab2war[index2];
			//zerujemy wpisy w obu tablicach
			tab2adr[index2] = 0;
			tab2war[index2] = 0;
		}
		else if ((index1 != -1) && (index2 == -1)) {
			root->lewy = nowy_wezel(index1, tab1[index1]);//parametry (znak, wystapienia)
			root->wartosc += tab1[index1]; //dodaje wartość do korzenia obecnego drzewa
			tab1[index1] = 0;
		}
		//prawo
		index1 = searchminindex1(tab1);
		index2 = searchminindex2(tab2war);


		if ((index1 != -1) && (index2 != -1)) {
			if (tab1[index1] <= tab2war[index2]) {//tab1 wygrywa, czyli dopisujemy znak do drzewa
				root->prawy = nowy_wezel(index1, tab1[index1]);//parametry (znak, wystapienia)
				root->wartosc += tab1[index1]; //dodaje wartość do korzenia obecnego drzewa
				tab1[index1] = 0; //zeruję tablicę, żeby nie użyć drugi raz
			}
			else {//tab2 wygrywa, czyli wpisujemy do lewej gałęzi adres drzewa, które wygenerowaliśmy wcześniej
				root->prawy = tab2adr[index2];
				root->wartosc += tab2war[index2];
				//zerujemy wpisy w obu tablicach
				tab2adr[index2] = 0;
				tab2war[index2] = 0;
			}
		}
		else if ((index1 == -1) && (index2 != -1)) {
			root->prawy = tab2adr[index2];
			root->wartosc += tab2war[index2];
			//zerujemy wpisy w obu tablicach
			tab2adr[index2] = 0;
			tab2war[index2] = 0;
		}
		else if ((index1 != -1) && (index2 == -1)) {
			root->prawy = nowy_wezel(index1, tab1[index1]);//parametry (znak, wystapienia)
			root->wartosc += tab1[index1]; //dodaje wartość do korzenia obecnego drzewa
			tab1[index1] = 0;
		}
		//dodaję nowo wykonane drzewo do tablicy 2, w wolne miejsce
		for (int i = 0; i < 128; i++) {
			if (tab2war[i] == 0) {
				tab2war[i] = root->wartosc;
				tab2adr[i] = root;
				break;
			}
		}

	} while (true);

	//funkcja zwraca adres korzenia wygenerowanego drzewa
	for (int i = 0; i < 128; i++) {
		if (tab2war[i] != 0) {
			return tab2adr[i];
		}
	}
}

void tworz_slownik(int tab[]) {
	fstream tekst;	//odczyt z pliku
	tekst.open("tekst.txt", fstream::in);
	if (tekst.is_open() == false) cout << "Nie udalo sie otworzyc pliku";
	char znak;
	do {
		tekst.get(znak); //zapis wystapien do tablicy w pamieci
		if (tekst.eof()) break;
		tab[znak]++;
	} while (true);

	tekst.close();


	fstream slownik;  // zapis z tablicy do pliku slownik, bez spacji na koncu pliku
	slownik.open("slownik.txt", fstream::out);
	for (int i = 0; i < 127; i++) {
		slownik << tab[i];
		slownik << " ";
	}
	slownik << tab[127];
	slownik.close();
	cout << "\nPlik slownik.txt zostal stworzony pomyslnie!";
}

void czytaj_slownik(int tab[]){
	fstream slownik;
	char znak;
	int counter = 0;
	slownik.open("slownik.txt", fstream::in);
	do {
		slownik.get(znak);
		if (slownik.eof()) break;
		else if (znak == ' ') {
			counter++;
		}
		else {
			tab[counter] *= 10;
			tab[counter] += znak - '0';
		}
	} while (true);
	cout << "\nSlownik zostal przeczytany pomyslnie!";
}

void tworz_kody(wezel* root, string kody[], string kod) {
	if (root) {
		if (root->znak != -1) kody[root->znak] = kod;
		kod += "0";
		tworz_kody(root->lewy, kody, kod);
		kod.pop_back();
		kod += "1";
		tworz_kody(root->prawy, kody, kod);
		kod.pop_back();
	}
}


void koduj(int tab[], string kody[]) {
	fstream tekst, zakodowany_tekst;
	tekst.open("tekst.txt", fstream::in);
	zakodowany_tekst.open("zakodowany_tekst.txt", fstream::out);
	char znak;
	do {
		tekst.get(znak);
		if (tekst.eof()) break;
		zakodowany_tekst << kody[znak];
	} while (true);
	tekst.close();
	zakodowany_tekst.close();
	cout << "\nTekst zostal zakodowany pomyslnie!";
}

void odkoduj(int tab[], wezel* root) {
	fstream tekst, zakodowany_tekst;
	tekst.open("tekst.txt", fstream::out);
	zakodowany_tekst.open("zakodowany_tekst.txt", fstream::in);
	wezel* ptr = root;
	char znak;
	
	do {
		zakodowany_tekst.get(znak);
		if (zakodowany_tekst.eof()) break;
		else if (znak == '0') ptr = ptr->lewy;
		else if (znak == '1') ptr = ptr->prawy;
		
		if (ptr->znak != -1) {
			tekst << static_cast<char>(ptr->znak);
			ptr = root;
		}
	} while (true);
	tekst.close();
	zakodowany_tekst.close();
	cout << "\nTekst zostal odkodowany pomyslnie!";
}

void create_files() {
	fstream a, b, c;
	a.open("tekst.txt", fstream::trunc);
	a.close();
	b.open("slownik.txt", fstream::trunc);
	b.close();
	c.open("zakodowany_tekst.txt", fstream::trunc);
	c.close();
}

int main()
{
	cout << "\nProgram kodujacy i odkodowujacy pliki tekstowe uzywajac kodowania Huffmana.";
	cout << "\nZeby zakodowac tekst nalezy umiescic go w pliku tekst.txt, program tworzy odpowiedni slownik. Zakodowany tekst jest umieszczany w pliku zakodowany_tekst.txt";
	cout << "\nAby odkodowac tekst nalezy umiescic go w pliku tekst.txt, do pliku slownik.bin wkleic odpowiedni slownik. Odkodowany tekst jest umieszczany w pliku odkodowany_tekst.txt";

	int tab[128]{ 0 };
	int wybor;
	string kody[128];
	string kod;
	
	do {
		cout << "\n\nCo chcesz zrobic?\n(0. Stworz pliki tekstowe)\n1. Stworzyc slownik i zakodowac tekst\n2. Odkodowac tekst korzystajac z podanego slownika\n3. Tylko stworzyc slownik\n4. Wyjdz z programu" << endl;
		cin >> wybor;
		switch (wybor) {
		case 0:
			create_files();
			break;
		case 1:
			tworz_slownik(tab);
			tworz_kody(tworz_drzewo(tab), kody, kod);
			koduj(tab, kody);
			break;
		case 2:
			czytaj_slownik(tab);
			odkoduj(tab, tworz_drzewo(tab));
			break;
		case 3:
			tworz_slownik(tab);
			break;
		}
	} while (wybor != 4);
	return 0;
}
