#include <iostream>
#include <string>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a;
    cin>>a;
    if(a%2==0){
        a=a/2;
    }
    if(a%2==1){
        a=(a+1)/2;
    }
    cout<<a;
    return 0;
}