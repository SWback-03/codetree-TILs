#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define MAX_P 31

using namespace std;

struct my_str{
    int y;
    int x;
    int stun_time=0;
    int score=0;
    bool fall = false;
};

int N,M,P,C,D;
int rudolf_y, rudolf_x;
vector<my_str> santa(MAX_P);

int rudolf_dy[8] = {-1,0,1,0,-1,-1,1,1};
int rudolf_dx[8] = {0,1,0,-1,-1,1,1,-1};

int santa_dy[4] = {-1,0,1,0};
int santa_dx[4] = {0,1,0,-1};

void print_position(){
    cout<<"rudolf:"<<rudolf_y<<","<<rudolf_x<<endl;
    cout<<"santa:"<<endl;
    for(int i=1; i<=P; ++i){
        cout<<santa[i].y<<","<<santa[i].x<<","<<santa[i].stun_time<<","<<santa[i].score<<","<<santa[i].fall<<endl;
    }
    cout<<endl;
    return;
}


int cal_dist(int y_1, int x_1, int y_2, int x_2){
    return (y_1-y_2)*(y_1-y_2) + (x_1-x_2)*(x_1-x_2);
}

bool check_collide(int santa_num){
    if(santa[santa_num].y == rudolf_y && santa[santa_num].x == rudolf_x) return true;

    return false;
}

bool check_falling(int santa_num){
    if(santa[santa_num].y <= 0 || santa[santa_num].y > N || santa[santa_num].x <= 0 || santa[santa_num].x > N){
        return true;
    }
    return false;
}

void interact(int santa_num, int dir_num){

    if(check_falling(santa_num)){
        return;
    }

    for(int i=1; i<=P; ++i){
        if(i == santa_num) continue;

        if(santa[i].y == santa[santa_num].y && santa[i].x == santa[santa_num].x){
            santa[i].y = santa[i].y + rudolf_dy[dir_num];
            santa[i].x = santa[i].x + rudolf_dx[dir_num];

            interact(i, dir_num);
        }
    }

    return;
}

void back_push(int santa_num, int dir_num, string pushed_obj){
    if(pushed_obj == "rudolf"){ //루돌프가 시작
        santa[santa_num].y = santa[santa_num].y + C * rudolf_dy[dir_num];
        santa[santa_num].x = santa[santa_num].x + C * rudolf_dx[dir_num];
        santa[santa_num].score += C;
        santa[santa_num].stun_time = 2;
    }
    else{ //산타가 시작
        dir_num = (dir_num + 2)%4;
        santa[santa_num].y = santa[santa_num].y + D * rudolf_dy[dir_num];
        santa[santa_num].x = santa[santa_num].x + D * rudolf_dx[dir_num];
        santa[santa_num].score += D;
        santa[santa_num].stun_time = 1;
    }

    // santa[santa_num].stun_time = 2;

    if(check_falling(santa_num)) santa[santa_num].fall = true;

    interact(santa_num, dir_num);
}

int find_min_santa(int input_y, int input_x){
    int min_dist = INT_MAX;
    int fixed_y, fixed_x, result_santa_num;
    for(int i=1; i<=P; ++i){
        if(check_falling(i)) continue;

        int tmp_dist = cal_dist(santa[i].y,santa[i].x,input_y,input_x);
        if(tmp_dist<min_dist){
            min_dist = tmp_dist;
            fixed_y = santa[i].y;
            fixed_x = santa[i].x;
            result_santa_num = i;
        }
        else if(tmp_dist == min_dist){
            if(santa[i].y > fixed_y){
                fixed_y = santa[i].y;
                fixed_x = santa[i].x;
                result_santa_num = i;
            }
            else if(santa[i].y == fixed_y){
                if(santa[i].x > fixed_x){
                    fixed_y = santa[i].y;
                    fixed_x = santa[i].x;
                    result_santa_num = i;
                }
                else continue;
            }
        }
    }
    return result_santa_num;
}


