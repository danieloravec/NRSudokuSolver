#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define UNVISITED -1
#define VISITED 1
#define mp(a, b) make_pair(a, b)

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<vll> vvll;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<bool> vb;
const ll N = 3456789;

int grid[9][9];
bool fix[9][9];

bool row(int r, int c) {
    for(int i = 0; i < 9; i++)
        if(i != c && grid[r][c] == grid[r][i])
            return false;
    return true;
}
bool col(int r, int c) {
    for(int i = 0; i < 9; i++)
        if(i != r && grid[i][c] == grid[r][c])
            return false;
    return true;
}

bool box(int r, int c) {
    int sr = (r / 3) * 3, sc = (c / 3) * 3;
    for(int i = sr; i < sr + 3; i++)
        for(int j = sc; j < sc + 3; j++)
            if(i != r && j != c && grid[i][j] == grid[r][c])
                return false;
    return true;
}

bool forward(int &row, int &col) {
    do {
        if(col < 8) col++;
        else if(row < 8) { row++; col = 0; }
        else return false;
        if(!fix[row][col]) return true;
    } while(fix[row][col]);
    return true;
}

bool back(int &row, int &col) {
    do {
        if(col > 0) col--;
        else if(row > 0) { row--; col = 8; }
        else return false;
        if(!fix[row][col]) return true;
    } while(fix[row][col]);
    return true;
}

bool solve() {
    int r = 0, c = 0;
    while(true) {
        if(!fix[r][c]) {
            if(grid[r][c] < 8) {
                bool upd = false;
                for(int i = grid[r][c] + 1; i <= 8; i++) {
                    grid[r][c] = i;
                    if(row(r, c) && col(r, c) && box(r, c)) {
                        upd = true;
                        bool sol = forward(r, c);
                        if(!sol) return true;
                        break;
                    }
                }
                if(!upd) {
                    grid[r][c] = -1;
                    bool sol = back(r, c);
                    if(!sol)
                        return false;
                }
            }
            else {
                grid[r][c] = -1;
                bool sol = back(r, c);
                if(!sol)
                    return false;
            }
        }
        else {
            bool sol = forward(r, c);
            if(!sol) return true;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cin >> t; t--;
            grid[i][j] = t;
            if(t != -1) fix[i][j] = 1;
            else fix[i][j] = 0;
        }
    }
    bool sol = solve();
    if(sol) {
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                cout << grid[i][j] + 1 << (j < 8 ? ' ' : '\n');
        cout << '\n';
    }
    else cout << "UNSOLVABLE!!!\n";


    return 0;
}