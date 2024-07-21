#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int n, m;
int map[5][5];

// 박스 값 더하기
int add_box(int y_1, int x_1, int y_2, int x_2) {
    int result = 0;
    for (int i = y_1; i <= y_2; ++i) {
        for (int j = x_1; j <= x_2; ++j) {
            result += map[i][j];
        }
    }
    return result;
}

// 겹치는 박스인지 확인
bool check(int y1_1, int x1_1, int y1_2, int x1_2, int y2_1, int x2_1, int y2_2, int x2_2) {
    if (y2_1 > y1_2 || x2_1 > x1_2) {
        return true; // 겹치지 않음
    }
    return false; // 겹침
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }

    int max_val = INT_MIN;

    // 첫번째 박스
    for (int y1_1 = 0; y1_1 < n; ++y1_1) {
        for (int x1_1 = 0; x1_1 < m; ++x1_1) {
            for (int y1_2 = y1_1; y1_2 < n; ++y1_2) {
                for (int x1_2 = x1_1; x1_2 < m; ++x1_2) {
                    int box1_sum = add_box(y1_1, x1_1, y1_2, x1_2);

                    // 두번째 박스
                    for (int y2_1 = 0; y2_1 < n; ++y2_1) {
                        for (int x2_1 = 0; x2_1 < m; ++x2_1) {
                            for (int y2_2 = y2_1; y2_2 < n; ++y2_2) {
                                for (int x2_2 = x2_1; x2_2 < m; ++x2_2) {
                                    if (check(y1_1, x1_1, y1_2, x1_2, y2_1, x2_1, y2_2, x2_2)) {
                                        int box2_sum = add_box(y2_1, x2_1, y2_2, x2_2);
                                        max_val = max(max_val, box1_sum + box2_sum);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << max_val;

    return 0;
}