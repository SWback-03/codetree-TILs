#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

int N, M;

int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, -1, 1, 1, -1};
char map[50][50];

int find_word(int y, int x){
    int val = 0;
    if(map[y][x] == 'L'){
        for(int i=0; i<8; ++i){
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny>=N || ny<0 || nx>=M || nx<0){
                continue;
            }
            if(map[ny][nx] == 'E'){
                int nny = ny + dy[i];
                int nnx = nx + dx[i];
                if(nny>=N || nny<0 || nnx>=M || nnx<0){
                    continue;
                }
                if(map[nny][nnx] == 'E'){
                    // cout<<"x,y: "<<x<<","<<y<<","<<map[y][x]<<"\n";
                    // cout<<"nx,ny: "<<nx<<","<<ny<<","<<map[ny][nx]<<"\n";
                    // cout<<"nnx,nny: "<<nnx<<","<<nny<<","<<map[nny][nnx]<<"\n";
                    val++;
                }
                else
                    continue;
            }
            else
                continue;
        }
        return val;
    }
    else
        return 0;
}

int main() {
    cin>>N>>M;
    
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            cin>>map[i][j];
        }
    }

    int result = 0;
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            result += find_word(i,j);
        }
    }

    cout<<result;

    return 0;
}