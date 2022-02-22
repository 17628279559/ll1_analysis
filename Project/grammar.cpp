#include "grammar.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
using namespace std;

grammar::grammar(vector<char> Vn, vector<char> Vt, map<char, vector<string>> P, char S)
{
	this->Vn = Vn;
	this->Vt = Vt;
	this->P = P;
	this->S = S;
}

void grammar::set_value(vector<char> Vn, vector<char> Vt, map<char, vector<string>> P, char S)
{
	this->Vn = Vn;
	this->Vt = Vt;
	this->P = P;
	this->S = S;
	return ;
}

int grammar::len()
{
	return (this->P).size();
}

map<char, vector<string>>& grammar::getP()
{
	return this->P;
}

bool grammar::is_in_Vn(char n)
{
	for (int i = 0; i < (this->Vn).size(); i++) {
		if (n == (this->Vn)[i]) {
			return true;
		}
	}
	return false;
}