void move_rudolf(){
    int closest_santa_num = find_min_santa(rudolf_y,rudolf_x);
    int min_dist = INT_MAX;
    int rudolf_dir;

    for(int i=0; i<8; ++i){
        int rudolf_ny = rudolf_y + rudolf_dy[i];
        int rudolf_nx = rudolf_x + rudolf_dx[i];

        int tmp_dist = cal_dist(rudolf_ny,rudolf_nx,santa[closest_santa_num].y,santa[closest_santa_num].x);
        
        if(tmp_dist<min_dist){
            min_dist = tmp_dist;
            rudolf_dir = i;
        }
    }

    rudolf_y = rudolf_y + rudolf_dy[rudolf_dir];
    rudolf_x = rudolf_x + rudolf_dx[rudolf_dir];

    if(check_collide(closest_santa_num)){ //충돌했을 때
        back_push(closest_santa_num, rudolf_dir, "rudolf");
    }

    return;
}

bool check_santa_boundry(int input_y, int input_x){
    if(input_y <= 0 || input_y > N || input_x <= 0 || input_x > N) return true;
    for(int i=1; i<=P; ++i){
        if(santa[i].y == input_y && santa[i].x == input_x) return true;
    }
    return false;
}

void fall_santa_write(){
    for(int i=1; i<=P; ++i){
        if(santa[i].y <= 0 || santa[i].y > N || santa[i].x <= 0 || santa[i].x > N){
            santa[i].fall = true;
        }
    }
}

void move_santa(){
    for(int i=1; i<=P; ++i){
        if(santa[i].stun_time > 0){
            santa[i].stun_time--;
            continue;
        }

        if(check_falling(i)) continue;

        int min_dist = cal_dist(rudolf_y, rudolf_x, santa[i].y, santa[i].x);
        int santa_dir;
        bool enable = false;

        for(int j=0; j<4; ++j){
            int santa_ny = santa[i].y + santa_dy[j];
            int santa_nx = santa[i].x + santa_dx[j];

            if(check_santa_boundry(santa_ny,santa_nx)) continue; 

            // cout<<i<<"/"<<santa_ny<<"/"<<santa_nx<<"/";

            int tmp_dist = cal_dist(rudolf_y, rudolf_x, santa_ny, santa_nx);
            // cout<<tmp_dist<<"/min:"<<min_dist<<endl;

            if(tmp_dist<min_dist){
                min_dist = tmp_dist;
                santa_dir = j;
                enable = true;
            }
        }

        if(enable){
            // cout<<"santa_dir,min_dist:"<<santa_dir<<","<<min_dist<<endl;
            santa[i].y = santa[i].y + santa_dy[santa_dir];
            santa[i].x = santa[i].x + santa_dx[santa_dir];
        }

        if(check_collide(i)){ //충돌했을 때
            back_push(i, santa_dir, "santa");
        }

        fall_santa_write();
    }

    return;
}

void run(){
    move_rudolf();

    // print_position();

    move_santa();

    // print_position();

    return;
}

void add_score(){
    for(int i=0; i<=P; ++i){
        if(santa[i].fall == false){
            santa[i].score++;
        }
    }
    return;
}

void print_score(){
    for(int i=1; i<=P; ++i){
        cout<<santa[i].score<<" ";
    }
    return;
}

int main() {
    cin>>N>>M>>P>>C>>D;

    cin>>rudolf_y>>rudolf_x;

    for(int i=1; i<=P; ++i){
        int tmp_num, tmp_sr, tmp_sc;
        cin>>tmp_num>>tmp_sr>>tmp_sc;
        santa[tmp_num] = {tmp_sr, tmp_sc, 0, 0, false};
    }

    for(int i=0; i<M; ++i){
        // cout<<"time:"<<i+1<<endl;
        run();

        add_score();
    }

    print_score();

    return 0;
}