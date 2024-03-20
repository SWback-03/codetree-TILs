#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;



int main() {
    // 여기에 코드를 작성해주세요.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin>>n>>k;

    vector<int> vect(n);
    unordered_multiset<int> u_m;

    for(int i=0; i<n; ++i){
        int input;
        cin>>input;
        //q.push(input);
        vect[i]=input;
        u_m.insert(input);
    }

    int result=0;
    for(int i=0; i<n; ++i){
        int diff = k-vect[i];
        u_m.erase(u_m.find(vect[i]));
        result += u_m.count(diff);
    }
    cout<<result;


    return 0;
}