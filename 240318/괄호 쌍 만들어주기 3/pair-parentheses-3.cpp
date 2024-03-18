#include <iostream>
#include <string>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.

    int left_cnt = 0, total_cnt = 0;
    string A;
    cin>>A;
    for(int i=0; i<A.length(); ++i){
        if(A[i] == ')'){
            total_cnt += left_cnt;
        }
        else{
            left_cnt++;
        }
    }

    cout<<total_cnt;
    return 0;
}