//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/exam-room/
//用set来使得segment分段
//用哈希表 记录本已有的segment的对应的左右部分 用于合并
struct Segment {
    int l, r, no, dist;
    bool operator<(const Segment &that) const {
        return dist > that.dist || (dist == that.dist && no < that.no);
    }
};

class ExamRoom {
    int N;
    unordered_map<int, vector<Segment>> left, right;
    set<Segment> s;
    void add_segment(int l, int r) {
        l = max(l, 0);
        r = min(r, N - 1);
        if (r < l)
            return;
        int mid = (l + r) / 2;
        int dist = mid - l + 1;
        if (l == 0 && r != 0) { //避免只有0位置空出来的时候 使得dist = 0
            mid = 0;
            dist = r;
        } else if (r == N - 1) {
            mid = N - 1;
            dist = r - l + 1;
        }
        Segment new_segment {l, r, mid, dist};
        s.insert(new_segment);
        left[r].emplace_back(new_segment);
        right[l].emplace_back(new_segment);
    }

    void remove_segment(Segment &segment) {
        auto [l, r, no, dist] = segment;
        s.erase(segment);
        left[r].clear();
        right[l].clear();
    }

public:
    ExamRoom(int N) {
        this->N = N;
        Segment start{0, N - 1, 0, N};
        s.insert(start);
        right[0].emplace_back(start);
        left[N - 1].emplace_back(start);
    }

    int seat() {
        Segment best = *s.begin();
        remove_segment(best);
        auto [l, r, no, dist] = best;
        add_segment(l, no - 1);
        add_segment(no + 1, r);
        return no;
    }

    void leave(int p) {
        int l = p, r = p;
        if (!left[p - 1].empty()) {
            Segment ls = left[p - 1][0];
            l = ls.l;
            remove_segment(ls);
        }
        if (!right[p + 1].empty()) {
            Segment rs = right[p + 1][0];
            r = rs.r;
            remove_segment(rs);
        }
        add_segment(l, r);
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
