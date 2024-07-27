#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX_N 100000
//중간값을 기준으로 중간값보다 작은 값은 min, 큰 값은 max heap에 저장?

//min-h, max-h, median으로 구성
//홀수번째에서 median보다 작으면 min, 크면 max에 삽입
//짝수번째에서 median보다 작으면 min, 크면 max에 삽입
//숫자 더 많은곳 top->새로운 median, 해당 값 pop
//기존 median 새로운 median보다 크면 max, 작으면 min

void find_median(int arr[], int m){
    int median = arr[0];
    priority_queue<int> min_h;
    priority_queue<int,vector<int>,greater<int>> max_h;

    cout<<median<<" ";

    for(int i=1; i<m; ++i){
        if(arr[i]>= median){
            max_h.push(arr[i]);
        }
        else{
            min_h.push(arr[i]);
        }

        if(max_h.size()>min_h.size()+1){
            min_h.push(median);
            median = max_h.top();
            max_h.pop();
        }
        else if(max_h.size()<min_h.size()){
            max_h.push(median);
            median = min_h.top();
            min_h.pop();
        }
        if(i%2 == 0){ //홀수
            cout<<median<<" ";
        }
    }
}


int main() {
    int t;
    cin>>t;

    for(int i=0; i<t; ++i){
        int m;
        cin>>m;

        int arr[MAX_N];

        for(int j=0; j<m; ++j){
            cin>>arr[j];
        }

        find_median(arr, m);
        cout<<endl;

    }
    return 0;
}