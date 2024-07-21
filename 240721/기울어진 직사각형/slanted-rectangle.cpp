#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int dy[4] = {-1,-1,1,1};
int dx[4] = {1,-1,-1,1};

int map[22][22] = {0,};

int n;

bool check(int y, int x){
    if(map[y][x] == 0)
        return false;
    else
        return true;
}

int cal(int y, int x, int k, int l){
    int move_num[4] = {k,l,k,l};

    int result = 0;

    for(int i = 0; i<4; ++i){
        for(int j = 0; j<move_num[i]; ++j){
            y += dy[i];
            x += dx[i];

            if(!check(y,x))
                return 0;
            
            else
                result += map[y][x];
        }
    }

    return result;
}


int main() {
    cin>>n;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            cin>>map[i][j];
        }
    }

    int result = 0;

    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            for(int k=1; k<n; ++k){
                for(int l=1; l<n; ++l){
                    result = max(result, cal(i,j,k,l));
                }
            }
        }
    }

    cout<<result;


    return 0;
}