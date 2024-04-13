#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

int N,M,K;

int map[20][20] = {0,};
int point_map[20][20] = {0,};
int dy[4] = {0,-1,0,1};
int dx[4] = {1,0,-1,0};
int visited_move[20][20] = {0,};

//0, 머리 사람 찾기
queue<pair<int,int>> find_head(){
    queue<pair<int,int>> q;
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            if(map[i][j] == 1){
                q.push({i,j});
            }
        }
    }

    return q;
}

//1, 머리사람을 따라 이동
void move(int sy, int sx){//머리사람 좌표 제공, move 할때마다 visited 초기화 필수(main함수 내)
    queue<pair<int,int>> q;
    q.push({sy,sx});
    int flag = 0;

    for(int i=0; i<4; ++i){
        int ny = sy + dy[i];
        int nx = sx + dx[i];
        if(map[ny][nx] == 3){ //다 이어져있음
            flag = 1;

        }
        
    }

    for(int i=0; i<4; ++i){
        int ny = sy + dy[i];
        int nx = sx + dx[i];

        if(map[ny][nx]==4 || map[ny][nx]==3){
            visited_move[ny][nx] = 1;
            map[ny][nx] = 1;
            point_map[ny][nx] = point_map[sy][sx];
            map[sy][sx] = 4;
            point_map[sy][sx] = 0;
            break;
        }
        
    }//머리 이동 완료

    int final_y, final_x;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];

            if(visited_move[ny][nx] == 0 && (map[ny][nx]==2 || map[ny][nx]==3)){
                q.push({ny,nx});
                if(map[ny][nx]==2){
                    map[y][x] = 2;
                }
                else{
                    map[y][x] = 3;
                }
                point_map[y][x] = point_map[ny][nx];
                point_map[ny][nx] = 0;

                visited_move[y][x] = 1;
                map[ny][nx] = 4;
                break;
            }
        }
        final_y = y;
        final_x = x;
    }

    if(flag == 1){
        map[final_y][final_x] = 3;
    }


    return;
}

//2-0, k번째 찾기
int k_bfs(int sy, int sx){
    queue<pair<int,int>> q;
    int visited[20][20] = {0,};
    int path[20][20] = {0,};
    q.push({sy,sx});
    visited[sy][sx] = 1;

    if(map[sy][sx] == 1){
        return 1;
    }
    
    int flag = 0;
    if(map[sy][sx] == 3){
        for(int i=0; i<4; ++i){
            int ny = sy + dy[i];
            int nx = sx + dx[i];
            if(map[ny][nx] == 1){
                flag = 1;
            }
        }
    }

    if(flag == 1){
        //cout<<"flag on\n";
        for(int i=0; i<4; ++i){
            int ny = sy + dy[i];
            int nx = sx + dx[i];
            if(map[ny][nx] == 2){
                return k_bfs(ny,nx)+1;
            }
        }
    }

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(visited[ny][nx] == 0 && (map[ny][nx]>0 && map[ny][nx] != 4 && map[ny][nx] != 3)){
                q.push({ny,nx});
                path[ny][nx] = path[y][x] + 1;
                visited[ny][nx] = 1;
            }
            if(map[ny][nx] == 1){
                return path[ny][nx]+1;
            }
        }
    }

    
}

//3. 머리사람 꼬리사람 바꾸기
void change(int sy, int sx){
    queue<pair<int,int>> q;
    int visited[20][20] = {0,};
    q.push({sy,sx});
    visited[sy][sx] = 1;
    if(map[sy][sx] == 3){
        map[sy][sx] = 1;
    }
    else if(map[sy][sx] == 1){
        map[sy][sx] = 3;
    }



    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(visited[ny][nx] == 0 && (map[ny][nx]>0 && map[ny][nx] != 4)){
                q.push({ny,nx});
                visited[ny][nx] = 1;
                if(map[ny][nx] == 3){
                    map[ny][nx] = 1;
                }
                else if(map[ny][nx] == 1){
                    map[ny][nx] = 3;
                }
            }
        }
    }
}

//2. 공던지기

void ball(int round, int dir){
    if(dir == 0){
        int y = round;
        int x = 0;
        for(int i=0; i<N; ++i){
            if(map[y][x] == 1 || map[y][x] == 2 || map[y][x] == 3){
                point_map[y][x] += pow(k_bfs(y,x),2);
                change(y,x);
                break;
            }
            y += dy[dir];
            x += dx[dir];
        }
    }
    else if(dir == 1){
        int y = N-1;
        int x = round;
        for(int i=0; i<N; ++i){
            if(map[y][x] == 1 || map[y][x] == 2 || map[y][x] == 3){
                point_map[y][x] += pow(k_bfs(y,x),2);
                change(y,x);
                break;
            }
            y += dy[dir];
            x += dx[dir];
        }
    }
    else if(dir == 2){
        int y = N-1-round;
        int x = N-1;
        for(int i=0; i<N; ++i){
            if(map[y][x] == 1 || map[y][x] == 2 || map[y][x] == 3){
                point_map[y][x] += pow(k_bfs(y,x),2);
                change(y,x);
                break;
            }
            y += dy[dir];
            x += dx[dir];
        }
    }
    else if(dir == 3){
        int y = 0;
        int x = N-1-round;
        for(int i=0; i<N; ++i){
            if(map[y][x] == 1 || map[y][x] == 2 || map[y][x] == 3){
                point_map[y][x] += pow(k_bfs(y,x),2);
                change(y,x);
                break;
            }
            y += dy[dir];
            x += dx[dir];
        }
    }
    return;
}

int main() {

    cin>>N>>M>>K;

    for(int i= 0; i<N; ++i){
        for(int j= 0; j<N; ++j){
            cin>>map[i][j];
        }
    }

    
    for(int i=0; i<K; ++i){
        int input_round = i;
        int dir  = (input_round/N)%4;
        int round = input_round%N;

        //cout<<"round, dir: "<<round<<" "<<dir<<"\n";

        queue<pair<int,int>> tmp_q = find_head();
        while(!tmp_q.empty()){
            int y = tmp_q.front().first;
            int x = tmp_q.front().second;
            tmp_q.pop();
            
            memset(visited_move,0,sizeof(visited_move));

            move(y,x);

        }
        
        //if(i<4)
            ball(round,dir);

    }

    int total_point = 0;
    for(int i= 0; i<N; ++i){
        for(int j= 0; j<N; ++j){
            if(point_map[i][j]>0){
                total_point+=point_map[i][j];
            }
        }
    }

    cout<<total_point;

    // cout<<"\n";
    // for(int i= 0; i<N; ++i){
    //     for(int j= 0; j<N; ++j){
    //         cout<<point_map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    // for(int i= 0; i<N; ++i){
    //     for(int j= 0; j<N; ++j){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    return 0;
}