#include <iostream>
#include <string>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    char a[10];
    for(int i=0; i<10; i++){
        cin>>a[9-i];
    }
    for(int i=0; i<10; i++){
        cout<<a[i];
    }
    return 0;
}