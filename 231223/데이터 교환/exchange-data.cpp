#include <iostream>
#include <string>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int temp1;
    int a=5, b=6, c=7;
    temp1=b;
    b=a;
    int temp2 = c;
    c=temp1;
    int temp3 = a;
    a = temp2;
    cout<<a<<endl<<b<<endl<<c;
    return 0;
}