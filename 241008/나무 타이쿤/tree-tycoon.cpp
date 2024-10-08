#include <iostream>
#include <vector>
#include <cstring>

#define MAX_N 16
using namespace std;

int n,m;
int map[MAX_N][MAX_N] = {0,};
bool used[MAX_N][MAX_N] = {false,};
int dy[8] = {0,-1,-1,-1,0,1,1,1};
int dx[8] = {1,1,0,-1,-1,-1,0,1};

vector<pair<int,int>> health;

void print_map(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}

void move(int d, int p){
    for(auto& element : health){
        int y = element.first;
        int x = element.second;

        y = y + p * dy[d];
        x = x + p * dx[d];

        if(y<0)
            y += n;
        else if(y>=n)
            y -= n;
        if(x<0)
            x += n;
        else if(x>=n)
            x -= n;

        element.first = y;
        element.second = x;
    }
    return;
}

void grow(){
    for(auto element : health){
        map[element.first][element.second]++;
    }
    return;
}

void sub_grow(){
    int sub_map[MAX_N][MAX_N] = {0,};

    for(auto element : health){
        int y = element.first;
        int x = element.second;
        int count = 0;

        for(int i=1; i<8; i+=2){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;

            if(map[ny][nx] >= 1) count++;
        }
        sub_map[y][x] = count;
    }

    for(auto element : health){
        int y = element.first;
        int x = element.second;
        
        map[y][x] += sub_map[y][x];
    }

    return;
}

void clear_health(){
    for(auto element : health){
        used[element.first][element.second] = true;
    }
    vector<pair<int,int>> clear_tmp;
    health = clear_tmp;
    return;
}

void cut(){

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j] >= 2 && !used[i][j]){
                map[i][j] -= 2;
                health.push_back(make_pair(i,j));
            }
        }
    }

    memset(used,0,sizeof(used));

    return;
}

void run(int d, int p){

    move(d,p);

    grow();

    sub_grow();

    clear_health();

    cut();

    return;
}

int cal_height(){

    int total_height = 0;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            total_height += map[i][j];
        }
    }

    return total_height;
}

void init(){

    for(int i=n-2; i<n; ++i){
        for(int j=0; j<2; ++j){
            health.push_back(make_pair(i,j));
        }
    }

    return;
}

int main() {
    cin>>n>>m;

    init();

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>map[i][j];
        }
    }
    
    for(int i=0; i<m; ++i){
        int d, p;
        cin>>d>>p;
        run(d-1,p);
    }

    cout<<cal_height();


    return 0;
}