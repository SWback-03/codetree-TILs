#include <iostream>
#include <cmath>
using namespace std;

int main() {
    //첫번째 줄에 a 주어짐
    int a;
    cin>>a;

    int real = a;
    int tmp = a;
    //자릿수 찾는 코드
    int len = 0;
    while(tmp!=0){
        tmp = tmp/10;
        len += 1;
    }

    for(int i=1; i<=len; ++i){
        int curr = a/static_cast<int>(pow(10,len-i));
        a = a%static_cast<int>(pow(10,len-i));
        if(curr == 0){
            real += static_cast<int>(pow(10,len-i));
            break;
        }
        if(i == len){
            real -= 1;
        }
    }   

    //cout<< real << endl;

    int result = 0;
    for(int i=0; i<len; ++i){
        int curr = real%10;
        real = real/10;
        if(curr == 0)
            continue;
        result += static_cast<int>(pow(2,i));
    }

    cout<<result;
    
    return 0;
}