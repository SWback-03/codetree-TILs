#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int max_int = 0;

void recursive(int a, int b, int c, int cnt) {
    if ((a == b) || (b == c) || (a == c)||(b==a+1&&c==b+1)) {
        if (cnt >= max_int) max_int = cnt;
        return;
    }

    //왼쪽꺼 이동
    recursive(b, c-1, c, cnt + 1);
    //오른쪽꺼 이동
    recursive(a, a+1, b, cnt + 1);


}

int solve(int a, int b, int c){
    int max_value = max(b-a,c-b);
    return (max_value+1)/2+1;
}

int main() {
    // 여기에 코드를 작성해주세요.


    int x1, x2, x3;
    cin >> x1 >> x2 >> x3;
    int cnt = 0;
    max_int = solve(x1, x2, x3);
    cout << max(x2-x1,x3-x2)-1;
    return 0;
}