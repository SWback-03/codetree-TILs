#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//뒤에서부터 정렬된 부분 확인
//해당 정렬된 부분에서 가장 가까운 작은수 바로 뒤에 삽입

int N;

//이미 오름차순인지 체크하는 함수
int check(vector<int> v){
    for(int i=N-1; i>0; --i){
        if(v[i-1]<v[i])
            continue;
        else
            return i;
    }
    return 0; //전체가 오름차순
}

//해당 수보다 작은 가까운 수 탐색 함수
int find(vector<int> v, int start){
    //start~end 사이 값 중에서 탐색
    int min = 0;
    int pos = -1;
    for(int i = start; i<N; ++i){
        if(v[i]<v[0] && v[i]>min){
            min = v[i];
            pos = i;
        }
    }
    //cout<<"start: "<<start<<"/  ";
    return pos; //가까운 수 위치 저장
    // -1 이 출력일 때 맨 앞자리 수보다 작은 수가 없다는 것을 뜻하므로
    // start-1에 insert
}


vector<int> run(vector<int> v, int pos, int start){
    //0~pos까지 숫자를 pos~끝 숫자 사이에 삽입함
    //v[0]과 오름차순 숫자 내 해당 수보다 제일 가까운 작은 수 뒤에 삽입
    int count = 0;

    //cout<<"pos: "<<pos<<"/  ";
    if(pos>=0){
        v.insert(v.begin()+pos+1,v[0]);
        v.erase(v.begin());
    }
    else if(pos<0){
        v.insert(v.begin()+start,v[0]);
        v.erase(v.begin());
    }

    // for(int tmp : v){
    //     cout<<tmp<<" ";
    // }
    // cout<<endl;

    // if(check(v) == 0){
    //     return count;
    // }
    
    return v;
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
    while(1){
        if(check(v) == 0){
            cout<<count;
            return 0;
        }
        else{
            int start = check(v);
            //cout<<"start: "<<start<<"/  ";
            int pos = find(v,start);

            v = run(v,pos,start);
            count++;
        }
    }

    return 0;
}

// 15
// 45 1 6 36 43 24 7 58 56 42 2 8 10 12 13