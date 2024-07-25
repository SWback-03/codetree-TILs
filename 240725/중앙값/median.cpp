#include <iostream>
#include <queue>
using namespace std;

int main() {
    int t;
    cin>>t;

    for(int i=0; i<t; ++i){
        int m;
        cin>>m;

        priority_queue<int> pq;

        for(int j=1; j<=m; ++j){
            int tmp;
            cin>>tmp;
            pq.push(tmp);
            if(j%2 == 1){
                // j/2번째 숫자 읽기
                priority_queue<int> tmp_q;
                for(int k=0; k<j; ++k){
                    tmp_q.push(pq.top());
                    if(k == j/2)
                        cout<<pq.top()<<" ";
                    pq.pop();
                }
                pq = tmp_q;
            }
            

        }
        cout<<endl;
    }

    return 0;
}