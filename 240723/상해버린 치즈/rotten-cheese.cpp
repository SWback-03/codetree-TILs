#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, D, S;
//N: 사람 수
//M: 치즈 수
//D: 치즈 먹은 기록 수
//S: 아픈 기록 수

vector<pair<int,int>> v_person[51];

//아프기 전에 먹은 치즈 종류 저장
vector<int> find_bad_cheese(int person, int time){
    vector<int> bad_cheese;
    for(pair<int,int> element : v_person[person]){
        if(element.second<time){
            bad_cheese.push_back(element.first);
        }
    }
    return bad_cheese;
}

//교집합 구하기
vector<int> find_same_cheese(vector<int> a, vector<int> b){
    int arr[51] = {0,};
    for(int element : a){
        arr[element]=1;
    }
    vector<int> result;
    for(int element : b){
        if(arr[element]==1){
            result.push_back(element);
        }
    }

    return result;
}

//교집합의 각 원소당 가능한 최대 수 구하기
int find_max(vector<int> a){
    int max_num = 0;
    for(int element : a){
        int num = 0;
        for(int i=1; i<=N; ++i){
            for(pair<int,int> element_p : v_person[i]){
                if(element_p.first == element){
                    num++;
                    break;
                }
            }
        }
        max_num = max(num, max_num);
    }
    return max_num;
}


int main() {
    cin>>N>>M>>D>>S;
    for(int i=0; i<D; ++i){
        int p, m, t;
        cin>>p>>m>>t;
        v_person[p].push_back({m,t});
    }

    vector<int> first_v;
    for(int i=1; i<=M; ++i){
        first_v.push_back(i);
    }

    for(int i=0; i<S; ++i){
        int p, t;
        cin>>p>>t;
        vector<int> v = find_bad_cheese(p,t);
        first_v = find_same_cheese(first_v, v);
    }

    int result = find_max(first_v);

    cout<<result;

    return 0;
}