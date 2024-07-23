#include <iostream>
#include <cstring>
using namespace std;

//N: 개발자 수 2 ≤ N ≤ 100
//K: 악수 횟수 1 ≤ K ≤ 250 , 이 이후에는 안옮김
//P: 처음 전염병 걸린 개발자 번호 1 ≤ P ≤ N
//T: 악수 횟수 1 ≤ T ≤ 250
int N, K, P, T;

int programmer[101] = {0};

pair<int,int> log[251];

 
int main() {
    memset(log,0,sizeof(log));

    cin>>N>>K>>P>>T;

    for(int i=0; i<T; ++i){
        int t, x, y;
        cin>>t>>x>>y;
        log[t].first = x;
        log[t].second = y;
    }
    // cout<<"K: "<<K<<endl;

    programmer[P] = 1;

    int programmer_count[101];
    // memset(programmer_count,K,sizeof(programmer_count));
    fill(programmer_count,programmer_count+101,K);

    for(int i=1; i<=250; ++i){

        int first = log[i].first;
        int second = log[i].second;

        if(first != 0 && second != 0){

            // cout<<programmer_count[first]<<" "<<programmer_count[second]<<endl;

            if(programmer[first] == 1 && programmer[second] == 1 && (programmer_count[first] > 0 || programmer_count[second] > 0)){
                programmer_count[first]--;
                programmer_count[second]--;
                programmer[first] = 1;
                programmer[second] = 1;
            }
            else if(programmer[first] == 0 && programmer[second] == 1 && (programmer_count[second] > 0)){
                programmer_count[second]--;
                programmer[first] = 1;
                programmer[second] = 1;
            }
            else if(programmer[first] == 1 && programmer[second] == 0 && (programmer_count[first] > 0)){
                programmer_count[first]--;
                programmer[first] = 1;
                programmer[second] = 1;
            }
            else{
                continue;
            }
        }
    }

    for(int i=1; i<=N; ++i){
        cout<<programmer[i];
    }

    return 0;
}