#include <iostream>
#include <vector>
#include <climits>

using namespace std;


int N;
vector<int> v;

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>N;

    for(int i=0; i<N; ++i){
        int input;
        cin>>input;
        v.push_back(input);
    }

    int min_val = INT_MAX;
    for(int i=0; i<N; ++i){
        int sum = 0;
        for(int j=0; j<N; ++j){
            sum += j * v[j];
        }
        if(min_val >= sum)
            min_val = sum;
        
        //rotate
        int temp = v.front();
        v.erase(v.begin());
        v.push_back(temp);
    }
    //0 - N-1까지

    cout<<min_val;



    return 0;
}