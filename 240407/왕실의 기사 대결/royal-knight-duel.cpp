#include <iostream>
#include <vector>
#include <cstring>
#include <stack>

using namespace std;

struct knight_info{
    int y;
    int x;
    int health;
    int conflict = 0;
    int damage = 0;
};

vector<pair<int,int>> knight_loc[31];

struct knight_info knight[31] = {0,};

int dy[4] = {-1,0,1,0}; //상우하좌
int dx[4] = {0,1,0,-1};

int l,n,q;

stack<int> stk;
stack<int> temp_stk;

int check_knight[31] = {0,};

int map[42][42] = {0,};
int knight_map[42][42] = {0,};

// void push(int number, int d){
//     for(int i=0; i<knight_loc[number].size(); ++i){
//         knight_loc[number][i].first += dy[d];
//         knight_loc[number][i].second += dx[d];
//     }

//     for(int i=0; i<knight_loc[king_i].size(); ++i){
//         //기사 맨처음 이동, 벽 있었으면 복귀
//         if(map[knight_loc[king_i][i].first][knight_loc[king_i][i].second] == 2){ //맵 해당위치 벽일때
//             for(int i=0; i<knight_loc[king_i].size(); ++i){
//                 knight_loc[king_i][i].first -= dy[d];
//                 knight_loc[king_i][i].second -= dx[d];
//             }//기사 원상 복귀
//             return;
//         }
//     }

//     //기사 벽 없을 때

//     for(int i=0; i<knight_loc[king_i].size(); ++i){
//         if(knight_map[knight_loc[king_i][i].first][knight_loc[king_i][i].second] != king_i){
//             if(knight_map[knight_loc[king_i][i].first][knight_loc[king_i][i].second] != 0){ // 이동한 기사맵에 다른 기사 있을때
//                 int ano_knight = knight_map[knight_loc[king_i][i].first][knight_loc[king_i][i].second]; //다른기사 번호 저장
//                 push(ano_knight,d);
//             }
//         }
//     }
// }

// void move_knight(int king_i, int d){

//     memset(check_knight,0,sizeof(check_knight));//check_knight 초기화, 수정 필요할수도

//     int flag = 0; //복귀 플래그
//     for(int i=0; i<knight_loc[king_i].size(); ++i){
//         knight_loc[king_i][i].first += dy[d];
//         knight_loc[king_i][i].second += dx[d];
//     }//기사 이동

//     for(int i=0; i<knight_loc[king_i].size(); ++i){
//         //기사 맨처음 이동, 벽 있었으면 복귀
//         if(map[knight_loc[king_i][i].first][knight_loc[king_i][i].second] == 2){ //맵 해당위치 벽일때
//             for(int i=0; i<knight_loc[king_i].size(); ++i){
//                 knight_loc[king_i][i].first -= dy[d];
//                 knight_loc[king_i][i].second -= dx[d];
//             }//기사 원상 복귀

//             flag = 1;
//             break;
//         }
//     }

//     if(flag == 1) return; //벽있었으면 함수 탈출

//     //맨처음 기사 벽 없을 때


//     for(int i=0; i<knight_loc[king_i].size(); ++i){
//         if(knight_map[knight_loc[king_i][i].first][knight_loc[king_i][i].second] != king_i){
//             if(knight_map[knight_loc[king_i][i].first][knight_loc[king_i][i].second] != 0){ // 이동한 기사맵에 다른 기사 있을때
//                 int ano_knight = knight_map[knight_loc[king_i][i].first][knight_loc[king_i][i].second]; //다른기사 번호 저장
//                 if(check_knight[ano_knight] == 0){
//                     check_knight[ano_knight] = 1; //다른 기사들 번호 저장됨
//                 }
//             }
//         }
//     }

//     for(int i=1; i<=n; ++i){ 
//         if(check_knight[i] == 1){ //마주친 다른 기사들 push
//             //push(i,d);
//             while(1){
//                 knight_loc[i].first += dy[d];
//                 knight_loc[i].second += dx[d];
//                 for(int j=0; j<knight_loc[i].size(); ++j){

//                 }
//         }
//     }
//     }

    
    
// }

