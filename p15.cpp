#include <bits/stdc++.h>

using namespace std;

#define N 20
#define PAIR(r, c) pair<int, int>(r, c)

struct pair_hash {
	size_t operator() (const pair<int, int> & p) const {
		ostringstream out;
		out << p.first << ',' << p.second;
		return hash<string>()(out.str());
	}
};

int main() {
	unordered_map<pair<int, int>, unsigned long long, pair_hash> num_routes;

	for (int r = N; r >= 0; r--) {
		for (int c = N; c >= 0; c--) {
			pair<int, int> coord(r, c);

			if (r == N && c == N) {
				num_routes[coord] = 1;
			} else if (r == N) {
				num_routes[coord] = num_routes[PAIR(r, c + 1)];
			} else if (c == N) {
				num_routes[coord] = num_routes[PAIR(r + 1, c)];
			} else {
				num_routes[coord] = num_routes[PAIR(r + 1, c)] + \
						    num_routes[PAIR(r, c + 1)];
			}
		}
	}

	cout << num_routes[PAIR(0, 0)] << endl;
	return 0;
}
