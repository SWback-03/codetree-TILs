#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

#define MAX_M 100000
using namespace std;

struct box{
    int id;
    int weight;
};

vector<box> present[MAX_M];
bool broken_rail_visited[MAX_M] = {false,};
int q, n, m;

unordered_map<int,int> u_map; //id, rail_num

// bool index_check(int index, int d_id){
//     for(auto element : present[index]){
//         if(element.id == d_id) return true;
//     }
//     return false;
// }

// bool binary_search(int index, int d_id){
//     if(index_check(index, d_id)) return true;

//     else{
//         binary_search((index))
//     }

//     return false;
// }

void print_rail(){
    for(int i=0; i<m; ++i){
        for(auto element : present[i]){
            cout<<element.id<<" ";
            // cout<<element.id<<","<<element.weight<<" ";
        }
        cout<<endl;
    }
    return;
}

void build_factory(){
    
    cin>>n>>m;
    queue<int> id_q;
    queue<int> weight_q;
    int rail_count = n/m;
    for(int i=0; i<n; ++i){
        int tmp;
        cin>>tmp;
        id_q.push(tmp);
    }
    for(int i=0; i<n; ++i){
        int tmp;
        cin>>tmp;
        weight_q.push(tmp);
    }
    int rail_num = 0;
    for(int i=0; i<n; ++i){
        present[rail_num].push_back({id_q.front(), weight_q.front()});
        //hash
        u_map.insert(make_pair(id_q.front(), rail_num));
        id_q.pop();
        weight_q.pop();
        if(i%rail_count == rail_count-1){
            rail_num++;
        }
    }
    return;
}

int get_present(){
    int w_max;
    cin>>w_max;

    int get_total = 0;

    for(int i=0; i<m; ++i){
        if(present[i].size() <= 0) continue;

        if(present[i][0].weight<=w_max){
            get_total += present[i][0].weight;
            present[i].erase(present[i].begin());
        }
        else{
            present[i].push_back({present[i][0].id, present[i][0].weight});
            present[i].erase(present[i].begin());
        }
    }

    return get_total;
}

int delete_present(){
    int r_id;
    cin>>r_id;

    int i = u_map[r_id];

    // for(int i=0; i<m; ++i){
        // if(present[i].size() <= 0) continue;

        int count = 0;
        for(auto element : present[i]){
            if(element.id == r_id){
                present[i].erase(present[i].begin()+count);
                return r_id;
            }
            count++;
        }
    // }

    return -1;
}

int check_present(){
    int f_id;
    cin>>f_id;

    int i = u_map[f_id];

    // for(int i=0; i<m; ++i){
        // if(present[i].size() <= 0) continue;

        int count = 0;
        queue<box> tmp_q;
        for(auto element : present[i]){
            if(element.id == f_id){
                while(!tmp_q.empty()){
                    present[i].push_back({tmp_q.front().id,tmp_q.front().weight});
                    tmp_q.pop();
                }
                for(int j=0; j<count; ++j){
                    present[i].erase(present[i].begin());
                }

                return i+1;
            }

            tmp_q.push({element.id, element.weight});

            count++;
        }
    // }

    return -1;
}

int broken_rail(){
    int b_num;
    cin>>b_num;
    b_num--;

    if(broken_rail_visited[b_num]) return -1;

    broken_rail_visited[b_num] = true;

    queue<box> tmp_q;
    while(present[b_num].size()>0){
        tmp_q.push({present[b_num][0].id,present[b_num][0].weight});
        present[b_num].erase(present[b_num].begin());
    }

    for(int i=(b_num+1)%m; i!=b_num; i = (i+1)%m){
        if(broken_rail_visited[i] == false){
            while(!tmp_q.empty()){
                present[i].push_back({tmp_q.front().id, tmp_q.front().weight});
                u_map[tmp_q.front().id] = i;
                tmp_q.pop();
            }
            return b_num+1;
        }
    }

    return -99;
}

void input_func(int input){
    switch(input){
        case 100:
            build_factory();
            // print_rail();
            break;

        case 200:
            cout<<get_present()<<endl;
            break;

        case 300:
            cout<<delete_present()<<endl;
            
            break;

        case 400:
            cout<<check_present()<<endl;
            // print_rail();
            break;

        case 500:
            cout<<broken_rail()<<endl;
            // print_rail();
            break;

        default:
            break;
    }
    return;
}

int main() {
    cin>>q;

    for(int i=0; i<q; ++i){
        int tmp;
        cin>>tmp;
        input_func(tmp);
    }

    return 0;
}