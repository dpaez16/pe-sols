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

unordered_set<int> get_squares(int upper_bound) {
	unordered_set<int> squares;

	int n = 0;
	while (true) {
		int n_sq = pow(n, 2);

		if (n_sq >= upper_bound)
			break;
		
		squares.insert(n_sq);
		n++;
	}

	return squares;
}

vector<char> get_unique_letters(string & word) {
	unordered_set<char> unique_letters(word.begin(), word.end());
	vector<char> letters_vec;

	for (char letter : unique_letters) {
		letters_vec.push_back(letter);
	}

	return letters_vec;
}

void decrement_vec(vector<int> & v) {
	int r = -1;
	for (int idx = v.size() - 1; idx >= 0; idx--) {
		v[idx] += r;
		
		if (v[idx] == -1) {
			v[idx] = 9;
			r = -1;
		} else {
			r = 0;
		}
	}
}

vector<int> get_begin_vec(int n) {
	vector<int> vec;

	for (int i = 0; i < n; i++) {
		vec.push_back(9);
	}

	return vec;
}

bool subs_are_unique(vector<int> & subs) {
	unordered_set<int> unique_nums(subs.begin(), subs.end());

	return subs.size() == unique_nums.size();
}

int create_num(string word, vector<char> & unique_letters, vector<int> & subs) {
	unordered_map<char, char> letter_map;
	for (unsigned idx = 0; idx < unique_letters.size(); idx++) {
		char letter = unique_letters[idx];
		char sub = '0' + subs[idx];

		letter_map[letter] = sub;
	}

	string new_word = word;
	for (unsigned idx = 0; idx < new_word.size(); idx++) {
		char letter = new_word[idx];
		new_word[idx] = letter_map[letter];
	}

	int num = stoi(new_word);
	return num;
}

pair<string, string> get_pair(unordered_set<string> & s) {
	auto it = s.begin();
	string word = *it;
	it++;
	string other_word = *it;
	pair<string, string> p(word, other_word);

	return p;
}

int get_square(unordered_set<string> & anagram_group, unordered_set<int> & squares) {
	pair<string, string> p = get_pair(anagram_group);
	string word = p.first;
	string other_word = p.second;
	vector<char> unique_letters = get_unique_letters(word);
	int n_digits = unique_letters.size();
	int upper_bound = pow(10, n_digits);

	vector<int> curr_subs = get_begin_vec(n_digits);
	int max_square = -1;

	for (int i = 0; i < upper_bound; i++, decrement_vec(curr_subs)) {
		if (!subs_are_unique(curr_subs)) {
			continue;
		}

		int num = create_num(word, unique_letters, curr_subs);
		int other_num = create_num(other_word, unique_letters, curr_subs);

		if (squares.find(num) == squares.end()) continue;
		if (squares.find(other_num) == squares.end()) continue;
		
		max_square = max(max_square, max(num, other_num));
	}

	return max_square;
}

int main() {
	unordered_set<string> words = process_file();
	vector<unordered_set<string>> anagram_groups = get_anagram_groups(words);

	int max_n_digits = 0;

	for (auto anagram_group : anagram_groups) {
		pair<string, string> p = get_pair(anagram_group);
		string word = p.first;
		int n_digits = word.size();
		max_n_digits = max(max_n_digits, n_digits);
	}

	int upper_bound = pow(10, max_n_digits);
	unordered_set<int> squares = get_squares(upper_bound);

	int max_square = 0;

	for (auto anagram_group : anagram_groups) {
		string word = *(anagram_group.begin());
		int square = get_square(anagram_group, squares);
		max_square = max(max_square, square);
		cout << max_square << endl;
	}

	return 0;
}
