#include <iostream>
#include <cstdlib>

using namespace std;

int max_int = 0;

void recursive(int a, int b, int c, int cnt) {
    if ((a == b) || (b == c) || (a == c)||(b==a+1&&c==b+1)) {
        if (cnt >= max_int) max_int = cnt;
        return;
    }
    //왼쪽꺼 이동
    //recursive(b, (b + c) / 2, c, cnt + 1);
    //오른쪽꺼 이동
    //recursive(a, (a + b) / 2, b, cnt + 1);

    for(int i=b+1; i<c; ++i){
        recursive(b, i, c, cnt + 1);
    }
    for(int i=a+1; i<b; ++i){
        recursive(a, i, b, cnt + 1);
    }

}

int main() {
    // 여기에 코드를 작성해주세요.


    int x1, x2, x3;
    cin >> x1 >> x2 >> x3;
    int cnt = 0;
    recursive(x1, x2, x3, cnt);
    cout << max_int;
    return 0;
}