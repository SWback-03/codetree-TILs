#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

priority_queue<int> pq;
priority_queue<int> temp;
vector<int> v;
int t, m;

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>t;
    for(int i=0; i<t; ++i){
        pq = priority_queue<int>();
        cin>>m;
        for(int j=0; j<m; ++j)
        {
            int tmp;
            cin>>tmp;
            pq.push(tmp);
            temp = pq;
            if(!(j%2)){ //홀수일 때
                int cnt = 0;
                while(1){
                    if(cnt == j/2){
                        cout<<temp.top()<<" ";
                        break;
                    }
                    cnt++;
                    temp.pop();
                    
                }
            }
        }
        cout<<"\n";
    }
    return 0;
}