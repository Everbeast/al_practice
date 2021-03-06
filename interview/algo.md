LRU(重点)

## 查找

### 桶排序

> 将要排序的数据分到几个有序的桶里，每个桶里的数据再单独进行排序。
>
> 要排序的数据有 n 个，我们把它们均匀地划分到 m 个桶内，每个桶里就有 k=n/m 个元素。每个桶内部使用快速排序，时间复杂度为 O(k * logk)。m 个桶排序的时间复杂度就是 O(m * k * logk).整个桶排序的时间复杂度就是 O(n*log(n/m))。当桶的个数 m 接近数据个数 n 时，log(n/m) 就是一个非常小的常量，这个时候桶排序的时间复杂度接近 O(n)。
>
> 用途:
>
> 需要数据容易划分成m个桶,且在各个桶之间的分布是比较均匀
>
> **比较适合用在外部排序中**:即数据存储在外部磁盘中，数据量比较大，内存有限，无法将数据全部加载到内存中

计数排序

> 是一种特殊的桶排序:当要排序的 n 个数据，所处的范围并不大的时候，比如最大值是 k，我们就可以把数据划分成 k 个桶
>
> 如:高考人数很多,按总分750分分成750个桶
>
> 实际例子:
>
> A是8个同学的分数,最高分是5分,c为桶,表示各个分数的人数的前向和,即c[6] = {2,0,2,3,0,1}得到的,A从后面到前面遍历,各个分数找到在c对应的位置找到排名(减1)即为R中的位置
>
> ![image-20210302103813871](https://gitee.com/chillchan/images/raw/master/test/image-20210302103813871.png)
> 
>计数排序只是用于数据范围比数据量少得多,且只能给非负整数排序(可以做一个偏移再用)
>

### 二分查找

> 需要有序数据,顺序表,不适合太大数据(对内存要求高,要排序1GB就需要同样大小的连续空间)