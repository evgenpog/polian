#include <string>
#include <string.h>
#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
#include <vector>

using namespace std;

char s[10000], op[10000];
long long res[10005];
vector <string> pol;
int n, f, ptr = 0;
long long x, y;

int prior(char s) {
	if (s == '+' || s == '-') return 1;
	if (s == '*' || s == '/') return 2;
	if (s == '^') return 4;
	if (s == '#') return 3;
}

long long qpow(long long a, long long n) {
	long long b = 1;
	if (n < 0) return 0;
	while (n > 0) {
		if (n % 2 != 0) b *= a;
		a = a * a;
		n /= 2;
	}
	return b;
}


int main() {

	cin >> s;
	n = strlen(s);

	for (int i = 0; i < n; i++) {
		if (s[i] == '-') {
			if (i == 0 || s[i - 1] == '(') {
				s[i] = '#';
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (s[i] == '(') { op[ptr] = s[i]; ptr++; }
		if (s[i] == ')') {
			while (op[ptr - 1] != '(') {
				string st(1, op[ptr - 1]);
				pol.push_back(st);
				ptr--;
			}
			ptr--;
		}
		if (s[i] == 'x' || s[i] == 'y') {
			string st(1, s[i]);
			pol.push_back(st);
		}
		if (s[i] == '^') {
			op[ptr] = '^';
			ptr++;
		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '#') {
			while (ptr != 0 && op[ptr - 1] != '(' && prior(s[i]) <= prior(op[ptr - 1])) {
				string st(1, op[ptr - 1]);
				pol.push_back(st);
				ptr--;
			}
			op[ptr] = s[i];
			ptr++;
		}
		if ('0' <= s[i] && s[i] <= '9') {
			string st = "";
			while ('0' <= s[i] && s[i] <= '9') {
				st += s[i];
				i++;
			}
			pol.push_back(st);
			i--;
		}
	}

	for (int i = ptr - 1; i >= 0; i--) {
		string st(1, op[i]);
		pol.push_back(st);
	}
	//    for(int i = 0; i < pol.size(); i++) cout << pol[i];
	//    cout << endl;
	//    return 0;

	cin >> f;
	while (f--) {
		cin >> x >> y;
		res[0] = 0;
		ptr = 0;
		for (int i = 0; i < pol.size(); i++) {
			if (pol[i] == "x") {
				res[ptr] = x;
				ptr++;
			}
			if (pol[i] == "y") {
				res[ptr] = y;
				ptr++;
			}
			if ('0' <= pol[i][0] && pol[i][0] <= '9') {
				long long v = 0;
				for (int j = 0; j < pol[i].size(); j++) {
					int abc = (int)(pol[i][j] - '0');
					v = v * 10 + abc;
				}
				res[ptr] = v;
				ptr++;
			}
			if (pol[i] == "+") {
				res[ptr - 2] += res[ptr - 1];
				ptr--;
			}
			if (pol[i] == "-") {
				res[ptr - 2] -= res[ptr - 1];
				ptr--;
			}
			if (pol[i] == "*") {
				res[ptr - 2] = res[ptr - 2] * res[ptr - 1];
				ptr--;
			}
			if (pol[i] == "/") {
				res[ptr - 2] = res[ptr - 2] / res[ptr - 1];
				ptr--;
			}
			if (pol[i] == "#") {
				res[ptr - 1] = (-1)*(res[ptr - 1]);
			}
			if (pol[i] == "^") {
				res[ptr - 2] = qpow(res[ptr - 2], res[ptr - 1]);
				ptr--;
			}
		}
		cout << res[0] << endl;
	}
	system("pause");
	return 0;
}