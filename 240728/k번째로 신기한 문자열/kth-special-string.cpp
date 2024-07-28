#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//앞자리 체크

bool check(string str, string check_str){
    for(int i=0; i<check_str.length(); ++i){
        if(str[i] != check_str[i])
            return false;
    }
    return true;
}

int main() {
    int n, k;
    string T;
    cin>>n>>k>>T;

    vector<string> v;

    for(int i=0; i<n; ++i){
        string tmp;
        cin>>tmp;
        if(check(tmp, T))
            v.push_back(tmp);
    }

    sort(v.begin(), v.end());

    int count = 1;
    for(auto element : v){
        if(count == k)
            cout<<element<<endl;

        count++;
    }

    return 0;
}