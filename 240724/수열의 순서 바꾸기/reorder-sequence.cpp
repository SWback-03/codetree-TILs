#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//1 이상, N 이하 숫자 겹치지 않게 구성됨
//원소의 개수 N개인 수열 주어짐
//N = 3, ex) 1, 2, 7
//맨 앞 숫자 선택, 수열 중간에 집어넣음
//오름차순 정렬
//맨 뒤에서 해당 숫자보다 큰 숫자 앞에 배치, 그리고 작은 숫자 만나기 전에 배치
//해당 숫자보다 작은 숫자가 없다면 

//2, 1, 3, 4
//2 1 4 3 - 1 4 2 3 - 4 1 2 3 - 1 2 3 4
//2 1 4 3 - 1 2 4 3 - 2 4 1 3 - 4 1 2 3 - 1 2 3 4
//2 1 4 3 5 - 1 4 2 3 5 - 4 1 2 3 5 - 1 2 3 4 5
//3 1 9 4 8 - 1 9 3 4 8 - 9 1 3 4 8 - 1 3 4 8 9
//3 1 2 - 1 2 3

//큰수 중 가장 가까운 수 앞에 배치하기
//더 큰 수 없을 경우 맨 뒤 배치
//이미 오름차순인지 체크하기

int N;

//이미 오름차순인지 체크하는 함수
bool check(vector<int> v){
    for(int i=0; i<N-1; ++i){
        if(v[i]>v[i+1])
            return false;
    }
    return true;
}

int sort(vector<int> v){
    int count = 0;
    // for(int i =0; i<N; ++i){
    while(1){
        int first = v[0];
        int min = INT_MAX;
        int position = 0;
        for(int j=2; j<N; ++j){
            if(min > v[j] && v[j] > first){
                min = v[j];
                position = j;
            }
        }
        if(position == 0){
            v.push_back(v[0]);
            v.erase(v.begin());
            // cout<<"back ";
        }
        else{
            v.insert(v.begin()+position,v[0]);
            v.erase(v.begin());
        }
        count++;
        
        // for(int element : v){
        //     cout<<element<<" ";
        // }
        // cout<<endl;
        
        if(check(v)){
            return count;
        }
    }
    return -1;
}

int main() {
    cin>>N;

    vector<int> v;

    for(int i=0; i<N; ++i){
        int tmp;
        cin>>tmp;
        v.push_back(tmp);
    }

    int count = 0;

    if(!check(v)){
        count = sort(v);
    }

    cout<<count;

    return 0;
}