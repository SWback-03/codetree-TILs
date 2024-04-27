#include <iostream>

using namespace std;

int n, m;

char arr[50][50] = {0,};

int dy[8] = {-1, 0, 1, 0, 1, -1, 1, -1};
int dx[8] = {0, -1, 0, 1, 1, -1, -1, 1};

int main() {
    // 여기에 코드를 작성해주세요.

    cin>>n>>m;

    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin>>arr[i][j];
        }
    }

    // for(int i=0; i<n; ++i){
    //     for(int j=0; j<m; ++j){
    //         cout<<arr[i][j];
    //     }
    //     cout<<'\n';
    // }

    // if(arr[0][0]=='T') cout<<"true\n";
    // else cout<<"false\n";

    int cnt = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(arr[i][j] == 'L'){
                //cout<<"find\n";
                for(int k=0; k<8; ++k){
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                    if((ny>=0 && nx >=0 && ny<n && nx<m)&&arr[ny][nx]=='E'){
                        ny = ny + dy[k];
                        nx = nx + dx[k];
                        if((ny>=0 && nx >=0 && ny<n && nx<m)&&arr[ny][nx]=='E'){
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