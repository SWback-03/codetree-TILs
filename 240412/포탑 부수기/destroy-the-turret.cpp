#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M, K;

int map[10][10] = {0,};
int recent_map[10][10] = {0,};

//포탑 struct
//공격력 정보==체력
//위치정보
//최근공격시점
struct tower{
    int first;
    int second;
    int attack;
    int recent = 0;
};

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

struct location{
    int first;
    int second;
};


//1 약한 포탑 선정
location select_attacker(int K){
    int min_attack = 10000;
    int y = 0; //이전값
    int x = 0; //이전값

    for(int i=0; i<N; i++){
        for(int j=0; j<M; ++j){
            if(map[i][j] == 0) continue;
            if(min_attack>map[i][j]){
                min_attack = map[i][j];
                y = i;
                x = j;
            }
            else if(min_attack == map[i][j]){
                if(recent_map[i][j]>recent_map[y][x]){ //1-2,가장 최근 포탑 찾기
                    y = i;
                    x = j;
                }
                else if(recent_map[i][j] == recent_map[y][x]){//1-3,행과 열의 합이 가장 큰 포탑 찾기
                    if(i+j > y+x){
                        y = i;
                        x = j;
                    }
                    else if(i+j < y+x){
                        continue;
                    }
                    else if(i+j == y+x){
                        if(j>x){//1-4 열 값이 가장 큰 포탑찾기
                            y = i;
                            x = j;
                        }
                        else if(j<x){
                            continue;
                        }
                        else{
                            cout<<"error\n";
                        }
                    }
                }
            }
        }
    }

    //cout<<"y,x: "<<y<<" "<<x<<"\n";
    recent_map[y][x] = K+1;
    return {y,x};//가장 약한 포탑 좌표 return
}

//2 가장 강한 포탑 선정
location select_strong(){
    int max_attack = 0;
    int y = 0; //이전값
    int x = 0; //이전값




    for(int i=0; i<N; i++){
        for(int j=0; j<M; ++j){
            if(map[i][j] == 0) continue;
            if(max_attack<map[i][j]){
                max_attack = map[i][j];
                y = i;
                x = j;
            }
            else if(max_attack == map[i][j]){
                if(recent_map[i][j]<recent_map[y][x]){ //1-2,가장 오래된 포탑 찾기
                    y = i;
                    x = j;
                }
                else if(recent_map[i][j] == recent_map[y][x]){//1-3,행과 열의 합이 가장 작은 포탑 찾기
                    if(i+j < y+x){
                        y = i;
                        x = j;
                    }
                    else if(i+j > y+x){
                        continue;
                    }
                    else if(i+j == y+x){
                        if(j<x){//1-4 열 값이 가장 작은 포탑찾기
                            y = i;
                            x = j;
                        }
                        else if(j>x){
                            continue;
                        }
                        else{
                            cout<<"error\n";
                        }
                    }
                }
            }
        }
    }










    return {y,x};
}

int no_attack[10][10] = {0,};

//2-1
int bfs(int sy, int sx, int de_y, int de_x){ //레이저공격 실행
    
    memset(no_attack, 0, sizeof(no_attack));
    int temp_map[10][10] = {0,};
    for(int j=0; j<N; ++j){
        for(int k=0; k<M; ++k){
            temp_map[j][k] = map[j][k];
        }
    }
    queue<pair<int,int>> q;
    int visited_bfs[10][10] = {0,};
    location path[10][10] = {0,};
    int visited_path[10][10] = {0,};
    int damage = map[sy][sx] + N + M;
    int half_damage = damage/2;
    map[sy][sx] += (N + M);
    no_attack[sy][sx] = 1;

    q.push({sy,sx});
    visited_bfs[sy][sx] = 1;
    path[sy][sx] = {sy,sx};
    visited_path[sy][sx] = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];

            if(ny < 0){ //맵 밖으로 나갈 때
                ny = N-1;
            }
            else if(nx < 0){
                nx = M-1;
            }
            else if(ny >= N){
                ny = 0;
            }
            else if(nx >= M){
                nx = 0;
            }//맵 밖으로 나갈 때

            if(visited_bfs[ny][nx] == 0 && map[ny][nx] > 0){
                visited_bfs[ny][nx] = 1;
                q.push({ny,nx});
                if(visited_path[ny][nx] == 0){
                    path[ny][nx] = {y,x};
                    visited_path[ny][nx] = 1;
                }
            }

            if(ny == de_y && nx == de_x){
                //cout<<"bfs worked\n";
                map[ny][nx] -= damage;
                if(map[ny][nx]<0){
                    map[ny][nx]=0;
                }

                while(1){
                    y = ny;
                    x = nx;
                    ny = path[y][x].first;
                    nx = path[y][x].second;

                    if(ny == sy && nx == sx){
                        //공격과 무관한 포탑 찾기
                        for(int j=0; j<N; ++j){
                            for(int k=0; k<M; ++k){
                                if(map[j][k]!=temp_map[j][k]){
                                    no_attack[j][k] = 1;
                                }
                            }
                        }


                        return 0; //0반환시 레이저 공격 실행 완료
                    }

                    map[ny][nx] -= half_damage;
                    if(map[ny][nx]<0){
                        map[ny][nx]=0;
                    }

                    
                }
                
            }
        }

    }
    map[sy][sx] -= (N + M);
    return 1; //1 반환시 포탄공격 실행
}

