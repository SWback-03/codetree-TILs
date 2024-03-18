#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int R, C;
    cin>>R>>C;
    char arr[15][15];
    for(int i=0; i<R; ++i){
        for(int j=0; j<C; ++j){
            cin>>arr[i][j];
        }
    }

    char current_val = arr[0][0];
    char end_val = arr[R-1][C-1];
    int cnt = 0;
    if(current_val != end_val){
    for(int i=1; i<R-2; ++i){
        for(int j=1; j<C-2; ++j){
            if(arr[i][j] != current_val){
                char current_val_2 = arr[i][j];
                for(int k = i+1; k<R-1; ++k){
                    for(int l=j+1; l<C-1; ++l){
                        if(arr[k][l] != current_val_2){
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    cout<<cnt;
    }
    return 0;
}