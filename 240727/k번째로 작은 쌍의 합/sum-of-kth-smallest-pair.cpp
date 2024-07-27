#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> arr1(n);
    vector<int> arr2(m);

    for (int i = 0; i < n; ++i) {
        cin >> arr1[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> arr2[i];
    }

    // 정렬
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    // 최소 힙
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> min_heap;

    // 최소 힙 초기화
    for (int i = 0; i < n; ++i) {
        min_heap.push({arr1[i] + arr2[0], {i, 0}});
    }

    // k번째 작은 합을 찾기
    int result = 0;
    for (int count = 0; count < k; ++count) {
        auto current = min_heap.top();
        min_heap.pop();
        result = current.first;
        int i = current.second.first;
        int j = current.second.second;
        if (j + 1 < m) {
            min_heap.push({arr1[i] + arr2[j + 1], {i, j + 1}});
        }
    }

    cout << result << endl;

    return 0;
}