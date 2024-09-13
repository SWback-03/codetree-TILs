#include <iostream>
#include <queue>

using namespace std;

int K, M, result = 0;
int map[5][5] = {0,};
queue<int> q;

int dy[4] = {0,0,-1,1};
int dx[4] = {-1,1,0,0};

void cout_map(){
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
}

int bfs(int sy, int sx, int input_map[][5], int state){

    queue<pair<int,int>> bfs_q;
    bool visited[5][5] = {false,};
    bfs_q.push(make_pair(sy,sx));
    visited[sy][sx] = true;

    queue<pair<int,int>> del_q;
    del_q.push(make_pair(sy,sx));
    int del_count = 1;

    while(!bfs_q.empty()){
        int y = bfs_q.front().first;
        int x = bfs_q.front().second;
        bfs_q.pop();

        // if(input_map[y][x] == input_map[sy][sx]) del_count++;

        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny<0 || nx<0 || ny>=5 || nx>=5 || visited[ny][nx] || input_map[ny][nx] == 0) continue;
            if(input_map[ny][nx] == input_map[sy][sx]){
                bfs_q.push(make_pair(ny,nx));
                del_q.push(make_pair(ny,nx));
                del_count++;
                
                visited[ny][nx] = true;
            }
        }
    }

    if(del_count >= 3 && state == 0){
        while(!del_q.empty()){
            int y = del_q.front().first;
            int x = del_q.front().second;
            del_q.pop();

            input_map[y][x] = 0;
        }
    }
    else if(del_count >=3 && state == 1){
        while(!del_q.empty()){
            int y = del_q.front().first;
            int x = del_q.front().second;
            del_q.pop();

            input_map[y][x] = 0;
            map[y][x] = 0;
        }
    }

    if(del_count>=3) return del_count;
    return 0;
}

int bridge(int input_map[][5], int state){
    int total_count = 0;

    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            int tmp = bfs(i,j,input_map,state);
            // if(tmp>2 && state == 1)
            //     cout<<"tmp:"<<tmp<<endl;
            total_count += tmp;
        }
    }
    return total_count;
}

int rotate(int y, int x, int rotate_count, int state){ //state:0 tmp, state:1 real_map

    int r_dy[8] = {-1,-1,-1,0,1,1,1,0};
    int r_dx[8] = {-1,0,1,1,1,0,-1,-1};

    int tmp_map[5][5] = {0,};

    //map카피
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            tmp_map[i][j] = map[i][j];
        }
    }

    for(int i=0; i<8; ++i){
        int ny = y + r_dy[i];
        int nx = x + r_dx[i];
        int nny = y + r_dy[(i+2*rotate_count)%8];
        int nnx = x + r_dx[(i+2*rotate_count)%8];
        tmp_map[nny][nnx] = map[ny][nx];
    }

    if(state == 1){
        for(int i=0; i<5; ++i){
            for(int j=0; j<5; ++j){
                map[i][j] = tmp_map[i][j];
            }
        }
    }

    return bridge(tmp_map,state);
}

void adventure(){
    int max_rotate=0;
    int max_value=0;
    int result_y=0, result_x=0;
    for(int i=1; i<4; ++i){
        for(int j=1; j<4; ++j){
            for(int k=1; k<4; ++k){
                //rotate가 한 지점 체크
                int tmp_val = rotate(i,j,k,0);
                if(tmp_val>max_value){
                    max_value = tmp_val;
                    max_rotate = k;
                    result_y = i, result_x = j;
                }
                else if(tmp_val == max_value){
                    if(k<max_rotate){
                        max_value = tmp_val;
                        max_rotate = k;
                        result_y = i, result_x = j;
                    }
                    else if(k == max_rotate){
                        if(i<result_y){
                            max_value = tmp_val;
                            max_rotate = k;
                            result_y = i, result_x = j;
                        }
                        else if(i == result_y){
                            if(j<result_x){
                                max_value = tmp_val;
                                max_rotate = k;
                                result_y = i, result_x = j;
                            }
                            else break;
                        }
                    }
                }
            }
        }
    }

    if(max_value == 0) return;

    //출력
    int real_tmp = rotate(result_y,result_x,max_rotate,1);
    result += real_tmp;

    //벽면 채우기
    for(int i=0; i<5; ++i){
        for(int j=4; j>=0; --j){
            if(map[j][i] == 0){
                map[j][i] = q.front();
                q.pop();
            }
        }
    }

    while(real_tmp != 0){
        real_tmp = rotate(result_y,result_x,0,1);
        result += real_tmp;
        //벽면 채우기
        for(int i=0; i<5; ++i){
            for(int j=4; j>=0; --j){
                if(map[j][i] == 0){
                    map[j][i] = q.front();
                    q.pop();
                }
            }
        }
    }

    return;
}

int main(){

    cin>>K>>M;

    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            cin>>map[i][j];
        }
    }

    for(int i=0; i<M; ++i){
        int tmp;
        cin>>tmp;
        q.push(tmp);
    }
    for(int i=0; i<K; ++i)
        adventure();

    cout<<result<<endl;

    return 0;
}