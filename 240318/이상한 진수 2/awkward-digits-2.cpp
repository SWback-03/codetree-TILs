#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string a;
    cin>>a;
    int len = a.length();
    for(int i=0; i<len; ++i){
        if(a[i] == '0'){
            a[i] = '1';
            break;
        }
        else if(i == len-1){
            a[i] = '0';
        }
    }
    int output = stoi(a);
    
    int sum = 0;
    for(int i=0; i<len; ++i){
        sum += (output & 1)*pow(2,i);
        output /=10;
    }
    cout<<sum;


    return 0;
}