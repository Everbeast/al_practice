//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/sliding-puzzle/
int slidingPuzzle(vector<vector<int>>& board) {
    int m = 2, n = 3;
    vector<vector<int>> neighbour = {
            {1, 3},
            {0, 2, 4},
            {1, 5},
            {0, 4},
            {1, 3, 5},
            {2, 4}
    };

    string start;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            start += board[i][j] + '0';
        }
    }

    string target = "123450";

    //bfs
    unordered_set<string> visited;
    queue<string> q;
    q.push(start);
    visited.insert(start);

    int step = 0;
    while(!q.empty()){
        int len = q.size();
        for(int i = 0; i < len; i++){
            string cur = q.front();q.pop();
            if(cur == target){
                return step;
            }
            //find 0
            int idx = 0;
            for(;cur[idx] != '0'; idx++);
            for(int nb : neighbour[idx]){
                string new_board = cur;
                swap(new_board[nb], new_board[idx]);

                if(!visited.count(new_board)){
                    q.push(new_board);
                    visited.insert(new_board);
                }
            }
        }
        step++;
    }
    return -1;

}
}