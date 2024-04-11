#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

int N,M;

int dy[4] = {1,0,0,-1};
int dx[4] = {0,1,-1,1};

struct Mystr{
    int first;
    int second;
    int curr_y;
    int curr_x;
    int state = 0;
};

vector<Mystr> conv_store;
vector<pair<int,int>> base_camp;

int map[17][17] = {0,};

int calc(int y1, int x1, int y2, int x2){
    return abs(y1-y2)+abs(x1-x2);
}

//1
void move(int num){ //num번째 편의점 가고자하는사람
    //현재좌표
    int y = conv_store[num].curr_y;
    int x = conv_store[num].curr_x;
    //최단거리 계산
    int curr_dist = calc(y,x,conv_store[num].first,conv_store[num].second);
    //하우좌상 최단거리 탐색
    for(int i = 0; i<4; ++i){
        int ny = conv_store[num].curr_y + dy[i];
        int nx = conv_store[num].curr_x + dx[i];
        int n_curr_dist = calc(ny,nx,conv_store[num].first,conv_store[num].second);
        if(n_curr_dist<=curr_dist && map[ny][nx] != 2){
            curr_dist = n_curr_dist;
            y = ny;
            x = nx;
        }
    }
    //최단거리로 위치 이동
    conv_store[num].curr_y = y;
    conv_store[num].curr_x = x;
}

//2
void check_conv_store(int num){
    //편의점에 도착
    if(conv_store[num].curr_y == conv_store[num].first && conv_store[num].curr_x == conv_store[num].second){
        //해당편의점 map = 2로 변경
        //중요! 격자에 있는 사람들이 모두 이동하고 나서야 편의점 도착 체크 필요
        map[conv_store[num].first][conv_store[num].second] = 2;
        //편의점에 도착한 사람 vector 지워버리기
        //conv_store.erase(conv_store.begin()+num);
        conv_store[num].state = 1;

        //cout<<"check: "<<num<<"\n";
    }
}

//3
void check_time(int num){
    //자기 편의점과 제일 가까운 베이스캠프 찾기, 해당 좌표 curr값에 넣기
    int y = conv_store[num].first;
    int x = conv_store[num].second;
    int min_dist = 999999;
    
    for(int i=0; i<base_camp.size(); ++i){
        int base_camp_y = base_camp[i].first;
        int base_camp_x = base_camp[i].second;
        //베이스캠프간 거리 탐색
        int dist = calc(y,x,base_camp_y,base_camp_x);
        if(min_dist>dist){
            min_dist = dist;
            conv_store[num].curr_y = base_camp_y;
            conv_store[num].curr_x = base_camp_x;
        }
        //가장 가까운 베이스캠프 여러개
        else if(min_dist == dist){
            if(base_camp_y<conv_store[num].curr_y){
                conv_store[num].curr_y = base_camp_y;
                conv_store[num].curr_x = base_camp_x;
            }
            else if(base_camp_y==conv_store[num].curr_y){
                if(base_camp_x<conv_store[num].curr_x){
                    conv_store[num].curr_y = base_camp_y;
                    conv_store[num].curr_x = base_camp_x;
                }
            }
        }

    }
    // conv_store[num].curr_y = y;
    // conv_store[num].curr_x = x;

    //베이스캠프에 진입, 해당 베이스캠프 erase하기, 해당 베이스캠프 map = 2로 변경
    map[conv_store[num].curr_y][conv_store[num].curr_x] = 2;
    for(int i=0; i<base_camp.size(); ++i){
        if(base_camp[i].first == conv_store[num].curr_y && base_camp[i].second == conv_store[num].curr_x){
            base_camp.erase(base_camp.begin()+i);
            break;
        }
    }

    
}

int main() {
    cin>>N>>M;
    for(int i=0; i<=N+1; ++i){
        for(int j=0; j<=N+1; ++j){            
            map[i][j] = 2; //2가 벽
        }
    }

    for(int i=1; i<=N; ++i){
        for(int j=1; j<=N; ++j){
            int input_tmp;
            cin>>input_tmp;
            map[i][j] = input_tmp;
            if(input_tmp == 1){
                base_camp.push_back({i,j});
            }
        }
    }

    for(int i=0; i<M; ++i){
        int y_tmp,x_tmp;
        cin>>y_tmp>>x_tmp;
        conv_store.push_back({y_tmp,x_tmp,99,99,0});
    }

    int clear_time = 1;
    int curr_time = 0;
    
    //while(!conv_store.empty()){
    // for(int k = 0; k<7; ++k){
    int cnt = 0;

    while(1){
        //3, 베이스캠프에 사람 넣기
        if(curr_time<M){
            if(conv_store[curr_time].state == 0){
                check_time(curr_time);
            }
        }

        //1, 사람들 이동
        for(int i=0; i<M; ++i){
            if(conv_store[i].state == 0){
                move(i);
                //cout<<"move_run\n";
            }
        }

        //2, 편의점 도착 체크
        for(int i=0; i<M; ++i){
            if(conv_store[i].state == 0){
                check_conv_store(i);
            }
        }

        

        // int temp_map[17][17] = {0,};
        // for(int i=0; i<M; ++i){
        //     temp_map[conv_store[i].curr_y][conv_store[i].curr_x] = 1;
        // }
        // for(int i=1; i<=N; ++i){
        //     for(int j=1; j<=N; ++j){
        //         cout<<temp_map[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";

        // memset(temp_map,0,sizeof(temp_map));
        // for(int i=0; i<M; ++i){
        //     temp_map[conv_store[i].first][conv_store[i].second] = 2;
        // }
        // for(int i=1; i<=N; ++i){
        //     for(int j=1; j<=N; ++j){
        //         cout<<temp_map[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";

        curr_time++;
        clear_time++;

        //탈출조건
        int cnt = 0;
        for(int i=0; i<M; ++i){
            
            if(conv_store[i].state == 1){
                cnt++;
            }
            if(cnt == M){
                cout<<clear_time;
                return 0;
            }
        }

    }
    // cout<<clear_time;
    
    return 0;
}