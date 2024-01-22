#include <iostream>
#include <string>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int m;
    cin>>m;
    if(m/3==1){
        cout<<"Spring";
    }
    else if(m/3==2){
        cout<<"Summer";
    }
    else if(m/3==3){
        cout<<"Fall";
    }
    else{
        cout<<"Winter";
    }
    return 0;
}