//2-2
int bomb_dy[8] = {-1,1,0,0,-1,-1,1,1};
int bomb_dx[8] = {0,0,-1,1,-1,1,-1,1};
void bomb(int sy, int sx, int de_y, int de_x){ //포탄공격 실행
    //cout<<"bomb worked\n";
    memset(no_attack, 0, sizeof(no_attack));
    int temp_map[10][10] = {0,};
    for(int j=0; j<N; ++j){
        for(int k=0; k<M; ++k){
            temp_map[j][k] = map[j][k];
        }
    }
    no_attack[sy][sx] = 1;

    int damage = map[sy][sx] + N + M;
    int half_damage = damage/2;
    map[sy][sx] += (N + M);

    int curr_tower = map[sy][sx]; //원래 포탑값 보관

    map[de_y][de_x] -= damage;
    if(map[de_y][de_x]<0){
        map[de_y][de_x] = 0;
    }

    for(int i=0; i<8; ++i){
        int ny = de_y + bomb_dy[i];
        int nx = de_x + bomb_dx[i];

        if(ny < 0){ //맵 밖으로 나갈 때
            ny = N-1;
        }
        if(nx < 0){
            nx = M-1;
        }
        if(ny >= N){
            ny = 0;
        }
        if(nx >= M){
            nx = 0;
        }//맵 밖으로 나갈 때

        if(map[ny][nx]>0){
            map[ny][nx] -= half_damage;
            if(map[ny][nx]<0){
                map[ny][nx] = 0;
            }
        }
    }

    //공격과 무관한 포탑 찾기
    for(int j=0; j<N; ++j){
        for(int k=0; k<M; ++k){
            if(map[j][k]!=temp_map[j][k]){
                no_attack[j][k] = 1;
            }
        }
    }

    map[sy][sx] = curr_tower; //원래 포탑 복원
}

//4 포탑정비

void repair_tower(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            if(map[i][j]>0 && no_attack[i][j]==0){
                map[i][j]++;
            }
        }
    }
}


int main() {
    cin>>N>>M>>K;

    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            cin>>map[i][j];
        }
    }

    // int state = bfs(0,1,2,3);
    // repair_tower();
    // bomb(0,1,2,3);

    // cout<<"state: "<<state<<"\n";

    // for(int i=0; i<N; ++i){
    //     for(int j=0; j<M; ++j){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    for(int i=0; i<K; ++i){
        int tmp_y = select_attacker(i).first;
        int tmp_x = select_attacker(i).second;
        int tmp_dest_y = select_strong().first;
        int tmp_dest_x = select_strong().second;
        
        int state = bfs(tmp_y,tmp_x,tmp_dest_y,tmp_dest_x);
        if(state==1){
            bomb(tmp_y,tmp_x,tmp_dest_y,tmp_dest_x);
        }
        repair_tower();

        

    }
    int final_max = 0;
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            final_max=max(final_max,map[i][j]);
        }
            
    }

    cout<<final_max;

    

    return 0;
}