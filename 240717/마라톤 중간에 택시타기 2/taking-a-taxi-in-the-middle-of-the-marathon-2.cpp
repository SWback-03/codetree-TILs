#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

int N;
vector<pair<int, int>> v;

int cal_dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }

    int result = INT_MAX;
    for (int i = 1; i < N - 1; ++i) {
        pair<int, int> temp = v[i];
        v.erase(v.begin() + i);

        int dist = 0;
        for (int j = 0; j < N - 2; ++j) {
            dist += cal_dist(v[j].first, v[j].second, v[j + 1].first, v[j + 1].second);
        }

        if (dist <= result) {
            result = dist;
        }

        v.insert(v.begin() + i, temp);
    }

    cout << result << endl;

    return 0;
}