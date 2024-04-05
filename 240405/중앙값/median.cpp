#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> v;

int t, m;

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>t;
    for(int i=0; i<t; ++i){
        v = vector<int>();
        cin>>m;
        for(int j=0; j<m; ++j)
        {
            int tmp;
            cin>>tmp;
            v.push_back(tmp);
            sort(v.begin(),v.end());
            if(j%2==0){
                cout<<v[j/2]<<" ";
            }
        }
        cout<<"\n";
    }
    return 0;
}