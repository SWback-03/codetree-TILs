#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX_N 21
using namespace std;

int n, m;

int map[MAX_N][MAX_N] = {0,};
bool visited[MAX_N][MAX_N] = {false,};
int dy[4] = {0,-1,0,1};
int dx[4] = {1,0,-1,0};

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

void rotate(){
    int tmp_map[MAX_N][MAX_N] = {0,};
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            tmp_map[n-1-j][i] = map[i][j];
        }
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            map[i][j] = tmp_map[i][j];
        }
    }
    return;
}

void clear_red_visited(){

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j] == 0) visited[i][j] = false;
        }
    }
    return;
}

pair<int,int> find_condition(vector<pair<int,int>> input_vec){
    sort(input_vec.begin(), input_vec.end());
    // int max_y = input_vec[0].first;
    // int min_x = input_vec[0].second;
    int max_y = -1;
    int min_x = n+1;
    for(auto element : input_vec){
        if(map[element.first][element.second] == 0) continue;
        // if(element.first >= max_y && element.second < min_x){
        //     max_y = element.first;
        //     min_x = element.second;
        // }
        if(element.first > max_y){
            max_y = element.first;
            min_x = element.second;
        }
        else if(element.first == max_y){
            if(element.second < min_x){
                max_y = element.first;
                min_x = element.second;
            }
        }
    }
    // cout<<"y,x:"<<max_y<<","<<min_x<<endl;
    return make_pair(max_y, min_x);
}

bool check(){

    int count = 0;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j]<=0) continue;
            int tmp_count = 1;
            for(int k=0; k<4; ++k){
                int y = i + dy[k];
                int x = j + dx[k];
                if(y<0 || x<0 || y>=n || x>=n) continue;
                if(map[y][x] == map[i][j] || map[y][x] == 0){
                    tmp_count++;
                }
            }
            count = max(count, tmp_count);
        }
    }
    if(count >= 2) return true;
    else return false;
}

int whole_dfs(){

    int max_val = 0, red_count = 0, max_y = 0, max_x = n+1;
    vector<pair<int,int>> result_vec;
    memset(visited,false,sizeof(visited));
    
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(visited[i][j] || map[i][j] <= 0) continue;
            queue<pair<int,int>> tmp_q;
            vector<pair<int,int>> tmp_vec;
            int tmp_red_count = 0;
            int count = 1;

            tmp_q.push(make_pair(i,j));
            tmp_vec.push_back(make_pair(i,j));
            visited[i][j] = true;

            while(!tmp_q.empty()){
                int y = tmp_q.front().first;
                int x = tmp_q.front().second;
                tmp_q.pop();

                for(int k=0; k<4; ++k){
                    int ny = y + dy[k];
                    int nx = x + dx[k];
                    if(ny<0 || nx<0 || ny>=n || nx>=n || visited[ny][nx]) continue;
                    if(map[ny][nx] == map[i][j] || map[ny][nx] == 0){
                        if(map[ny][nx] == 0) tmp_red_count++;
                        tmp_q.push(make_pair(ny,nx));
                        tmp_vec.push_back(make_pair(ny,nx));
                        visited[ny][nx] = true;
                        count++;
                    }
                }
            }
            pair<int,int> tmp_pair = find_condition(tmp_vec);
            if(tmp_vec.size() > max_val){
                max_val = tmp_vec.size();
                red_count = tmp_red_count;
                max_y = tmp_pair.first, max_x = tmp_pair.second;
                result_vec = tmp_vec;
            }
            else if(tmp_vec.size() == max_val){
                if(tmp_red_count < red_count){
                    red_count = tmp_red_count;
                    max_y = tmp_pair.first, max_x = tmp_pair.second;
                    result_vec = tmp_vec;
                }
                else if(tmp_red_count == red_count){
                    // cout<<"i,j:"<<i<<","<<j<<endl;
                    // pair<int,int> tmp_pair = find_condition(tmp_vec);
                    if(max_y < tmp_pair.first){
                        max_y = tmp_pair.first, max_x = tmp_pair.second;
                        result_vec = tmp_vec;
                    }
                    else if(max_y == tmp_pair.first && max_x > tmp_pair.second){
                        max_y = tmp_pair.first, max_x = tmp_pair.second;
                        result_vec = tmp_vec;
                    }
                }
            }
            clear_red_visited();

            
        }
    }

    // //////
    // for(auto element : result_vec){
    //     cout<<element.first<<","<<element.second<<endl;
    // }
    // cout<<endl;

    for(auto element : result_vec){
        map[element.first][element.second] = -2;
    }

    return result_vec.size();
}

void go_down(){
    // int tmp_map[MAX_N][MAX_N] = {0,};
    for(int i=n-1; i>0; --i){
        for(int j=0; j<n; ++j){
            if(map[i][j] == -1) continue;
            if(map[i][j] == -2){
                for(int k=i-1; k>=0; --k){
                    if(map[k][j] == -1) break;
                    if(map[k][j] >= 0){
                        map[i][j] = map[k][j];
                        map[k][j] = -2;
                        
                        break;
                    }
                }
            }
        }
    }
}

void run(){
    int result = 0;
    while(1){
        if(!check()) break;
        int C = whole_dfs();
        // print_map();
        go_down();
        // print_map();
        rotate();
        // print_map();
        go_down();
        // print_map();
        result += (C*C);
    }
    cout<<result;
}

int main() {
    cin>>n>>m;
    
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>map[i][j];
        }
    }

    run();

    return 0;
}