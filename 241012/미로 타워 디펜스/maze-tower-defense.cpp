#include <iostream>
#include <vector>

#define MAX_N 26
using namespace std;

struct monster{
    int val, map_y, map_x;
};

int n,m;
int map[MAX_N][MAX_N] = {0,};

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int total_val = 0;

monster arr[MAX_N * MAX_N] = {0,};

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

void attack(int d, int p){
    int mid_y = n/2;
    int mid_x = n/2;
    for(int i=1; i<=p; ++i){
        int y = mid_y + i * dy[d];
        int x = mid_x + i * dx[d];
        if(map[y][x]>0) total_val += map[y][x];
        // cout<<"d,p:"<<d<<","<<p<<endl;
        // cout<<"deleted:"<<map[y][x]<<endl;
        map[y][x] = 0;
    }
    return;
}

void shorten(){

    vector<int> vec;
    for(int i=0; i<n*n-1; ++i){
        if(arr[i].val > 0) vec.push_back(arr[i].val);
    }
    for(int i=0; i<MAX_N * MAX_N; ++i){
        arr[i].val = 0;
    }
    for(int i=0; i<vec.size(); ++i){
        arr[i].val = vec[i];
    }

    return;
}

void make_arr(){

    int mid_y = n/2;
    int mid_x = n/2;

    int cur_y = mid_y;
    int cur_x = mid_x;

    int index = 2;
    int count = 1;
    bool tmp_bool = false;
    int arr_count = 0;

    for(int i=0; i<=2*(n-1); ++i){
        
        for(int i=0; i<count; ++i){
            cur_y = cur_y + dy[index];
            cur_x = cur_x + dx[index];
            // cout<<cur_y<<","<<cur_x<<endl;
            arr[arr_count] = {map[cur_y][cur_x],cur_y,cur_x};
            arr_count++;
        }
        if(i == 2*(n-1)-1){
            index--;
            if(index<0) index = 3;
            continue;
        }
        if(tmp_bool == false){
            tmp_bool = true;
        }
        else{
            tmp_bool = false;
            count++;
        }
        index--;
        if(index<0) index = 3;
    }

    return;
}

bool repeat(){

    int repeat_count = 1;
    int prev_val = arr[0].val;

    bool enable = false;

    for(int i=1; i<n*n-1; ++i){
        if(arr[i].val == prev_val && prev_val > 0){
            repeat_count++;
        }
        else{
            if(repeat_count >= 4){
                for(int j = 1; j<=repeat_count; ++j){
                    total_val += arr[i-j].val;
                    // cout<<"deleted:"<<arr[i-j].val<<endl;
                    arr[i-j].val = 0;
                }
                enable = true;
            }
            repeat_count = 1;
            prev_val = arr[i].val;
        }
    }

    if(repeat_count >= 4){
        for(int j = 0; j<repeat_count; ++j){
            total_val += arr[n*n-2-j].val;
            arr[n*n-2-j].val = 0;
        }
        enable = true;
    }

    return enable;
}

void longer(){

    int num_count = 1;
    int cur_val = arr[0].val;
    vector<int> tmp_vec;

    for(int i=1; i<n*n-1; ++i){
        // if(arr[i].val == 0) break;
        int prev_val = cur_val;
        cur_val = arr[i].val;

        if(prev_val == cur_val) num_count++;
        else if(prev_val == 0) continue;
        else{
            tmp_vec.push_back(num_count);
            tmp_vec.push_back(prev_val);
            num_count = 1;
        }

    }

    for(int i=0; i<MAX_N * MAX_N; ++i){
        arr[i].val = 0;
    }
    for(int i=0; i<tmp_vec.size(); ++i){
        arr[i].val = tmp_vec[i];
    }

    for(int i=n*n-1; i<MAX_N; ++i){
        arr[i].val = 0;
    }

    return;
}

void roll_back(){

    int tmp_map[MAX_N][MAX_N] = {0,};

    for(int i=0; i<n*n-1; ++i){
        tmp_map[arr[i].map_y][arr[i].map_x] = arr[i].val;
    }
    // map = tmp_map;

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            map[i][j] = 0;
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            map[i][j] = tmp_map[i][j];
        }
    }

    return;
}

void clear_arr(){
    for(int i=0; i<MAX_N*MAX_N; ++i){
        arr[i].val = 0;
    }
    return;
}

void run(int d, int p){
    clear_arr();

    attack(d,p);

    // print_map();

    make_arr();

    // if(d==1 && p ==3){
    //     for(int i=0; i<n*n-1; ++i){
    //         cout<<arr[i].val<<" ";
    //     }
    //     cout<<endl;
    // }

    // if(d==1 && p ==3){
    //     print_map();
    // }

    while(1){
        shorten();

        // if((d==1 && p ==3)){
        //     for(int i=0; i<n*n-1; ++i){
        //         cout<<arr[i].val<<" ";
        //     }
        //     cout<<endl;
        // }

        if(!repeat()) break;
    }

    // if((d==2 && p ==2)){
    //         for(int i=0; i<n*n-1; ++i){
    //             cout<<arr[i].val<<" ";
    //         }
    //         cout<<endl;
    //     }

    longer();

    // if((d==2 && p ==2)){
    //         for(int i=0; i<n*n-1; ++i){
    //             cout<<arr[i].val<<" ";
    //         }
    //         cout<<endl;
    //     }

    roll_back();

    // if(d==2 && p ==2){
    //     print_map();
    // }

    // print_map();

    // cout<<total_val<<endl;

}

int main() {

    cin>>n>>m;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin>>map[i][j];
        }
    }

    for(int i=0; i<m; ++i){
        int d,p;
        cin>>d>>p;
        run(d,p);
    }

    cout<<total_val;

    return 0;
}