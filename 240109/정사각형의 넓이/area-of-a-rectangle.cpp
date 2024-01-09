#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;
    cout<<pow(n,2);
    if(n<5){
        cout<<endl<<"tiny";
    }
    return 0;
}