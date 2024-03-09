#include <iostream>
#include <vector>
using namespace std;

int N; 
vector<vector<int>> solutions;
vector<vector<int>> board;

bool isSafe(int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;
    return true;
}

bool solveNQUtil(int col) {
    if (col >= N) {
        vector<int> solution;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j]) solution.push_back(j + 1);
        solutions.push_back(solution);
        return true;
    }

    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            res = solveNQUtil(col + 1) || res;
            board[i][col] = 0; 
        }
    }
    return res;
}

void solveNQ() {
    if (!solveNQUtil(0)) {
        cout << "Solution does not exist\n";
        return;
    }

    for (int i = 0; i < solutions.size(); i++) {
        cout << "Solution " << i + 1 << ":\n";
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                cout << (k + 1 == solutions[i][j] ? "Q " : "- ");
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main() {
    cout << "Enter the size of the chessboard: ";
    cin >> N;

    
    if (N <= 0) {
        cout << "The size of the chessboard must be a positive integer.\n";
        return 1;
    }

    board.resize(N, vector<int>(N, 0)); 

    solveNQ();
    return 0;
}
