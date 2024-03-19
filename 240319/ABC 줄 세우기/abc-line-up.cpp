#include <iostream>

using namespace std;

int arr[26] = { 0, };

void swap(int* a, int* b) {
    int* tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int main() {

    // 여기에 코드를 작성해주세요.
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char input;
        cin >> input;
        arr[i] = (int)(input - 'A');
    }

    //swap(arr[0], arr[1]);

    int order;
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[j] == i) {

                order = j;
                break;
            }//j번째 자리 i존재
        }
        while (arr[i] != i) {
            if (order > i) {
                for (int k = order; k > i; --k) {
                    swap(arr[k], arr[k - 1]);
                    cnt++;
                }
            }
            else {
                for (int k = order; k < i; ++k) {
                    swap(arr[k], arr[k + 1]);
                    cnt++;
                }
            }

        }
    }
    cout << cnt << "\n";

    return 0;
}