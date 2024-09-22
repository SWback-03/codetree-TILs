#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 21

using namespace std;

int n,m,k;
int map[MAX_N][MAX_N];

int ball_dy[4] = {0,-1,0,1};
int ball_dx[4] = {1,0,-1,0};

void print_map(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    return;
}

pair<int,int> find_ball(int i, int ball_dir, int ball_sy, int ball_sx){
    if(ball_dir == 0){
        ball_sy = i%n;
        ball_sx = 0;
    }
    else if(ball_dir == 1){
        ball_sy = n-1;
        ball_sx = i%n;
    }
    else if(ball_dir == 2){
        ball_sy = n-i%n-1;
        ball_sx = n-1;
    }
    else{
        ball_sy = 0;
        ball_sx = n-i%n-1;
    }

    // cout<<ball_sy<<","<<ball_sx<<","<<ball_dir<<endl;

    return make_pair(ball_sy, ball_sx);
}

int bfs(int input_y, int input_x){
    queue<pair<int,int>> q;
    q.push(make_pair(input_y, input_x));
    int visited[MAX_N][MAX_N] = {0,};
    visited[input_y][input_x] = 1;

    int head_y, head_x, tail_y, tail_x;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        if(map[y][x] == 1){
            head_y = y, head_x = x;
        }

        if(map[y][x] == 3){
            tail_y = y, tail_x = x;
        }

        for(int i=0; i<4; ++i){
            int ny = y + ball_dy[i];
            int nx = x + ball_dx[i];

            if(ny<0 || nx<0 || ny >= n || nx >= n) continue;
            if(visited[ny][nx]>0 || map[ny][nx] == 4 || map[ny][nx] == 0) continue;

            q.push(make_pair(ny,nx));
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
    int dist = visited[head_y][head_x];
    // print_map();

    map[head_y][head_x] = 3;
    map[tail_y][tail_x] = 1;

    // cout<<"head:"<<head_y<<","<<head_x<<endl;

    // for(int i=0; i<n; ++i){
    //     for(int j=0; j<n; ++j){
    //         cout<<visited[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;

    // print_map();

    return dist;
}

void move_person(){
    //tmp_map 생성 & 복제
    int tmp_map[MAX_N][MAX_N] = {0,};
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            tmp_map[i][j] = map[i][j];
        }
    }

    
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            vector<pair<int,int>> count[5];

            if(map[i][j] == 1){
                for(int l=0; l<4; ++l){
                    int ni = i + ball_dy[l];
                    int nj = j + ball_dx[l];

                    if(ni<0 || nj <0 || ni>=n || nj>=n) continue;

                    for(int p=0; p<5; ++p){
                        if(map[ni][nj] == p){
                            count[p].push_back(make_pair(ni,nj));
                            break;
                        }
                    }
                }
                if(count[4].size() == 1 && count[2].size() == 1){
                    tmp_map[count[4][0].first][count[4][0].second] = 1;
                    tmp_map[i][j] = 2;
                }
                else if(count[3].size() == 1 && count[2].size() == 1){
                    tmp_map[count[3][0].first][count[3][0].second] = 1;
                    tmp_map[i][j] = 2;
                }
            }

            else if(map[i][j] == 3){
                for(int l=0; l<4; ++l){
                    int ni = i + ball_dy[l];
                    int nj = j + ball_dx[l];

                    if(ni<0 || nj <0 || ni>=n || nj>=n) continue;

                    if(map[ni][nj] == 2){
                        tmp_map[ni][nj] = 3;
                        if(tmp_map[i][j] == 3) tmp_map[i][j] = 4;
                    }
                }
            }
        }
    }

    //tmp_map 재복제
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            map[i][j] = tmp_map[i][j];
        }
    }
}

void run(){

    // print_map();

    int ball_sy = 0;
    int ball_sx = 0;
    int result = 0;

    for(int i=0; i<k; ++i){
        move_person();

        int ball_dir = (i / n) % 4;
        int dist = 0;

        pair<int,int> tmp_pair = find_ball(i, ball_dir, ball_sy, ball_sx);
        ball_sy = tmp_pair.first;
        ball_sx = tmp_pair.second;

        // cout<<ball_sy<<","<<ball_sx<<endl;
        // print_map();

        // int ball_dir = (i / n) % 4;
        // int dist = 0;

        int ball_y = ball_sy;
        int ball_x = ball_sx;

        for(int j=0; j<n; ++j){
            //충돌
            if(map[ball_y][ball_x]>=1 && map[ball_y][ball_x]<=3){
                // cout<<"run:"<<ball_y<<","<<ball_x<<endl;

                dist = bfs(ball_y, ball_x);
                // cout<<"dist:"<<dist<<endl;
                break;
            }

            ball_y += ball_dy[ball_dir];
            ball_x += ball_dx[ball_dir];
        }

        // pair<int,int> tmp_pair = find_ball(i, ball_dir, ball_sy, ball_sx);
        // ball_sy = tmp_pair.first;
        // ball_sx = tmp_pair.second;

        result += (dist*dist);
    }

    cout<<result;

    return;
}

int main() {

    cin>>n>>m>>k;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>map[i][j];
        }
    }

    run();

    return 0;
}