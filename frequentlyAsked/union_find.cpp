//
// Created by ChanChill on 2020-09-12.
//
class UF{
    int count; //记录连通分量
    vector<int> parent;
    vector<int> size; //存储树的大小
public:
    UF(int n){
        this->count = n;
        parent = vector<int>(n);
        size = vector<int>(n, 1); //每棵树大小为1
        for(int i = 0; i < n; i++){
            parent[i] = i; //parent指向自己
        }
    }

    void connect(int p, int q){
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ) return;

        if(size[rootQ] > size[rootP]){
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }else{
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
        count--;
    }

    int find(int x){
        while(parent[x] != x){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool connected(int p, int q){
        int rootP = find(p);
        int rootQ = find(q);
        return rootQ == rootP;
    }

};


//applicate in surroud region
//https://leetcode-cn.com/problems/surrounded-regions/

class Solution {
public:
    //虚拟节点 为m*n
    //二维压缩为1维： x*n + y
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        if(m == 0) return;
        int n = board[0].size();

        UF uf = UF(m * n + 1);
        int dummy = m * n;
        //将边界上的0和dummy连通
        for(int i = 0; i < m; i++){
            if(board[i][0] == 'O'){
                uf.connect(dummy, i * n);
            }
            if(board[i][n - 1] == 'O'){
                uf.connect(dummy, i * n + n - 1);
            }
        }

        for(int i = 0; i < n; i++){
            if(board[0][i] == 'O'){
                uf.connect(dummy, i);
            }
            if(board[m - 1][i] == 'O'){
                uf.connect(dummy, n * (m - 1) + i);
            }
        }

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        for(int i = 1; i < m - 1; i++){
            for(int j = 1; j < n - 1; j++){
                if(board[i][j] == 'O'){
                    for(int k = 0; k < 4; k++){
                        int x = i + dx[k];
                        int y = j + dy[k];
                        if(board[x][y] == 'O'){
                            uf.connect(i * n + j, x * n + y);
                        }
                    }
                }
            }
        }

        for(int i = 1; i < m - 1; i++){
            for(int j = 1; j < n - 1; j++){
                if(!uf.connected(dummy, i * n + j)){
                    board[i][j] = 'X';
                }
            }
        }
    }
};

//判断等式的连通性
//https://leetcode-cn.com/problems/satisfiability-of-equality-equations/
bool equationsPossible(vector<string>& equations) {
    UF uf = UF(26); //26个字母
    for(auto equation : equations){
        if(equation[1] == '='){
            char a = equation[0];
            char b = equation[3];
            uf.connect(a - 'a', b - 'a');
        }
    }
    for(auto equation : equations){
        if(equation[1] == '!'){
            char a = equation[0];
            char b = equation[3];
            if(uf.connected(a - 'a', b - 'a')){
                return false;
            }
        }
    }
    return true;
}
