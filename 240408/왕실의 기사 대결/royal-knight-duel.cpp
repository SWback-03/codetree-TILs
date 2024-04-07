#include <iostream>
#include <vector>
#include <cstring>
#include <stack>

using namespace std;

struct knight_info {
    int y;
    int x;
    int health;
    int conflict = 0;
    int damage = 0;
};

vector<pair<int, int>> knight_loc[31];

struct knight_info knight[31] = { 0, };

int dy[4] = { -1,0,1,0 }; //상우하좌
int dx[4] = { 0,1,0,-1 };

int l, n, q;

stack<int> stk;
stack<int> temp_stk;

int check_knight[31] = { 0, };

int map[42][42] = { 0, };
int knight_map[42][42] = { 0, };


void move(int king_i, int d) {

    stk = stack<int>();
    temp_stk = stack<int>();

    stk.push(king_i);

    

    int count = 0;

    while (!stk.empty()) {

        count++;

        int temp = stk.top();
        stk.pop();

        temp_stk.push(temp);

        if (knight[temp].health <= 0) {
            temp_stk.pop();
            continue;
        }

        for (int i = 0; i < knight_loc[temp].size(); ++i) {

            knight_loc[temp][i].first += dy[d];
            knight_loc[temp][i].second += dx[d];

        }//기사 이동
        //stk.pop();

        //벽있을 때
        for (int i = 0; i < knight_loc[temp].size(); ++i) {
            if (map[knight_loc[temp][i].first][knight_loc[temp][i].second] == 2) {
                while (!temp_stk.empty()) {
                    temp = temp_stk.top();
                    for (int j = 0; j < knight_loc[temp].size(); ++j) {
                        knight_loc[temp][j].first -= dy[d];
                        knight_loc[temp][j].second -= dx[d];
                        knight[temp].conflict = 0;
                    }
                    temp_stk.pop();
                }
                return;
            }
        }

        memset(check_knight, 0, sizeof(check_knight));
        for (int i = 0; i < knight_loc[temp].size(); ++i) {
            if (knight_map[knight_loc[temp][i].first][knight_loc[temp][i].second] != temp) {
                if (knight_map[knight_loc[temp][i].first][knight_loc[temp][i].second] != 0) { // 이동한 기사맵에 다른 기사 있을때
                    int ano_knight = knight_map[knight_loc[temp][i].first][knight_loc[temp][i].second]; //다른기사 번호 저장
                    
                    knight[ano_knight].conflict = 1; //충돌 확인
                    
                    if(check_knight[ano_knight] == 0)
                        stk.push(ano_knight); //다른 기사 번호 저장됨
                    check_knight[ano_knight] = 1;


                }
            }
        }

    } //이동 완료

    memset(knight_map, 0, sizeof(knight_map)); //기사맵 초기화
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < knight_loc[i].size(); ++j) {
            if (knight[i].health > 0)
            {
                knight_map[knight_loc[i][j].first][knight_loc[i][j].second] = i;
            }
        }
    } //맵 다시 생성

    for (int i = 1; i <= n; ++i) {
        if (knight[i].conflict == 1) {
            for (int j = 0; j < knight_loc[i].size(); ++j) {
                if (map[knight_loc[i][j].first][knight_loc[i][j].second] == 1) {
                    knight[i].health--;
                    knight[i].damage++;
                }
            }
        }
    }//체력 함정 확인

    memset(knight_map, 0, sizeof(knight_map)); //기사맵 초기화
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < knight_loc[i].size(); ++j) {
            if (knight[i].health > 0)
            {
                knight_map[knight_loc[i][j].first][knight_loc[i][j].second] = i;
            }
        }
    } //맵 다시 생성

    for (int i = 1; i <= n; ++i) {
        if (knight[i].conflict == 1) {
            knight[i].conflict = 0;
        }
    }//체력 함정 확인


}

int main() {
    cin >> l >> n >> q;

    for (int i = 0; i <= l + 1; ++i) {
        for (int j = 0; j <= l + 1; ++j) {
            map[i][j] = 2;
        }
    }

    for (int i = 1; i <= l; ++i) {
        for (int j = 1; j <= l; ++j) {
            cin >> map[i][j];
        }
    }
    //맵 생성


    int r, c, h, w, k;
    for (int i = 1; i <= n; ++i) {
        cin >> r >> c >> h >> w >> k;
        knight[i].y = r;
        knight[i].x = c;
        knight[i].health = k;
        // int cnt = 0;
        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < w; ++k) {
                knight_map[r + j][c + k] = i;
                knight_loc[i].push_back({ r + j,c + k });
            }
        }

    }
    //기사 맵 생성


    int king_i, d;
    for (int i = 0; i < q; ++i) {
        cin >> king_i >> d;
        if (knight[king_i].health > 0)
            move(king_i, d);
    }

    int total_damage = 0;
    for (int i = 1; i <= n; ++i) {
        if (knight[i].health > 0) {
            total_damage += knight[i].damage;
        }
    }

    cout << total_damage;

    return 0;
}