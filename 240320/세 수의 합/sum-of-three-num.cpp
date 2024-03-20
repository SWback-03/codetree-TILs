#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // 배열 정렬
    //sort(arr.begin(), arr.end());

    int ans = 0;
    // 세 수의 조합을 찾기
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            for(int l = j + 1; l < n; ++l) {
                if(arr[i] + arr[j] + arr[l] == k) {
                    ans++;
                }
            }
        }
    }

    cout << ans;
    return 0;
}