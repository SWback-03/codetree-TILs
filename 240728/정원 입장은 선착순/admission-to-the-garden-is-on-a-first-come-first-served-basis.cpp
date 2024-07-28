#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_A 1000000000


struct second_first_compare{
    bool operator()(const pair<int,pair<int,int>>& a, const pair<int,pair<int,int>>& b){
        return a.second.first>b.second.first;
    }
};

struct buffer_compare{
    bool operator()(const pair<int,pair<int,int>>& a, const pair<int,pair<int,int>>& b){
        return a.first>b.first;
    }
};

int main() {
    int N;
    cin>>N;

    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>, second_first_compare> person;
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>, buffer_compare> buffer;


    for(int i=0; i<N; ++i){
        int a, t;
        cin>>a>>t;
        person.push(make_pair(i+1,make_pair(a,t)));
    }

    buffer.push(person.top());
    person.pop();

    int current_time = buffer.top().second.first;

    int max_waiting_time = 0;

    while(!person.empty() || !buffer.empty()){

        if(buffer.empty()){
            buffer.push(person.top());
            person.pop();
            current_time = buffer.top().second.first;
        }
        
        
        int waiting_time = current_time - buffer.top().second.first;
        if(waiting_time > max_waiting_time){
            max_waiting_time = waiting_time;
        }

        current_time = current_time + buffer.top().second.second;

        ////
        //cout<<buffer.top().first<<" "<<current_time<<" "<<max_waiting_time<<endl;
        ////

        buffer.pop();

        while(!person.empty() && (person.top().second.first < current_time)){

            buffer.push(person.top());
            person.pop();
            
        }
    }

    cout<<max_waiting_time;


    return 0;
}