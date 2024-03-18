#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>

using namespace std;

int calculate(vector<int> a, int n){

    int min_value = INT_MAX;

    for(int i=0; i<n; ++i){
        int sum = 0;
        for(int j=0; j<n; ++j){
            if(i==j) continue;
            sum += (abs(i-j))*a[j];
        }
        if(min_value>=sum) min_value = sum;
    }
    return min_value;
}

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;
    vector<int> vect;
    for(int i=0; i<n; ++i){
        int person;
        cin>>person;
        vect.push_back(person);
    }
    cout<<calculate(vect,n);

    return 0;
}