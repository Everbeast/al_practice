//
// Created by ChanChill on 2020-09-11.
//
//merge intervals
//合并
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> ans;
    if(intervals.empty()) return ans;
    sort(intervals.begin(), intervals.end());
    int font=intervals[0][0];
    int rear=intervals[0][1];
    for(int i=1; i<intervals.size(); ++i){
        if(intervals[i][0]>rear){
            ans.push_back({font, rear});
            font = intervals[i][0];
            rear = intervals[i][1];
        }
        else if(intervals[i][0]<=rear && intervals[i][1]>=rear){
            rear = intervals[i][1];
        }
    }
    ans.push_back({font,rear});
    return ans;
}

//intersection
//区间交集
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> ans;
    int i = 0, j = 0;
    while(i < A.size() && j < B.size()){
        int a1 = A[i][0], a2 = A[i][1];
        int b1 = B[j][0], b2 = B[j][1];
        if(a1 <= b2 && a2 >= b1){

            ans.push_back({max(a1, b1), min(a2, b2)});
        }
        if(a2 > b2) j++;
        else i++;
    }
    return ans;
}
