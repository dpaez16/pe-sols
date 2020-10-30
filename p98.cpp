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

vector<int> get_squares(int upper_bound) {
	vector<int> squares;

	int n = 0;
	while (true) {
		int n_sq = pow(n, 2);

		if (n_sq >= upper_bound)
			break;
		
		squares.push_back(n_sq);
		n++;
	}

	reverse(squares.begin(), squares.end());
	return squares;
}

bool subs_are_unique(unordered_map<char, int> & letter_map) {
	unordered_map<int, unordered_set<char>> num_map;

	for (auto p : letter_map) {
		int letter = p.first;
		int num = p.second;
		
		if (num_map.find(num) == num_map.end()) {
			num_map[num] = {};
		}

		num_map[num].insert(letter);
	}

	for (auto p : num_map) {
		auto letters = p.second;

		if (letters.size() > 1)
			return false;
	}

	return true;
}

int create_num(string word, unordered_map<char, int> & letter_map) {
	for (unsigned idx = 0; idx < word.size(); idx++) {
		char letter = word[idx];
		word[idx] = '0' + letter_map[letter];
	}

	if (word[0] == '0') return -1;

	int num = stoi(word);
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

bool subs_work_helper(vector<int> & subs, string & word) {
	if (subs.size() != word.size()) return false;

	for (unsigned i = 0; i < word.size(); i++) {
		for (unsigned j = 0; j < word.size(); j++) {
			if (word[i] != word[j]) continue;
			if (subs[i] != subs[j]) return false;
		}
	}

	return true;
}

bool subs_work(vector<int> & subs, unordered_set<int> & squares, string & word, string & other_word) {
	if (subs_work_helper(subs, word)) {
		unordered_map<char, int> letter_map;
		for (unsigned i = 0; i < word.size(); i++) {
			char letter = word[i];
			letter_map[letter] = subs[i];
		}
		
		if (!subs_are_unique(letter_map)) {
			return false;
		}

		int num = create_num(other_word, letter_map);
		return squares.find(num) != squares.end();
	} else if (subs_work_helper(subs, other_word)) {
		unordered_map<char, int> letter_map;
		for (unsigned i = 0; i < other_word.size(); i++) {
			char letter = other_word[i];
			letter_map[letter] = subs[i];
		}

		if (!subs_are_unique(letter_map)) {
			return false;
		}

		int num = create_num(word, letter_map);
		return squares.find(num) != squares.end();
	} else {
		return false;
	}
}

vector<int> num_to_vec(int n) {
	vector<int> v;
	
	while (n > 0) {
		v.push_back(n % 10);
		n /= 10;
	}

	reverse(v.begin(), v.end());
	return v;
}

int get_square(unordered_set<string> & anagram_group) {
	pair<string, string> p = get_pair(anagram_group);
	string word = p.first;
	string other_word = p.second;
	int n_digits = word.size();
	int upper_bound = pow(10, n_digits);

	vector<int> squares = get_squares(upper_bound);
	unordered_set<int> squares_set(squares.begin(), squares.end());
	
	for (int i : squares) {
		vector<int> subs = num_to_vec(i);
		
		if (!subs_work(subs, squares_set, word, other_word)) {
			continue;
		}

		return i;
	}

	return -1;
}

int main() {
	unordered_set<string> words = process_file();
	vector<unordered_set<string>> anagram_groups = get_anagram_groups(words);

	int max_square = 0;

	for (auto anagram_group : anagram_groups) {
		int square = get_square(anagram_group);
		max_square = max(max_square, square);
	}

	cout << max_square << endl;
	return 0;
}
