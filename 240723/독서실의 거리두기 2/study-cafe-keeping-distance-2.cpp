#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <climits>
using namespace std;

//좌석 갯수
int N;
vector<int> seat;

//1과 1사이 거리 구하는 함수
int find_lst_dist(vector<int> input){
    bool flag = false;
    int i=0;
    int min_val = INT_MAX;
    int mem = 0;

    for(int element : input){
        
        if(element == 1 && flag == false){
            flag = true;
            mem = i;
        }
        else if(element == 1 && flag == true){
            min_val = min(min_val, i-mem);
            mem = i;
        }
        ++i;
    }

    return min_val;
}

int main() {
    cin>>N;

    for(int i=0; i<N; ++i){
        char tmp;
        cin>>tmp;
        int tmp_int =(int)(tmp - '0');
        seat.push_back(tmp_int);
    }

    int max_val = 0;

    for(int i=0; i<N; ++i){
        if(seat[i] == 0){
            vector<int> input = seat;
            input[i] = 1;
            max_val = max(find_lst_dist(input),max_val);
            
        }
    }

    cout<<max_val;

    return 0;
}