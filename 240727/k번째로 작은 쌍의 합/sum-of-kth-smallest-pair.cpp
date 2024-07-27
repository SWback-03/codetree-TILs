#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

#define MAX_N 100000
#define MAX_M 100000

int n, m, k;

priority_queue<int> arr;
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
            int sum = iter+tmp;
            if(arr.size()==k){
                if(sum<arr.top()){
                    arr.pop();
                    arr.push(sum);
                }
            }
            else{
                arr.push(sum);
            }
        }
    }

    // while(!arr.empty()){
    //     cout<<arr.top()<<" ";
    //     arr.pop();
    // }
    cout<<arr.top();

    return 0;
}