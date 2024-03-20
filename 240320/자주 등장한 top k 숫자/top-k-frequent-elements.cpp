#include <iostream>
#include <unordered_map>
#include<vector>
#include<algorithm>
using namespace std;
unordered_map<int,int> map;
vector<pair<int,int>> vect;
int n,k;
int arr[100000];

int main() {
    
    cin>>n>>k;

    int max = 0;
    int index= 0;
    int cnt = 0;

    
    for(int i=0; i<n; ++i){
        
        cin>>arr[i];
        map[arr[i]]++;

        // if(!map[input]){
        //     vect.push_back(input);
        //     //cnt++;
        // }
        // map[input]++;
    }

    for(unordered_map<int, int>::iterator it = map.begin(); it!=map.end(); it++){
        vect.push_back(make_pair(it->second,it->first));
    }

    sort(vect.begin(), vect.end());

    for(int i = (int)vect.size() - 1; i >= (int)vect.size() - k; i--)
        cout << vect[i].second << " ";

    return 0;
}