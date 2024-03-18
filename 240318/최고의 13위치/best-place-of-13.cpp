#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;
    int arr[20][20];
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>arr[i][j];
        }
    }

    int max_num = 0;

    for(int i=0; i<n; ++i){
        
        for(int j=0; j<n-2; ++j){
            int cnt = 0;
            for(int k=0; k<3; ++k){
                if(arr[i][j+k]) cnt++;
            }
            if(cnt>=max_num) max_num = cnt;
        }
    }

    cout<<max_num;

    return 0;
}