#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.

    int N;
    
    int max_dist = 0;
    int min_dist = 99;
    int x;
    cin>>N;
    char str[10];
    for(int i=0; i<N; ++i){
        cin>>str[i];
    }
    for(int i=0; i<N; ++i){

        if(str[i]=='1'){
            for(int j=i+1; j<N; ++j){
                if(str[j]=='1'){
                    if(j-i>=max_dist) {
                        x = i;
                        
                        max_dist  = j-i;
                        //cout<<i<<j<<"\n";
                        }
                    break;
                }
            }
        }
    }

    //cout<<"\n"<<max_dist<<"\n";
    int dist = max_dist/2;
    
    str[x+dist] = '1';

    for(int i=0; i<N; ++i){

        if(str[i]=='1'){
            for(int j=i+1; j<N; ++j){
                if(str[j]=='1'){
                    if(min_dist>=j-i) {
                        min_dist  = j-i;
                        }
                    break;
                }
            }
        }
    }

    cout<<min_dist;

    return 0;


}