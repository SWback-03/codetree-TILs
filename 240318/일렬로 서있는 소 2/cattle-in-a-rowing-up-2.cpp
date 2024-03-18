#include <iostream>
#include <vector>

using namespace std;

vector<int> vect;

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;
    for(int i=0; i<n; ++i){
        int a;
        cin>>a;
        vect.push_back(a);
    }
    int cnt = 0;
    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            for(int k=j+1; k<n; ++k){
                if(vect[i]<=vect[j]&&vect[j]<=vect[k]){
                    cnt++;
                }
            }
        }
    }
    cout<<cnt;
    return 0;
}