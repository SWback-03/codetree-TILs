#include <iostream>

#define MAX_N 20
using namespace std;

int n,m,k,c;
int map[MAX_N][MAX_N] = {0,};
int doubling_map[MAX_N][MAX_N] = {0,};
int clean_map[MAX_N][MAX_N] = {0,};

int dy[4] = {0,-1,0,1};
int dx[4] = {-1,0,1,0};
int ulter_dy[4] = {-1,-1,1,1};
int ulter_dx[4] = {-1,1,1,-1};

void print_map(){
    cout<<"map\n";
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    return;
}

void print_clean_map(){
    cout<<"clean\n";
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout<<clean_map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    return;
}

int grow_check(int i_y, int i_x){
    int tree_count = 0;

    for(int i=0; i<4; ++i){
        int ny = i_y + dy[i];
        int nx = i_x + dx[i];

        if(ny<0 || nx<0 || ny >=n || nx>=n) continue;
        if(clean_map[ny][nx]>0 || map[ny][nx]<=0) continue;

        if(map[ny][nx]>0){
            tree_count++;
        }
    }

    return tree_count;
}

void grow(){
    int tmp_map[MAX_N][MAX_N] = {0,};

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j]>0){
                tmp_map[i][j] = map[i][j] + grow_check(i,j);
            }
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j]>0 && tmp_map[i][j]>0){
                map[i][j] = tmp_map[i][j];
            }
        }
    }

    return;
}

void clear_doubling_map(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            doubling_map[i][j] = 0;
        }
    }
    return;
}

void doubling_check(int i_y, int i_x){
    int tree_count = 0;

    for(int i=0; i<4; ++i){
        int ny = i_y + dy[i];
        int nx = i_x + dx[i];

        if(ny<0 || nx<0 || ny >=n || nx>=n) continue;
        if(clean_map[ny][nx]>0 || map[ny][nx]<0) continue;

        if(map[ny][nx]==0){
            tree_count++;
        }
    }

    for(int i=0; i<4; ++i){
        int ny = i_y + dy[i];
        int nx = i_x + dx[i];

        if(ny<0 || nx<0 || ny >=n || nx>=n) continue;
        if(clean_map[ny][nx]>0 || map[ny][nx]<0) continue;

        if(map[ny][nx]==0){
            doubling_map[ny][nx] += (map[i_y][i_x])/tree_count;
        }
    }

    return;
}

void doubling(){

    clear_doubling_map();

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j]>0){
                doubling_check(i,j);
            }
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            map[i][j] += doubling_map[i][j];
        }
    }

    return;
}

int cal_clean(int i_y, int i_x){
    int count = 0;
    count += map[i_y][i_x];

    for(int i=0; i<4; ++i){
        for(int j=1; j<=k; ++j){
            int ny = i_y + j*ulter_dy[i];
            int nx = i_x + j*ulter_dx[i];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(map[ny][nx]<0) break;

            count += map[ny][nx];
            if(map[ny][nx]==0) break;
        }
    }

    return count;
}

int clean_do(int i_y, int i_x){
    int cleaned_tree = map[i_y][i_x];

    clean_map[i_y][i_x] = c+1;
    map[i_y][i_x] = 0;
    for(int i=0; i<4; ++i){
        for(int j=1; j<=k; ++j){
            int ny = i_y + j*ulter_dy[i];
            int nx = i_x + j*ulter_dx[i];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(map[ny][nx]<0) break;

            clean_map[ny][nx] = c+1;
            if(map[ny][nx]>0) cleaned_tree += map[ny][nx];

            if(map[ny][nx]==0) break;
            map[ny][nx] = 0;
            
        }
    }

    return cleaned_tree;
}

int clean_pos(){
    int max_val = -1;
    int max_y = 0;
    int max_x = 0;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(map[i][j]>0){
                int tmp_clean = cal_clean(i,j);
                if(max_val<tmp_clean){
                    max_val = tmp_clean;
                    max_y = i, max_x = j;
                }
                else if(max_val == tmp_clean){
                    if(max_y > i){
                        // cout<<"1--------------------------\n";
                        max_y = i, max_x = j;
                    }
                    else if(max_y == i){
                        if(max_x > j){
                            // cout<<"2--------------------------\n";
                            max_y = i, max_x = j;
                        }
                    }
                }
            }
        }
    }

    return clean_do(max_y, max_x);
}

void clean_did(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(clean_map[i][j]>0) clean_map[i][j]--;
        }
    }
    return;
}

void run(){
    int total_cleaned_trees = 0;

    for(int i=0; i<m; ++i){
        grow();

        doubling();

        // print_map();

        total_cleaned_trees += clean_pos();

        clean_did();

        // print_map();

        // print_clean_map();
    }

    cout<<total_cleaned_trees;

    return;
}

int main() {
    cin>>n>>m>>k>>c;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>map[i][j];
        }
    }

    run();

    return 0;
}