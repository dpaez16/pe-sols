#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p042_words.txt"

vector<string> process_line(string & line) {
	stringstream ss(line);
	string temp_str;
	vector<string> names;
	
	while(getline(ss, temp_str, ',')) {
        names.push_back(temp_str);
	}

    return names;
}

vector<string> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	getline(file, line);
    vector<string> names = process_line(line);

	file.close();
	return names;
}

unsigned long long name_alpha_value(string & name) {
    unsigned long long val = 0;
    for (char c : name) {
        if (!isalpha(c)) continue;
        val += (toupper(c) - 'A') + 1;
    }

    return val;
}

unsigned long long triangle_number(int n) {
    return n * (n + 1) / 2;
}

bool is_triangle_number(unsigned long long & a) {
    int n = 1;
    
    while (triangle_number(n) < a) n++;

    return triangle_number(n) == a;
}

bool is_triangle_word(string & word) {
    unsigned long long word_val = name_alpha_value(word);
    return is_triangle_number(word_val);
}

int main() {
    vector<string> words = process_file();
    int n_triangle_words = 0;

    for (string word : words) {
        if (is_triangle_word(word)) n_triangle_words++;
    }

    cout << n_triangle_words << endl;
    return 0;
}