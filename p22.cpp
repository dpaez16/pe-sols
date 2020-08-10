#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p022_names.txt"

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

int main() {
    vector<string> names = process_file();
    sort(names.begin(), names.end());
    unsigned long long total = 0;

    for (size_t i = 0; i < names.size(); i++) {
        string name = names[i];
        total += (i + 1) * name_alpha_value(name);
    }

    cout << total << endl;
    return 0;
}