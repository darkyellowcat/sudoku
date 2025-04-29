#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

const int N = 9;

enum choice { EASY = 64, NORMAL = 49, HARD = 36 };

static void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Sudoku {
public:
    Sudoku() {
        memset(board, 0, sizeof(board));
        //随机种子
        rng.seed(random_device{}());
    }

    bool generateFull() {
        return fillBoard(0, 0);
    }

    void digHoles(int remain) {
        vector<pair<int,int>> cells;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cells.emplace_back(i, j);
        shuffle(cells.begin(), cells.end(), rng);   //打乱

        int to_remove = N*N - remain;
        for (auto &cell : cells) {
            if (to_remove <= 0) break;
            int r = cell.first, c = cell.second;
            int backup = board[r][c];
            board[r][c] = 0;
            if (!hasUniqueSolution()) {
                board[r][c] = backup;
            } else {
                --to_remove;
            }
        }
    }

    void print() const {
        cout << "+-------+-------+-------+" << endl;
        for (int i = 0; i < N; ++i) {
            cout << "| ";
            for (int j = 0; j < N; ++j) {
                cout << (board[i][j] ? board[i][j] : 0) << ' ';
                if ((j+1) % 3 == 0) cout << "| ";
            }
            cout << endl;
            if ((i+1) % 3 == 0)
                cout << "+-------+-------+-------+" << endl;
        }
    }

    void Copy() {
        // memcpy(copyBoard, board, sizeof(board));
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                copyBoard[i][j] = board[i][j];
    }

    void PrintCopy() {
        cout << "+-------+-------+-------+" << endl;
        for (int i = 0; i < N; ++i) {
            cout << "| ";
            for (int j = 0; j < N; ++j) {
                cout << (copyBoard[i][j] ? copyBoard[i][j] : 0) << ' ';
                if ((j+1) % 3 == 0) cout << "| ";
            }
            cout << endl;
            if ((i+1) % 3 == 0)
                cout << "+-------+-------+-------+" << endl;
        }
    }

private:
    int board[N][N];
    int copyBoard[N][N];
    mt19937 rng;

    bool fillBoard(int r, int c) {
        if (r == N) return true;
        int nr = (c == N-1 ? r+1 : r);
        int nc = (c == N-1 ? 0   : c+1);
        if (board[r][c] != 0)
            return fillBoard(nr, nc);

        vector<int> nums(N);
        iota(nums.begin(), nums.end(), 1);
        shuffle(nums.begin(), nums.end(), rng);
        for (int v : nums) {
            if (isValid(r, c, v)) {
                board[r][c] = v;
                if (fillBoard(nr, nc)) return true;
                board[r][c] = 0;
            }
        }
        return false;
    }

    bool isValid(int r, int c, int v) const {
        for (int i = 0; i < N; ++i) {
            if (board[r][i] == v || board[i][c] == v) return false;
        }
        int br = (r/3)*3, bc = (c/3)*3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[br+i][bc+j] == v) return false;
        return true;
    }

    bool hasUniqueSolution() {
        int copyBoard[N][N];
        memcpy(copyBoard, board, sizeof(board));
        int cnt = 0;
        solve(copyBoard, cnt);
        return cnt == 1;
    }

    void solve(int b[N][N], int &cnt) {
        if (cnt > 1) return;
        int r = -1, c = -1;
        for (int i = 0; i < N && r == -1; ++i)
            for (int j = 0; j < N; ++j)
                if (b[i][j] == 0) { r = i; c = j; break; }
        if (r == -1) {
            ++cnt;
            return;
        }
        for (int v = 1; v <= N; ++v) {
            if (isValidStatic(b, r, c, v)) {
                b[r][c] = v;
                solve(b, cnt);
                b[r][c] = 0;
                if (cnt > 1) return;
            }
        }
    }

    bool isValidStatic(int b[N][N], int r, int c, int v) const {
        for (int i = 0; i < N; ++i) {
            if (b[r][i] == v || b[i][c] == v) return false;
        }
        int br = (r/3)*3, bc = (c/3)*3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (b[br+i][bc+j] == v) return false;
        return true;
    }
};

int main() {
    Sudoku game;
    game.generateFull();
    game.Copy();
    cout << "Sudoku has been created successfully:" << endl;

    int remain;
    cout << "Enter number of cells to keep (17-81): ";
    while (!(cin >> remain) || remain < 17 || remain > 81) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 17 and 81: ";
    }
    game.digHoles(remain);
    clear();

    cout << "Puzzle Sudoku:" << endl;
    game.print();

    cout << "Are you ready to see the answer?";
    _getch();
    clear();
    cout << "Sudoku Solution:" << endl;
    game.PrintCopy();

    cout << "Press any key to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
