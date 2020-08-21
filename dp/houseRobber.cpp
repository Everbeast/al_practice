//
// Created by ChanChill on 2020-08-21.
//
//
//https://leetcode-cn.com/problems/house-robber
//给定一串数，代表每家房子有的金钱，当你偷相邻的两家钱就会引起报警。
//求能偷取的最多金钱

int rob(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    vector<int> memo(n, -1);
    return dp(nums, 0, memo);
}

int dp(vector<int>& nums, int start, vector<int>& memo){
    int n = nums.size();
    if(start >= n) return 0;
    if(memo[start] != -1){
        //偷过了
        return memo[start];
    }
    int res = max(dp(nums, start + 1, memo), //不偷此间，偷下一间
                  nums[start] + dp(nums, start + 2, memo)); //偷此间，偷下下间

    memo[start] = res;
    return res;
}
//观察得至于相邻的+1 和 +2有关 ，可以压缩空间，因为需要先算后面的 因此遍历顺序需要从后到前

int rob(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;

    int dp_0 = 0, dp_1 = 0, dp_2 = 0;
    for(int i = n - 1; i >= 0; i--){
        dp_0 = max(dp_1, dp_2 + nums[i]);
        dp_2 = dp_1;
        dp_1 = dp_0;
    }
    return dp_0;
}


//https://leetcode-cn.com/problems/house-robber-ii/submissions/
//把可偷的家变成一个环
//即第一个和最后一个不能同时偷
//即有三种情况 1 偷first 不偷last  2偷last 不偷first  3两个都不偷
//因为#3肯定比 #1 #2的金钱都要少 因此 只有两种情况，只用调用上述函数 加个开始和结束的限制即可

int rob(vector<int>& nums){
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    return max(dp(nums, 0, n-2), dp(nums, 1, n-1));
}

int dp(vector<int>& nums, int start, int end) {
    int dp_0 = 0;
    int dp_1 = 0, dp_2 = 0;
    for(int i = end; i >= start; i--){
        dp_0 = max(dp_1, dp_2 + nums[i]);
        dp_2 = dp_1;
        dp_1 = dp_0;
    }
    return dp_0;
}


//可偷的家变成树结构

//暴力递归法
int rob(TreeNode* root) {
    if(root == NULL) return 0;
    int do_it = root->val +
                (root->left == NULL ? 0 :rob(root->left->left) + rob(root->left->right)) +
                (root->right == NULL ? 0 : rob(root->right->left) + rob(root->right->right));

    int not_do = rob(root->left) + rob(root->right);
    int res = max(do_it, not_do);
    return res;
}

//memo法
map<TreeNode*, int> memo;
int rob(TreeNode* root) {
    if(root == NULL) return 0;
    if(memo.find(root) != memo.end()) return memo[root];
    int do_it = root->val +
                (root->left == NULL ? 0 :rob(root->left->left) + rob(root->left->right)) +
                (root->right == NULL ? 0 : rob(root->right->left) + rob(root->right->right));

    int not_do = rob(root->left) + rob(root->right);
    int res = max(do_it, not_do);
    memo[root] = res;
    return res;
}



//拓展 分治法？
//表示偷。 不偷
//vector<int> res[0] res[1]
int rob(TreeNode* root) {
    if(root == NULL) return 0;
    vector<int> res = dp(root);
    return max(res[0], res[1]);
}

vector<int> dp(TreeNode* root){
    vector<int> res(2, 0);
    if(root == NULL) return res;

    vector<int> left = dp(root->left);
    vector<int> right = dp(root->right);

    //本节点不偷 则左右可以偷或者不偷
    res[0] = max(left[0], left[1]) + max(right[0], right[1]);
    //本节点偷 则左右不偷
    res[1] = left[0] + right[0] + root->val;
    return res;
}