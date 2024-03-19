#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.

    int arr[100];

    int n, m, cnt = 0;
    cin>>n>>m;

    int flag = -300;
    for(int i=0; i<n; ++i){
        cin>>arr[i];
        if(arr[i]==1 && i>flag+m){
            flag = i+m;
            cnt++;
        }
    }

    cout<<cnt;
    return 0;
}