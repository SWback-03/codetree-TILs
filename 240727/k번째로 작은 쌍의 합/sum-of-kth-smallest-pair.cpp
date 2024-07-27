#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

#define MAX_N 100000
#define MAX_M 100000

int n, m, k;

priority_queue<int,vector<int>,greater<int>> arr_n;
priority_queue<int> arr_m;
unordered_multiset<int> umset;

int main() {
    // 여기에 코드를 작성해주세요.

    cin>>n>>m>>k;

    for(int i=0; i<n; ++i){
        int tmp;
        cin>>tmp;
        umset.insert(tmp);
    }

    for(int i=0; i<m; ++i){
        int tmp;
        cin>>tmp;
        for(auto iter : umset){
            arr_n.push(iter + tmp);
        }
    }

    for(int i=0; i<k-1; ++i){
        
        arr_n.pop();
        // cout<<arr_n.top()<<" ";
        
    }

    // for(int i=0; i<n*m; ++i){
    //     cout<<arr_n.top()<<" ";
    //     arr_n.pop();
    // }

    cout<<arr_n.top();

    return 0;
}