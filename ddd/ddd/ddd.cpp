
#include "pch.h"
#include <iostream>
#include <deque>
#include <vector>
#include <fstream>

using namespace std;


void wypisz_plik(vector<bool> naglowek, vector<bool> dane) {
	fstream plik;
	plik.open("obrazek.bssz", ios::out || ios::binary);
	for (int i = 0; i < naglowek.size(); i++) {
		plik << naglowek[i];
	}
	for (int i = 0; i < dane.size(); i++) {
		plik << dane[i];
	}
	plik.close();
}

int c;
plik >> c;
naglowek.push_back(c);

vector<bool> odczytaj_plik() {
	vector<bool> dane;
	deque<bool> naglowek;
	deque<bool> temp;
	
	fstream plik;
	plik.open("obrazek.bssz", ios::in || ios::binary);
	for (int i = 0; i < 142; i++) {
		naglowek.push_back(plik.get());
	}
	//sygnatura
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			temp.push_back(naglowek.front());
			naglowek.pop_front();
		}
		sygnatura[i] = static_cast<char>(binary_to_int(temp));
	}
	temp.clear();

	//szerokosc
	for (int i = 0; i < 8 * 4; i++) {
		temp.push_back(naglowek.front());
		naglowek.pop_front();
	}
	width = binary_to_int(temp);
	temp.clear();
	//wysokosc
	for (int i = 0; i < 8 * 4; i++) {
		temp.push_back(naglowek.front());
		naglowek.pop_front();
	}
	height = binary_to_int(temp);
	temp.clear();
	//wybor palety
	for (int i = 0; i < 8; i++) {
		temp.push_back(naglowek.front());
		naglowek.pop_front();
	}
	wybor_palety = binary_to_int(temp);
	temp.clear();
	//wybor rozmiaru bufora
	for (int i = 0; i < 8; i++) {
		temp.push_back(naglowek.front());
		naglowek.pop_front();
	}
	wybor_rozmiaru_bufora = binary_to_int(temp);
	temp.clear();
	//paleta dedykowana
	for (int i = 0; i < 16; i++) {
		for (int i = 0; i < 8; i++) {
			temp.push_back(naglowek.front());
			naglowek.pop_front();
		}
		PaletaD[i].r = binary_to_int(temp);
		for (int i = 0; i < 8; i++) {
			temp.push_back(naglowek.front());
			naglowek.pop_front();
		}
		PaletaD[i].g = binary_to_int(temp);
		for (int i = 0; i < 8; i++) {
			temp.push_back(naglowek.front());
			naglowek.pop_front();
		}
		PaletaD[i].b = binary_to_int(temp);
	}
	bool tmp;
	while (tmp = plik.get()) {
		dane.push_back(tmp);
	}
	return dane;


}


SDL_Surface* outputBMP = SDL_CreateRGBSurfaceFrom(tablica_pikseli, width, height, 8, 8*width, 0, 0, 0, 0);
SDL_SaveBMP(outputBMP, "obrazek_po_dekompresji.bmp");




int main() 
{
	int opcja = 0; // liczby od 0 do 9
	// wybierz liczbe od 0-9, wielkoscia slownika bedzie podstawa * 2^n podstawa wielkosci to 8 bajtow
	//zapisywanie opcji dla slownika
	//opcja += [podana liczba]*10;
	//zapisywanie opcji dla bufora wejsciowego
	//opcja += [podana liczba];
	
	
	//odczytywanie opcji
	int p_opcja = (opcja / 10) % 10;
	int c_opcja = opcja % 10;
	
	int c_length = 8 + 3 + c_opcja; //decyduje o ilosci bitow w buforze wejsciowym 
	int p_length = 8 + 3 + p_opcja;
	int s_length = 4;



}
	

	
