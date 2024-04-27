#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
//n개의 숫자 주어짐, 서로 다른 3개 숫자 선택
//carry 발생 x
//carry란 10넘어가는 수
//각 자리수 더했을 때 10 이상 x
//싹다 돌린다
//

int n;
vector<int> vect;

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n;
    for(int i =0; i<n; ++i){
        int temp;
        cin>>temp;
        vect.push_back(temp);
    }

    sort(vect.begin(),vect.end());

    int max_val = -1;

    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            for(int k=j+1; k<n; ++k){
                int temp_vect1 = vect[i];
                int temp_vect2 = vect[j];
                int temp_vect3 = vect[k];

                int result = temp_vect1 + temp_vect2 +temp_vect3;
                // cout<<result<<"\n";
                int re_result = result;

                int first_val = temp_vect1%10 + temp_vect2%10 +temp_vect3%10;
                temp_vect1 = temp_vect1/10;
                temp_vect2 = temp_vect2/10;
                temp_vect3 = temp_vect3/10;
                int second_val = temp_vect1%10 + temp_vect2%10 +temp_vect3%10;
                temp_vect1 = temp_vect1/10;
                temp_vect2 = temp_vect2/10;
                temp_vect3 = temp_vect3/10;
                int third_val = temp_vect1%10 + temp_vect2%10 +temp_vect3%10;
                temp_vect1 = temp_vect1/10;
                temp_vect2 = temp_vect2/10;
                temp_vect3 = temp_vect3/10;
                int fourth_val = temp_vect1%10 + temp_vect2%10 +temp_vect3%10;
                temp_vect1 = temp_vect1/10;
                temp_vect2 = temp_vect2/10;
                temp_vect3 = temp_vect3/10;
                int fifth_val = temp_vect1%10 + temp_vect2%10 +temp_vect3%10;
                temp_vect1 = temp_vect1/10;
                temp_vect2 = temp_vect2/10;
                temp_vect3 = temp_vect3/10;

                int real_first = result%10;
                result = result/10;
                int real_second = result%10;
                result = result/10;
                int real_third = result%10;
                result = result/10;
                int real_fourth = result%10;
                result = result/10;
                int real_fifth = result%10;
                result = result/10;

                // cout<<fifth_val<<" "<<fourth_val<<" "<<third_val<<" "<<second_val<<" "<<first_val<<"\n";
                // cout<<real_fifth<<" "<<real_fourth<<" "<<real_third<<" "<<real_second<<" "<<real_first<<"\n";

                if(first_val == real_first){
                    if(second_val == real_second){
                        if(third_val == real_third){
                            if(fourth_val == real_fourth){
                                if(fifth_val == real_fifth){
                                    if(max_val<re_result){
                                        max_val = re_result;
                                    }
                                }
                                else{
                                    continue;
                                }
                            }
                            else{
                                continue;
                            }
                        }
                        else{
                            continue;
                        }
                    }
                    else{
                        continue;
                    }
                }
                else{
                    continue;
                }

            } 
        }   
    }

    cout<<max_val;

    return 0;
}