#include <iostream>

using namespace std;

int n, m, p, c, d;

int map[52][52] = { 0, }; //산타위치 자기 자신 번호, 루돌프 위치 -1
int santa[31][5] = { 0, }; //y,x좌표, 점수, 현재상태(기절시 1), 탈락여부
int ludolf[2] = { 0, }; //루돌프 y,x좌표

int l_dy[8] = { -1,-1,0,1,1,1,0,-1 };
int l_dx[8] = { 0,1,1,1,0,-1,-1,-1 };

int santa_dy[4] = { -1,0,1,0 };
int santa_dx[4] = { 0,1,0,-1 };

//거리 계산 함수
int calc(int a_y, int a_x, int b_y, int b_x) {
    return (a_y - b_y) * (a_y - b_y) + (a_x - b_x) * (a_x - b_x);
}

//산타함수에서 산타 상호작용 밀림 함수
void s_push(int number, int move_y, int move_x) {
    if (map[santa[number][0]][santa[number][1]] > 0) { //이동한 산타자리에 다른 산타 있을 때
        int ano_santa = map[santa[number][0]][santa[number][1]];
        santa[ano_santa][0] += move_y;
        santa[ano_santa][1] += move_x;

        s_push(ano_santa, move_y, move_x);
        map[santa[ano_santa][0]][santa[ano_santa][1]] = ano_santa;
    }
}

//루돌프함수에서 산타 상호작용 밀림 함수
void l_push(int number, int move_y, int move_x) {
    if (map[santa[number][0]][santa[number][1]] > 0) { //이동한 산타자리에 다른 산타 있을 때
        int ano_santa = map[santa[number][0]][santa[number][1]];
        santa[ano_santa][0] -= move_y;
        santa[ano_santa][1] -= move_x;
        l_push(ano_santa, move_y, move_x);
        map[santa[ano_santa][0]][santa[ano_santa][1]] = ano_santa;
    }
}

//루돌프가 가장 가까운 산타 찾기
int find_close_santa() {
    int dist = 99999;
    int close_santa_num = 0;
    for (int i = 1; i <= p; ++i) {
        if (santa[i][4] == 1) continue;
        if (santa[i][0] > 0 && santa[i][1] <= n && santa[i][4] == 0)// map내의 산타에 대해서만 탐색
        {
            int curr_dist = calc(ludolf[0], ludolf[1], santa[i][0], santa[i][1]);
            if (curr_dist < dist) {
                close_santa_num = i;
                dist = curr_dist;
            }
            else if (curr_dist == dist) {
                if (santa[close_santa_num][0] > santa[i][0]) {
                    continue;
                } //지금 산타가 저장된 산타보다 r값 작을 때

                else if (santa[close_santa_num][0] == santa[i][0] && santa[close_santa_num][1] > santa[i][1]) {
                    continue;
                }
                else {
                    close_santa_num = i;
                }
            }
        }
    }

    return close_santa_num; //가장 가까운 산타 숫자 번호 return
}



//루돌프가 가장 가까운 산타 찾고 이동
void find_santa() {

    int min_dist = 99999;
    int y=0, x=0;
    int move_y=0, move_x=0;
    int closest_santa_num = find_close_santa();
    for (int i = 0; i < 8; ++i) {

        int ny = ludolf[0] + l_dy[i];
        int nx = ludolf[1] + l_dx[i];
        int curr_dist = calc(ny, nx, santa[closest_santa_num][0], santa[closest_santa_num][1]);
        if (curr_dist < min_dist) {
            min_dist = curr_dist;
            y = ny;
            x = nx;
            move_y = l_dy[i];
            move_x = l_dx[i];
        }
    }
    map[ludolf[0]][ludolf[1]] = 0;

    ludolf[0] = y;
    ludolf[1] = x;
    
    //루돌프 이동

    if (map[ludolf[0]][ludolf[1]] > 0) {
        int curr_santa_num = map[ludolf[0]][ludolf[1]];
        santa[curr_santa_num][0] += move_y * c;
        santa[curr_santa_num][1] += move_x * c;

        if (santa[curr_santa_num][0]<=0 || santa[curr_santa_num][1]<=0 || santa[curr_santa_num][0]>n || santa[curr_santa_num][1]>n) {
            santa[curr_santa_num][4] = 1; //산타 탈락
        }

       
        santa[curr_santa_num][3] = 2; // 산타 기절
        santa[curr_santa_num][2] += c; //산타 점수 추가
        
         
        s_push(curr_santa_num, move_y, move_x);
        if(santa[curr_santa_num][4] != 1){
        map[santa[curr_santa_num][0]][santa[curr_santa_num][1]] = curr_santa_num;}
    }
    map[ludolf[0]][ludolf[1]] = -1;

    ////출력 테스트
    //    for (int i = 1; i <= n; ++i) {
    //        for (int j = 1; j <= n; ++j) {
    //            if (map[i][j] >= 0)
    //                cout << " " << map[i][j];
    //            else
    //                cout << map[i][j];
    //        }
    //        cout << "\n";
    //    }
    //    cout << "\n";

    ////출력 테스트

}

