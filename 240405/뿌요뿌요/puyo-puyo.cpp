#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int map[102][102] = {0,};
int visited[102][102] = {0,};
int bomb[102][102] = {0,};

int bomb_cnt = 0;

int bfs(int sy, int sx) {
    queue<pair<int, int>> q;
    q.push({sy, sx});
    int val = map[sy][sx];
    int cnt = 1;
    visited[sy][sx] = 1;

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny > 0 && ny <= n && nx > 0 && nx <= n && map[ny][nx] == val && !visited[ny][nx]) {
                visited[ny][nx] = 1;
                q.push({ny, nx});
                cnt++;
            }
        }
    }
    return cnt >= 4 ? cnt : 0; // 터질 경우 해당 블럭 크기 반환, 아닐 경우 0 반환
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> map[i][j];
        }
    }

    int max_block = 0, total_bombs = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!visited[i][j]) {
                int result = bfs(i, j);
                if (result > 0) {
                    total_bombs++;
                    if (result > max_block) max_block = result;
                }
            }
        }
    }

    cout << total_bombs << " " << max_block;

    return 0;
}