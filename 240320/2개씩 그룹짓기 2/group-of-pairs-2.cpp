#include <iostream>
#include <vector>
#include<algorithm>
#include<climits>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.

    vector<int> vect;
    int n;
    cin>>n;
    for(int i=0; i<2*n; ++i){
        int a;
        cin>>a;
        vect.push_back(a);
    }
    sort(vect.begin(),vect.end());
    int min_val = INT_MAX;
    for(int i=0; i<n; ++i){
        int a=vect[n+i]-vect[i];
        if(min_val>=a) min_val = a;
    }
    cout<<min_val;

    return 0;
}