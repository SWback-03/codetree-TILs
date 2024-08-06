#include <iostream>
#include <vector>
#include <stack>

#define MAX_NUM 1000

using namespace std;

int vertex_cnt = 0;

vector<int> graph[MAX_NUM+1];
bool visited[MAX_NUM+1];

// void DFS(int vertex){
//     for(int i=0; i<(int) graph[vertex].size(); ++i){
//         int curr_v = graph[vertex][i];
//         if(!visited[curr_v]){
//             visited[curr_v] = true;
//             vertex_cnt++;
//             DFS(curr_v);
//         }
//     }
// }

void DFS(int vertex){
    stack<int> stack;

    stack.push(vertex);

    while(!stack.empty()){
        int v = stack.top();
        stack.pop();
        
        if(!visited[v]){
            visited[v] = true;
            vertex_cnt++;
        }
        for(auto i=graph[v].begin(); i!=graph[v].end(); ++i){
            if(!visited[*i])
                stack.push(*i);
        }
    }
}

int main() {
    int N, M;
    cin>>N>>M;

    for(int i=0; i<M; ++i){
        int n1, n2;
        cin>>n1>>n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    visited[1] = true;
    DFS(1);

    cout<<vertex_cnt;

    return 0;
}