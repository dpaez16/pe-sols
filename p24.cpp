#include<iostream>
#include<vector>
#include<algorithm>

#define IDX 1000000 - 1

using namespace std;

vector<long long> permutations;

void add_permutation(vector<int> & arr) {
	string num = "";
	for (auto elem : arr)
		num += to_string(elem);
	
	permutations.push_back(stoll(num));
}

void heap_permutation(vector<int> & arr, int size) {
	if (size == 1) {
		add_permutation(arr);
		return;
	}

	for (int i = 0; i < size; i++) {
		heap_permutation(arr, size - 1);
		if (size % 2 == 1)
			swap(arr[0], arr[size - 1]);
		else
			swap(arr[i], arr[size - 1]);
	}
}

int main() {
	vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	heap_permutation(arr, arr.size());
	sort(permutations.begin(), permutations.end());

	cout << permutations[IDX] << endl;

	return 0;
}

