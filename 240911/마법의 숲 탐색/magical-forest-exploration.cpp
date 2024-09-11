#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

#define MAX_R 73
#define MAX_C 70

using namespace std;

int R, C, K, result_val = 0;
vector<pair<int,int>> input_vec;
int map[MAX_R][MAX_C] = {0,};
bool visited[MAX_R][MAX_C] = {false,};

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

void clear_map(){
    for(int i=0; i<MAX_R; ++i){
        for(int j=0; j<MAX_C; ++j){
            map[i][j] = 0;
        }
    }
    return;
}

void clear_visited(){
    for(int i=0; i<MAX_R; ++i){
        for(int j=0; j<MAX_C; ++j){
            visited[i][j] = false;
        }
    }
    return;
}

void cout_visited(){
    for(int i=0; i<R+3; ++i){
        for(int j=0; j<C; ++j){
            cout<<visited[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}

//visited 확인 함수
int check_visited(){
    int max_height = 0;

    for(int i=0; i<MAX_R; ++i){
        for(int j=0; j<MAX_C; ++j){
            if(visited[i][j]){
                max_height = max(max_height, i);
            }
        }
    }

    // cout_visited();

    clear_visited();

    return max_height;
}

int bfs(int sy, int sx){
    int curr_state = 2;
    queue<pair<int,int>> q;
    q.push(make_pair(sy,sx));
    visited[sy][sx] = true;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        curr_state = map[y][x];
        q.pop();

        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny < 0 || nx < 0 || ny >= R+3 || nx >= C) continue;
            if(visited[ny][nx] == true || map[ny][nx] == 0) continue;
            if((curr_state == 2 && map[ny][nx] == 3) || (curr_state == 3 && map[ny][nx] == 3) ||(curr_state == 3 && map[ny][nx] == 1) || (curr_state == 1 && map[ny][nx] == 2)){
                q.push(make_pair(ny,nx));
                visited[ny][nx] = true;
            }
            else if((curr_state == 2 && map[ny][nx] == 1)) visited[ny][nx] = true;
        }
    }

    return check_visited();
}

bool check_outside(){
    for(int i=0; i<3; ++i){
        for(int j=0; j<C; ++j){
            if(map[i][j]>0) return false;
        }
    }
    return true;
}

bool check_state(string state, int y, int x){
    //하단 체크
    if(state == "down"){
        if(y+2 >= R+3 || map[y+2][x] > 0 || map[y+1][x-1] > 0 || map[y+1][x+1] > 0) return false;
        return true;
    }
    //좌측 체크
    else if(state == "left"){
        if(x-2 < 0 || map[y][x-2] > 0 || map[y-1][x-1] > 0 || map[y+1][x-1] > 0) return false;
        if(y+2 >= R+3 || map[y+1][x-2] > 0 || map[y][x-1] > 0 || map[y+2][x-1] > 0) return false;
        return true;
    }
    //우측 체크
    else if(state == "right"){
        if(x+2 >= C || map[y][x+2] > 0 || map[y-1][x+1] > 0 || map[y+1][x+1] > 0) return false;
        if(y+2 >= R+3 || map[y+1][x+2] > 0 || map[y][x+1] > 0 || map[y+2][x+1] > 0) return false;
        return true;
    }
    return true;
}

void cout_map(){
    for(int i=0; i<R+3; ++i){
        for(int j=0; j<C; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}

void draw_map(int y, int x, int dir){
    
    for(int i=0; i<4; ++i){
        int ny = y + dy[i];
        int nx = x + dx[i];
        map[ny][nx] = 1;
    }
    map[y][x] = 2;
    map[y+dy[dir]][x+dx[dir]] = 3;
    
    return;
}

void move_golem(int sy, int sx, int dir){

    while(1){
        if(!check_state("down",sy,sx)) break;
        sy++;
    }
    while(1){
        if(!check_state("left",sy,sx)) break;
        sy++;
        sx--;
        dir = (dir-1)%4;
    }
    while(1){
        if(!check_state("right",sy,sx)) break;
        sy++;
        sx++;
        dir = (dir+1)%4;
    }

    draw_map(sy,sx,dir);

    if(!check_outside()){
        clear_map();
    }
    else{
        // cout<<"result: "<<bfs(sy,sx)<<endl;
        // cout<<bfs(sy,sx) - 2<<endl;
        result_val += (bfs(sy,sx) - 2);
    }

    // cout_map();

    return;
}

int main() {
    cin>>R>>C>>K;

    for(int i=0; i<K; ++i){
    // for(int i=0; i<1; ++i){
        int ci, di;
        cin>>ci>>di;
        ci--;
        input_vec.push_back(make_pair(ci, di));
        move_golem(0,ci,di);
    }

    cout<<result_val;

    return 0;
}