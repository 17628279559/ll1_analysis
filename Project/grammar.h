#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
using namespace std;


class grammar {
private:
    vector<char> Vn;
    vector<char> Vt;
    map<char, vector<string>> P;
    char S;
public:
    grammar() {};
    grammar(vector<char> Vn, vector<char> Vt, map<char, vector<string>> P, char S);

    void set_value(vector<char> Vn, vector<char> Vt, map<char, vector<string>> P, char S);
    int len();
    map<char, vector<string>>& getP();
    bool is_in_Vn(char n);
};