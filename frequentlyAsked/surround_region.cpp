//
// Created by ChanChill on 2020-09-12.
//

//https://leetcode-cn.com/problems/surrounded-regions/

//dfs
void dfs(vector<vector<char>>& board, int x, int y){
    if(x >= board.size() || x < 0 || y < 0 || y >= board[0].size() || board[x][y] != 'O')
        return;
    board[x][y] = 'A';
    dfs(board, x - 1, y);
    dfs(board, x, y - 1);
    dfs(board, x + 1, y);
    dfs(board, x, y + 1);
}

void solve(vector<vector<char>>& board) {
    int m = board.size();
    if(m == 0) return;
    int n = board[0].size();
    for(int i = 0; i < m; i++){
        dfs(board, i, 0);
        dfs(board, i, n - 1);
    }

    for(int i = 1; i < n - 1; i++){
        dfs(board, 0, i);
        dfs(board, m - 1, i);
    }

    for(int i = 0; i < m; i++){
        for(int j =0; j < n; j++){
            if(board[i][j] == 'A') board[i][j] = 'O';
            else if(board[i][j] == 'O') board[i][j] = 'X';
        }
    }
    return;
}


//bfs
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

void solve(vector<vector<char>>& board) {
    int n = board.size();
    if (n == 0) {
        return;
    }
    int m = board[0].size();
    queue<pair<int, int>> que;
    for (int i = 0; i < n; i++) {
        if (board[i][0] == 'O') {
            que.emplace(i, 0);
        }
        if (board[i][m - 1] == 'O') {
            que.emplace(i, m - 1);
        }
    }
    for (int i = 1; i < m - 1; i++) {
        if (board[0][i] == 'O') {
            que.emplace(0, i);
        }
        if (board[n - 1][i] == 'O') {
            que.emplace(n - 1, i);
        }
    }
    while (!que.empty()) {
        int x = que.front().first, y = que.front().second;
        que.pop();
        board[x][y] = 'A';
        for (int i = 0; i < 4; i++) {
            int mx = x + dx[i], my = y + dy[i];
            if (mx < 0 || my < 0 || mx >= n || my >= m || board[mx][my] != 'O') {
                continue;
            }
            que.emplace(mx, my);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'A') {
                board[i][j] = 'O';
            } else if (board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }
}

//union find
//look in the related file