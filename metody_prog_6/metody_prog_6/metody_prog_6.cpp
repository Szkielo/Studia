#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <string>

using namespace std;

ofstream zapis("mux.txt"); // globalną nie trzeba sie bawić

bool czy_powtorki(string *X, string A, int i, int p){		//funkcja sprawdza, czy kombinacje wierszy macierzy X powtarzaja sie w macierzy
	for (int j = 0; j < i; j++) {
		if (X[j] == A) return false;
	}
	return true;
}

int dziesietnie(int x1, int x2) {		//funkcja zwraca wartosc dziesietna liczb podanych na wejsciu (do funkcji dekompozycja())
	return x2 * 1 + x1 * 2;
}

void wypelnij_tablice(int X[10][1024], int Y[1024], int n, int stany)		//funkcja wypełnia losowo macierz X i Y
{
	int i, j;
	string *kombinacja = new string[stany];			// używam stringa, bo łatwiej go porównać
	for (i = 0; i < stany; i++){
		j = 0;
		while (j < n){
			if ((rand() % 2) == 1)			//losowo wpisujemy zera i jedynki do macierzy
				kombinacja[i] += "1";
			else
				kombinacja[i] += "0";
			j++;
		}
		if (czy_powtorki(kombinacja, kombinacja[i], i, stany) == false){ 	//sprawdzamy, czy kombinacja jest unikalna
			kombinacja[i] = "";
			i--;
		}
	}
	string w;
	for (i = 0; i < stany; i++){		//przepisujemy kombinacje ze stringow na tablice int
		w = kombinacja[i];
		for (int j = 0; j < n; j++){
			X[j][i] = w[j] - '0';
		}
	}

	for (i = 0; i < stany; i++){		//losujemy macierz Y
		if (((rand() % 2) + 0) == 1)
			Y[i] = 1;
		else
			Y[i] = 0;
	}


}

