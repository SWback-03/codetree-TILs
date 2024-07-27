#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

#define MAX_N 100000
#define MAX_M 100000

int n, m, k;

priority_queue<int> arr;
unordered_multiset<int> umset;

int main() {
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        umset.insert(tmp);
    }

    for (int i = 0; i < m; ++i) {
        int tmp;
        cin >> tmp;
        for (auto iter : umset) {
            int sum = iter + tmp;
            if (arr.size() < k) {
                arr.push(sum);
            } else if (sum < arr.top()) {
                arr.pop();
                arr.push(sum);
            }
        }
    }

    cout << arr.top() << endl;

    return 0;
}