//산타가 가장 가까운 루돌프 찾고 이동
void find_ludolf() {

    for (int j = 1; j <= p; ++j)
    {
        //cout << "스턴 여부: " << santa[1][3] << " " << santa[2][3] << " " << santa[3][3] << " " << santa[4][3] << " " << santa[5][3] <<"\n";
        //cout << "탈락 여부: " << santa[1][4] << " " << santa[2][4] << " " << santa[3][4] << " " << santa[4][4] << " " << santa[5][4] << "\n";
        if (santa[j][4] == 1) continue;
        if (santa[j][3] > 0) { //기절한 산타는 한턴 쉼
            santa[j][3]--;
            continue;
        }
        int min_dist = calc(ludolf[0], ludolf[1], santa[j][0], santa[j][1]); //현재거리가 최소거리
        int y = 0, x = 0;
        int move_y = 0;
        int move_x = 0;
        int cantgo = 0;
        for (int i = 0; i < 4; ++i) {
            int ny = santa[j][0] + santa_dy[i];
            int nx = santa[j][1] + santa_dx[i];
            if (map[ny][nx] > 0) { 
                cantgo++;
                continue; } //해당부분에 산타있으면 이동 x
            int curr_dist = calc(ny, nx, ludolf[0], ludolf[1]);
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                y = ny;
                x = nx;
                move_y = santa_dy[i];
                move_x = santa_dx[i];
            }
            else {
                cantgo++; //산타 이동 불가
            }
            if (cantgo == 4) {
                y = santa[j][0];
                x = santa[j][1];
            }
        }
        
        //cout << "\n\n" <<"j : "<<j << " move: " << move_x << " " << move_y << " y,x : " << y << " " << x << "\n\n";
        //cout << "cantgo: " << cantgo << "\n";
        if (cantgo != 4 && santa[j][0] > 0 && santa[j][1] <= n && santa[j][3] == 0 && map[y][x] <= 0)
        {

            map[santa[j][0]][santa[j][1]] = 0;
            santa[j][0] = y;
            santa[j][1] = x;
            //산타 이동

            if (map[y][x] == -1) {
                santa[j][0] -= move_y * d;
                santa[j][1] -= move_x * d;
                if (santa[j][0] <= 0 || santa[j][1] <= 0 || santa[j][0] > n || santa[j][1] > n) {
                    santa[j][4] = 1; //산타 탈락
                }
                santa[j][3] = 1; // 산타 기절
                santa[j][2] += d; //산타 점수 추가
            }
            if(cantgo!=4)
            {
                l_push(j, move_y, move_x); //산타 밀기
            }

            map[santa[j][0]][santa[j][1]] = j;
            ////출력 테스트
            //    for (int i = 1; i <= n; ++i) {
            //        for (int j = 1; j <= n; ++j) {
            //            if (map[i][j] >= 0)
            //                cout << " " << map[i][j];
            //            else
            //                cout << map[i][j];
            //        }
            //        cout << "\n";
            //    }
            //    cout << "\n";

            //
            ////출력 테스트

        }
    }

}





int main() {
    // 여기에 코드를 작성해주세요.

    cin >> n >> m >> p >> c >> d;
    cin >> ludolf[0] >> ludolf[1];
    map[ludolf[0]][ludolf[1]] = -1;



    for (int i = 1; i <= p; ++i) {
        int num, tmp1, tmp2;
        cin >> num;
        cin >> tmp1 >> tmp2;
        santa[num][0] = tmp1;
        santa[num][1] = tmp2;
        map[santa[num][0]][santa[num][1]] = num;

    }
    //입력값 받기 완료

    //m번 만큼 루돌프, 산타 이동
    for (int i = 0; i < m; ++i) {

        //cout << "루돌프 이동" << "\n";
        find_santa();
        //cout << "산타 이동" << "\n";
        find_ludolf();


        int cnt = 0;
        //탈락하지 않은 산타들에게 1점씩 추가
        for (int j = 1; j <= p; ++j) {
            if (santa[j][0] > 0 && santa[j][0] <= n && santa[j][1] > 0 && santa[j][1] <= n) {
            //if(!santa[j][4]){
                santa[j][2]++;
            }
            else {//다 탈락하면 정지
                cnt++;
                if (cnt == p) {
                    for (int k = 1; k <= p; ++k) {
                        cout <<santa[k][2] << " ";
                    }
                    return 0;
                }
            }
        }
    }

     for(int k=1; k<=p; ++k){
         cout<<santa[k][2]<<" ";
     }



    return 0;
}