string sprawdz(int A[10][1024], int Ay[1024], int a, int k, int x2){	//funkcja sprawdzajaca zaleznosc liniowa poszczegolnych wierszy macierzy
	string wynik; // funkcja musi być typu string, żeby mogła wyświetlać "-" itp
	int rowne = 0;
	int neg = 0;
	if (a == 0)		//jesli kombinacja nie wystepuje, wypisujemy -
		return "-";
	if (a == 1)			//jesli z danej kombinacji powtarza sie tylko jeden wiersz, zwracamy wartosc tego wiersza
	{
		wynik += Ay[a - 1] + '0';
		return wynik;
	}
	for (int i = 1; i < a; i++)	// dla wiekszej ilosci sprawdzamy, czy wartosci macierzy Y zgadzaja sie ze soba
	{
		if (Ay[i] != Ay[i - 1])
		{
			rowne = 0;
			break;
		}
		else rowne = 1;
	}
	if (rowne == 1)
	{
		wynik += Ay[a - 1] + '0';
		return wynik;
	}

	for (int i = 0; i < k; i++)		// jesli nie, sprawdzamy czy wynikiem jest ktoras ze zmiennych
	{
		for (int j = 0; j < a; j++)
		{
			if (A[i][j] != Ay[j])
			{
				rowne = 0;
				break;
			}
			else
			{
				rowne = 1;
			}
		}
		if (rowne == 1)
		{
			wynik += "x";
			wynik += (x2 + 2 + i) + '0';
			return wynik;
		}
	}
	for (int i = 0; i < k; i++){		//jeśli też nie, to sprawdzamy ich zanegowane wartości
		for (int j = 0; j < a; j++){
			if (Ay[j] == 0) 
				neg = 1;
			else
				neg = 0;
			if (A[i][j] != neg)
			{
				rowne = 0;
				break;
			}
			else rowne = 1;		
		}
		if (rowne == 1)
		{
			wynik += "-x";
			wynik += (x2 + 2 + i) + '0';
			return wynik;
		}
	}
	if (k == 1)
		return "error";
	return "MUX";		//zapis jest zgodny z tym z pliku
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dekompozycja(int X[][1024], int Y[], int n, int stany, int x1, int x2, int L, int nr){
	int a, b, c, d;
	a = b = c = d = 0;
	int A[10][1024], B[10][1024], C[10][1024], D[10][1024];
	int	Ay[1024]{ 0 }, By[1024]{ 0 }, Cy[1024]{ 0 }, Dy[1024]{ 0 }; // y to podmacierze
	for (int i = 0; i < stany; i++)
	{
		if (L == 0)
		{
			for (int j = 0; j < n; j++)
			{					//wypisujemy macierz poczatkowa X oraz Y
				cout << X[j][i];
				zapis << X[j][i];
			}
			cout << "	" << Y[i] << endl;
			zapis << "	" << Y[i] << endl;
		}
		if (X[x1][i] == 0 && X[x2][i] == 0)
		{
			for (int j = 0; j < n - 2; j++)		//dla kolejnych kombinacji wpisujemy do podmacierzy wiersze macierzy glownej
				A[j][a] = X[j + 2][i];
			Ay[a] = Y[i];		
			a++;
		}
		if (X[x1][i] == 0 && X[x2][i] == 1)
		{
			for (int j = 0; j < n - 2; j++)
				B[j][a] = X[j + 2][i];
			By[b] = Y[i];
			b++;
		}
		if (X[x1][i] == 1 && X[x2][i] == 0)
		{
			for (int j = 0; j < n - 2; j++)
				C[j][c] = X[j + 2][i];
			Cy[c] = Y[i];
			c++;
		}
		if (X[x1][i] == 1 && X[x2][i] == 1)
		{
			for (int j = 0; j < n - 2; j++)
				D[j][d] = X[j + 2][i];
			Dy[d] = Y[i];
			d++;
		}
		
	}

	cout << endl << "------------------" << endl << "L = " << L << endl;		//wypisujemy kolejny poziom
	zapis << endl << "------------------" << endl << "L = " << L << endl;

	if (sprawdz(A, Ay, a, n - x2 - 1, x2) != "MUX")		//sprawdzamy, czy potrzebna jest dalsza dekompozycja
	{
		cout << "MUX" << nr << "(00) = " << sprawdz(A, Ay, a, n - x2 - 1, x2) << endl;
		zapis << "MUX" << nr << "(00) = " << sprawdz(A, Ay, a, n - x2 - 1, x2) << endl;
	}
	else
	{
		cout << "MUX" << nr << "(00) = " << sprawdz(A, Ay, a, n - x2 - 1, x2) << dziesietnie(0, 0) << endl; // funkcja dziesiętnie dopisze numer MUXa (np MUX1)
		zapis << "MUX" << nr << "(00) = " << sprawdz(A, Ay, a, n - x2 - 1, x2) << dziesietnie(0, 0) << endl;
	}
	if (sprawdz(B, By, b, n - x2 - 1, x2) != "MUX")
	{
		cout << "MUX" << nr << "(01) = " << sprawdz(B, By, b, n - x2 - 1, x2) << endl;
		zapis << "MUX" << nr << "(01) = " << sprawdz(B, By, b, n - x2 - 1, x2) << endl;
	}
	else
	{
		cout << "MUX" << nr << "(01) = " << sprawdz(B, By, b, n - x2 - 1, x2) << dziesietnie(0, 1) << endl;
		zapis << "MUX" << nr << "(01) = " << sprawdz(B, By, b, n - x2 - 1, x2) << dziesietnie(0, 1) << endl;
	}
	if (sprawdz(C, Cy, c, n - x2 - 1, x2) != "MUX")
	{
		cout << "MUX" << nr << "(10) = " << sprawdz(C, Cy, c, n - x2 - 1, x2) << endl;
		zapis << "MUX" << nr << "(10) = " << sprawdz(C, Cy, c, n - x2 - 1, x2) << endl;
	}
	else
	{
		cout << "MUX" << nr << "(10) = " << sprawdz(C, Cy, c, n - x2 - 1, x2) << dziesietnie(1, 0) << endl;
		zapis << "MUX" << nr << "(10) = " << sprawdz(C, Cy, c, n - x2 - 1, x2) << dziesietnie(1, 0) << endl;
	}
	if (sprawdz(D, Dy, d, n - x2 - 1, x2) != "MUX")
	{
		cout << "MUX" << nr << "(11) = " << sprawdz(D, Dy, d, n - x2 - 1, x2) << endl;
		zapis << "MUX" << nr << "(11) = " << sprawdz(D, Dy, d, n - x2 - 1, x2) << endl;
	}
	else
	{
		cout << "MUX" << nr << "(11) = " << sprawdz(D, Dy, d, n - x2 - 1, x2) << dziesietnie(1, 1) << endl;
		zapis << "MUX" << nr << "(11) = " << sprawdz(D, Dy, d, n - x2 - 1, x2) << dziesietnie(1, 1) << endl;
	}

	if (sprawdz(A, Ay, a, n - x2 - 1, x2) == "MUX")		//sprawdzamy, czy dla kombinacji kolejnego poziomu potrzebna jest dalsza dekompozycja, przekazujemy L+1
		dekompozycja(A, Ay, n - 2, a, x1, x2, L + 1, dziesietnie(0, 0));
	if (sprawdz(B, By, b, n - x2 - 1, x2) == "MUX")
		dekompozycja(B, By, n - 2, b, x1, x2, L + 1, dziesietnie(0, 1));
	if (sprawdz(C, Cy, c, n - x2 - 1, x2) == "MUX")
		dekompozycja(C, Cy, n - 2, c, x1, x2, L + 1, dziesietnie(1, 0));
	if (sprawdz(D, Dy, d, n - x2 - 1, x2) == "MUX")
		dekompozycja(D, Dy, n - 2, d, x1, x2, L + 1, dziesietnie(1, 1));
}


int main()
{
	int n, stany;
	int X[10][1024];
	int Y[1024]{ 0 };
	srand(time(NULL));
	
	cout << "Program dokonuje syntezy układu kombinacyjnego UK(X, Y) realizowanej na multiplekserach MUX 2^n:1.";
	cout << "\nWyniki działania programu sa zapisywane do pliku mux.txt" << endl;

	
	cout << "\nPodaj liczbe wejsc ukladu z zakresu [1, 10]: ";
	cin >> n;
	zapis << "\nPodaj liczbe wejsc ukladu z zakresu [1, 10]: " << n;

	int max_stany = pow(2, n);
	
	cout << "Podaj liczbe stanow okreslonych z zakresu [1, " << max_stany << ")]: ";
	cin >> stany;
	zapis << "Podaj liczbe stanow okreslonych z zakresu [1, " << max_stany << ")]: " << stany << endl;

	wypelnij_tablice(X, Y, n, stany);
	cout << "X  Y" << endl << endl;
	zapis << "X	Y" << endl << endl;

	dekompozycja(X, Y, n, stany, 0, 1, 0, 0);

	char pauza;
	cin >> pauza;
	return 0;
}

