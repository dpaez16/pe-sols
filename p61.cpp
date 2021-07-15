#include <bits/stdc++.h>

using namespace std;

#define N_DIGITS 4

#define TRIANGLE(n)         int(n * (n + 1) / 2)
#define SQUARE(n)           int(n * n)
#define PENTAGONAL(n)       int(n * (3 * n - 1) / 2)
#define HEXAGONAL(n)        int(n * (2 * n - 1))
#define HEPTAGONAL(n)       int(n * (5 * n - 3) / 2)
#define OCTAGONAL(n)        int(n * (3 * n - 2))

bool nums_good(int left, int right) {
    string left_digits = to_string(left).substr(N_DIGITS - 2);
    string right_digits = to_string(right).substr(0, 2);
    return left_digits == right_digits;
}

unordered_map<int, vector<pair<int, int>>> construct_map(vector<int> & nums, int idx) {
    unordered_map<int, vector<pair<int, int>>> num_map;
    for (int i = 0; i < 10; i++) {
        num_map[i] = vector<pair<int, int>>();
    }

    for (int i = 10; i < 100; i++) {
        vector<pair<int, int>> matching_nums;
        for (int num : nums) {
            string digits = to_string(num).substr(0, 2);
            if (digits != to_string(i)) continue;

            matching_nums.push_back({num, idx});
        }

        num_map[i] = matching_nums;
    }

    return num_map;
}

vector<int> construct_nums(int i) {
    vector<int> nums;

    int n = 0;
    while (true) {
        int num = 0;
        switch (i) {
        case 0:
            num = TRIANGLE(n);
            break;
        case 1:
            num = SQUARE(n);
            break;
        case 2:
            num = PENTAGONAL(n);
            break;
        case 3:
            num = HEXAGONAL(n);
            break;
        case 4:
            num = HEPTAGONAL(n);
            break;
        case 5:
            num = OCTAGONAL(n);
            break;
        default:
            break;
        }

        int n_digits = to_string(num).size();
        if (n_digits > N_DIGITS) break;
        
        if (n_digits == N_DIGITS) {
            nums.push_back(num);
        }

        n++;
    }

    return nums;
}

bool helper(vector<pair<int, int>> & curr, unordered_map<int, vector<pair<int, int>>> & main_map, unsigned n) {
    if (curr.size() == n) {
        vector<int> nums;
        unordered_set<int> idxs;
        int sum = 0;

        for (pair<int, int> p : curr) {
            sum += p.first;
            nums.push_back(p.first);
            idxs.insert(p.second);
        }

        if (idxs.size() != n || !nums_good(nums[n - 1], nums[0])) {
            return false;
        }

        cout << sum << endl;
        return true;
    }

    int digits = curr[curr.size() - 1].first % 100;
    vector<pair<int, int>> neighbors = main_map[digits];
    
    for (pair<int, int> neighbor : neighbors) {
        vector<pair<int, int>> new_curr = curr;
        new_curr.push_back(neighbor);

        if (helper(new_curr, main_map, n)) {
            return true;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> all_nums = {
        construct_nums(0),
        construct_nums(1),
        construct_nums(2),
        construct_nums(3),
        construct_nums(4),
        construct_nums(5)
    };

    vector<unordered_map<int, vector<pair<int, int>>>> maps;
    for (int i = 0; i < all_nums.size(); i++) {
        maps.push_back(construct_map(all_nums[i], i));
    }

    unordered_map<int, vector<pair<int, int>>> main_map;
    for (int i = 0; i < 100; i++) {
        main_map[i] = vector<pair<int, int>>();
    }

    for (int i = 0; i < 100; i++) {
        for (int idx = 0; idx < maps.size(); idx++) {
            main_map[i].insert(main_map[i].end(), maps[idx][i].begin(), maps[idx][i].end());
        }
    }

    for (int num : all_nums[0]) {
        vector<pair<int, int>> curr = {{num, 0}};
        if (helper(curr, main_map, all_nums.size()))
            break;
    }

    return 0;
}