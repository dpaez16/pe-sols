#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p098_words.txt"

set<string> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
	set<string> words;

	while(getline(file, line)) {
		stringstream ss(line);
		string raw_word;
		vector<int> row;
		
		while(getline(ss, raw_word, ',')) {
			size_t word_size = raw_word.size() - 2;
			string word = raw_word.substr(1, word_size);
			words.insert(word);
		}
	}

	file.close();
	return words;
}

int main() {
	set<string> words = process_file();

	return 0;
}
