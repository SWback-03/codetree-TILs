#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> list_1;
vector<int> list_2;
vector<int> list_3;
vector<int> list_4;

unordered_map<int,int> map_12;
unordered_map<int,int> map_34;


int main() {
    int n;
    cin>>n;
    for(int i=0; i<4; ++i){
        for(int j=0; j<n; ++j){
            int temp;
            cin>>temp;
            switch(i){
                case 0:
                list_1.push_back(temp);
                break;
                case 1:
                list_2.push_back(temp);
                break;
                case 2:
                list_3.push_back(temp);
                break;
                case 3:
                list_4.push_back(temp);
                break;
            }
        }
    }

    for(auto element_list_1 : list_1){
        for(auto element_list_2 : list_2){
            map_12[element_list_1+element_list_2]++;
        }
    }

    for(auto element_list_3 : list_3){
        for(auto element_list_4 : list_4){
            map_34[-(element_list_3+element_list_4)]++;
        }
    }

    int total = 0;
    for(auto&iter : map_12){
        if(map_34.find(iter.first) != map_34.end()){
            total += map_12[iter.first]*map_34[iter.first];
        }
    }

    cout<<total;

    return 0;
}