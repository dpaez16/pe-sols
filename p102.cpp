#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p102_triangles.txt"
#define ORIGIN pair<int, int>(0, 0)

vector<pair<int, int>> process_line(string & line) {
	stringstream ss(line);
	string temp_str;
    vector<pair<int, int>> triangle;
	
    for (int i = 0; i < 3; i++) {
        pair<int, int> vertex;
        
        getline(ss, temp_str, ',');
        vertex.first = stoi(temp_str);

        getline(ss, temp_str, ',');
        vertex.second = stoi(temp_str);

        triangle.push_back(vertex);
    }

    return triangle;
}

vector<vector<pair<int, int>>> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
    vector<vector<pair<int, int>>> triangles;

	while (getline(file, line)) {
		vector<pair<int, int>> triangle = process_line(line);
		triangles.push_back(triangle);
	}

	file.close();
	return triangles;
}

double compute_area(vector<pair<int, int>> & triangle) {
    int x1 = triangle[0].first, y1 = triangle[0].second;
    int x2 = triangle[1].first, y2 = triangle[1].second;
    int x3 = triangle[2].first, y3 = triangle[2].second;

    return 0.5 * abs(x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3);
}

bool triangle_has_origin(vector<pair<int, int>> & triangle) {
    double triangle_area = compute_area(triangle);

    double total_area_of_subtriangles = 0;
    for (unsigned i = 0; i < 3; i++) {
        vector<pair<int, int>> subtriangle = {triangle[i], triangle[(i + 1) % 3], ORIGIN};
        total_area_of_subtriangles += compute_area(subtriangle);
    }

    return total_area_of_subtriangles == triangle_area;
}

int main() {
    vector<vector<pair<int, int>>> triangles = process_file();
    int count = 0;

    for (auto triangle : triangles) {
        if (triangle_has_origin(triangle)) count++;
    }

    cout << count << endl;
    return 0;
}