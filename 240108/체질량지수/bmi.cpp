#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    double c, k;
    cin>>c>>k;
    double bmi = k/pow((c/100),2);
    cout<<(int)bmi<<endl;
    if(bmi>=25){
        cout<<"Obesity";
    }
    return 0;
}