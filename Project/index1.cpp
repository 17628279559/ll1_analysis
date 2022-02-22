#include "grammar.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
using namespace std;

int num = 1;

bool S_start(string yipipei, string daipipei, grammar& g) {
	int index = 0, i;

	for (i = 0; i < yipipei.size(); i++) {
		if (!g.is_in_Vn(yipipei[i])) {
			if (i == daipipei.size())
				return false;
			if (yipipei[i] != daipipei[i])
				return false;
		}
		else {
			if (i == daipipei.size()) {
				for (int j = i; j < yipipei.size(); j++) {
					if (!g.is_in_Vn(yipipei[j]))
						return false;
					else {
						int k;
						for (k = 0; k < g.getP()[yipipei[j]].size(); k++) {
							if (g.getP()[yipipei[j]][k] == "/") {
								cout << yipipei[j]<<"替换为空串" << endl;
								break;
							}

						}
						if (k == g.getP()[yipipei[j]].size())
							return false;
					}
				}
				cout << "第" << num << "次匹配结果:" << endl;
				cout << "左部:" << yipipei << endl;
				cout << "右部:" << daipipei << endl;
				cout << "匹配成功"<< endl;
				cout << "*********************************************" << endl;
				num++;
				return true;
			}
			index = i;
			break;
		}
	}
	if (i == yipipei.size() && i == daipipei.size())
		return true;
	if (i == yipipei.size() && i < daipipei.size())
		return false;
	vector<string> right = g.getP()[yipipei[index]];
	for (i = 0; i < right.size(); i++) {
		if (!g.is_in_Vn(right[i][0]) && right[i][0] != daipipei[index]) {
			if (right[i][0] == '/') {
				cout << "第" << num << "次匹配结果:" << endl;
				cout << "左部:" << yipipei << endl;
				cout << "右部:" << daipipei << endl;
				cout << "将       " << yipipei[index] <<  "       替换为       " << right[i] << endl;
				cout << "*********************************************" << endl;
				num++;
				if (S_start(yipipei.substr(0, index) + yipipei.substr(index + 1, yipipei.size() - index - 1), daipipei, g)) {
					return true;
				}

			}
			continue;
		}
		else {
			cout << "第" << num << "次匹配结果:" << endl;
			cout << "左部:    " << yipipei << endl;
			cout << "右部:    " << daipipei << endl;
			cout << "将       " << yipipei[index] << "       替换为       " << right[i] << endl;
			cout << "*********************************************" << endl;
			num++;
			if (S_start(yipipei.substr(0, index) + right[i] + yipipei.substr(index + 1, yipipei.size() - index - 1), daipipei, g)) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	ifstream OutFile("ll2.txt");

	vector<char> Vn;
	vector<char> Vt;
	map<char, vector<string>> P;
	char S;

	OutFile >> S;
	if (S == '0') {
		return 0;
	}

	string tmp_str;
	OutFile >> tmp_str;
	int n1 = tmp_str.size();
	for (int i = 0; i < n1; ++i) {
		if (tmp_str[i] == ',') {
			tmp_str[i] = ' ';
		}
	}
	istringstream out1(tmp_str);
	char str;
	while (out1 >> str) {
		Vt.push_back(str);
	}

	OutFile >> tmp_str;
	int n2 = tmp_str.size();
	for (int i = 0; i < n2; ++i) {
		if (tmp_str[i] == ',') {
			tmp_str[i] = ' ';
		}
	}
	istringstream out2(tmp_str);
	while (out2 >> str) {
		Vn.push_back(str);
	}

	while (OutFile >> tmp_str) {
		if (P.count(tmp_str[0]) == 0) {
			vector<string> temp;
			temp.push_back(tmp_str.substr(3, tmp_str.size() - 3));
			P.insert(pair<char, vector<string>>(tmp_str[0], temp));
		}
		else {
			P[tmp_str[0]].push_back(tmp_str.substr(3, tmp_str.size() - 3));
		}
	}

	grammar g(Vn, Vt, P, S);
	string yipipei;
	yipipei = S;

	while (true) {
		string s;
		cin >> s;

		if (S_start(yipipei, s, g))
			cout << s << "符合该文法" << endl;
		else
			cout << s << "不符合该文法" << endl;
		cout << "*********************************************\n\n" << endl;
	}
	return 0;
}