#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

int N;
vector<int,int> v;

int cal_dist(int x1, int y1, int x2, int y2){
    return abs(x1-x2)+abs(y1-y2);
}


int main() {
    cin>>N;
    for(int i=0; i<N; ++i){
        int x, y;
        cin>>x>>y;
        v.push_back({x,y});
    }

    for(int i=1; i<N-1; ++i){
        int temp_x = v[v.begin()+i][0];
        int temp_y = v[v.begin()+i][1];
        v.erase(v.begin()+i);

        int dist = 0;
        for(int j=0; j<N-1; ++j){
            dist += 
        }

        v.insert(v.begin()+i,{temp_x,temp_y});
    }

    
    return 0;
}