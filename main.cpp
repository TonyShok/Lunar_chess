#include<iostream>
using namespace std;
class condition{
    public:
    void initial();
    void clear();
    bool add_chess(int place);
    int check_win();
    void print_chess();

    int chess[9];
    int turns;
};

void condition::initial(){
    for(int i = 0;i < 9;i++){
        chess[i] = 0;
    }
    turns = 0;
};
void condition::clear(){
    for(int i = 0;i < 9;i++){
        if(chess[i] > 6){
            chess[i] = 0;
        }
    }
};
bool condition::add_chess(int place){
    if((place < 0) || (place > 8)){
        cout << "stop" << endl;
        return false;
    }
    if(chess[place] != 0){
        cout << "invalid input" << endl;
        return false;
    }
    for(int i = 0;i < 9;i++){
        if(chess[i] > 0){
            chess[i]++;
        }
    }
    turns++;
    chess[place] = 1;
    return true;
};
int condition::check_win(){
        int lines[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (int i = 0; i < 8; i++) {
            int a = lines[i][0], b = lines[i][1], c = lines[i][2];
            if (chess[a] % 2 != 0 && chess[b] % 2 != 0 && chess[c] % 2 != 0) {
                return ((1 + turns) % 2);
            }
            if (chess[a] != 0 && chess[b] != 0 && chess[c] != 0 &&
                chess[a] % 2 == 0 && chess[b] % 2 == 0 && chess[c] % 2 == 0) {
                return (turns % 2);
            }
        }
        return 2;
    };
    void condition::print_chess(){
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(((chess[3 * i + j] + turns) % 2 == 1) && (chess[3 * i + j] > 0)){
                    cout << "o" << " ";
                }else if(chess[3 * i + j] == 0){
                    cout << "_ ";
                }else{
                    cout << "x" << " ";
                }
            }
            cout << endl;
        }
        cout << turns << endl;
    };

int main(){
    condition board;
    board.initial();
    int c;
    int win = 0;
    while(cin >> c){
        if(c == 0){
            break;
        }
        if(board.add_chess(c - 1)){
            board.clear();
            win = board.check_win();
            board.print_chess();
            if(win == 0){
                cout << "x wins" << endl;
                break;
            }else if(win == 1){
                cout << "o wins" << endl;
                break;
            }
        }
    }
    return 0;
}