void move(int king_i,int d){


    stk.push(king_i);

    while(!stk.empty()){

    int temp = stk.top();
    temp_stk.push(temp);

    for(int i=0; i<knight_loc[temp].size(); ++i){
        
        knight_loc[temp][i].first += dy[d];
        knight_loc[temp][i].second += dx[d];
        
    }//기사 이동
    stk.pop();

    //벽있을 때
    for(int i=0; i<knight_loc[temp].size(); ++i){
        if(map[knight_loc[temp][i].first][knight_loc[temp][i].second] == 2){
            while(!temp_stk.empty()){
                temp = temp_stk.top();
                for(int j=0; j<knight_loc[temp].size(); ++j){
                    knight_loc[temp][j].first -= dy[d];
                    knight_loc[temp][j].second -= dx[d];
                    knight[temp].conflict = 0;
                }
                temp_stk.pop();
            }
            return;
        }
    }

    for(int i=0; i<knight_loc[temp].size(); ++i){
        if(knight_map[knight_loc[temp][i].first][knight_loc[temp][i].second] != temp){
            if(knight_map[knight_loc[temp][i].first][knight_loc[temp][i].second] != 0){ // 이동한 기사맵에 다른 기사 있을때
                int ano_knight = knight_map[knight_loc[temp][i].first][knight_loc[temp][i].second]; //다른기사 번호 저장
                knight[ano_knight].conflict = 1; //충돌 확인
                stk.push(ano_knight); //다른 기사 번호 저장됨
                
            }
        }
    }
    
    } //이동 완료

    memset(knight_map,0,sizeof(knight_map)); //기사맵 초기화
    for(int i=1; i<=n; ++i){
        for(int j=0; j<knight_loc[i].size(); ++j){
            if(knight[i].health>0)
            {knight_map[knight_loc[i][j].first][knight_loc[i][j].second] = i;}
        }
    } //맵 다시 생성

    for(int i=1; i<=n; ++i){
        if(knight[i].conflict == 1){
            for(int j=0; j<knight_loc[i].size(); ++j){
                if(map[knight_loc[i][j].first][knight_loc[i][j].second] == 1){
                    knight[i].health--;
                    knight[i].damage++;
                }
            }
        }
    }//체력 함정 확인

    memset(knight_map,0,sizeof(knight_map)); //기사맵 초기화
    for(int i=1; i<=n; ++i){
        for(int j=0; j<knight_loc[i].size(); ++j){
            if(knight[i].health>0)
            {knight_map[knight_loc[i][j].first][knight_loc[i][j].second] = i;}
        }
    } //맵 다시 생성

    for(int i=1; i<=n; ++i){
        if(knight[i].conflict == 1){
            knight[i].conflict = 0;
        }
    }//체력 함정 확인

    // //맵 생성 확인
    // for(int i=1; i<=l; ++i){
    //     for(int j=1; j<=l; ++j){
    //         cout<<knight_map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"damage: "<<knight[1].damage<<" "<<knight[2].damage<<" "<<knight[3].damage<<" ";
    // //맵 생성 확인


}

int main() {
    cin>>l>>n>>q;

    for(int i=0; i<=l+1; ++i){
        for(int j=0; j<=l+1; ++j){
            map[i][j] = 2;
        }
    }

    for(int i=1; i<=l; ++i){
        for(int j=1; j<=l; ++j){
            cin>>map[i][j];
        }
    }
    //맵 생성

    // //맵 생성 확인
    // for(int i=0; i<=l+1; ++i){
    //     for(int j=0; j<=l+1; ++j){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // //맵 생성 확인

    int r,c,h,w,k;
    for(int i=1; i<=n; ++i){
        cin>>r>>c>>h>>w>>k;
        knight[i].y = r;
        knight[i].x = c;
        knight[i].health = k;
        // int cnt = 0;
        for(int j=0; j<h; ++j){
            for(int k=0; k<w; ++k){
                knight_map[r+j][c+k] = i;
                knight_loc[i].push_back({r+j,c+k});

                // cout<<knight_loc[i][cnt].first<<" ";
                // cout<<knight_loc[i][cnt].second<<"\n";
                // cnt++;
            }
        }

    }
    //기사 맵 생성
    // //맵 생성 확인
    // for(int i=1; i<=l; ++i){
    //     for(int j=1; j<=l; ++j){
    //         cout<<knight_map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // //맵 생성 확인

    int king_i, d;
    for(int i=0; i<q; ++i){
        cin>>king_i>>d;
        move(king_i,d);
        //cout<<"\n";
    }

    int total_damage = 0;
    for(int i=1; i<=n; ++i){
        if(knight[i].health>0){
            total_damage += knight[i].damage;
        }
    }

    cout<<total_damage;

    return 0;
}