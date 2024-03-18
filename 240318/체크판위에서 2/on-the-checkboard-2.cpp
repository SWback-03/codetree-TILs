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
    int cnt = 0;
    //cout<<"hello\n";
    for(int i=1; i<R-2; ++i){
        //cout<<"hello\n";
        for(int j=1; j<C-2; ++j){
            if(arr[i][j] != current_val){
                current_val = arr[i][j];
                for(int k = i+1; k<R-1; ++k){
                    for(int l=j+1; l<C-1; ++l){
                        if(arr[k][l] != current_val){
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    cout<<cnt;
    return 0;
}