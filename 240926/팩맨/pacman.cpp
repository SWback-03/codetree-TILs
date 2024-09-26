#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct monster_struct
{
    int y, x, dir;
    bool egg;
    int condition;
};

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int m, t, r, c;
vector<monster_struct> monster;

int monster_count[4][4] = {
    0,
};
bool visited[4][4] = {
    false,
};
int dead[4][4] = {
    0,
};

void print_map()
{
    int map[4][4] = {
        0,
    };
    for (auto element : monster)
    {
        if (element.egg == false || element.condition < 0)
            continue;
        if (element.condition == 0)
        {
            map[element.y][element.x] = 4;
            continue;
        }
        map[element.y][element.x] = 1;
    }
    cout << "r,c:" << r + 1 << "," << c + 1 << endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init_monster_count()
{
    memset(monster_count, 0, sizeof(monster_count));

    for (auto &element : monster)
    {
        if (element.egg && element.condition > 0)
        {
            monster_count[element.y][element.x]++;
        }
    }
}

void copy_start()
{
    int count = monster.size();
    for (int i = 0; i < count; ++i)
    {
        // 죽거나 알 제외
        if (monster[i].egg == false || monster[i].condition <= 0)
            continue;
        monster.push_back({monster[i].y, monster[i].x, monster[i].dir, false, 1});
    }
    return;
}

void monster_move()
{
    init_monster_count();

    int count = monster.size();
    for (int i = 0; i < count; ++i)
    {
        if (monster[i].egg == false || monster[i].condition <= 0)
            continue;

        for (int j = 0; j < 8; ++j)
        {
            int ny = monster[i].y + dy[(monster[i].dir + j) % 8];
            int nx = monster[i].x + dx[(monster[i].dir + j) % 8];
            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4 || (ny == r && nx == c))
                continue;
            if (dead[ny][nx] > 0)
                continue;

            monster_count[monster[i].y][monster[i].x]--;
            monster[i].y = ny;
            monster[i].x = nx;
            monster[i].dir = (monster[i].dir + j) % 8;
            monster_count[ny][nx]++;
            break;
        }
    }
    return;
}

void clear_visited()
{
    memset(visited, false, sizeof(visited));
    return;
}

int check_eating_count(int i_y, int i_x)
{
    int count = 0;
    if (visited[i_y][i_x])
        return count;
    visited[i_y][i_x] = true;

    count = monster_count[i_y][i_x];

    return count;
}

void kill_monster(int *pos)
{
    for (int i = 0; i < 6; i += 2)
    {
        for (auto &element : monster)
        {
            if (element.egg && element.condition > 0 && element.y == pos[i] && element.x == pos[i + 1])
            {
                element.condition = -3;
                dead[pos[i]][pos[i + 1]] = 3;
                monster_count[pos[i]][pos[i + 1]]--;
            }
        }
    }

    return;
}
void pacman_move()
{
    int eating_count = -1;
    int pos[6] = {
        0,
    };
    int new_r = r, new_c = c;

    for (int i = 0; i < 8; i += 2)
    {
        int first_ny = r + dy[i];
        int first_nx = c + dx[i];
        if (first_ny < 0 || first_nx < 0 || first_ny >= 4 || first_nx >= 4)
            continue;
        for (int j = 0; j < 8; j += 2)
        {
            int second_ny = first_ny + dy[j];
            int second_nx = first_nx + dx[j];
            if (second_ny < 0 || second_nx < 0 || second_ny >= 4 || second_nx >= 4)
                continue;
            for (int k = 0; k < 8; k += 2)
            {
                int third_ny = second_ny + dy[k];
                int third_nx = second_nx + dx[k];
                if (third_ny < 0 || third_nx < 0 || third_ny >= 4 || third_nx >= 4)
                    continue;

                int tmp = 0;
                clear_visited();

                tmp += check_eating_count(first_ny, first_nx);
                tmp += check_eating_count(second_ny, second_nx);
                tmp += check_eating_count(third_ny, third_nx);

                if (tmp > eating_count)
                {
                    eating_count = tmp;
                    pos[0] = first_ny;
                    pos[1] = first_nx;
                    pos[2] = second_ny;
                    pos[3] = second_nx;
                    pos[4] = third_ny;
                    pos[5] = third_nx;
                    new_r = third_ny;
                    new_c = third_nx;
                }
            }
        }
    }

    if (eating_count > 0)
    {
        kill_monster(pos);
        r = new_r;
        c = new_c;
    }
    else
    {
        for (int i = 0; i < 8; i += 2)
        {
            int first_ny = r + dy[i];
            int first_nx = c + dx[i];
            if (first_ny < 0 || first_nx < 0 || first_ny >= 4 || first_nx >= 4)
                continue;
            for (int j = 0; j < 8; j += 2)
            {
                int second_ny = first_ny + dy[j];
                int second_nx = first_nx + dx[j];
                if (second_ny < 0 || second_nx < 0 || second_ny >= 4 || second_nx >= 4)
                    continue;
                for (int k = 0; k < 8; k += 2)
                {
                    int third_ny = second_ny + dy[k];
                    int third_nx = second_nx + dx[k];
                    if (third_ny < 0 || third_nx < 0 || third_ny >= 4 || third_nx >= 4)
                        continue;

                    r = third_ny;
                    c = third_nx;
                    return;
                }
            }
        }
    }

    return;
}

void dead_monster()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (dead[i][j] > 0)
            {
                dead[i][j]--;
            }
        }
    }

    return;
}

void copy_complete()
{
    int count_limit = monster.size();
    for (int i = 0; i < count_limit; ++i)
    {
        if (monster[i].egg == false)
        {
            monster[i].egg = true;
        }
    }

    return;
}

void run()
{

    for (int i = 0; i < t; ++i)
    {
        copy_start();
        // print_map();

        monster_move();
        // print_map();

        pacman_move();
        // print_map();

        dead_monster();
        // print_map();

        copy_complete();
        // print_map();
    }

    return;
}

int check_survived_monster()
{
    int survived_count = 0;
    for (auto element : monster)
    {
        if (element.condition > 0)
            survived_count++;
    }
    return survived_count;
}

int main()
{
    cin >> m >> t >> r >> c;
    r--, c--;

    for (int i = 0; i < m; ++i)
    {
        int mon_r, mon_c, mon_dir;
        cin >> mon_r >> mon_c >> mon_dir;
        monster.push_back({mon_r - 1, mon_c - 1, mon_dir - 1, true, 1});
    }

    run();

    cout << check_survived_monster();

    return 0;
}