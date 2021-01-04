#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

string generate_letters();

vector<string> get_dictionary();

bool check_word(string slowo, string lista);

bool check_dictionary(string slowo, vector<string> slownik);

bool check_base(string slowo, vector<string> baza);

string result(string slowo, string lista, vector<string> slownik, vector<string> baza);



#endif // MAIN_H
