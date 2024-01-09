#include <iostream>
#include <string>
using namespace std;


int main() {
    // 여기에 코드를 작성해주세요.
    int a,b;
    cin>>a>>b;
    int max = a>=b ? a : b;
    cout<<max;
    return 0;
}