#include <iostream>
#include <vector>
#include <cstring> // memset 사용을 위해 추가

using namespace std;

struct monster_struct {
    int y, x, dir;
    bool egg;
    int condition;
};

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int m, t, r, c;
vector<monster_struct> monster;
int monster_count[4][4] = {0,};  // 각 좌표에 있는 몬스터 수를 기록
bool visited[4][4] = {false,};
int dead[4][4] = {0,};  // 몬스터 시체를 기록 (2턴 동안 유지됨)

void print_map(){
    int map[4][4] = {0,};
    for(auto element : monster){
        if(element.egg == false || element.condition<0) continue;
        if(element.condition == 0){
            map[element.y][element.x] = 4;
            continue;
        }
        map[element.y][element.x] = 1;
    }
    cout<<"r,c:"<<r+1<<","<<c+1<<endl;
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

// 몬스터 수를 초기화
void init_monster_count() {
    memset(monster_count, 0, sizeof(monster_count));  // 배열 초기화
    for (auto& element : monster) {
        if (element.egg && element.condition > 0) {
            monster_count[element.y][element.x]++;
        }
    }
}

// 몬스터 복제 시도
void copy_start() {
    int count = monster.size();
    for (int i = 0; i < count; ++i) {
        if (monster[i].egg && monster[i].condition > 0) {
            monster.push_back({monster[i].y, monster[i].x, monster[i].dir, false, 1});
        }
    }
}

// 팩맨이 먹을 수 있는 몬스터 수를 계산
int check_eating_count(int y, int x) {
    if (visited[y][x]) return 0;
    visited[y][x] = true;
    return monster_count[y][x];
}

// 팩맨이 몬스터를 죽임
void kill_monster(int* pos) {
    for (int i = 0; i < 6; i += 2) {
        for (auto& element : monster) {
            if (element.egg && element.condition > 0 && element.y == pos[i] && element.x == pos[i + 1]) {
                element.condition = -3;  // 몬스터 시체로 변경
                dead[element.y][element.x] = 3;  // 시체 2턴 동안 유지
                monster_count[element.y][element.x]--;  // 몬스터 수 감소
            }
        }
    }
}

// 팩맨이 최적 경로를 탐색
void pacman_move() {
    int max_eating_count = -1;
    int pos[6] = {0,};
    int new_r = r, new_c = c;

    for (int i = 0; i < 8; i += 2) {
        int first_ny = r + dy[i];
        int first_nx = c + dx[i];
        if (first_ny < 0 || first_nx < 0 || first_ny >= 4 || first_nx >= 4) continue;

        for (int j = 0; j < 8; j += 2) {
            int second_ny = first_ny + dy[j];
            int second_nx = first_nx + dx[j];
            if (second_ny < 0 || second_nx < 0 || second_ny >= 4 || second_nx >= 4) continue;

            for (int k = 0; k < 8; k += 2) {
                int third_ny = second_ny + dy[k];
                int third_nx = second_nx + dx[k];
                if (third_ny < 0 || third_nx < 0 || third_ny >= 4 || third_nx >= 4) continue;

                // 초기화
                memset(visited, false, sizeof(visited));

                int tmp_eating_count = check_eating_count(first_ny, first_nx) +
                                       check_eating_count(second_ny, second_nx) +
                                       check_eating_count(third_ny, third_nx);

                if (tmp_eating_count > max_eating_count) {
                    max_eating_count = tmp_eating_count;
                    pos[0] = first_ny; pos[1] = first_nx;
                    pos[2] = second_ny; pos[3] = second_nx;
                    pos[4] = third_ny; pos[5] = third_nx;
                    new_r = third_ny;
                    new_c = third_nx;
                }
            }
        }
    }

    if (max_eating_count > 0) {
        kill_monster(pos);
        r = new_r;
        c = new_c;
    }
    else{
        for (int i = 0; i < 8; i += 2) {
            int first_ny = r + dy[i];
            int first_nx = c + dx[i];
            if (first_ny < 0 || first_nx < 0 || first_ny >= 4 || first_nx >= 4) continue;
            for (int j = 0; j < 8; j += 2) {
                int second_ny = first_ny + dy[j];
                int second_nx = first_nx + dx[j];
                if (second_ny < 0 || second_nx < 0 || second_ny >= 4 || second_nx >= 4) continue;
                for (int k = 0; k < 8; k += 2) {
                    int third_ny = second_ny + dy[k];
                    int third_nx = second_nx + dx[k];
                    if (third_ny < 0 || third_nx < 0 || third_ny >= 4 || third_nx >= 4) continue;
                    
                    r = third_ny; c = third_nx;
                    return;
                }
            }
        }
    }

    return;
}

// 몬스터를 이동시킴
void monster_move() {
    init_monster_count();
    int count = monster.size();
    for (int i = 0; i < count; ++i) {
        if (!monster[i].egg || monster[i].condition <= 0) continue;

        for (int j = 0; j < 8; ++j) {
            int ny = monster[i].y + dy[(monster[i].dir + j) % 8];
            int nx = monster[i].x + dx[(monster[i].dir + j) % 8];
            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4 || (ny == r && nx == c) || dead[ny][nx] > 0) continue;

            monster_count[monster[i].y][monster[i].x]--;
            monster[i].y = ny;
            monster[i].x = nx;
            monster[i].dir = (monster[i].dir + j) % 8;
            monster_count[ny][nx]++;
            break;
        }
    }
}

// 몬스터 시체 소멸
void dead_monster() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (dead[i][j] > 0) {
                dead[i][j]--;
            }
        }
    }
}

// 몬스터 복제 완료 (알이 부화함)
void copy_complete() {
    for (auto& element : monster) {
        if (!element.egg) {
            element.egg = true;
        }
    }
}

// 게임 실행
void run() {
    for (int i = 0; i < t; ++i) {
        copy_start();   // 몬스터 복제 시도
        // print_map();
        monster_move(); // 몬스터 이동
        // print_map();
        pacman_move();  // 팩맨 이동
        // print_map();
        dead_monster(); // 몬스터 시체 소멸
        // print_map();
        copy_complete(); // 몬스터 복제 완료
        // print_map();
    }
}

// 살아남은 몬스터 수 계산
int check_survived_monster() {
    int survived_count = 0;
    for (auto& element : monster) {
        if (element.condition > 0) survived_count++;
    }
    return survived_count;
}

int main() {
    cin >> m >> t >> r >> c;
    r--, c--;

    for (int i = 0; i < m; ++i) {
        int mon_r, mon_c, mon_dir;
        cin >> mon_r >> mon_c >> mon_dir;
        monster.push_back({mon_r - 1, mon_c - 1, mon_dir - 1, true, 1});
    }

    run();
    cout << check_survived_monster();
    return 0;
}