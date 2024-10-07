#include <iostream>
#include <queue>

#define MAX_N 22
using namespace std;

int dice_map[3][3] = {{0,5,1},{4,6,3},{0,2,0}};

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

int map[MAX_N][MAX_N] = {0,};
int n, m, curr_y = 0, curr_x = 0, total = 0;

int dfs(){
    queue<pair<int,int>> tmp_q;
    bool visited[MAX_N][MAX_N] = {false,};

    tmp_q.push(make_pair(curr_y,curr_x));
    visited[curr_y][curr_x] = true;
    int count = 1;

    while(!tmp_q.empty()){
        int y = tmp_q.front().first;
        int x = tmp_q.front().second;
        tmp_q.pop();

        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny<0 || nx<0 || ny>=n || nx>=n || visited[ny][nx] || map[ny][nx]!=map[curr_y][curr_x]) continue;

            tmp_q.push(make_pair(ny,nx));
            visited[ny][nx] = true;
            count++;

        }
    }
    return count;
}

int find_bottom(int bottom, int dir){
    int index;
    int next_bottom;

    if(dir == 0){
        int tmp_arr[3];
        for(int i=0; i<3; ++i){
            int tmp_index = i-1;
            if(tmp_index < 0){
                tmp_arr[0] = dice_map[0][2];
            }
            else{
                tmp_arr[i] = dice_map[tmp_index][1];
            }
        }
        dice_map[0][2] = dice_map[2][1];
        for(int i=0; i<3; ++i){
            dice_map[i][1] = tmp_arr[i];
        }
    }
    else if(dir == 1){
        int tmp_arr[3];
        for(int i=0; i<3; ++i){
            int tmp_index = i+1;
            if(tmp_index >= 3){
                tmp_arr[2] = dice_map[0][2];
            }
            else{
                tmp_arr[i] = dice_map[1][tmp_index];
            }
        }
        dice_map[0][2] = dice_map[1][0];
        for(int i=0; i<3; ++i){
            dice_map[1][i] = tmp_arr[i];
        }
    }
    else if(dir == 2){
        int tmp_arr[3];
        for(int i=0; i<3; ++i){
            int tmp_index = i+1;
            if(tmp_index >= 3){
                tmp_arr[2] = dice_map[0][2];
            }
            else{
                tmp_arr[i] = dice_map[tmp_index][1];
            }
        }
        dice_map[0][2] = dice_map[0][1];
        for(int i=0; i<3; ++i){
            dice_map[i][1] = tmp_arr[i];
        }
    }
    else{
        int tmp_arr[3];
        for(int i=0; i<3; ++i){
            int tmp_index = i-1;
            if(tmp_index < 0){
                tmp_arr[0] = dice_map[0][2];
            }
            else{
                tmp_arr[i] = dice_map[1][tmp_index];
            }
        }
        dice_map[0][2] = dice_map[1][2];
        for(int i=0; i<3; ++i){
            dice_map[1][i] = tmp_arr[i];
        }
    }

    return dice_map[1][1];
}

pair<int,int> find_dir(int curr_bottom, int dir){

    if(curr_bottom < map[curr_y][curr_x]){
        dir--;
        if(dir<0) dir = 3;
    }
    else if(curr_bottom > map[curr_y][curr_x]){
        dir = (dir+1)%4;
    }

    return make_pair(curr_bottom,dir);
}

pair<int,int> move(int curr_bottom, int dir){

    int ny = curr_y + dy[dir];
    int nx = curr_x + dx[dir];

    if(ny<0 || nx<0 || ny>=n || nx>=n){
        dir = (dir+2)%4;
        ny = curr_y + dy[dir];
        nx = curr_x + dx[dir];
    }

    curr_y = ny, curr_x = nx;

    curr_bottom = find_bottom(curr_bottom, dir);

    return find_dir(curr_bottom, dir);
}

pair<int,int> run(int curr_bottom, int dir){

    pair<int,int> tmp = move(curr_bottom,dir);
    curr_bottom = tmp.first;
    dir = tmp.second;

    total += map[curr_y][curr_x]*dfs();

    return make_pair(curr_bottom,dir);
}


int main() {
    cin>>n>>m;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>map[i][j];
        }
    }

    int curr_bottom = 6;
    int dir = 1;

    for(int i=0; i<m; ++i){
        pair<int,int> tmp = run(curr_bottom, dir);
        curr_bottom = tmp.first;
        dir = tmp.second;
    }

    cout<<total;
    

    return 0;
}