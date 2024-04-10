#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include<cstring>

using namespace std;

int N, M, K;

struct player_struct {
    int first; //현재위치
    int second; //현재위치
    int dir;
    int ability;
    int gun = 0;
    int point = 0;
};

player_struct player[31] = { 0, };

int map[22][22][2] = { 0, };

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

vector<vector<vector<int>>> map_gun_info(22, vector<vector<int>>(22));

void gun_erase(int num) {
    stack<int> temp_stk;
    for (int i = 0; i < map_gun_info[player[num].first][player[num].second].size(); ++i) {
        if (map_gun_info[player[num].first][player[num].second][i] == 0) {
            temp_stk.push(i);
        }
    }
    while (!temp_stk.empty()) {
        map_gun_info[player[num].first][player[num].second].erase(map_gun_info[player[num].first][player[num].second].begin() + temp_stk.top());
        temp_stk.pop();
    }
    if (map_gun_info[player[num].first][player[num].second].size() == 0) {
        map[player[num].first][player[num].second][0] = 0;
    }
}

void get_point(int num, int lose_num) {
    int a = player[num].gun + player[num].ability;
    int b = player[lose_num].gun + player[lose_num].ability;

    player[num].point += abs(a - b);
    //cout << num << "->get\n";

}

void win_player(int num) { //2-2-3
    int y = player[num].first;
    int x = player[num].second;
    
    //if(map[y][x][0] > 0){
    if (map_gun_info[y][x].size() > 0) {
        for (int j = 0; j < map_gun_info[y][x].size(); ++j) {
            if (player[num].gun < map_gun_info[y][x][j]) { //가장 강한 총으로 변경
                int gun_info_tmp = player[num].gun;
                player[num].gun = map_gun_info[y][x][j];
                map_gun_info[y][x][j] = gun_info_tmp;
                
                gun_erase(num);
            }
        }
    }
}

void lose_player(int num) { //2-2-2
    int y = player[num].first;
    int x = player[num].second;

    map_gun_info[y][x].push_back(player[num].gun);
    /*for (int i = 0; i < map_gun_info[y][x].size(); ++i) {
        cout << y<<" "<<x<<" "<<map_gun_info[y][x][i] << "\n";
    }
    cout << "\n";*/
    player[num].gun = 0;//총 내려놓기

    y += dy[player[num].dir];
    x += dx[player[num].dir];
    if (map[y][x][0] < 0 || map[y][x][1] == 1) { //벽 확인, 사람 확인
        while (1) {
            int curr_dir = player[num].dir;
            curr_dir = (curr_dir + 1) % 4; //90도 회전
            player[num].dir = curr_dir;
            //cout<<"num: "<<curr_dir<<"\n";

            //player[num].dir = (player[num].dir+1)%4; //90도 회전
            y = player[num].first;
            x = player[num].second;
            y += dy[player[num].dir];
            x += dx[player[num].dir];
            //cout<<"y: "<<y<<" /x: "<<x<<"\n";
            if (map[y][x][0] >= 0 && map[y][x][1] == 0) break;
        }
    }
    player[num].first = y;
    player[num].second = x;
    map[player[num].first][player[num].second][1] = 1;

    //if(map[y][x][0] > 0){
    if (map_gun_info[y][x].size() > 0) {
        for (int j = 0; j < map_gun_info[y][x].size(); ++j) {
            if (player[num].gun < map_gun_info[y][x][j]) { //가장 강한 총으로 변경
                int gun_info_tmp = player[num].gun;
                player[num].gun = map_gun_info[y][x][j];
                map_gun_info[y][x][j] = gun_info_tmp;
                
            }
            
        }
        gun_erase(num);
    }
}

