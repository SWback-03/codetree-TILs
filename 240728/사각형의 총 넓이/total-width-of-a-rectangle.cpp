#include <iostream>
using namespace std;

#define max_point 20001

bool arr[max_point][max_point] = {false};

int main() {
    int N;
    cin>>N;

    for(int i=0; i<N; ++i){
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        x1 = x1+10000;
        y1 = y1+10000;
        x2 = x2+10000;
        y2 = y2+10000;
        for(int x = x1; x<x2; ++x){
            for(int y = y2; y<y1; ++y){
                arr[y][x] = true;
            }
        }
    }

    int count = 0;

    for(int i=0; i<max_point; ++i){
        for(int j=0; j<max_point; ++j){
            if(arr[i][j]==true){
                count++;
                
            }
        }
    }

    cout<< count;

    return 0;
}