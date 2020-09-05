//
// Created by ChanChill on 2020-09-05.
//
//回溯法 框架

//result = []
//def backtrack(路径, 选择列表):
//    if 满足结束条件:
//        result.add(路径)
//        return
//
//    for 选择 in 选择列表:
//        做选择
//        backtrack(路径, 选择列表)
//        撤销选择

//子集
//https://leetcode-cn.com/problems/subsets/
vector<vector<int>> res;
vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> track;
    backtrack(nums, track, 0);
    return res;
}

void backtrack(vector<int>& nums, vector<int>& track, int start){
    res.push_back(track);
    for(int i = start; i < nums.size(); i++){
        track.push_back(nums[i]);
        backtrack(nums, track, i + 1);
        track.pop_back();
    }
}


//全排列
//https://leetcode-cn.com/problems/permutations/
vector<vector<int>> res;
vector<vector<int>> permute(vector<int>& nums) {
    vector<int> track;
    backtrack(nums, track);
    return res;
}

void backtrack(vector<int>& nums, vector<int>& track){
    if(track.size() == nums.size()){
        res.push_back(track);
        return;
    }

    for(int i = 0; i < nums.size(); i++){
        int have = 0;
        for(int j = 0; j < track.size(); j++){
            if(track[j] == nums[i]) have = 1;
        }
        if(have == 1) continue;
        // 以上实现if(track.contain(nums[i])) continue;


        track.push_back(nums[i]);
        backtrack(nums, track);
        track.pop_back();
    }
}


//组合
//https://leetcode-cn.com/problems/combinations/
//给n个数字，求k个数字的全部组合

vector<vector<int>> res;
vector<vector<int>> combine(int n, int k) {
    if(n <= 0 || k <= 0) return res;
    vector<int> track;
    backtrack(n, k, 1, track);
    return res;
}

void backtrack(int n, int k, int start, vector<int>& track){
    if(track.size() == k){
        res.push_back(track);
        return;
    }
    for(int i = start; i <= n; i++){
        track.push_back(i);
        backtrack(n, k, i + 1, track);
        track.pop_back();
    }
}


//八皇后
//https://leetcode-cn.com/problems/n-queens/
class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return res;
    }

    void backtrack(vector<string>& board, int row){
        if(row == board.size()){
            res.push_back(board);
            return;
        }

        int n = board[row].size();
        //循环选择列表
        for(int col = 0; col < n; col++){
            //先排除
            if(!isValid(board, row, col)){
                continue;
            }
            //做选择
            board[row][col] = 'Q';
            //下一个决策
            backtrack(board, row + 1);
            //撤销选择
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col){
        int n = board.size();
        //检查该列
        for(int i = row; i >= 0; i--){
            if(board[i][col] == 'Q')
                return false;
        }
        //检查左斜上方
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
            if(board[i][j] == 'Q')
                return false;
        }
        //检查右斜上方
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++){
            if(board[i][j] == 'Q')
                return false;
        }
        return true;
    }
};


//解数独
//https://leetcode-cn.com/problems/sudoku-solver/
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0, 0);
        return;
    }

    bool backtrack(vector<vector<char>>& board, int i, int j){
        int m = 9, n = 9;
        if(j == n){
            return backtrack(board, i + 1, 0); //遍历下一行
        }
        if(i == m) return true; //全部都遍历完 有可行解

        if(board[i][j] != '.'){
            return backtrack(board, i, j + 1); //是预设数字 下一个
        }

        for(char ch = '1'; ch <= '9'; ch++){
            if(!isValid(board, ch, i, j)){
                continue;
            }

            board[i][j] = ch;
            //该格子有可行解 立即返回
            if(backtrack(board, i, j + 1)){
                return true;
            }
            board[i][j] = '.';
        }
        return false; //无可解
    }

    bool isValid(vector<vector<char>>& board, char ch, int r, int c){
        for(int i = 0; i < 9; i++){
            if(board[i][c] == ch) return false;
            if(board[r][i] == ch) return false;
            if(board[(r/3)*3 + i/3][(c/3)*3 + i%3] == ch) return false;
        }
        return true;
    }
};


//给定数目 求解所有合法组成的左右括号
//https://leetcode-cn.com/problems/generate-parentheses/
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string track;
        backtrack(n , n, res, track);
        return res;
    }

    void backtrack(int left, int right, vector<string>& res, string& track){
        if(right < left) return;
        if(left < 0 || right < 0) return;
        if(left == 0 && right == 0){
            res.push_back(track);
            return;
        }

        //try push '('
        track.push_back('(');
        backtrack(left - 1, right, res, track);
        track.pop_back();

        //try push ')'
        track.push_back(')');
        backtrack(left, right - 1, res, track);
        track.pop_back();
    }
};