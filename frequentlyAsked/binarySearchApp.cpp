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
