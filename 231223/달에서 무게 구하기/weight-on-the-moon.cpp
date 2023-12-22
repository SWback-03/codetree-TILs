#include <iostream>
#include <string>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    cout<<fixed;

    double a=0.165000;
    int b=13;
    double c=a*b;

    cout.precision(6);
    cout<<b<<" * "<<a<<" = "<< c;
    

    return 0;
}