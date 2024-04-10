#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N;
int map[31][31] = {0,};

struct Mystr{
    int first;
    int second;
};

//그룹에 속한 칸의 수 찾기, BFS 사용 변수 선언
queue<Mystr> q;
int visited_bfs[31][31] = {0,};
int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};
vector<int> group_cnt;
vector<int> group_value;
vector<vector<Mystr>> group_loc(900);
int group_addr = 0;

//예술점수 변수
int design_score = 0;
int design_temp_map[31][31] = {0,};
int design_visited_bfs[31][31] = {0,};



//그룹에 속한 칸의 수 찾기, BFS 사용
int bfs(int sy, int sx){
    q = queue<Mystr>();
    // memset(visited_bfs,0,sizeof(visited_bfs));
    int cnt = 1;
    //초기화
    q.push({sy,sx});
    visited_bfs[sy][sx] = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        group_loc[group_addr].push_back({y,x});
        q.pop();
        for(int i=0; i<4; ++i){
            int ny = y +dy[i];
            int nx = x +dx[i];
            if(map[ny][nx]==map[sy][sx] && visited_bfs[ny][nx] == 0){ // 숫자같을 때, 방문안한곳일 때
                visited_bfs[ny][nx] = 1;
                q.push({ny,nx});
                group_loc[group_addr].push_back({ny,nx});
                cnt++;
            }

        }
    }

    return cnt;
}

//예술 점수용 bfs
int design_bfs(int sy, int sx){
    q = queue<Mystr>();
    int cnt = 0;
    //초기화
    q.push({sy,sx});
    design_visited_bfs[sy][sx] = 1;
    for(int j=0; j<4; ++j){
        int nny = sy +dy[j];
        int nnx = sx +dx[j];
        if(design_temp_map[nny][nnx]!=design_temp_map[sy][sx] && design_temp_map[nny][nnx]!=0) cnt++;
    }

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for(int i=0; i<4; ++i){
            int ny = y +dy[i];
            int nx = x +dx[i];
            if(design_temp_map[ny][nx]==design_temp_map[sy][sx] && design_visited_bfs[ny][nx] == 0){ //같은값,방문안한곳일 때
                design_visited_bfs[ny][nx] = 1;
                q.push({ny,nx});
                for(int j=0; j<4; ++j){
                    int nny = ny +dy[j];
                    int nnx = nx +dx[j];
                    if(design_temp_map[nny][nnx]!=design_temp_map[sy][sx] && design_temp_map[nny][nnx]!=0) cnt++;
                }
            }
            // else if(design_temp_map[ny][nx]!=design_temp_map[sy][sx] && design_temp_map[ny][nx]!=0){
            //     cnt++;//맞닿은 변 갯수
            // }

        }
    }

    return cnt;
}

//예술점수찾기
int find_design_score(int group_1, int group_2){
    memset(design_temp_map,0,sizeof(design_temp_map));
    memset(design_visited_bfs,0,sizeof(design_visited_bfs));
    for(int i=0; i<group_loc[group_1].size(); ++i){
        design_temp_map[group_loc[group_1][i].first][group_loc[group_1][i].second] = group_value[group_1];
    }
    for(int i=0; i<group_loc[group_2].size(); ++i){
        design_temp_map[group_loc[group_2][i].first][group_loc[group_2][i].second] = group_value[group_2];
    }
    int meet = 0;
    for(int i=1; i<=N; ++i){
        for(int j=1; j<=N; ++j){
            if(design_visited_bfs[i][j] == 0 && design_temp_map[i][j] == group_value[group_1]){
                meet = design_bfs(i,j);
            }
        }
    }


    // //map 출력
    // for(int i=1; i<=N; ++i){
    //     for(int j=1; j<=N; ++j){
    //         cout<<design_temp_map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    // //map 출력

    return meet;
}



//십자모양 회전시키기(역 90도 = 270도)
void re_rotate_90(){
    //가운데 숫자 찾기
    int center = N/2+1;
    int rect_size = N;
    int r = 1;
    int c = 1;

    for(int k=0; k<3; ++k){
        int temp_map[31][31] = {0,};
        for(int i=0; i<rect_size; ++i){
            for(int j=0; j<rect_size; ++j){
                temp_map[r+j][c+rect_size-1-i] = map[r+i][c+j];
            }
        }
        for(int i=1; i<=N; ++i){
            map[center][i] = temp_map[center][i];
        }
        for(int i=1; i<=N; ++i){
            map[i][center] = temp_map[i][center];
        }
    }
}

//작은 정사각형 회전시키기(90도)
void rotate_90(int r, int c){ //r, c: 정사각형 왼쪽 위 좌표
    //한변 길이 찾기
    int rect_size = N/2;

    int temp_map[31][31] = {0,};
    for(int i=0; i<rect_size; ++i){
        for(int j=0; j<rect_size; ++j){
            temp_map[r+j][c+rect_size-1-i] = map[r+i][c+j];
        }
    }

    for(int i=r; i<r+rect_size; ++i){
        for(int j=c; j<c+rect_size; ++j){
            map[i][j] = temp_map[i][j];
        }
    }
    
}

//회전시키기
void rotate(){
    //십자모양 회전시키기(역 90도)
    re_rotate_90();
    //작은 정사각형 회전시키기(90도)
    int r=1;
    int c=1;
    int move = N/2+1;
    for(int i=0; i<4; ++i){
        rotate_90(r,c);
        r += move * dy[i];
        c += move * dx[i];
    }

}



int main() {
    cin>>N;

    for(int i=1; i<=N; ++i){
        for(int j=1; j<=N; ++j){
            cin>>map[i][j];
        }
    }

    for(int ijk=0; ijk<4; ++ijk){//3회까지의 예술점수 구하기
        memset(visited_bfs,0,sizeof(visited_bfs));
        group_cnt = vector<int>();
        group_value = vector<int>();
        group_loc = vector<vector<Mystr>>(900);

        //각 그룹 찾기
        group_addr = 0;
        for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
                if(visited_bfs[i][j]==0){
                    int tmp = bfs(i,j);
                    group_addr++; //각 그룹 벡터에 좌표값 저장
                    group_cnt.push_back(tmp); //각 그룹내 갯수 저장
                    group_value.push_back(map[i][j]);
                }
            }
        }

        //예술 점수 찾기
        int group_size = group_cnt.size(); // 전체 그룹 갯수 구하기


        //design_score = 0;


        //cout<<group_size<<"\n";
        int temp_score;
        for(int i =0; i<group_size; ++i){
            for(int j=i+1; j<group_size; ++j){
                int meet = find_design_score(i,j);
                //cout<<meet<<"\n";
                temp_score = (group_cnt[i]+group_cnt[j])*group_value[i]*group_value[j]*meet;
                design_score += temp_score;
                //design_score += (group_cnt[i]+group_cnt[j])*group_value[i]*group_value[j];
            }
        }
        //cout<<design_score<<"\n";
        

        //회전시키기
        rotate();

        // //map 출력
        // for(int i=1; i<=N; ++i){
        //     for(int j=1; j<=N; ++j){
        //         cout<<map[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";
        // //map 출력
        
    }

    cout<<design_score;


    return 0;
}