#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>

#define MAX_M 100000
using namespace std;

struct box {
    int id;
    int weight;
};

list<box> present[MAX_M];  // vector -> list로 변경
bool broken_rail_visited[MAX_M] = {false,};
int q, n, m;

unordered_map<int, int> u_map;  // id, rail_num

void print_rail() {
    for (int i = 0; i < m; ++i) {
        for (auto& element : present[i]) {
            cout << element.id << " ";
        }
        cout << endl;
    }
    return;
}

void build_factory() {
    cin >> n >> m;
    queue<int> id_q;
    queue<int> weight_q;
    int rail_count = n / m;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        id_q.push(tmp);
    }
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        weight_q.push(tmp);
    }
    int rail_num = 0;
    for (int i = 0; i < n; ++i) {
        present[rail_num].push_back({id_q.front(), weight_q.front()});
        // hash
        u_map.insert(make_pair(id_q.front(), rail_num));
        id_q.pop();
        weight_q.pop();
        if (i % rail_count == rail_count - 1) {
            rail_num++;
        }
    }
    return;
}

int get_present() {
    int w_max;
    cin >> w_max;

    int get_total = 0;

    for (int i = 0; i < m; ++i) {
        if (present[i].empty()) continue;

        auto front_box = present[i].front();
        if (front_box.weight <= w_max) {
            get_total += front_box.weight;
            present[i].pop_front();  // list에서는 pop_front로 삭제
        } else {
            present[i].push_back(front_box);  // 맨 뒤로 이동
            present[i].pop_front();  // 맨 앞에서 삭제
        }
    }

    return get_total;
}

int delete_present() {
    int r_id;
    cin >> r_id;

    int i = u_map[r_id];

    auto it = present[i].begin();
    while (it != present[i].end()) {
        if (it->id == r_id) {
            present[i].erase(it);  // 해당 id를 삭제
            return r_id;
        }
        ++it;
    }

    return -1;
}

int check_present() {
    int f_id;
    cin >> f_id;

    int i = u_map[f_id];

    auto it = present[i].begin();
    int count = 0;
    queue<box> tmp_q;
    
    while (it != present[i].end()) {
        if (it->id == f_id) {
            // 앞에 있는 상자들을 맨 뒤로 보냄
            for (int j = 0; j < count; ++j) {
                present[i].push_back(tmp_q.front());
                tmp_q.pop();
            }
            // 앞에 있는 상자들을 삭제
            for (int j = 0; j < count; ++j) {
                present[i].pop_front();
            }
            return i + 1;
        }
        tmp_q.push(*it);
        ++it;
        count++;
    }

    return -1;
}

int broken_rail() {
    int b_num;
    cin >> b_num;
    b_num--;

    if (broken_rail_visited[b_num]) return -1;

    broken_rail_visited[b_num] = true;

    queue<box> tmp_q;
    while (!present[b_num].empty()) {
        tmp_q.push(present[b_num].front());
        present[b_num].pop_front();
    }

    for (int i = (b_num + 1) % m; i != b_num; i = (i + 1) % m) {
        if (broken_rail_visited[i] == false) {
            while (!tmp_q.empty()) {
                present[i].push_back(tmp_q.front());
                u_map[tmp_q.front().id] = i;
                tmp_q.pop();
            }
            return b_num + 1;
        }
    }

    return -99;
}

void input_func(int input) {
    switch (input) {
        case 100:
            build_factory();
            break;

        case 200:
            cout << get_present() << endl;
            break;

        case 300:
            cout << delete_present() << endl;
            break;

        case 400:
            cout << check_present() << endl;
            break;

        case 500:
            cout << broken_rail() << endl;
            break;

        default:
            break;
    }
    return;
}

int main() {
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int tmp;
        cin >> tmp;
        input_func(tmp);
    }

    return 0;
}