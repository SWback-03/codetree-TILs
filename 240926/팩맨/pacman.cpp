#include <iostream>
#include <vector>

using namespace std;

struct monster_struct{
    int y;
    int x;
    int dir;
    bool egg;
    int condition;
};

int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,-1,-1,-1,0,1,1,1};

int m,t,r,c;
vector<monster_struct> monster;

void print_egg_map(){
    int map[4][4] = {0,};
    for(auto element : monster){
        if(element.egg == false){
            map[element.y][element.x] = 1;
        }
    }

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

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
    // map[r][c] = 2;

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void copy_start(){
    int count = monster.size();
    for(int i=0; i<count; ++i){
        if(monster[i].egg == false || monster[i].condition<=0) continue;
        monster.push_back({monster[i].y,monster[i].x,monster[i].dir,false,1});
    }
    return;
}

bool check_pacman_dead_monster(int i_y, int i_x){
    if(i_y == r && i_x == c) return false;
    for(auto element : monster){
        if(element.egg == false) continue;

        if(element.condition<=0 && element.y == i_y && element.x == i_x) return false;
    }
    return true;
}

void monster_move(){
    int count = monster.size();
    for(int i=0; i<count; ++i){
        if(monster[i].egg == false || monster[i].condition<0) continue;
        
        for(int j=0; j<8; ++j){
            int ny = monster[i].y + dy[(monster[i].dir + j)%8];
            int nx = monster[i].x + dx[(monster[i].dir + j)%8];
            if(ny<0 || nx<0 || ny>=4 || nx>=4) continue;
            if(!check_pacman_dead_monster(ny,nx)) continue;

            monster[i].y = ny;
            monster[i].x = nx;
            break;
        }
    }
    return;
}

int check_eating_count(int i_y, int i_x){
    int count = 0;
    for(auto element : monster){
        if(element.egg == false || element.condition<=0) continue;

        if(element.y == i_y && element.x == i_x) count++;
    }
    return count;
}

void kill_moster(int *pos){
    // for(int i=0; i<6; ++i){
    //     cout<<pos[i]+1<<" ";
    // }
    // cout<<endl;
    int count_limit = monster.size();
    for(int i=0; i<count_limit; ++i){
        if(monster[i].egg == false || monster[i].condition<=0) continue;

        if(monster[i].y == pos[0] && monster[i].x == pos[1] || monster[i].y == pos[2] && monster[i].x == pos[3] || monster[i].y == pos[4] && monster[i].x == pos[5]){
            monster[i].condition = -3;
        }
    }

    return;
}

void pacman_move(){
    bool visited[4][4] = {false,};
    int eating_count = 0;
    int new_r, new_c;

    bool enable = false;
    int pos[6] = {0,};

    for(int i=0; i<8; i+=2){
        int first_ny = r + dy[i];
        int first_nx = c + dx[i];
        if(first_ny<0 || first_nx<0 || first_ny>=4 || first_nx>=4 || visited[first_ny][first_nx]) continue;
        visited[first_ny][first_nx] = true;
        for(int j=0; j<8; j+=2){
            int second_ny = first_ny + dy[j];
            int second_nx = first_nx + dx[j];
            if(second_ny<0 || second_nx<0 || second_ny>=4 || second_nx>=4 || visited[second_ny][second_nx]) continue;
            visited[second_ny][second_nx] = true;
            for(int k=0; k<8; k+=2){
                int third_ny = second_ny + dy[k];
                int third_nx = second_nx + dx[k];
                if(third_ny<0 || third_nx<0 || third_ny>=4 || third_nx>=4 || visited[third_ny][third_nx]) continue;
                visited[third_ny][third_nx] = true;

                int tmp = 0;
                tmp+=check_eating_count(first_ny,first_nx);
                tmp+=check_eating_count(second_ny,second_nx);
                tmp+=check_eating_count(third_ny,third_nx);

                if(tmp>eating_count){
                    eating_count =tmp;
                    enable = true;
                    pos[0] = first_ny;
                    pos[1] = first_nx;
                    pos[2] = second_ny;
                    pos[3] = second_nx;
                    pos[4] = third_ny;
                    pos[5] = third_nx;
                    new_r = third_ny, new_c = third_nx;
                }

                visited[third_ny][third_nx] = false;
            }
            visited[second_ny][second_nx] = false;
        }
        visited[first_ny][first_nx] = false;
    }

    if(enable){
        kill_moster(pos);
        r = new_r, c = new_c;
    }

    return;
}

void dead_monster(){
    int count_limit = monster.size();
    for(int i=0; i<count_limit; ++i){
        if(monster[i].condition<0){
            monster[i].condition++;
        }
    }

    return;
}

void copy_complete(){
    int count_limit = monster.size();
    for(int i=0; i<count_limit; ++i){
        if(monster[i].egg==false){
            monster[i].egg=true;
        }
    }

    return;
}

void run(){

    for(int i=0; i<t; ++i){
        copy_start();
        // print_map();

        monster_move();
        // print_map();

        pacman_move();
        // print_map();

        dead_monster();
        // print_map();
        // cout<<"eggmap\n";
        // print_egg_map();

        copy_complete();
        // print_map();
    }

    return;
}

int check_survived_monster(){
    int survived_count = 0;
    for(auto element : monster){
        if(element.condition>0) survived_count++;
    }
    return survived_count;
}


int main() {
    cin>>m>>t>>r>>c;
    r--, c--;

    for(int i=0; i<m; ++i){
        int mon_r,mon_c, mon_dir;
        cin>>mon_r>>mon_c>>mon_dir;
        monster.push_back({mon_r-1,mon_c-1,mon_dir-1,true,1});
    }

    run();

    cout<<check_survived_monster();

    return 0;
}