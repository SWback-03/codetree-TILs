#include <iostream>
using namespace std;

#define max_point 10001

int arr[max_point][max_point] = {0};

int main() {
    int N;
    cin>>N;

    for(int i=0; i<N; ++i){
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        for(int x = x1; x<x2; ++x){
            for(int y = y2; y<y1; ++y){
                arr[y][x] = 1;
            }
        }
    }

    int count = 0;

    for(int i=0; i<max_point; ++i){
        for(int j=0; j<max_point; ++j){
            if(arr[i][j]>0){
                count++;
                
            }
        }
    }

    cout<< count;

    return 0;
}