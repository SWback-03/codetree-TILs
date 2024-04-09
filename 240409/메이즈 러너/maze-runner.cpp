#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

int n,m,k,exit_y,exit_x;

struct candidate{
    int first;
    int second;
    int state;
};

vector<candidate> cand;

int map[12][12] = {0,};

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

int total_dist = 0;

int calc(int y1, int x1, int y2, int x2){
    return abs(y2-y1)+abs(x2-x1);
}

void move(){
    for(int i=0; i<cand.size(); ++i){
        if(cand[i].state == 1) continue;
        int curr_y = cand[i].first;
        int curr_x = cand[i].second;
        int min_dist = calc(exit_y,exit_x,curr_y,curr_x);
        for(int j=0; j<4; ++j){
            int ny = curr_y + dy[j];
            int nx = curr_x + dx[j];
            int curr_dist = calc(exit_y,exit_x,ny,nx);
            if(curr_dist<=min_dist && map[ny][nx] == 0){
                min_dist = curr_dist;
                cand[i].first = ny;
                cand[i].second = nx;
                if(ny == exit_y && nx == exit_x){
                    cand[i].state = 1;
                }
            }
            if(j==3 && (cand[i].first != curr_y || cand[i].second != curr_x)){
                total_dist++;
            }
        }
    }
}

int find_min(int y, int x){
    int width = abs(exit_x - x);
    int height = abs(exit_y - y);
    if(width>=height) return width;
    else return height;
}

int r, c, min_rect;

void make_rect(int ny, int nx, int rect_size){
    int y, x;
    if(ny<exit_y){
        y = exit_y - rect_size;
    }
    else{
        y = ny - rect_size;
    }
    if(nx<exit_x){
        x = exit_x - rect_size;
    }
    else{
        x = nx - rect_size;
    }
    r = y;
    c = x;

    if(r<=0){
        r = 1;
    }
    if(c<=0){
        c = 1;
    }
    min_rect = rect_size;
}

void rect(){
    int max_size = 20;
    int y, x;
    for(int i=0; i<cand.size(); ++i){
        if(cand[i].state == 1) continue;
        int ny = cand[i].first;
        int nx = cand[i].second;
        int rect_size = find_min(ny, nx);
        if(rect_size<max_size){
            max_size = rect_size;
            y = ny;
            x = nx;
            make_rect(y,x,max_size);
        }
        else if(rect_size == max_size){
            make_rect(y,x,max_size);
            int y1 = r;
            int x1 = c;
            make_rect(ny,nx,max_size);
            int y2 = r;
            int x2 = c;

            if(y1<y2){
                r = y1;
                c = x1;
            }
            else if(y2<y1){
                r = y2;
                c = x2;
            }
            else{
                if(x1<x2){
                r = y1;
                c = x1;
                }
                else if(x2<x1){
                    r = y2;
                    c = x2;
                }
            }
        }

    }

    // cout<<"r, c, min_rect, exit: "<< r<<" "<< c<<" "<< min_rect<<" "<<exit_y<<" "<<exit_x<<"\n";
}

void rotate(){
    //맵 회전
    int temp_map[12][12] = {0,};
    int temp_y = r-1;
    int temp_x = c-1;
    for(int i=0; i<=min_rect; ++i){
        for(int j=0; j<=min_rect; ++j){ //r, c, min_rect 기준 회전
            //temp_map[c+j][min_rect-i+r] = map[r+i][c+j];
            temp_map[r+j][c+min_rect-i] = map[r+i][c+j];
        }
    }
    
    for(int i=r; i<=r+min_rect; ++i){
        for(int j=c; j<=c+min_rect; ++j){
            map[i][j] = temp_map[i][j];
            if(map[i][j]>0)
                map[i][j]--;
        }
    }
    //사람 회전
    for(int k=0; k<cand.size(); ++k){
        if(cand[k].state == 1) continue;
        int cand_map[12][12] = {0,};
        memset(temp_map,0,sizeof(temp_map));
        int y = cand[k].first;
        int x = cand[k].second;
        cand_map[y][x] = 1;
        if(y>=r && y<=r+min_rect && x>=c && x<=c+min_rect){
            //cout<<"person checked\n";
            for(int i=0; i<=min_rect; ++i){
                for(int j=0; j<=min_rect; ++j){ //r, c, min_rect 기준 회전
                    //temp_map[c+j][min_rect-i+r] = cand_map[r+i][c+j];
                    temp_map[r+j][c+min_rect-i] = cand_map[r+i][c+j];
                }
            }
            for(int i=r; i<=r+min_rect; ++i){
                for(int j=c; j<=c+min_rect; ++j){
                    if(temp_map[i][j] == 1){
                        cand[k].first = i;
                        cand[k].second = j;
                        //cout<<"person rotate\n";
                    }
                }
            }
        }
    }

    //exit 회전
    int exit_map[12][12] = {0,};
    memset(temp_map,0,sizeof(temp_map));
    exit_map[exit_y][exit_x] = 1;
    for(int i=0; i<=min_rect; ++i){
        for(int j=0; j<=min_rect; ++j){ //r, c, min_rect 기준 회전
            //temp_map[c+j][min_rect-i+r] = exit_map[r+i][c+j];
            temp_map[r+j][c+min_rect-i] = exit_map[r+i][c+j];
        }
    }
    for(int i=r; i<=r+min_rect; ++i){
        for(int j=c; j<=c+min_rect; ++j){
            if(temp_map[i][j] == 1){
                exit_y = i;
                exit_x = j;
            }
        }
    }

}



int main() {
    cin>>n>>m>>k;
    for(int i=0; i<=11; ++i){
        for(int j=0; j<=11; ++j){
            map[i][j] = 101;
        }
    }
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            cin>>map[i][j];
        }
    }
    for(int i=0; i<m; ++i){
        int tmp1, tmp2;
        cin>>tmp1>>tmp2;
        cand.push_back({tmp1,tmp2,0});
    }
    cin>>exit_y>>exit_x;


    

    for(int i=0; i<k; ++i){
        //move
        move();

        

        //rect
        rect();

        
        //rotate
        rotate();

        // cout<<"r, c, min_rect, exit: "<< r<<" "<< c<<" "<< min_rect<<" "<<exit_y<<" "<<exit_x<<"\n";

        // for(int i=1; i<=n; ++i){
        //     for(int j=1; j<=n; ++j){
        //         cout<<map[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";

        // int temporary[12][12] ={0,};
        // for(int i=0; i<cand.size(); ++i){
        //     if(cand[i].state == 1) continue;
        //     int y = cand[i].first;
        //     int x = cand[i].second;
        //     temporary[y][x] = 1;
        // }
        // for(int i=1; i<=n; ++i){
        //     for(int j=1; j<=n; ++j){
        //         cout<<temporary[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";


    }

    cout<<total_dist<<"\n"<<exit_y<<" "<<exit_x;

    
    return 0;
}