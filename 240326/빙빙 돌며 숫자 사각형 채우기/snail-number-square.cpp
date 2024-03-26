#include <iostream>
#include<cstring>

using namespace std;

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int map[102][102] = {0,};

// void recursive(){
//     if(map[i][j]!=0)
// }
int main() {
    // 여기에 코드를 작성해주세요.

    int n, m;
    cin>>n>>m;
    int snail = 1;
    memset(map,-1,sizeof(map));
    
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            map[i][j]=0;
        }
    }
    
    int y=1, x=1;
    int prev_y=y, prev_x=x;
    int index = 0;
    int curr = 1;
    map[1][1] = 1;
    for(int i=2; i<=n*m; ++i){
        int ny = y+dy[index%4];
        int nx = x+dx[index%4];
        if(map[ny][nx]!=0){
            //회전
            index++;
            ny = y+dy[index%4];
            nx = x+dx[index%4];
        }
        map[ny][nx] = i;
        y=ny;
        x=nx;
    }

    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }

    return 0;
}