#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.

    int N;
    cin>>N;

    vector<int> origin_num;
    vector<int> sorted_num;

    for(int i=0; i<N; ++i){
        int tmp;
        cin>>tmp;
        origin_num.push_back(tmp);
    }

    sorted_num = origin_num;
    sort(sorted_num.begin(), sorted_num.end());

    while(!origin_num.empty()){
        int cur_ = find(sorted_num.begin(), sorted_num.end(), origin_num.front())-sorted_num.begin();
        cout<<cur_+1<<" ";
        origin_num.erase(origin_num.begin());
        sorted_num[cur_] = 0;
    }


    return 0;
}