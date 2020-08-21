//
// Created by ChanChill on 2020-08-21.
//


//Given a collection of intervals,
// find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
//

//链接：https://leetcode-cn.com/problems/non-overlapping-intervals

static bool cmp(const vector<int>& a, const vector<int>& b){
    return a[1] < b[1];
}
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if(intervals.size() == 0) return 0;
    sort(intervals.begin(), intervals.end(), cmp);

    int count = 1;
    int x_end = intervals[0][1];
    for(int i = 0; i < intervals.size(); i++){
        int start = intervals[i][0];
        if(start >= x_end){
            count ++;
            x_end = intervals[i][1];
        }
    }
    return intervals.size() - count;
}

//最少箭射完全部气球
//气球的宽度用points的[][0]到points[][1]来表示， 重合的部分能用一支箭全部射穿
//其实就是求不重合的的区间

//https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons/

static bool cmp(const vector<int>& a, const vector<int>& b){
    return a[1] < b[1];
}
int findMinArrowShots(vector<vector<int>>& points) {
    if(points.size() == 0) return 0;
    sort(points.begin(), points.end(), cmp);

    int x_end = points[0][1];
    int count = 1;
    for(int i = 0; i < points.size(); i++){
        int start = points[i][0];
        if(start > x_end){
            count++;
            x_end = points[i][1];
        }
    }
    return count;
}
