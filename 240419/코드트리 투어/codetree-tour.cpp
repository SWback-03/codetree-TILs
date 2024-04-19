#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INF 0x7fffffff 
#define MAX_N 2000 
#define MAX_ID 30005 

using namespace std;

int N, M; // 정점의 수 N, 간선의 수 M
int A[MAX_N][MAX_N]; // 각 정점간의 거리를 저장하는 배열
int D[MAX_N]; // 시작점에서 각 정점까지의 최단 거리
bool isMade[MAX_ID]; // 패키지 생성 여부
bool isCancel[MAX_ID]; // 패키지 취소 여부
int S; // 시작 정점

struct Package {
    int id; 
    int revenue; 
    int dest; 
    int profit; 

    struct Comparator {
        bool operator()(const Package& a, const Package& b) const {
            if (a.profit == b.profit) {
                return a.id > b.id; // 수익이 같다면 ID가 작은 것을 우선
            }
            return a.profit < b.profit; // 더 큰 이익을 가진 패키지를 우선
        }
    };
};

priority_queue<Package, vector<Package>, Package::Comparator> pq; // 이익에 따른 우선순위 큐

void dijkstra() {
    bool visit[MAX_N];
    for (int i=0;i<N;i++){
        D[i] = INF;
        visit[i] = false;
    }
    D[S] = 0;
    for (int i=0; i<N-1;i++){
        int v=0, minDist = INF;
        for (int j=0;j<N;j++) {
            if (!visit[j] && minDist > D[j]) {
                v = j;
                minDist = D[j];
            }
        }
        visit[v] = true;
        for (int j=0;j<N;j++){
            if (!visit[j] && D[v] != INF && A[v][j] != INF && D[j] > D[v] + A[v][j]) {
                D[j] = D[v] + A[v][j];
            }
        }
    }
}

void buildLand() {
    cin >> N >> M;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            A[i][j] = INF;
        }
        A[i][i] = 0;
    }
    for (int i=0;i<M;i++){
        int u,v,w;
        cin >> u >> v >> w;
        A[u][v] = min(A[u][v], w); // 무방향 그래프이므로 두 방향 모두 최소 가중치 갱신
        A[v][u] = min(A[v][u], w);
    }
}

void addPackage(int id, int revenue, int dest) {
    Package p;
    isMade[id] = true;
    p.id = id;
    p.revenue = revenue;
    p.dest = dest;
    p.profit = p.revenue - D[p.dest]; // 이익 계산

    pq.push(p);
}

void cancelPackage(int id) {
    if (isMade[id]) isCancel[id] = true;
}

int sellPackage() {
    while(!pq.empty()) {
        Package p = pq.top();
        if (p.profit < 0)
            break;
        pq.pop();
        if (!isCancel[p.id])
            return p.id; // 패키지 판매
    }
    return -1; // 판매할 패키지 없음
}

void changeStart() {
    cin >> S;
    vector<Package> packages;
    dijkstra(); // 새로운 시작점에서 다익스트라 재실행
    while(!pq.empty()) {
        packages.push_back(pq.top());
        pq.pop();
    }
    for (Package p : packages) {
        
        addPackage(p.id, p.revenue, p.dest);
    }
}
int main() {
    int Q, id, revenue, dest;
    cin >> Q;
    while (Q--) {
        int T;
        cin >> T;

        switch (T)
        {
        case 100:
            buildLand();
            dijkstra(); // 그래프 구축 및 최단 거리 계산
            break;
        case 200:
            cin >> id >> revenue >> dest;
            addPackage(id, revenue, dest);
            break;
        case 300:
            cin >> id;
            cancelPackage(id);
            break;
        case 400:
            cout << sellPackage() << endl; // 패키지 판매 처리
            break;
        case 500:
            changeStart(); // 시작점 변경
            break;
        }
    }

    return 0;
}