#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool check(int x){
    x = x % 1000000;
    int a[6] = {0};
    int t = 0;
    while(x > 0){
        a[t] = x % 10;
        x /= 10;
        t++;
    }
    for(int i = 0;i < t - 1;i++){
        for(int j = i + 1;j < t;j++){
            if((a[i] == a[j]) && ((a[i] != 0) && (a[j] != 0))){
                return false;
            }
        }
    }
    return true;
}
int win(int x){
    int turns = x / 1000000;
    x = x % 1000000;
    int a[6] = {0};
    int t = 0;
    while(x > 0){
        a[t] = x % 10;
        x /= 10;
        t++;
    }
    int lines[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},  
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };
    std::sort(a + 3 - 3 * turns, a + 3 - 3 * turns + 3);
    for (int i = 0; i < 8; ++i) {
        bool match = true;
        for (int j = 0; j < 3; ++j) {
            if (a[j + 3 - 3 * turns] != lines[i][j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return (-1 + 2 * turns);
        }
    }
    return 0;
}
void nexts(int *next, int x){
    int turns = x / 1000000;
    x = x % 1000000;
    for(int i = 0;i < 10;i++){
        next[i] = -1;
    }
    int t = 0;
    int a[6] = {0};
    while(x > 0){
        a[t] = x % 10;
        x /= 10;
        t++;
    }
    for(int i = 1;i <= 9;i++){
        bool flag = true;
        for(int j = 0;j < 6;j++){
            if(a[j] == i){
                flag = false;
                break;
            }
        }
        if(flag){
            if(turns == 1){
                next[i] = (1 - turns) * 1000000 + a[0] * 1 + a[1] * 10 + a[2] * 100 + a[4] * 1000 + a[5] * 10000 + i * 100000;
            }else{
                next[i] = (1 - turns) * 1000000 + a[1] * 1 + a[2] * 10 + i * 100 + a[3] * 1000 + a[4] * 10000 + a[5] * 100000;
            }
        }
    }
}

int main(){
    vector<int> a(2000000, 0);
    vector<int> b(2000000, 0);
    bool stop = true;
    int next[10];
    int result;
    int turns = 0;
    for(int i = 0;i < 2000000;i++){
        if(check(i)){
            a[i] = win(i);
            b[i] = a[i];
        }
    }
    while(stop){
        stop = false;
        cout << a[0]  << a[500200] << a[1000200] << a[1500120] << a[350120] << endl;
        for(int i = 0;i < 2000000;i++){
            if(check(i)){
                nexts(next,i);
                if(i / 1000000 == 0){
                    result = -1;
                    for(int j = 0;j < 10;j++){
                        if(next[j] != -1){
                            if(win(next[j]) == 1){
                                result = 1;
                                break;
                            }
                            result = max(result,b[next[j]]);
                        }
                    }
                }else{
                    result = 1;
                    for(int j = 0;j < 10;j++){
                        if(next[j] != -1){
                            if(win(next[j]) == -1){
                                result = -1;
                                break;
                            }
                            result = min(result,b[next[j]]);
                        }
                    }
                }
                if(win(i) != 0){
                    result = win(i);
                }
                a[i] = result;
            }
        }
        for(int i = 0;i < 2000000;i++){
            if(a[i] != b[i]){
                stop = true;
                b[i] = a[i];
            }
        }
        turns++;
    }
    std::cout << turns << std::endl;
    int c;
    int put;
    while(std::cin >> c){
        std::cout << a[c] << endl;
        nexts(next,c);
        for(int i = 0;i < 10;i++){
            if(next[i] != -1){
                if(win(next[i]) == a[c]){
                    put = next[i];
                    cout << put << endl;
                }
                if(a[next[i]] == a[c]){
                    put = next[i];
                    cout << put << endl;
                }
            }
        }
    }
    return 0;
}