void move() { //플레이어 이동
    for (int i = 1; i <= M; ++i) {
        //1-1
        map[player[i].first][player[i].second][1] = 0;
        player[i].first += dy[player[i].dir];
        player[i].second += dx[player[i].dir];
        if (map[player[i].first][player[i].second][0] < 0) { //방향 반대로 전환
            int curr_dir = player[i].dir;
            curr_dir = (curr_dir + 2) % 4;
            player[i].dir = curr_dir;
            player[i].first += 2 * dy[player[i].dir];
            player[i].second += 2 * dx[player[i].dir];
        }
        // map[player[i].first][player[i].second][1] = 1;

        //2-1
        //cout<<player[i].first<<"worked"<<player[i].second<<"\n";
        if (map[player[i].first][player[i].second][1] == 0) {//이동방향에 플레이어X
            //cout<<"worked"<<"\n";
            //if(map[player[i].first][player[i].second][0]>0){//이동방향에 총O
            if (map_gun_info[player[i].first][player[i].second].size() > 0) {//이동방향에 총O
                //cout<<"worked"<<"\n";
                for (int j = 0; j < map_gun_info[player[i].first][player[i].second].size(); ++j) {
                    if (player[i].gun < map_gun_info[player[i].first][player[i].second][j]) { //가장 강한 총으로 변경
                        //cout<<"worked"<<"\n";
                        int gun_info_tmp = player[i].gun;
                        player[i].gun = map_gun_info[player[i].first][player[i].second][j];
                        map_gun_info[player[i].first][player[i].second][j] = gun_info_tmp;
                        
                    }
                    
                }
                gun_erase(i);
            }
        }

        //2-2-1
        else if (map[player[i].first][player[i].second][1] != 0) {
            for (int j = 1; j <= M; ++j) {
                if (i != j && player[j].first == player[i].first && player[j].second == player[i].second) {//같은위치 플레이어 찾기
                    //전투 시작
                    if (player[i].ability + player[i].gun > player[j].ability + player[j].gun) {//player i win
                        get_point(i, j);
                        lose_player(j);
                        win_player(i);
                        //cout << "0 win: " << i << " /lose: " << j << "\n";
                    }
                    else if (player[i].ability + player[i].gun == player[j].ability + player[j].gun) {//동점
                        if (player[i].ability > player[j].ability) {//player i win
                            get_point(i, j);
                            lose_player(j);
                            win_player(i);
                            //cout << "1 win: " << i << " /lose: " << j << "\n";
                        }
                        else {//player j win
                            get_point(j, i);
                            lose_player(i);
                            win_player(j);
                            //cout << "2 win: " << j << " /lose: " << i << "\n";
                        }
                    }
                    else {//player j win
                        get_point(j, i);
                        lose_player(i);
                        win_player(j);
                        //cout << "3 win: " << j << " /lose: " << i << "\n";
                    }
                }
            }
        }

        map[player[i].first][player[i].second][1] = 1;

    }
}

int main() {
    cin >> N >> M >> K; //격자크기, 플레이어 수, 라운드 수

    memset(map, 0, sizeof(map));

    for (int i = 0; i < N + 2; ++i) { //맵 전체 -1로 초기화
        for (int j = 0; j < N + 2; ++j) {
            map[i][j][0] = -1;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            int gun_info;
            cin >> gun_info;
            map[i][j][0] = gun_info;
            if (gun_info > 0) {
                map_gun_info[i][j].push_back(gun_info);
            }
        }
    }

    // for(int i=1; i<=N; ++i){
    //     for(int j=1; j<=N; ++j){
    //         if(map_gun_info[i][j].size()!=0)
    //             cout<<map_gun_info[i][j][0]<<" ";
    //         else
    //             cout<<0<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";

    // for(int i=0; i<=N+1; ++i){
    //     for(int j=0; j<=N+1; ++j){
    //         cout<<map[i][j][0]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";

    for (int i = 1; i <= M; ++i) {
        cin >> player[i].first >> player[i].second >> player[i].dir >> player[i].ability;
        map[player[i].first][player[i].second][1] = 1;
    }

     /*for(int i=1; i<=N; ++i){
         for(int j=1; j<=N; ++j){
             cout<<map[i][j][1]<<" ";
         }
         cout<<"\n";
     }
     cout<<"\n";*/

    //Run
    for (int i = 0; i < K; ++i) {
        move();

        /*for (int i = 0; i < map_gun_info[5][3].size(); ++i) {
            cout <<"info: "<<map_gun_info[5][3][i] << "\n";
        }
        cout << "\n";

        for (int i = 1; i <= M; ++i) {
            cout << player[i].first << "," << player[i].second << "/";
            cout << "dir:" << player[i].dir << "/abil:" << player[i].ability << "/gun:" << player[i].gun << "/point:" << player[i].point << "\n";
        }
        cout << "\n";*/

        // int temporary[22][22] = {0,};
        // for(i=1; i<=M; ++i){
        //     temporary[player[i].first][player[i].second] = i;
        // }

        // for(int i=1; i<=N; ++i){
        //     for(int j=1; j<=N; ++j){
        //         cout<<temporary[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";

        /* for(int i=1; i<=N; ++i){
             for(int j=1; j<=N; ++j){
                 cout<<map[i][j][1]<<" ";
             }
             cout<<"\n";
         }
         cout<<"\n";*/




    }

    for (int i = 1; i <= M; ++i) {
        cout << player[i].point << " ";
    }


    return 0;
}