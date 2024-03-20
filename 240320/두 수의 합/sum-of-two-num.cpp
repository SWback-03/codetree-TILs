#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> vect(n);
    unordered_map<int, int> um; // 각 숫자의 등장 횟수를 저장

    for (int i = 0; i < n; ++i) {
        cin >> vect[i];
        um[vect[i]]++; // 숫자의 등장 횟수를 증가
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        int diff = k - vect[i];
        if (um.find(diff) != um.end()) { // diff가 um에 존재하는 경우
            result += um[diff]; // diff의 등장 횟수를 결과에 추가
            // 자기 자신을 차이값으로 가지는 경우, 그 횟수를 1 감소시킴
            if (diff == vect[i]) {
                result--;
            }
        }
    }

    // 결과를 2로 나눔 (각 쌍이 두 번씩 세어졌기 때문)
    cout << result / 2 << endl;

    return 0;
}