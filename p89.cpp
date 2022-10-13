#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p089_roman.txt"

unordered_map<string, unsigned> DENOMINATIONS_MAP = {
    {"I", 1},
    {"IV", 4},
    {"V", 5},
    {"IX", 9},
    {"X", 10},
    {"XL", 40},
    {"L", 50},
    {"XC", 90},
    {"C", 100},
    {"CD", 400},
    {"D", 500},
    {"CM", 900},
    {"M", 1000}
};

vector<string> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
	vector<string> numerals;

	while(getline(file, line)) {
		numerals.push_back(line);
	}

	file.close();
	return numerals;
}

string get_substr(unsigned i, string & numeral) {
    if (i + 1 < numeral.size()) {
        string substr = numeral.substr(i, 2);
        if (DENOMINATIONS_MAP.find(substr) != DENOMINATIONS_MAP.end()) {
            return substr;
        } else {
            return numeral.substr(i, 1);
        }
    } else {
        return numeral.substr(i, 1);
    }
}

unsigned to_int(string numeral) {
    unsigned i = 0;
    unsigned ans = 0;

    while (i < numeral.size()) {
        string substr = get_substr(i, numeral);
        ans += DENOMINATIONS_MAP[substr];
        i += substr.size();
    }

    return ans;
}

string to_roman(unsigned n, vector<unsigned> & numerical_denominations, unordered_map<unsigned, string> & denominations_map_rev) {
    string ans = "";

    while (n > 0) {
        unsigned idx = numerical_denominations.size() - 1;
        while (numerical_denominations[idx] > n) {
            idx--;
        }

        unsigned numerical_denomination = numerical_denominations[idx];
        ans += denominations_map_rev[numerical_denomination];
        n -= numerical_denomination;
    }

    return ans;
}

int main() {
    vector<unsigned> numerical_denominations;
    unordered_map<unsigned, string> denominations_map_rev;
    for (auto kvPair : DENOMINATIONS_MAP) {
        numerical_denominations.push_back(kvPair.second);
        denominations_map_rev.insert({kvPair.second, kvPair.first});
    }

    sort(numerical_denominations.begin(), numerical_denominations.end());

    vector<string> numerals = process_file();
    unsigned sum = 0;
    for (string numeral : numerals) {
        unsigned numeral_int = to_int(numeral);
        string numeral_valid = to_roman(numeral_int, numerical_denominations, denominations_map_rev);
        sum += numeral.size() - numeral_valid.size();
    }

    cout << sum << endl;
    return 0;
}