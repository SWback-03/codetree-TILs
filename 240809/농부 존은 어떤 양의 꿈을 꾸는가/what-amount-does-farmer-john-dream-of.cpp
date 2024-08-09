#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//여러 특징 조합 소
//N마리 정보 주어짐
//갖고있는 소 조합 순서대로 나열, T번째로 나오는 소의 특징 출력

//전체 sort하면 안됨
//

string a;

int main() {
    // 여기에 코드를 작성해주세요.
    int N, T;
    cin>>N>>T;
    
    string str;

    for(int i=0; i<N; ++i){
        while(1){
            cin>>str;
            if(str.find("cow") != string::npos){
                break;
            }
            cout<<str<<endl;
        }
    }



    return 0;
}