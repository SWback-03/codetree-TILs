#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>

#define MAX_N 100
#define MAX_M 10000
using namespace std;

struct thief{
    int y;
    int x;
    int dir;
};

queue<int> dist_q;

int N,M,H,K;
vector<int> person_map[MAX_N][MAX_N];
int tree_map[MAX_N][MAX_N] = {0,};
vector<thief> person(MAX_M);
bool visited_person[MAX_M] = {false,};

int init_y, init_x;
int cap_y, cap_x;

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

int total_score = 0;

int cal_dist(int input_y, int input_x){
    int cap_theif_dist = abs(cap_y - input_y)+abs(cap_x-input_x);
    if(cap_theif_dist <= 3) return false;
    return true;
}

void print_person_map(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){

            if(i == cap_y && j == cap_x){
                cout<<"x ";
                continue;
            }

            if(tree_map[i][j] == 1){
                cout<<"T ";
                continue;
            }

            bool doing = true;
            if(person_map[i][j].size()>0){
                cout<<"(";
                for(auto element : person_map[i][j]){
                    cout<<element+1<<",";
                    doing = false;
                }
                cout<<")";
            }

            if(doing) cout<<"0 ";
        }
        cout<<endl;
    }
    cout<<endl;

    return;
}

void clear_person_map(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            while(person_map[i][j].size()>0){
                person_map[i][j].erase(person_map[i][j].begin());
            }
        }
    }

    return;
}

void move_person(){

    clear_person_map();

    for(int i=0; i<M; ++i){

        if(cal_dist(person[i].y,person[i].x)) continue;

        int ndir = person[i].dir;
        int ny = person[i].y + dy[ndir];
        int nx = person[i].x + dx[ndir];

        if(ny == cap_y && nx ==cap_x) continue;

        if(ny<0 || nx<0 || ny>=N || nx>=N){
            ndir = (ndir+2)%4;
            person[i].dir = ndir;
            person[i].y += dy[ndir];
            person[i].x += dx[ndir];
        }
        else{
            person[i].y += dy[ndir];
            person[i].x += dx[ndir];
        }
    }

    for(int i=0; i<M; ++i){
        if(visited_person[i] == true) continue;

        int ny = person[i].y;
        int nx = person[i].x;

        person_map[ny][nx].push_back(i);
    }

    return;
}

pair<int,int> find_dist(bool updown){
    
    int tmp = dist_q.front();
    dist_q.pop();

    if(dist_q.empty()){
        if(tmp+1 == N && updown){
            for(int i=0; i<(tmp)*6; ++i){
                dist_q.push(tmp);
                updown = false;
            }
        }
        else if(tmp - 1 == 0 && updown == false){
            for(int i=0; i<(tmp)*4; ++i){
                dist_q.push(tmp);
                updown = true;
            }
        }
        else{
            for(int i=0; i<(tmp+1)*2; ++i){
                if(updown)
                    dist_q.push(tmp+1);
                else
                    dist_q.push(tmp-1);
            }
        }

    }

    return make_pair(tmp,updown);

}

bool visited[MAX_N][MAX_N] = {false,};

void clear_visited(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            visited[i][j] = false;
        }
    }

    return;
}

pair<int,int> move_cap(bool updown, int cap_dir){
    
    cap_y += dy[cap_dir];
    cap_x += dx[cap_dir];

    int cap_ny = cap_y + dy[(cap_dir+1)%4];
    int cap_nx = cap_x + dx[(cap_dir+1)%4];

    if(!updown){
        cap_ny = cap_y + dy[cap_dir];
        cap_nx = cap_x + dx[cap_dir];
        if(cap_y == init_y && cap_x == init_x){
            clear_visited();
            cap_dir = (cap_dir+2)%4;
            updown = true;
        }
        else if(cap_ny<0 || cap_nx<0 || cap_ny>=N || cap_nx>=N){
            int tmp_dir = (cap_dir-1)%4;
            if(tmp_dir == -1) tmp_dir = 3;
            cap_dir = tmp_dir;
        }
        else if(visited[cap_ny][cap_nx]){
            int tmp_dir = (cap_dir-1)%4;
            if(tmp_dir == -1) tmp_dir = 3;
            cap_dir = tmp_dir;
        }
    }
    else if(updown && (visited[cap_ny][cap_nx] == false || (cap_y == 0 && cap_x == 0))){
        if(cap_y == 0 && cap_x == 0){
            clear_visited();
            cap_dir = (cap_dir+2)%4;
            updown = false;
        }
        else{
            cap_dir = (cap_dir+1)%4;
        }
    }
    
    return make_pair(updown,cap_dir);
}


bool check_boundry(int input_y, int input_x){
    if(input_y<0 || input_x<0 || input_y>=N || input_x>=N) return false;

    return true;
}

int check_map_person(int cap_dir){
    int cap_ny = cap_y;
    int cap_nx = cap_x;

    int get_count = 0;

    // while(check_boundry(cap_ny,cap_nx)){
    for(int i=0; i<3; ++i){
        if(tree_map[cap_ny][cap_nx] == 1){
            cap_ny += dy[cap_dir];
            cap_nx += dx[cap_dir];
            continue;
        }

        if(person_map[cap_ny][cap_nx].size()>0){
            for(int i=0; i<person_map[cap_ny][cap_nx].size(); ++i){
                if(visited_person[person_map[cap_ny][cap_nx][i]] == true) continue;
                visited_person[person_map[cap_ny][cap_nx][i]] = true;
                get_count++;
            }
        }
        cap_ny += dy[cap_dir];
        cap_nx += dx[cap_dir];
    }

    return get_count;
}

void run(){
    int dist = 0;
    bool updown = true;
    int curr = 0;
    int cap_dir = 0;

    visited[init_y][init_x] = true;

    for(int i=0; i<K; ++i){
        move_person();

        visited[cap_y][cap_x] = true;

        
        pair<int,int> tmp_pair_2 = move_cap(updown, cap_dir);
        updown = tmp_pair_2.first;
        cap_dir = tmp_pair_2.second;

        // cout<<cap_y+1<<","<<cap_x+1<<","<<updown<<","<<cap_dir<<endl;

        // cout<<"curr:"<<curr<<endl<<endl;

        int get_count = check_map_person(cap_dir%4);

        // cout<<"get_count:"<<get_count<<" count:"<<i+1<<" dir:"<<cap_dir<<endl;

        // print_person_map();

        total_score += (i+1) * get_count;
    }

    return;
}

void find_cap_pos(){
    cap_y = N/2, cap_x = N/2;

    init_y = cap_y;
    init_x = cap_x;
    return;
}

int main() {
    cin>>N>>M>>H>>K;

    for(int i=0; i<M; ++i){
        int tmp_y,tmp_x,tmp_dir;
        cin>>tmp_y>>tmp_x>>tmp_dir;
        person[i] = {tmp_y - 1, tmp_x - 1, tmp_dir};
    }

    for(int i=0; i<H; ++i){
        int tmp_y, tmp_x;
        cin>>tmp_y>>tmp_x;
        tree_map[tmp_y-1][tmp_x-1] = 1;
    }

    for(int i=0; i<2; ++i){
        dist_q.push(1);
    }

    find_cap_pos();

    run();

    cout<<total_score;

    return 0;
}