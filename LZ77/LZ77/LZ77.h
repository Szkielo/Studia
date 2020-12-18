#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

int binary_to_int(deque<bool> liczba);
deque<bool> int_to_binary(int liczba);



vector<bool> LZ77_kompresuj(int opcja, vector<int> dane);


//////////////////////////////////////////////////////////////////////////////////






vector<int> LZ77_dekompresuj(int opcja, vector<bool> dane);