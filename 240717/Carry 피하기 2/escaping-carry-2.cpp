#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;
vector<int> v;

//각자리수 찾는 함수
vector<int> find_num(int num){
    vector<int> output;
    while(num != 0){
        output.push_back(num%10);
        num = num/10;
    }
    return output;
}

//각자리수 더하는 함수, 두개 합
bool add(vector<int> a, vector<int> b, int size){
    vector<int> re;
    for(int i=0; i<size; ++i){
        re.push_back(a[i]+b[i]);
        if(re.back()>=10)
            return false;
    }
    return true;
}

int find_min(int a, int b){
    return min(a, b);
}

int main() {
    cin>>n;
    for(int i=0; i<n; ++i){
        int input;
        cin>>input;
        v.push_back(input);
    }

    int min_val = -1;

    for(int i=0; i<n-2; ++i){
        for(int j=i+1; j<n-1; ++j){
            for(int k=j+1; k<n; ++k){
                vector<int> first_ = find_num(v[i]);
                vector<int> second_ = find_num(v[j]);

                int first_size = first_.size();
                int second_size = second_.size();
                
                int size_1 = find_min(first_size,second_size);

                vector<int> fourth_;
                if(add(first_,second_,size_1)){
                    fourth_ = find_num(v[i]+v[j]);
                }
                else
                    continue;

                vector<int> third_ = find_num(v[k]);
                int third_size = third_.size();
                int fourth_size = fourth_.size();
                int size_2 = find_min(third_size,fourth_size);

                int result;
                if(add(third_,fourth_,size_2)){
                    result = v[i]+v[j]+v[k];
                }
                else
                    continue;

                if(min_val <= result){
                    min_val = result;
                }
            }
        }
    }

    cout<<min_val;

    return 0;
}