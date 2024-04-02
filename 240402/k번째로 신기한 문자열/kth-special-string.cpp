#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int n,K;
string T;
string arr[100];

int main() {
    cin>>n>>K>>T;
    int sizeT = T.length();
    int cnt = 0;
    for(int i=0; i<n; ++i){
        string tmp;
        cin>>tmp;
        for(int k=0; k<sizeT; ++k){
            if(T[k]!=tmp[k]) break;
            if(k==sizeT-1){
                arr[cnt] = tmp;
                cnt++;
            }
        }
    }
    sort(arr,arr+cnt);
    cout<<arr[K-1];


    return 0;
}