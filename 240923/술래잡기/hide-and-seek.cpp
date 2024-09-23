#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX_N 100
#define MAX_M 10000
using namespace std;

struct thief{
    int y;
    int x;
    int dir;
};

int N,M,H,K;
vector<int> person_map[MAX_N][MAX_N];
int tree_map[MAX_N][MAX_N] = {0,};
vector<thief> person(MAX_M);
bool visited_person[MAX_M] = {false,};

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

            bool doing = true;
            for(auto element : person_map[i][j]){
                cout<<element+1<<" ";
                doing = false;
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

    // print_person_map();

    return;
}

pair<int,int> find_dist(int count, int dist, bool updown){

    if(count%2 == 0){
        if(updown == true){
            dist++;
            if(dist == N){
                dist--;
                updown = false;
            }
        }
        else{
            dist--;
            if(dist == 0){
                dist++;
                updown = true;
            }
        }
    }

    return make_pair(dist, updown);
}

pair<int,int> move_cap(int curr, int dist, int cap_dir){

    if(curr == dist){
        curr = 0;
        cap_dir = (cap_dir+1)%4;
    }

    cap_y += dy[cap_dir];
    cap_x += dx[cap_dir];

    curr++;

    return make_pair(curr, cap_dir);
}

bool check_boundry(int input_y, int input_x){
    if(input_y<0 || input_x<0 || input_y>=N || input_x>=N) return false;

    return true;
}

int check_map_person(int cap_dir){
    int cap_ny = cap_y;
    int cap_nx = cap_x;

    int get_count = 0;

    while(check_boundry(cap_ny,cap_nx)){
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

    

    for(int i=0; i<K; ++i){
        move_person();

        pair<int,int> tmp_pair_1 = find_dist(i, dist, updown);
        dist = tmp_pair_1.first;
        updown = tmp_pair_1.second;

        // cout<<dist<<"/"<<updown<<endl;

        pair<int,int> tmp_pair_2 = move_cap(curr, dist, cap_dir);
        curr = tmp_pair_2.first;
        cap_dir = tmp_pair_2.second;

        int get_count = check_map_person((cap_dir+1)%4);

        // cout<<"get_count:"<<get_count<<"count:"<<i<<endl;

        // print_person_map();

        total_score += (i+1) * get_count;
    }

    return;
}

void find_cap_pos(){
    cap_y = N/2, cap_x = N/2;
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

    find_cap_pos();

    run();

    cout<<total_score;

    return 0;
}