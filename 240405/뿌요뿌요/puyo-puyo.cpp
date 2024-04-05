#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int n;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
int map[102][102] = {0,};
int visited[102][102]= {0,};
int bomb[102][102]= {0,};
int bomb_temp[102][102]= {0,};

int bomb_cnt = 0;

stack<pair<int,int>> q;

int bfs(int sy, int sx){
    q.push({sy,sx});
    int val = map[sy][sx];
    int cnt = 1;
    
    
    while(!q.empty()){
        int y = q.top().first;
        int x = q.top().second;
        visited[y][x] = 1;
        bomb[y][x] = 1;
        q.pop();

        for(int i=0; i<4; ++i){
            int ny = y+dy[i];
            int nx = x+dx[i];
            if(map[ny][nx] > 0 && !visited[ny][nx] && map[ny][nx] == val){
                q.push({ny,nx});
                cnt++;
            }
        }
    }
    if(cnt<4){
        bomb[102][102] = bomb_temp[102][102]; //이전으로 되돌림
    }
    else {
        bomb_temp[102][102] = bomb[102][102]; //bomb 업데이트
        bomb_cnt++;
    }

    return cnt; //이어서 터진 폭탄 갯수
}

int main() {
    cin>>n;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            cin>>map[i][j];
        }
    }

    int max = 0;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(visited[i][j]==0) {
                int result = bfs(i,j);
                if(max<result) max = result;
            }
            
        }
    }

    int cnt = 0;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(bomb[i][j] == 1) cnt++;
            
        }
    }
    cout<<bomb_cnt<<" "<<max;

    return 0;
}