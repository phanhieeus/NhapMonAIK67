// tictactoe.cpp: Sử dụng Minimax, triển khai AI để chơi Tic-Tac-Toe.

#include <bits/stdc++.h>

using namespace std;

int const SIZE = 3; //
char X = 'X';
char O = 'O';
char legalMove = ' ';

// define a state: 2D array, size = 3x3
typedef vector<vector<char>> State;
State initial_state = vector(SIZE, vector<char>(SIZE, legalMove));

void renderState(State s)
{
    // print state s to the terminal
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            cout << "| " << s[i][j] << ' ';
        }
        cout << "|\n";
    }
    cout << endl;
    return;
}

pair<bool, int> checkFinalState(State state)
{
    // check if state is a final state, calculate score: X win 1, O win -1, draw 0.
    int score;
    //check rows
    for (int i=0; i<SIZE; i++){
        if (state[i][0]==state[i][1] && state[i][0]==state[i][2] && state[i][0]!=legalMove){
            if (state[i][0]==X) score = 1;
            else score = -1;
            return make_pair(true, score);
        }
    }
    //check cols
    for (int i=0; i<SIZE; i++){
        if (state[0][i]==state[1][i] && state[0][i]==state[2][i] && state[0][i]!=legalMove){
            if (state[0][i]==X) score = 1;
            else score = -1;
            return make_pair(true, score);
        }
    }
    //check diagonals
    if (state[0][0]==state[1][1] && state[0][0]==state[2][2] && state[0][0]!=legalMove){
            if (state[1][1]==X) score = 1;
            else score = -1;
            return make_pair(true, score);
        }
    if (state[0][2]==state[1][1] && state[0][2]==state[2][0] && state[1][1]!=legalMove){
            if (state[1][1]==X) score = 1;
            else score = -1;
            return make_pair(true, score);
        }
    //check if draw state
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            if (state[i][j]==legalMove) return make_pair(false, 0);
        }
    }
    return make_pair(true, 0);
}

char player(State state)
{
    //input: state, output: which player’s turn it is (X or O).
    int countX = 0;
    int countO = 0;
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            if (state[i][j]==X) countX++;
            else if (state[i][j]==O) countO++;
        }
    }
    if (countX==countO) return X;
    return O;
}

State play(State state, int i, int j)
{
    //
    State s = state;
    if (player(state)==X) s[i][j] = X;
    else s[i][j] = O;
    return s;
}

vector<State> nextStates(State s){
    // return all valid next state of s
    vector<State> nextStates;
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            State nextState;
            if (s[i][j]==legalMove){
                nextState = play(s, i, j);
                nextStates.push_back(nextState);
            }
        }
    }
    return nextStates;
}

int getScore(State s){
    // return score of state s;
    pair p = checkFinalState(s);
    if (p.first){
        return p.second;
    }
    //TODO: return score of next state
    int score=-10;
    if (player(s)==X){
        for (State nextState: nextStates(s)){
            if (getScore(nextState)>score || score==-10) score=getScore(nextState);
        }
    }
    else {
        for (State nextState: nextStates(s)){
            if (getScore(nextState)<score || score==-10) score=getScore(nextState);
        }
    }
    return score;
}

State bestNextState(State s){

    for (State nextState: nextStates(s)){
        if (getScore(s)==getScore(nextState)){
            return nextState;
        }
    }
}

void firstMove(State &s){
    //first computer's move when you chosse O
    int i, j;
    srand (time(NULL));
    i = rand() % 3;
    j = rand() % 3;
    s = play(s, i, j);
    renderState(s);
    return;
}

void runner(){
    State s = initial_state;
    cout << "Choose your player (X or O): ";
    char humanPlayer;
    cin >> humanPlayer;
    if (humanPlayer == O) firstMove(s);
    while (!checkFinalState(s).first){
        if (humanPlayer == player(s)){
            int i, j;
            cout << "Your turn: ";
            cin >> i >> j;
            if (i>=0 && j>=0 && i<SIZE && j<SIZE){
                if (s[i][j] == legalMove){
                    s = play(s, i, j);
                    renderState(s);
                }
            }
            else {
                cout << "Invalid move" << endl;
            }
        }
        else{
            cout << "Computer's turn: " << endl;
            s = bestNextState(s);
            renderState(s);
        }
    }
    if (checkFinalState(s).second==1) cout << "X won";
    else if (checkFinalState(s).second==-1) cout << "O won";
    else cout << "Draw";
    return;
}

int main()
{
    runner();
    return 0;
}
