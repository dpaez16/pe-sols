#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p059_cipher.txt"


void increment_key(string & key) {
    int carry = 1;
    for (int i = key.size() - 1; i >= 0; i--) {
        char c = key[i] + carry;

        carry = c - 'z' > 0 ? 1 : 0;
        c = c - 'z' > 0 ? 'a' : c;

        key[i] = c;
    }
}

vector<int> process_line(string & line) {
	stringstream ss(line);
	string temp_str;
	vector<int> encrypted_vals;
	
	while(getline(ss, temp_str, ',')) {
        int encrypted_value = stoi(temp_str);
        encrypted_vals.push_back(encrypted_value);
	}

    return encrypted_vals;
}

vector<int> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	getline(file, line);
    vector<int> encrypted_vals = process_line(line);

	file.close();
	return encrypted_vals;
}

string try_key(string & key, vector<int> & encrypted_vals) {
    string decrypted_vals = "";

    for (unsigned i = 0; i < encrypted_vals.size(); i++) {
        int encrypted_val = encrypted_vals[i];
        int decrypted_val = encrypted_val ^ key[i % key.size()];

        decrypted_vals += (char)decrypted_val;
    }

    return decrypted_vals;
}

int sum_ascii_vals(string & decrypted_vals) {
    int sum = 0;

    for (char c : decrypted_vals) {
        sum += c;
    }

    return sum;
}

int compute_score(string & decrypted_vals) {
    int score = 0;

    for (char c : decrypted_vals) {
        if (isalpha(c)) score++;
    }

    return score;
}

int main() {
    vector<int> encrypted_vals = process_file();
    string key = "aaa";
    int max_score = 0;
    string optimal_key;

    while (true) {
        string decrypted_vals = try_key(key, encrypted_vals);
        int score = compute_score(decrypted_vals);
        
        if (score > max_score) {
            max_score = score;
            optimal_key = key;
        }
        
        increment_key(key);
        if (key == "aaa") break;
    }

    string decrypted_vals = try_key(optimal_key, encrypted_vals);
    cout << optimal_key << ": " << decrypted_vals << endl;
    cout << "Score: " << sum_ascii_vals(decrypted_vals) << endl;
    return 0;
}