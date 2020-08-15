//
// Created by ChanChill on 2020-08-15.
//题目
//题目是这样：你面前有一栋从 1 到 N 共 N 层的楼，然后给你 K 个鸡蛋（K 至少为 1）。
// 现在确定这栋楼存在楼层 0 <= F <= N，在这层楼将鸡蛋扔下去，鸡蛋恰好没摔碎（高于 F 的楼层都会碎，低于 F 的楼层都不会碎）。
// 现在问你，最坏情况下，你至少要扔几次鸡蛋，才能确定这个楼层 F 呢？

//状态： 鸡蛋个数 层数
//选择： 去哪层扔鸡蛋
//状态转移：
//    第i层扔 若鸡蛋碎了 k-1， 在i-1及一下层数再扔
//               没碎  k不变， 在i+1到n层再扔

//暴力
int superEggDrop(int K, int N) {
    return dp(K, N);
}
int dp(int K, int N){
    //base case
    if(K == 1) return N;
    if(N == 0) return 0;

    int res = INT_MAX;
    for(int i = 1; i<=N; i++){
        res = min(res,
                  max(
                          dp(K - 1, i - 1),
                          dp(K, N - i)
                  ) + 1
        );
    }
    return res;

}

//memo法
int superEggDrop(int K, int N) {
    map<string, int> memo;
    return dp(K, N, memo);
}
int dp(int K, int N, map<string, int>& memo){
    //base case
    if(K == 1) return N;
    if(N == 0) return 0;

    if(memo.find(to_string(K) + "," + to_string(N)) != memo.end())
        return memo.find(to_string(K) + "," + to_string(N))->second;

    int res = INT_MAX;
    for(int i = 1; i<=N; i++){
        res = min(res,
                  max(
                          dp(K - 1, i - 1, memo),
                          dp(K, N - i, memo)
                  ) + 1
        );
    }
    memo[to_string(K) + "," + to_string(N)] = res;
    return res;
}

//二分查找法
int superEggDrop(int K, int N) {
    map<string, int> memo;
    return dp(K, N, memo);
}
int dp(int K, int N, map<string, int>& memo){
    //base case
    if(K == 1) return N;
    if(N == 0) return 0;

    if(memo.find(to_string(K) + "," + to_string(N)) != memo.end())
        return memo.find(to_string(K) + "," + to_string(N))->second;

    int res = INT_MAX;

    while(lo <= hi){
        int mid = (lo + hi)/2;
        int broken = dp(K - 1, mid - 1, memo);
        int not_broken = dp(K, N - mid, memo);
        if(broken > not_broken){
            hi = mid - 1;
            res = min(res, broken + 1);
        }
        else{
            lo = mid + 1;
            res = min(res, not_broken + 1);
        }
    }

    memo[to_string(K) + "," + to_string(N)] = res;
    return res;
}

//改变dp状态
int superEggDrop(int K, int N) {
    //dp[k][m] 表示k个鸡蛋尝试m次能测试的最多层数
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));//线性情况最多尝试N次
    int m = 0;
    //for(int m = 1; dp[K][m] < N; m++){
    while(dp[K][m] < N){
        m++;
        for(int k = 1; k <= K; k++){
            dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
        }
    }
    return m;
}