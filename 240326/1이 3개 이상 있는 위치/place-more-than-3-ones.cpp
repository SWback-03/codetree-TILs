#include <iostream>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    //격자가 주어진다.
    //각 칸 중 상하좌우 체크 필요, 1 숫자 갯수 3개 이상->세기
    //인접부분이 격자 벗어난 경우 숫자 0이 적혀있는것으로 판단
    //n+2크기 격자 만들고, 0으로 초기화하기
    int dy[4] = {1,-1,0,0};
    int dx[4] = {0,0,1,-1};
    
    int n;
    cin>>n;
    int map[102][102] = {0,};
    for(int i=1; i<n+1; ++i){
        for(int j=1; j<n+1; ++j){
            cin>>map[i][j];
        }
    }
    //입력값 받기 완료
    int total_cnt = 0;
    for(int i=1; i<n+1; ++i){
        for(int j=1; j<n+1; ++j){
            if(map[i][j]==0){
                int cnt = 0;
                for(int k=0; k<4; ++k){
                    int ny = i+dy[k];
                    int nx = j+dx[k];
                    if(map[ny][nx]==1){
                        cnt++;
                    }
                    if(cnt==3){
                        total_cnt++;
                    }
                }
            }
        }
    }
    cout<<total_cnt;
    return 0;
}