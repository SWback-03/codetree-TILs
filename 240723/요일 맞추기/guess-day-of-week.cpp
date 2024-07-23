#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//1월 : 31일
//2월 : 28일
//3월 : 31일
//4월 : 30일
//5월 : 31일
//6월 : 30일
//7월 : 31일
//8월 : 31일
//9월 : 30일
//10월: 31일
//11월: 30일
//12월: 31일

int m1, d1, m2, d2;
int month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
string week[7] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

//날짜 계산
int cal_date(int m, int d){
    int total_day = 0;
    for(int i=0; i<m; ++i){
        total_day += month[i];
    }
    total_day += d;

    return total_day;
}

int main() {
    cin>>m1>>d1>>m2>>d2;

    int total_day = 0;
    for(int i=1; i<=12; ++i){
        total_day += month[i];
    }

    int diff = (abs(cal_date(m1,d1)-cal_date(m2,d2)))%7;
    if(cal_date(m1,d1)-cal_date(m2,d2)>0){
        cout<<week[7-diff];
    }
    else{
        cout<<week[diff];
    }


    return 0;
}