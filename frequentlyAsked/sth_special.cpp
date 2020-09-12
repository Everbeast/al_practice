//
// Created by ChanChill on 2020-09-12.
//
//https://leetcode-cn.com/problems/nim-game/
//你和你的朋友面前有一堆石子，你们轮流拿，一次至少拿一颗，最多拿三颗，谁拿走最后一颗石子谁获胜。
//是4的倍数就我必输
bool canWinNim(int n) {
    return n % 4 != 0;
}


//https://leetcode-cn.com/problems/stone-game/
//你和你的朋友面前有一排石头堆，用一个数组 piles 表示，piles[i] 表示第 i 堆石子有多少个。
// 你们轮流拿石头，一次拿一堆，但是只能拿走最左边或者最右边的石头堆。所有石头被拿完后，谁拥有的石头多，谁获胜。
//石头的总数为奇数
//先出手的必赢
bool stoneGame(vector<int>& piles) {
    return true;
}



//关灯游戏
//https://leetcode-cn.com/problems/bulb-switcher/
//有 n 盏电灯，最开始时都是关着的。现在要进行 n 轮操作：
//第 1 轮操作是把每一盏电灯的开关按一下（全部打开）。
//第 2 轮操作是把每两盏灯的开关按一下（就是按第 2，4，6... 盏灯的开关，它们被关闭）。
//第 3 轮操作是把每三盏灯的开关按一下（就是按第 3，6，9... 盏灯的开关，有的被关闭，比如 3，有的被打开，比如 6）...
//如此往复，直到第 n 轮，即只按一下第 n 盏灯的开关。
//现在给你输入一个正整数 n 代表电灯的个数，问你经过 n 轮操作后，这些电灯有多少盏是亮的？
int bulbSwitch(int n) {
    return sqrt(n);
}
