#include <iostream>
#include <unordered_map>
using namespace std;

#define max_n 5000

int arr[4][max_n] = {0};

unordered_map<int,int> map;
int n;

int main() {
    // 여기에 코드를 작성해주세요.

    cin>>n;

    for(int i=0; i<4; ++i){
        for(int j=0; j<n; ++j){
            int tmp;
            cin>>tmp;
            arr[i][j] = tmp;
        }
    }
    for(int i =0; i<n; ++i){
        for(int j=0; j<n; ++j){
            map[arr[0][i]+arr[1][j]]++;
        }
    }

    int count = 0;

    for(int i =0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map.find(-(arr[2][i]+arr[3][j])) != map.end()){
                count += map[-(arr[2][i]+arr[3][j])];
            }
        }
    }

    cout<<count;
    
    return 0;
}