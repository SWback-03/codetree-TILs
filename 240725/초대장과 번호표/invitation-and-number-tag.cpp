#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

#define max_n 100001
#define max_g 250001

int N, G;
//각 그룹 내 초대장 받지 않은 사람 저장, size가 1일 경우 그사람도 초대장 받음
unordered_set<int> set[max_g];
//각 사람이 속한 그룹 저장, v[1] 순회하여 해당 set에서 해당 사람 제거
vector<int> v[max_n];
//사람 한명 제거할 때 마다 count++
int count = 0;

//해당 사람 속한 그룹에서 제거
queue<int> del(queue<int> q){
    queue<int> result_q;
    while(!q.empty()){
        for(int i=1; i<=G; ++i){
            if(set[i].find(q.front()) != set[i].end()){
                set[i].erase(q.front());
            }
            // if(set[i].size() == 1){
            //     auto iter = set[i].begin();
            //     result_q.push(*iter);
            // }
        }
        q.pop();
        count++;
    }
    for(int i=1; i<=G; ++i){
        if(set[i].size() == 1){
            auto iter = set[i].begin();
            result_q.push(*iter);
        }
    }

    return result_q;
}

int main() {
    cin>>N>>G;

    queue<int> q;
    q.push(1);

    for(int i=1; i<=G; ++i){
        int n;
        cin>>n;
        for(int j=0; j<n; ++j){
            int temp;
            cin>>temp;
            //해당 그룹에 속한 사람 저장
            set[i].insert(temp);
            //해당 사람이 속한 그룹들 저장
            v[temp].push_back(i);
        }
    }

    while(!q.empty()){
        q = del(q);
    }

    cout<<count;

    

    return 0;
}