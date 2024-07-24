#include <iostream>
using namespace std;

//N개의 숫자들이 주어짐
//주어진 숫자 모두 사용, 각 묶음으로 나눔
//각각의 합을 구함
//첫번째 묶음부터 순서대로 짝,홀 번갈아 나옴

//최대묶음 수
//한 묶음당 갯수는 상관 X

//들어오는 숫자가 홀수인지, 짝수인지 세기

//짝수 갯수, 홀수 갯수 세기

//짝수+짝수 = 짝수
//짝수+홀수 = 홀수
//홀수+홀수 = 짝수

//짝수 10개, 홀수 1개인 경우 -> 짝수 1, 홀수 1, 짝수 9
//짝수 1개, 홀수 10개인 경우 -> 짝수 1, 홀수 10 ->짝수 1, 홀수 7, 홀수 2, 홀수 1
//짝수 1개, 홀수 2개인 경우 -> 짝수 1 && 홀수 2개
//짝수 2개, 홀수 2개인 경우

//홀수 8개 -> 2, 1, 2, 1, 2
//홀수 7개 -> 2, 1, 2, 1, 1 -> -되는 순간 count -= 2
//홀수 6개 -> 2, 1, 2, 1
//홀수 5개 -> 2, 1, 2
//홀수 4개 -> 2, 1, 1 -되는 순간 count -= 2
//홀수 3개 -> 2, 1
//홀수 2개 -> 2
//홀수 1개 -> 1 - 되는 순간 count -= 2

//짝수 8개 -> 하나로 묶어버림 -> 홀수를 못만들기 때문

//1,1,1,1식으로 테스트해보기
//이후에 짝수

int N;

int make_box(int odd, int even){
    int count = 0;

    if(odd > even){
        odd = odd - even;
        count += (even*2);
        int flag = 0;
        while(1){
            if(flag % 2 == 0){ // 짝수
                odd -= 2;
            }
            else{
                odd -= 1;
            }

            count++;

            if(odd < 0){
                count -= 2;
                break;
            }
            else if(odd == 0){
                break;
            }
            flag++;
        }
    }

    else if(odd < even){
        count += (2*odd);
        count++;
    }

    else if(odd == even){
        count += (2*odd);
    }

    return count;
}

int main() {
    cin>>N;

    int even = 0;
    int odd = 0;

    for(int i=0; i<N; ++i){
        int temp;
        cin>>temp;
        if(temp%2 == 1){
            odd++;
        }
        else{
            even++;
        }
    }

    cout<<make_box(odd, even);

    return 0;
}