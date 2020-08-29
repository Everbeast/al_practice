//
// Created by ChanChill on 2020-08-29.
//

//大根二叉堆




class MaxPQ{

private:
    vector<int> pq;
    int N; //pq的元素

public:
    MaxPQ(int cap):N(cap){
        pq = new vector<int>(N+1, 0); //多创建一个空间 0位置不用
    }

    int max(){
        return pq[1];
    }

    void insert(int e){
        N++;
        pq[N] = e;
        swim(N);

    }

    int deleteMax(){
        int res = pq[1];
        exch(1, N);
        pq[N] == NULL;
        N--;
        sink(1);
        return res;

    }

private:
    int parent(int root) {
        return root / 2;
    }

// 左孩子的索引
    int left(int root) {
        return root * 2;
    }

// 右孩子的索引
    int right(int root) {
        return root * 2 + 1;
    }

    void exch(int i, int j){
        int temp = pq[i];
        pq[i] = pq[j];
        pq[j] = temp;
    }

    //pq[i] 是否比 pq[j] 小？
    bool less(int i, int j){
        return pq[i] < pq[j] ? true : false;
    }

    void swim(int k){
        while(k > 1 && less(parent(k), k)){
            exch(parent(k, k);
            k = parent(k);
        }
    }

    void sink(int k){
        while(left(k) < N){
            int older = left(k);
            if(right(k) < N && less(older, right(k))){
                older = right(k);
            }
            if(less(older, k)) break;
            exch(older, k);
            k = older;
        }
    }

};

