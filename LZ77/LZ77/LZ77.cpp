#include "pch.h"
#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

int binary_to_int(deque<bool> liczba) {
	int temp = 0;
	for (int i = 0; i < liczba.size(); i++) {
		if (liczba[i] == 1) temp += pow(2, liczba.size() - i - 1);
	}
	return temp;
}

deque<bool> int_to_binary(int liczba){
	deque<bool>temp;
	while (liczba > 0) { 
		temp.push_front(liczba % 2);
		liczba = liczba / 2;
	}
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////

class Kompresja {
private:
	int p_length; //ilosc bitow potrzebna na zapisanie pozycji
	int c_length; //ilosc bitow potrzebna na zapisanie ilosci znakow
	int s_length; //ilosc bitow potrzebna na zapisanie symbolu
	unsigned int rozmiar_bufora_slownikowego; //
	unsigned int rozmiar_bufora_wejsciowego; //128 bajtow, staly
	deque<int> text_raw; //kopia wprowadzonych danych, latwiej uzywac, dopasowanie kontenera
	deque<int> bufor_slownikowy;
	deque<int> bufor_wejsciowy;
	struct PCS {
		unsigned int p;
		unsigned int c;
		unsigned int s;
	};
	deque<PCS> tablica_trojek;
	PCS szukaj(); // zwraca trojke
	void przesun_bufory_o(int c);

public:
	vector<bool>output;

	Kompresja(vector<int> dane, int p_length, int c_length, int s_length);//konwertuj tekst, okresl rozmiar i wypelnij bufory
	bool check_if_input_empty(); //konczy kompresje
	void read_iteration(); // czytaj text, szukaj w buforze, zapisz trójkê do tablicy, przesuñ bufory
	void utworz_output();
};

Kompresja::Kompresja(vector<int> dane, int p_length, int c_length, int s_length) {
	for (int i = 0; i < dane.size(); i++) {
		text_raw.push_back(dane[i]);
	}
	
	this->p_length = p_length;
	this->c_length = c_length;
	this->s_length = s_length;
	rozmiar_bufora_slownikowego = pow(2, p_length - s_length); // p_length - s_length zachowa rozmiar w bitach, dostosowuj¹c siê do rozmiaru symbolu
	rozmiar_bufora_wejsciowego = pow(2, c_length - s_length);
	
	int first_symbol = text_raw.front();
	text_raw.pop_front();

	deque<bool> first = int_to_binary(first_symbol); //wypisanie pierwszego symbolu na wyjscie
	while (first.size() < s_length) {
		first.push_front(0);
	}
	for (int i = 0; i < s_length; i++) {
		output.push_back(first[i]);
	}

	//wypelnienie bufora slownikowego
	for (int i = 0; i < rozmiar_bufora_slownikowego; i++) {
		bufor_slownikowy.push_back(first_symbol);
	}

	//zaladowanie tekstu do bufora wejsciowego
	for (int i = 0; i < rozmiar_bufora_wejsciowego; i++) {
		bufor_wejsciowy.push_back(text_raw.front());
		text_raw.pop_front();
	}
}

bool Kompresja::check_if_input_empty() {
	if (bufor_wejsciowy.empty() == true) return true;
	else return false;
}

Kompresja::PCS Kompresja::szukaj() {
	PCS temp;
	temp.c = 0;
	temp.s = bufor_wejsciowy.front();
	for (int i = 0; i < bufor_slownikowy.size(); i++) {
		for (int j = 0; j < bufor_wejsciowy.size() - 1; j++) {
			if (i + j < bufor_slownikowy.size()) {
				if (bufor_wejsciowy[j] == bufor_slownikowy[i + j]) {
					if (j >= temp.c) {
						temp.c = j + 1;
						temp.p = i;
						temp.s = bufor_wejsciowy[j + 1];
					}
				}
				else break;
			}
		}
	}

	return temp;

}

void Kompresja::przesun_bufory_o(int c) {
	for (unsigned int i = 0; i < c; i++) {
		if (bufor_wejsciowy.empty() == false) {
			bufor_slownikowy.pop_front();
			bufor_slownikowy.push_back(bufor_wejsciowy.front());
			bufor_wejsciowy.pop_front();
			if (text_raw.empty() == false) {
				bufor_wejsciowy.push_back(text_raw.front());
				text_raw.pop_front();
			}
		}
	}
}

void Kompresja::read_iteration() {
	PCS trojeczka = szukaj();
	tablica_trojek.push_back(trojeczka);
	przesun_bufory_o(trojeczka.c + 1);
}


void Kompresja::utworz_output() {
	int p;
	int c;
	int s;
	deque<bool> temp;
	while (tablica_trojek.empty() == false) {
		p = tablica_trojek.front().p;
		c = tablica_trojek.front().c;
		s = tablica_trojek.front().s;

		temp = int_to_binary(p);
		while (temp.size() < p_length) {
			temp.push_front(0);
		}
		for (int i = 0; i < temp.size(); i++) {
			output.push_back(temp[i]);
		}
		temp.clear();

		temp = int_to_binary(c);
		while (temp.size() < c_length) {
			temp.push_front(0);
		}
		for (int i = 0; i < temp.size(); i++) {
			output.push_back(temp[i]);
		}
		temp.clear();

		temp = int_to_binary(s);
		while (temp.size() < s_length) {
			temp.push_front(0);
		}
		for (int i = 0; i < temp.size(); i++) {
			output.push_back(temp[i]);
		}
		temp.clear();

		tablica_trojek.pop_front();

	}
}
////////////////////////
vector<bool> LZ77_kompresuj(int opcja, vector<int> dane) {
	cout << "\nKompresowanie...";
	int c_length = 8 + 3; //decyduje o ilosci bitow w buforze wejsciowym 
	int p_length = 8 + 3;
	int s_length = 4;

	Kompresja obj1(dane, p_length, c_length, s_length);
	while (obj1.check_if_input_empty() == false) {
		obj1.read_iteration();
	}
	obj1.utworz_output();
	cout << "\nKompresowanie zakonczone!";

	return obj1.output;
}

////////////////////////////////////////////////////////////////////////////////////
class Dekompresja {
private:
	int p_length; //ilosc bitow potrzebna na zapisanie pozycji
	int c_length; //ilosc bitow potrzebna na zapisanie ilosci znakow
	int s_length; //ilosc bitow potrzebna na zapisanie symbolu
	unsigned int rozmiar_bufora_slownikowego; //
	unsigned int rozmiar_bufora_wejsciowego; //128 bajtow, staly
	deque<int> input_raw; //kopia wprowadzonych danych, latwiej uzywac, dopasowanie kontenera
	deque<int> bufor_slownikowy;
	deque<int> bufor_wejsciowy;
	struct PCS {
		unsigned int p;
		unsigned int c;
		unsigned int s;
	};
	deque<PCS> tablica_trojek;

	PCS czytaj_trojke();


public:
	Dekompresja(vector<bool> dane, int p_length, int c_length, int s_length);
	void przesun_bufory_wypisz();
	vector<int> output;
	bool check_if_input_empty();
	void read_iteration();
};

Dekompresja::Dekompresja(vector<bool> dane, int p_length, int c_length, int s_length) {
	for (int i = 0; i < dane.size(); i++) {
		input_raw.push_back(dane[i]);
	}

	this->p_length = p_length;
	this->c_length = c_length;
	this->s_length = s_length;
	rozmiar_bufora_slownikowego = pow(2, p_length - s_length); // p_length - s_length zachowa rozmiar w bitach, dostosowuj¹c siê do rozmiaru symbolu
	rozmiar_bufora_wejsciowego = pow(2, c_length - s_length);

	//czytanie pierwszego symbolu
	deque<bool> first;
	for (int i = 0; i < s_length; i++) {
		first.push_back(input_raw.front());
		input_raw.pop_front();
	}
	int first_symbol = binary_to_int(first);
	output.push_back(first_symbol);

	//wypelnienie bufora slownikowego
	for (int i = 0; i < rozmiar_bufora_slownikowego; i++) {
		bufor_slownikowy.push_back(first_symbol);
	}
}

bool Dekompresja::check_if_input_empty() {
	if (input_raw.empty() == true) return true;
	else return false;
}

Dekompresja::PCS Dekompresja::czytaj_trojke() {
	PCS trojka;
	deque<bool> temp;
	for (int i = 0; i < p_length; i++) {
		temp.push_back(input_raw.front());
		input_raw.pop_front();
	}
	trojka.p = binary_to_int(temp);
	temp.clear();
	for (int i = 0; i < c_length; i++) {
		temp.push_back(input_raw.front());
		input_raw.pop_front();
	}
	trojka.c = binary_to_int(temp);
	temp.clear();
	for (int i = 0; i < s_length; i++) {
		temp.push_back(input_raw.front());
		input_raw.pop_front();
	}
	trojka.s = binary_to_int(temp);
	temp.clear();
	return trojka;
}

void Dekompresja::przesun_bufory_wypisz() {
	while (bufor_wejsciowy.empty() == false) {
		bufor_slownikowy.pop_front();
		bufor_slownikowy.push_back(bufor_wejsciowy.front());
		output.push_back(bufor_wejsciowy.front());
		bufor_wejsciowy.pop_front();
	}
}

void Dekompresja::read_iteration() {
	PCS trojka = czytaj_trojke();
	if (trojka.c == 0) {
		bufor_wejsciowy.push_back(trojka.s);
		przesun_bufory_wypisz();
	}
	else {
		for (int i = 0; i < trojka.c; i++) {
			bufor_wejsciowy.push_back(bufor_slownikowy[trojka.p + i]);
		}
		bufor_wejsciowy.push_back(trojka.s);
		przesun_bufory_wypisz();
	}
	
}


///////////////////

vector<int> LZ77_dekompresuj(int opcja, vector<bool> dane) {
	cout << "\nDekompresowanie...";
	int c_length = 8 + 3; //decyduje o ilosci bitow w buforze wejsciowym 
	int p_length = 8 + 3;
	int s_length = 4;

	Dekompresja obj1(dane, p_length, c_length, s_length);
	while (obj1.check_if_input_empty() == false) {
		obj1.read_iteration();
	}
	obj1.przesun_bufory_wypisz();
	cout << "\nDekompresowanie zakonczone!";
	return obj1.output;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
	fstream plik;
	plik.open("dane.txt", ios::in);
	char ch;
	vector<int> ddd;
	while (plik.get(ch)) {
		ddd.push_back(ch);
	}

	vector<int> sss = LZ77_dekompresuj(4, LZ77_kompresuj(4, ddd));
	return 0;
}