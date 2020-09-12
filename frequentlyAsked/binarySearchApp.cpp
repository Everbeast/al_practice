//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/koko-eating-bananas/
int minEatingSpeed(vector<int>& piles, int H) {
    int minS = 1,  maxS = 1;
    for(int i = 0; i < piles.size(); i++){
        maxS = max(maxS, piles[i]);
    }
    int left = 1, right = maxS;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(canFinish(piles, H, mid)){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return left;
}

bool canFinish(vector<int>& piles, int H, int speed){
    long cnt = 0;
    for(int i = 0; i < piles.size(); i++){
        if(piles[i] <= speed){
            cnt++;
        }else{
            cnt+=piles[i] / speed + 1;
        }
    }
    return cnt <= H;
}

//https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/
int shipWithinDays(vector<int>& weights, int D) {
    int minW = 0;
    int maxW = 0;
    int n = weights.size();
    for(int i = 0; i < n; i++){
        minW = max(minW, weights[i]);
        maxW += weights[i];
    }

    while(minW <= maxW){
        int mid = minW + (maxW - minW) / 2;
        if(canFinish(weights, D, mid)){
            maxW  = mid - 1;
        }
        else{
            minW = mid + 1;
        }
    }
    return minW;
}

bool canFinish(vector<int>& weights, int D, int cap){
    int i = 0;
    for(int day = 0; day < D; day++){
        int maxCap = cap;

        while((maxCap -= weights[i]) >= 0){
            i++;
            if(i == weights.size())
                return true;
        }
    }
    return false;
}


//
bool isSubsequence(string s, string t) {
    int m = s.size();
    int n = t.size();
    vector<vector<int>> index(256); //直接字母的ascii码作为索引
    for(int i = 0; i < n; i++){
        char c = t[i];
        index[c].push_back(i);
    }

    int j = 0;
    for(int i = 0; i < m; i++){
        char c = s[i];
        if(index[c].empty())
            return false;


        int pos = left_bound(index[c], j);
        if(pos == index[c].size())
            return false;
        j = index[c][pos] + 1; //找到c相同的位置 +1指向下一个 即为寻找和s[i + 1]的字符
    }
    return true;
}

int left_bound(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    int left = 0;
    int right = nums.size() - 1; // 注意

    while (left <= right) { // 注意
        int mid = left + (right - left) / 2;
        if(nums[mid] == target){
            right = mid - 1;
        }else if(nums[mid] > target){
            right = mid - 1;
        }else if(nums[mid] < target){
            left = mid + 1;
        }
    }
    // if(left >= nums.size() || nums[left] != target) return -1; //遇到只有nums只有一个的时候 left==num.size 表示找不到
                                                                    //left == -1时 应该会回nums[0]的数字
    return left;
}