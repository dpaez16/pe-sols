#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p098_words.txt"

unordered_set<string> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
	unordered_set<string> words;

	while(getline(file, line)) {
		stringstream ss(line);
		string raw_word;
		
		while(getline(ss, raw_word, ',')) {
			size_t word_size = raw_word.size() - 2;
			string word = raw_word.substr(1, word_size);
			words.insert(word);
		}
	}

	file.close();
	return words;
}

bool is_anagram(string word, string other_word) {
	sort(word.begin(), word.end());
	sort(other_word.begin(), other_word.end());

	return word == other_word;
}

unordered_set<string> get_anagrams(string & word, unordered_set<string> & words) {
	unordered_set<string> anagrams;

	for (string possible_anagram : words) {
		if (!is_anagram(word, possible_anagram))
			continue;

		anagrams.insert(possible_anagram);
	}

	for (string anagram : anagrams) {
		words.erase(anagram);
	}

	return anagrams;
}

vector<unordered_set<string>> get_anagram_groups(unordered_set<string> & words) {
	vector<unordered_set<string>> anagram_groups;

	while (!words.empty()) {
		string word = *(words.begin());
		unordered_set<string> anagrams = get_anagrams(word, words);
		
		if (anagrams.size() == 1)
			continue;

		anagram_groups.push_back(anagrams);
	}

	return anagram_groups;
}

bool is_square(int n) {
	int sqrt_n = floor(sqrt(n));

	return pow(sqrt_n, 2) == n;
}

int main() {
	unordered_set<string> words = process_file();
	vector<unordered_set<string>> anagram_groups = get_anagram_groups(words);

	return 0;
}
