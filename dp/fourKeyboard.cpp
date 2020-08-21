//
// Created by ChanChill on 2020-08-20.
//
//只有4个按键 1 在屏幕上打印'A'
//           2 全选屏幕上的所有'A'
//           3 复制选中的所有'A'
//           4 粘贴复制的所有'A'到屏幕上
//给定按键次数N， 求进行上诉一系列操作后得到的屏幕最多的A的数目

int maxA(int N){
    return dp(N, 0, 0);
}

int dp(int N, int a_num, int c_num){
    //dp(剩余的操作次数，屏幕的a的数目， 复制的数目）
    if(N > 0){
        return  max(max(dp(N - 1, a_num + 1, c_num), //1
                      dp(N - 1, a_num + c_num, c_num)), //粘贴
                      dp(N - 2, a_num, a_num) //全选+复制
                );
    }
    else{
        return a_num;
    }
}

//上述方法超时

//发现最后的按键 只有两种可能：按A | 粘贴
//dp[i]表示点击i次按键 屏幕出现的A的数目
//因为 全选+复制 是连在一起的
//需要记录 粘贴的时候 复制了多少个A， 即 在j步粘贴的时候，j-2则为复制A的数目
int maxA(int N){
    vector<int> dp(N + 1, 0);
    for(int i = 1; i <= N; i++){
        dp[i] = dp[i-1] + 1; //按键a
        //找在哪一步粘贴最多；
        for(int j = 2; j < i; j++){
            //j-2为复制的a的数目，i-j为复制的次数，则得到的数目就是x*（i-j+1） //复制1次 为两倍， 复制2次，为三倍
            dp[i] = max(dp[i], dp[j-2]*(i-j+1));
        }
    }
    return dp[N];
}
