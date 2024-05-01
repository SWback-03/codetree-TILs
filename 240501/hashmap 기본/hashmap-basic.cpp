#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int,int> un_map;

void add_k_v(int k, int v){
    un_map.insert({k,v});
}

void remove_k(int k){
    un_map.erase(k);
}

auto find_k(int k){
    auto key = un_map.find(k);
    
    return key;
}


int main() {

    string input_str;
    int k, v;
    int n;
    cin>>n;
    for(int i=0; i<n; ++i){
        cin>>input_str;
        if(input_str == "add"){
            cin>>k>>v;
            if(un_map.find(k)!=un_map.end()){
                un_map[k] = v;
            }
            else{
                add_k_v(k,v);
            }
        }
        else if(input_str == "remove"){
            cin>>k;
            remove_k(k);
        }
        else{
            cin>>k;
            auto iter = find_k(k);
            if(iter == un_map.end()){
                cout<<"None"<<'\n';
            }
            else{
                cout<<iter->second<<'\n';
            }
        }
    }

    return 0;
}