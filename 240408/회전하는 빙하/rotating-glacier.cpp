#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

int n, q;
int map[66][66] = {0,};
int visited_map[66][66] = {0,};
int visited_queue[66][66] = {0,};
int map_info[66][66] = {0,};
int temp_map[66][66] = {0,};

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int rotate_dy[4] = {0,0,1,0};
int rotate_dx[4] = {0,1,0,-1};

queue<pair<int,int>> que;


int dfs(int sy, int sx){
    que = queue<pair<int,int>>();
    //memset(visited_queue,0,sizeof(visited_queue));

    que.push({sy,sx});
    visited_queue[sy][sx] = 1;

    int size = 0;

    while(!que.empty()){
        int y = que.front().first;
        int x = que.front().second;
        size++;
        que.pop();

        for(int i=0; i<4; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(!visited_queue[ny][nx] && map[ny][nx]>0){
                que.push({ny,nx});
                visited_queue[ny][nx] = 1;
            }
        }
    }

    return size;
}

bool check_side(int y, int x){
    int cnt = 0;

    for(int i=0; i<4; ++i){
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(map[ny][nx]>0) cnt++;
    }

    if(cnt >=3){
        return false;
    }

    return true;

}

void melt(){
    int map_len = pow(2,n);

    for(int i=1; i<=map_len; ++i){
        for(int j=1; j<=map_len; ++j){
            if(check_side(i,j) && map[i][j]>0){ //melt 조건 충족(3칸 인접X)
                map[i][j]--;
            }
        }
    }
}

void set_map(int level){
    int map_len = pow(2,n);
    int cut_size = pow(2,level);
    int f_cut_size = pow(2,level-1);

    for(int y= 1; y<=map_len; ++y){
        for(int x = 1; x<=map_len; ++x){

            int ny = y;
            int nx = x;

            if(visited_map[ny][nx]!=0) continue;

            for(int k = 0; k<4; ++k){
                ny += f_cut_size*rotate_dy[k];
                nx += f_cut_size*rotate_dx[k];

                if(visited_map[ny][nx]!=0) continue;

                for(int i=0; i<f_cut_size; ++i){
                    for(int j=0; j<f_cut_size; ++j){
                        map_info[ny+i][nx+j] = k;
                        visited_map[ny+i][nx+j] = 1;
                    }
                }


            }
        }
    }
}

void rotate(int level)
{
    int map_len = pow(2,n);
    int cut_size = pow(2,level);
    int f_cut_size = pow(2,level-1);

    for(int y_loc= 1; y_loc<=map_len; ++y_loc){
        for(int x_loc = 1; x_loc<=map_len; ++x_loc){
            int move = map_info[y_loc][x_loc];
            int ny = y_loc + f_cut_size*dy[move];
            int nx = x_loc + f_cut_size*dx[move];
            temp_map[ny][nx] = map[y_loc][x_loc];
            
        }
    }

    for(int y_loc= 1; y_loc<=map_len; ++y_loc){
        for(int x_loc = 1; x_loc<=map_len; ++x_loc){
            map[y_loc][x_loc] = temp_map[y_loc][x_loc];
            
        }
    }



    melt(); //회전 끝내고 melt
}

int main() {
    cin>>n>>q;

    int map_len = pow(2,n);

    for(int i=1; i<=map_len; ++i){
        for(int j=1; j<=map_len; ++j){
            cin>>map[i][j];
        }
    }//map 입력받기

    // for(int i=0; i<=map_len+1; ++i){
    //     for(int j=0; j<=map_len+1; ++j){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }//map 출력 확인

    int rotate_level;

    for(int i=0; i<q; ++i){
        cin>>rotate_level;
        //회전 실행
        if(rotate_level>0){
            
            set_map(rotate_level);
            rotate(rotate_level);


            // //map 출력 확인
            // for(int i=0; i<=map_len+1; ++i){
            //     for(int j=0; j<=map_len+1; ++j){
            //         cout<<map[i][j]<<" ";
            //     }
            //     cout<<"\n";
            // }
            // cout<<"\n";
            // //map 출력 확인



            memset(visited_map,0,sizeof(visited_map));
        }
        else
            melt();
    }

    // for(int i=0; i<=map_len+1; ++i){
    //     for(int j=0; j<=map_len+1; ++j){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }//map 출력 확인

    // for(int i=0; i<=map_len+1; ++i){
    //     for(int j=0; j<=map_len+1; ++j){
    //         cout<<map_info[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }//map 출력 확인

    int total = 0;
    for(int i=0; i<=map_len+1; ++i){
        for(int j=0; j<=map_len+1; ++j){
            total += map[i][j];
        }
    }

    cout<<total<<"\n";

    int max_dfs = 0;
    for(int i=1; i<=map_len; ++i){
        for(int j=1; j<=map_len; ++j){
            int curr_dfs = 0;
            if(map[i][j]>0){
                curr_dfs = dfs(i,j);
            }
            if(max_dfs<curr_dfs) max_dfs = curr_dfs;
        }
    }

    cout<<max_dfs;

    return 0;
}