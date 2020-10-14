##容器

### item 1

####选择容器

#### ·序列容器：vector string deque list (非标准slist rope)

#### ·关联容器：set multiset map multimap (非标准hash_set hash_multiset hash_map hash_multimap)

#### ·连续内容容器：vector string deque  (非标准 rope)

####·基于节点容器：list  slist 和标准的关联容器



### item 2

####typedef的好处
```cpp
//不要这样写
class Widget {...};
vector<Widget> vw;
Widget bestWidget;
... // 给bestWidget一个值
vector<Widget>::iterator i = // 寻找和bestWidget相等的Widget
 find(vw.begin(), vw.end(), bestWidget);


//应该这样写 typedef
class Widget { ... };
typedef vector<Widget> WidgetContainer;
typedef WidgetContainer::iterator WCIterator;
WidgetContainer cw;
Widget bestWidget;
...
WCIterator i = find(cw.begin(), cw.end(), bestWidget);

//即使typedef不用来封装 也能带来方便
map<string, vectorWidget>::iterator, CIStringCompare> // CIStringCompare是“忽略大小写的字符串比较”
map<string, vectorWidget>::iterator, CIStringCompare>::const_iterator //
```

用class封装隐藏你所用的容器
```cpp
class CustomerList {
private:
 typedef list<Customer> CustomerContainer;
 typedef CustomerContainer::iterator CCIterator;
 CustomerContainer customers;
public: // 通过这个接口
 ... // 限制list特殊信息的可见性
};
```



### item 3

注意容器对象的拷贝
```cpp
vector<Widget> vw;
class SpecialWidget:public Widget {...}; // SpecialWidget从上面的Widget派生
SpecialWidget sw;
vw.push_back(sw); // sw被当作基类对象拷入vw
 // 当拷贝时它的特殊部分丢失了
```



###item 4 

####用容器的empty替代size() == 0

 对于所有的标准容器，empty是一个常数时间的操作，但对于一些list实现，size花费线性时间。



### item 5

####尽量使用区间成员函数 而不是对单元素进行操作

v1和v2，使v1的内容和v2的后半部分一样的最简单方式是什么

best way:
```cpp
v1.assign(v2.begin() + v2.size() / 2, v2.end());  
//assign对于vector，string，deque和list都有效
```

用循环不可取
```cpp
vector<Widget> v1, v2; // 假设v1和v2是Widget的vector
v1.clear();
for (vector<Widget>::const_iterator ci = v2.begin() + v2.size() / 2; ci != v2.end(); ++ci)
    v1.push_back(*ci);
```

copy 也不可取 因为其内部也存在循环
```cpp
v1.clear();
copy(v2.begin() + v2.size() / 2, v2.end(), back_inserter(v1));
```



#### 原因：

表面上：区间成员函数更加简洁 直接

效率上：有三种浪费（税）
如若要将数组的内容拷贝到vector中

```c++
int data[numValues]; // 假设numValues在其他地方定义
vector<int> v;
...
//insert的区间方法//********************suggested************************
v.insert(v.begin(), data, data + numValues); // 把data中的int插入v前部

//不提倡的做法：
//insert单元素方法
vector<int>::iterator insertLoc(v.begin());
for (int i = 0; i < numValues; ++i) {
    insertLoc = v.insert(insertLoc, data[i]);
    ++insertLoc;
}
//注意要确保insert后的iterator（否则会导致迭代器无效， 或者是编程倒序（每次都在头插入））

//copy方法 （效率同insert单元素方法）
copy(data, data + numValues, inserter(v, v.begin()));
```


**1** 循环每次调用insert函数 （内敛函数可避免？）
**2** 连续内存容器：若每次insert到位置p，p和p位置后面的元素都应该往后移动一次，插入元素个数越多移动次数就越多
若vector中是自定义的类，每次移动会调用一次拷贝构造函数（内敛可解决）
区间成员函数 一次性将元素移动到其最终位置， 即每个元素都只需移动一次
**3** 处理内存分配：每次插入新的元素，若vector的capacity满了 会申请一个capacity*2的空间，然后将旧空间的内容复制到新的空间
	插入 num个元素，会导致log2（num）内存分配和拷贝， 如插入1000个元素 就需要 10次内存分配和拷贝
	区间成员函数 一次性知道需要分配的内存大小 （一个区间插入可以在开始插入东西前计算出需要多少新内存）

**·特地的 在list容器中 （双向列表）：**
循环插入节点，node a前插入，则会浪费每次改表node a->pre 指针 因为该指针一直都在改变直到指向最后插入的节点
区间成员函数 只用改变一次 



### item 6

#### 解析问题
若想传一对istream_iterator给list的区间构造函数

```c++
// container::container(InputIterator begin, // 区间的起点
//                     InputIterator end); // 区间的终点

ifstream dataFile("ints.dat");
list<int> data(istream_iterator<int>(dataFile), istream_iterator<int>()); // 不是像你想象的那样 （1）
```


事实上什么都没做

```c++
//补充：
int f(double d); 
int f(double (d)); 
int f(double); //三者等价  一个函数f 参数为double类型

int g(double (*pf)()); 
int g(double pf()); 
int g(double ());  //三者等价 一个函数g 参数为函数指针

class Widget {...}; // 假设Widget有默认构造函数
Widget w(); // 声明了w函数 返回类型widget  并不是初始化Widget

// 因此：（1）中
// 声明了一个函数data，它的返回类型是list<int>。这个函数data带有两个参数：
// 第一个参数叫做dataFile。类型是istream_iterator<int>
// 第二个参数没有名字。他是返回istream_iterator<int>的函数指针。
```

正确做法：

```c++
ifstream dataFile("ints.dat");
istream_iterator<int> dataBegin(dataFile);
istream_iterator<int> dataEnd;
list<int> data(dataBegin, dataEnd);
```



### item 7

#### new了容器的指针 要在销毁容器前delete该指针

```c++
void doSomething() {
    vector<Widget*> vwp;
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
    	vwp.push_back(new Widget); 
    ... ;// 使用vwp
    	// Widgets在这里泄漏!
}
```

可能的做法：

```c++
void doSomething(){
    vector<Widget*> vwp;
    ...;//同上循环
    for(vector<Widget*>::iterator = vwp.begin(); i != vwp.end(); i++){
        delete *i;
    }
}
//该方法当在建立的vwp后和删除他们之间发生异常 仍然会资源泄漏
```

可能的做法：

```c++
template<typename T>
struct DeleteObject: public unary_function<const T*, void>{
    void operator()(const T* ptr) const{
        delete ptr;
    }
}

void doSomething(){
    ...; //同上循环
    for_each(vwp.begin(), vwp.end(), DeleteObject<Widget>);
}
//该方法指定了delete的对象类型 若是其他容器则会出错
```

正确的做法：

```c++
struct DeleteObject { // 删除这里的 // 模板化和基类
    template<typename T> // 模板化加在这里 void operator()(const T* ptr) const
    {
        delete ptr; }
    }
}

void doSomething(){
    deque<SpecialString*> dssp;
    for_each(dssp.begin(), dssp.end(), DeleteObject());
}
```

或者使用boost的shared_ptr

```c++
void doSomething() {
	typedef boost::shared_ ptr<Widget> SPW; //SPW = "shared_ptr // to Widget"
	vector<SPW> vwp;
	for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
		vwp.push_back(SPW(new Widget)); // 从一个Widget建立SPW, // 然后进行一次push_back
	...; // 使用vwp
        // 这里没有Widget泄漏，甚至
        // 在上面代码中抛出异常
}
```



### item 8

#### 不要用auto_ptr建立容器

```c++
bool widgetAPCompare(const auto_ptr<Widget>& lhs, const auto_ptr<Widget>& rhs) {
    return *lhs < *rhs; // 对于这个例子，假设Widget存在operator<
} 

vector<auto_ptr<Widget> > widgets; // 建立一个vector，然后用Widget的auto_ptr填充它(记住这将不能编译！)

sort(widgets.begin(), widgets.end(), widgetAPCompare);
// 排序这个vector导致vector里面至少一个widget被删除 被设为null

//原因：
auto_ptr<Widget> pw1(new Widget); // pw1指向一个Widget
auto_ptr<Widget> pw2(pw1); // pw2指向pw1的Widget;
                        // pw1被设为NULL。（Widget的
                        // 所有权从pw1转移到pw2
pw1 = pw2; // pw1现在再次指向Widget；
            // pw2被设为NULL
```



#### item 9

####注意删除选项

对于连续内存容器(vector、deque或string）best way：

```c++
c.erase(remove(c.begin(), c.end(), 1963), c.end());

//删除判别式的值
bool badValue(int x);
c.erase(remove_if(c.begin(), c.end(), badValue), c.end());
```

对于list的best way：

```c++
c.remove(1963);

//删除判别式的值
bool badValue(int x);
c.remove_if(badValue);
```

对于关联容器（set、multiset、map或multimap）best way：

```c++
c.erase(1963);
    
//删除判别式的值
bool badValue(int x);

//低效：
AssocContainer<int> c;
AssocContainer<int> goodValues; //临时存放不删除的值
remove_copy_if(c.begin(), c.end(), inserter(goodValues, goodValues.end()), badValues);
c.swap(goodValues);

//高效：
for(AssocContainer<int>::iterator != c.begin(); i != c.end(); ){
    if(badValue(*i))
        c.erase(i++);
    else
        ++i;
}
//注意i的值不在for中改变 因为当删除一个元素，指向的那个元素的迭代器失效
```



### item 11

#### 分配器的使用

有如下的自定义的malloc和free程序

```c++
void* mallocShared(size_t bytesNeeded);
void freeShared(void *ptr); 

template<typename T>
class SharedMemoryANocator {
public:
    ...;
    pointer allocate(size_type numObiects, const void *localityHint = 0)
    {
        return static_cast<pointer>(mallocShared(numObiects * sizeof(T)));
    }
    void deallocate(pointer ptrToMemory, size_ type numObjects)
    {
        freeShared(ptrToMiemory);
    }
    ...;
};

```

想把stl的容器的内容放在共享内存里面：

```c++
//错误做法：
typedef vector<double, SharedMemoryAllocator<double> > SharedDoubleVec;
...;
{ // 开始一个块
 SharedDoubleVec v; // 建立一个元素在共享内存中的vector
 ...; // 结束这个块
}
//v只是一个普通的堆对象 运行时不会用共享内存

//正确做法：（分配空间 建立对象）
void *pVectorMemory = mallocShared(sizeof(SharedDoubleVec)); 
// 分配足够的共享内存来容纳一个SharedDoubleVec对象
SharedDoubleVec *pv = new (pVectorMemory) SharedDoubleVec; 
// 使用“placement new”来在那块内存中建立一个SharedDoubleVec对象；

...;//（删对象 销毁空间）
pv->~SharedDoubleVec(); //这个对象的使用（通过pv）销毁共享内存中的对象
freeShared(pVectorMemory); // 销毁原来的共享内存块
```

假设你有两个堆，命名为Heap1和Heap2类 都想联合stl用 如下：

```c++
class Heap1 {
public:
 ...
 static void* alloc(size_t numBytes, const void *memoryBlockToBeNear);
 static void dealloc(void *ptr);
 ...
};
class Heap2 { ... };  //同上
```

则必须定义一个分配器：

```c++
template<typenameT, typename Heap>
class SpecificHeapAllocator {
public:
 pointer allocate(size_type numObjects, const void *localityHint = 0)
 {
    return static_cast<pointer>(Heap::alloc(numObjects * sizeof(T),localityHint));
 }

 void deallocate(pointer ptrToMemory, size_type numObjects)
 {
    Heap::dealloc(ptrToMemory);
 }
 ...;
};
```

//才能进行下面的使用：

```c++
vector<int, SpecificHeapAllocator<int, Heap1 > > v;  
set<int, SpecificHeapAllocator<int Heap1 > > s; // 把v和s的元素放进Heap1
list<Widget, SpecificHeapAllocator<Widget, Heap2> > L; 
map<int, string, less<int>, SpecificHeapAllocator<pair<const int, string>, Heap2> > m; 
//把L和m的元素放进heap2
```



### item 12

#### 容器的线程安全

如找到vector中第一个值=5的 并设为0

```c++
vector<int> v;
vector<int>::iterator first5(find(v.begin(), v.end(), 5)); // 行1
if (first5 != v.end()){ // 行2
 *first5 = 0; // 行3
}
```

####别的线程可能情况：
·在行1结束 立马改变v中数据
·行1到行2之间 插入元素等操作 使得迭代器失效
·行2到行3之间 某种操作 使得first5失效

//solution1:

```c++
vector<int> v;
...
getMutexFor(v);
vector<int>::iterator first5(find(v.begin(), v.end(), 5));
if (first5 != v.end()) { // 这里现在安全了
 *first5 = 0; // 这里也是
}
releaseMutexFor(v);
```

// better solution: 

```c++
template<typename Container> // 获取和释放容器的互斥量
class Lock { // 的类的模板核心；
public: // 忽略了很多细节
    Lock(const Containers container):c(container)
    {
        getMutexFor(c); // 在构造函数获取互斥量
    }
    ~Lock()
    {
        releaseMutexFor(c); // 在析构函数里释放它
    }
private:
    const Container& c;
};

vector<int> v;
...;
{ // 建立新块；
    Lock<vector<int> > lock(v); // 获取互斥量
    vector<int>::iterator first5(find(v.begin(), v.end(), 5));
    if (first5 != v.end()) {
        *first5 = 0;
    }
} // 关闭块，自动
 // 释放互斥量!
 //用块来管理互斥量的好处是：若抛出异常 就离开了块 同样能释放互斥量
```

------

##vector 和 string

### item 13

#### 尽量用vector string来替代动态分配的数组



### item 14

#### 避免不必要的重新分配

```c++
 //需要重新分配10次 （2的10次方约等于1000）
vector<int> v;
for (int i = 1; i <= 1000; ++i) v.push_back(i);

//用reserve一次性分配1000个空间
vector<int> v;
v.reserve(1000);
for (int i = 1; i <= 1000; ++i) v.push_back(i);
```



### item 15

#### string 的实现 及其大小



### item 16

#### vector 和string 对c api的兼容

```c++
vector<int> v;
void doSomething(const int* pInts, size_t numInts); //第一个参数是一个接受一个数组

//可以这样
doSomething(&v[0], v.size()); 

//避免v为空的时候 &v[0]指向不存在的东西的指针
if (!v.empty()) {
    doSomething(&v[0], v.size());
}

//上述做法只能用于不改变vector的c风格api  （参数有const）
//若想用c风格api来初始化vector：
size_t fillArray(double *pArray, size_t arraySize); //返回的是元素的个数
vector<double> vd(maxNumDoubles); // 建立一个vector，它的大小是maxNumDoubles
vd.resize(fillArray(&vd[0], vd.size())); // 让fillArray把数据写入vd，然后调整vd的大小为fillArray写入的元素个数

//对于string：
size_t fillString(char *pArray, size_t arraySize);
vector<char> vc(maxNumChars); // 建立一个vector 它的大小是maxNumChars
size_t charsWritten = fillString(&vc[0], vc.size()); // 让fillString把数据写入vc 返回字符的个数
string s(vc.begin(), vc.begin()+charsWritten); // 从vc通过范围构造函数拷贝到数据s

//对于stl的其他容器来对接c风格的api  可以用vector作为桥梁

//c api->其他stl容器
size_t fillArray(double *pArray, size_t arraySize); // 同上
vector<double> vd(maxNumDoubles); // 一样同上

vd.resize(fillArray(&vd[0], vd.size())); //vector作为桥梁 传到其他stl的容器中
deque<double> d(vd.begin(), vd.end()); // 拷贝数据到deque
list<double> l(vd.begin(), vd.end()); // 拷贝数据到list
set<double> s(vd.begin(), vd.end()); // 拷贝数据到set

//stl容器-> c api
void doSomething(const int* pints, size_t numInts); // C API (同上)
set<int> intSet; // 保存要传递给API数据的set
...
vector<int> v(intSet.begin(), intSet.end()); // 拷贝set数据到vector
if (!v.empty()) doSomething(&v[0], v.size()); // 传递数据到AP
```



### item 17 

#### shrink to fit

```c++
vector<Contestant>(contestants).swap(contestants);
```

vector<Contestant>(contestants)会建立一个临时的vector 是contestant的拷贝 
这由vector拷贝构造函数完成 而且只分配拷贝的元素需要的内存
然后将临时vector和contestants交换数据  从而完成shrink to fit

例子

```c++
string s;
... // 使s变大，然后删除所有它的字符
string(s).swap(s); 
```

```c++
vector<Contestant> v;
string s;
... // 使用v和s
vector<Contestant>().swap(v); // 清除v而且最小化它的容量
string().swap(s); 

```



### item 18

#### 避免使用vector<bool>

vector<bool>不满足STL容器的必要条件，你最好不要使用它；
而deque<bool>和bitset是基本能满足你对vector<bool>提供的性能的需要的替代数据结构。

```c++
//vector<bool>不是stl容器的原因
//容器需要满足其中一条
T *p = &c[0]; // 无论operator[]返回什么，都可以用这个地址初始化一个T*
//vector<bool>不满足
vector<bool> v;
bool *pb = &v[0]; // 用vector<bool>::operator[]返回的东西的地址初始化一个bool*
//因为每个保存在“vector”中的“bool”占用一个单独的比特，而一个8比特的字节将容纳8个“bool”。 
```

------

## 关联容器

### item 19

#### 相等和等价

等价 (!a>b && !a<b)
		是根据这个比较函数定义的，所以标准关联容器的用户只需要为他们要使用的任意容器指定一个比较函数（决定排序顺序的那个

相等  (==)
		根据除了它用于排序的比较函数，还需要一个用于判断两个值是否相等的比较函数

```c++
set<string, CIStringCompare> ciss;  //忽略大小写的字符串集合
ciss.insert("Persephone"); // 一个新元素添加到set中
ciss.insert("persephone"); // 没有新元素添加到set中  两者是等价的
if (ciss.find("persephone") != ciss.end())... // 这个测试会成功    用的是等价
if (find(ciss.begin(), ciss.end(), "persephone") != ciss.end())... // 这个测试会失败
//（因为string("persephone") != string("Persephone)

```



### item 20

### 指针关联容器的比较类型

插入以下名字 想按字母的顺序输出

```c++
set<string*> ssp; // ssp = “set of string ptrs” ssp.insert(new 
string("Anteater"));
ssp.insert(new string("Wombat"));
ssp.insert(new string("Lemur"));
ssp.insert(new string("Penguin"));

for(set<string*>::const_iterator i = ssp.begin(); i != ssp.end(); i++)
    cout << *i <<endl;
//希望看到Anteater Lemur Penguin Wombat
```

结果四个十六进制的数  是指针的值
将*i改为**i也是不能按顺序 因为是按<u>指针</u>的顺序排序的

因此需要改变排序方法：

```c++
struct StringPtrLess: public binary_function<const string*, const string*, bool>{
    bool operator()(const string* ps1, const string* ps2) const{
        //ps1 ps2 是指针 应该比较指针的指向的内容来排序
        return *ps1 < *ps2;
    }
}

typedef set<string*, StringPtrLess> StringPtrSet;
StringPtrSet ssp;
...;//同上赋值

for(StringPtrSet::const_iterator i == ssp.begin(); i != ssp.end(); i++){
    cout<< **i <<endl;
}//能按期望顺序打印
```

set的第三个参数是一个种类， 因此要把 比较类型 的功能写成仿函数类

另一个种方法：

```c++
struct DereferenceLess {
    template<typename PtrType>
    bool operator()(PtrType pT1, PtrType pT2) const{
        return *pT1 < *pT2;
    }
}

set<string*, DereferenceLess> ssp; //

```



### item 21

#### 让比较函数 对相等的值放回false

在set中调用insert来判断新值，是用比较函数
若自定义比较函数当两值相等返回true
 set判断是否插入是利用等价 (!a>b && !a<b)
 若两者相等返回true 这上述等价判断为(!true && ! true) 即为false
 set 认为不等价  则set中拥有两个相等的值 破坏了set

 对于能容纳重复值得容器来说是同样的 如multiset
 multiset<int, less_equal<int> > s; // s仍然以“<=”排序
 s.insert(10); // 插入10A
 s.insert(10); // 插入10B
 用equal_range无法返回这两个10的范围 因为equal_range 也是利用等价的概念，而这两个10是不等价的



### item 22

### 避免原地修改set和multiset的键

```c++
EmpIDSet se; // 同前，se是一个以ID号排序的雇员set
Employee selectedID; // 同前，selectedID是一个带有需要ID号的雇员
...;
EmpIDSet::iterator i = se.find(selectedID); // 第一步：找到要改变的元素
if (i!=se.end()){
    Employee e(*i); // 第二步：拷贝这个元素
    se.erase(i++); // 第三步：删除这个元素；
    //自增这个迭代器以保持它有效（参见条款9）
    e.setTitle("Corporate Deity"); // 第四步：修改这个副本
    se.insert(i, e); // 第五步：插入新值；提示它的位置和原先元素的一样
}
```



###item 23

#### 用vector 代替 关联容器

由于vector是连续空间，在数据结构足够大的时候，vector比关联容易需要的页面要少，这样vector就会有更好的效率（插入删除等操作较少的时候）（前提这个vector需要是排序的）

以下是实现：

```c++
typedef pair<string, int> Data;

class DataCompare{
public:
    bool operator()(const Data& lhs, const Data& rhs) const{
        return KeyLess(lhs.fisrt, rhs.first);
    }
    
    bool operator()(const Data& lhs, const Data::first_type& k) const{
        return KeyLess(lhs.fisrt, k);
    }
    
    bool operator()(const Data::fisrt_type& k, const Data& rhs) const{
        return KeyLess(k, rhs.first);
    }
private:
    bool KeyLess(const Data::first_type& k1, const Data::first_type& k2) const{
        return k1 < k2;
    }
}

vector<Data> vd;
...;
sort(vd.begin(), vd.end(), DataCompare());

string s;
...;
if(binary_search(vd.begin(), vd.end(), s, DataCompare()))
    ...;
vector<Data>::iterator i = lower_bound(vd.begin(), vd.end(), s, DataCompare());
if(i != vd.end() && !DataCompare()(s, *i))
    ...;
pair<vector<Data>::iterator, vector<Data>::iterator> range =
    equal_range(vd.begin(), vd.end(), s, DataCompare());
if(range.first != range.second)
    ...
```



### item 24

#### map中 若更新已存在的map元素 operator[ ]更好 增加一个新的元素 insert更好

·增加新的元素 用 [ ]需要多调用 （insert一步到位）

​	1 临时的数据结构的构造函数来建立临时对象

​	2 销毁该临时

​	3 对该对象赋值

·更新已存在元素用insert

​	多耗费了一对构造函数和析构函数

------

## 迭代器

### item 26

#### 尽量用 iterator 代替 const_iterator reverse_iterator const_reverse_iterator

有些成员函数只接受iterator作为参数 而iterator能转换到其他迭代器，其他迭代器不能保证都能转化到iterator

###item 27

####用 advance 和 distance 来将 const_iterator 转换成iterator

```c++
typedef deque<int> IntDeque;
typedef IntDeque::iterator Iter;
typedef IntDeque::const_iterator ConstIter;

IntDeque d;
ConstIter ci;
...; 
Iter i(d.begin()); //初始化i为d.begin()
advance(i, distance(i, ci));
```

先让 i 指向d的起始位置，然后将将 i 往前移动到 ci 和开头的距离，即将 i 指向和 ci 指向的容器（以上程序不能编译）：
（distance的定义）：

```c++
template<typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator fisrt, InputIterator last);
```

distance 参数都是同一种迭代器类型，故要显示指明distance 调用

```c++
advance(i, distance<ConstIter>(i, ci));
```



### item 28

####如何通过reverse_iterator的base得到iterator

```c++
vector<int> v;
v.reserve(5); 
for(int i = 0;i < 5; ++ i) { v.push_back(i);
}
vector<int>::reverse_iterator ri =
find(v.rbegin(), v.rend(), 3); vector<int>::iterator i(ri.base());
//1 2 3 4 5
```

此时
	ri指向 3     i指向 4

对ri调用insert 99，则 99在ri的前面，即在3右侧
对 i 调用insert 99，则99在 i 的前面，即在4左侧
因此 插入的话 ri 和 ri.base() 等价

删除的话 位置不一样 因此需要减1:

```c++
v.erase(--ri.base()); //不能编译
//不能直接修改函数返回的指针
v.erase((++ri).base()); //注意ri的方向和ri.base()的方向

```



### item 29 

#### 用istreambuf_iterator来提高速度

```c++
//会忽略空格
ifstream inputFile("interestingData.txt");
string fileData((istream_iterator<char>(inputFile)),istream_iterator<char>()); // 把inputFile读入

//不会忽略空格
ifstream inputFile("interestingData.txt"); inputFile.unset(ios::skipws); // 关闭inputFile的忽略空格标志
string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>());

//用istreambuf_iterator提高速度
ifstream inputFile("interestingData.txt");
string fileData((istreambuf_iterator<char>(inputFile)),
istreambuf_iterator<char>());
```

------

## 算法

### item 30

### 保证插入目标空间足够大

```c++
//对x进行运算
int transmogrify(int x);
vector<int> values;
...; //数据放入values
vector<int> results; //通过transmogrify后的结果放入results
transform(values.begin(), values.end(), results.end(), transmogrify);
//这段代码有bug
```

若*results.end()没有对象 则后面的+i都没有对象 调用transform会发生错误

应该用back_inserter来产生目标区间的地点迭代器（此处为尾插入）

```c++
transform(values.begin(), values.end(), back_inserter(results), transmogrify);

//在results的中间插入
transfom(values.begin(), values.end(), inserter(results, results.begin() + result.size() /2 ), transmogrify);

```

**若是用front_inserter 注意顺序问题**

避免重新分配容器的内存 用reserve

```c++
//中间插入
results.reserve(result.size() + values.size());
transfom(values.begin(), values.end(), inserter(results, results.begin() + result.size() /2 ), transmogrify);
//尾插入
results.reserve(result.size() + values.size());
transform(values.begin(), values.end(), back_inserter(results), transmogrify);
//覆盖插入：
//1
if(results.size() < values.size()){
    results.resize(values.size())
}
transform(values.begin(), values.end(), results.begin(), transmogrify);
//2
results.clear();
results.resize(values.size());
tranform(values.begin(), values.end(), pack_inserter(results),transmogrify);

```



###item 31

#### 选择合适的排序算法

●  如果你需要在vector、string、deque或数组上进行完全排序，你可以使用sort或stable_sort。

●  如果你有一个vector、string、deque或数组，你只需要排序前n个元素，应该用partial_sort。

●  如果你有一个vector、string、deque或数组，你需要鉴别出第n个元素或你需要鉴别出最前的n个元素，

而不用知道它们的顺序，nth_element是你应该注意和调用的。

●  如果你需要把标准序列容器的元素或数组分隔为满足和不满足某个标准，你大概就要找partition或

stable_partition。

●  如果你的数据是在list中，你可以直接使用partition和stable_partition，你可以使用list的sort来代替sort和

stable_sort。如果你需要partial_sort或nth_element提供的效果，你就必须间接完成这个任务，但正如我 在上面勾画的，会有很多选择。

```c++
//按顺序把最好的20个元素放在widgets的前端
partial_sort(widgets.begin(),widgets.begin() + 20, widgets.end(), qualityCompare);

//把最好的20个元素放在widgets 这20个元素不关心顺序
nth_element(widgets.begin(), widgets.begin() + 19, widgets.end(), qualityCompare);

//找到中等质量的widgets （质量比一半的好）
nth_element(widgets.begin(), widgets.begin() + widgets.size()/2, widgets.end(), qualityCompare);

//质量比75%要好
nth_element(widgets.begin(), widgets.begin() + widgets.size()*0.25, widgets.end(), qualityCompare);
```

找出所有等级1和等级2的widgets

```c++
bool hasAcceptableQuality(const Widget& w) {
// 返回w质量等级是否是2或更高; 
}
vector<Widget>::iterator goodEnd = partition(widgets.begin(), widgets.end(),hasAcceptableQuality);
// 把所有满足hasAcceptableQuality的widgets移动到widgets前端,并且返回一个指向第一
```



### item 32

#### remove没有真正的删除元素

```c++
vector<int> v;
v.reserve(10);
for(int i = 1; i <= 10; ++i){
    v.push_back(i);
}

cout<< v.size(); //print 10
v[3] = v[5] = v[9] = 99;
remove(v.begin(), v.end(), 99);
cout<< v.size(); //print still 10;
```

v: 1 2 3 99 5 99 7 8 9 99

remove 后：1 2 3 4 5 7 8 9 8 9 99
					                         |
										newEnd

step: remove检测v[0] 发现不是要被删除的，移动到v[1]

一直i移动到v[3]发现应该被删除， 标定其应该被覆盖，移动到v[4]发现应该被保留，则将v[4]赋值到v[3] 将v[4]标记为应被覆盖.....以此类推

要真正的删除元素：

```c++
vector<int> v;
//remove返回newEnd 作为erase的第一个参数
v.erase(remove(v.begin(), v.end(), 99), v.end()); // 真的删除所有等于99的元素
cout << v.size();
```



### item 33

#### 指针的容器注意用remove算法有泄漏危险

```c++
vector<Widget*> v;
... // 动态分配的Widget 
v.push_back(new Widget);// 的指针填充

//下列删除会泄漏
v.erase(remove_if(v.begin(), v.end(), not1(mem_fun(&Widget::isCertified))), 	     v.end());

//解决方法：
//1
//应该删除指针 并置为空 再用remove erase
void delAndNullifyUncertified(Widget*& pWidget){
    if(!pWidget->isCertified()){
        delete pWidget;
        pWidget = 0;
    }
}

for_each(v.begin(), v.end(), delAndNullifyUncertified);
v.erase(remove(v.begin(), v.end(), static_case<Widget*>(0)),
       v.end());

//2
//替换为智能指针的容器
template<typename T>
class RCSP{...}; //智能指针
typedef RCSP<Widget> RCSPW;
vector<RCSPW> v;
...;
v.push_back(RCSPW(new Widget));
...;
v.erase(remove_if(v.begin(), v.end(), not1(mem_fun(&Widget::isCertified))),
       v.end());
```



### item 34

#### 下列算法需要有有序区间

binary_search 			upper_bound 			set_intersection
set_union 				   set_difference 		  set_symmetric_difference
merge 						 includes 				   inplace_merge
lower_bound 			  equal_range  



### item 35

#### 实现忽略大小写的字符串比较

```c++
//字符比较
int ciCharCompare(char c1, char c2) 
{
    // c1和c2，如果c1 < c2返回-1，
    // 如果c1==c2返回0，如果c1 > c2返回1
    int Ic1 = tolower(static_cast<unsigned char>(c1));
    int Ic2 = tolower(static_cast<unsigned char>(c2));
    if (Ic1 < Ic2) return -1; 
    if (lc1 > Ic2) return 1; 
    return 0;
}

//string比较
int ciStringCompareImpl(const string& s1, const string& s2); 
int ciStringCompare(const string& s1, const string& s2) {
    if (s1.size() <= s2.size()) return ciStringCompareImpl(s1, s2);
    else return -ciStringCompareImpl(s2, s1); 
}

int ciStringCompareImpl(const string& s1, const string& s2){
    typedef pair<string::const_iterator, string::const_iterator> PSCI;
    PSCI p = mismatch(s1.begin(), s1.end(), s2.begin(), not2(ptr_fun(ciCharCompare)));
    if(p.first == s1.end()){
        if(p.second == s2.end()) return 0; //s1等于s2
        else return -1; //s1 短于 s2；
    }
    return ciCharCompare(*p.first, *p.second);
}

//方法二
bool ciCharLess(char c1, char c2){
    tolower(static_cast<unsigned char>(c1)) < tolower(static_cast<unsigned char>(c2)); 
}

bool ciStringCompare(const string& s1, const string& s2) {
    return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess);
}
```

lexicographical_compare基于比较函数 需按照s1 和 s2 第一个不同的位置



### item 37

#### 用accumulate 或 for_each来统计区间

```c++
list<double> ld;
...;
double sum = accumulate(ld.begin(), Id.end(), 0.0); //必须为0.0 

//还可以这样用
cout << "The sum of the ints on the standard input is"
    accumulate(istream_iterator<int>(cin), // 打印cin中 <<那些int的和
    istream_iterator<int>(), 0);

//计算point区间的平均值
struct Point {
	Point(double initX, double initY): x(initX), y(initY) {}
    double x, y;
};

list<Point> lp;
...
Point avg = // 对Ip中的point求平均值
accumulate(lp.begin(), lp.end(), Point(0, 0), PointAverage());

//PointAverage定义如下：
class PointAverage:
	public binary_function<Point, Point, Point> { // 参见条款40
public:
	PointAverage(): numPoints(0), xSum(0), ySum(0) {}
    const Point operator()(const Point& avgSoFar, const Point& p) {
        ++numPoints;
        xSum += p.x;
        ySum += p.y;
        return Point(xSum/numPoints, ySum/numPoints);
	}
private:
	size_t numPoints; 
    double xSum; 
    double ySum;
};

//使用for_each
struct Point {...); // 同上 
class PointAverage:
	public unary_function<Point, void> { // 参见条款40 
public:
    PointAverage(): xSum(0), ySum(0), numPoints(0) {} 
    void operator()(const Point& p)
    {
    	++numPoints; xSum += p.x; ySum += p.y;
    }
    Point result() const {
    	return Point(xSum/numPoints, ySum/numPoints); 
    }
private:
	size_t numPoints; 
    double xSum; 
    double ySum;
};
list<Point> Ip;
...
Point avg = for_each(lp.begin(), lp.end(), PointAverage()).result;
```

------

## 仿函数 仿函数类 函数

### item 38

####把仿函数类设计为用于值传递

```c++
template<class InputIterator, class Function>
// 注意值返回
Function for_each(InputIterator first,InputIterator last, Function f);
// 注意值传递

//若是一个多态仿函数类需要建立一个包含一个指向实现类的指针的小而单态的类，然后把所有数据和虚函数放到实现类
//一个多态仿函数类
template<typename T>
class BPFC: public unary_function<T, void>{
private:
    Widget w;
    int x;
    ...;
public:
    virtual viod operator()(const T& val) const;//虚函数 值传递会切割
    ...;
}
//改为如下：
template<typename T> //新实现类 之前的bpfc类数据都放在这里
class BPFCImpl: public unary_function<T, void>{
private:
    Widget w;
    int x;
    ...;
    virtual ~BPFCImpl(); //多态类需要虚析构函数
    virtual viod operator()(const T& val) const;
    friend class BPFC<T>; // 让BPFC可以访问这些数据
};
//小的单态办BPFC
template<typename T>
class BPFC: public unary_function<T, void>{
private: 
    BPFCImpl<T> *pImpl; //该类的唯一数据 （小）
public:
    void operator()(const T& val) const{
        pImpl->operator()(val); //调用BPFCImpl
    }
    ...;
};
```



###item 39

####用纯函数做判断式

·判别式：返回bool 或可隐试转换为bool的东西

·纯函数：返回值只依赖于参数的函数 （返回值只有参数改变才会改变）

·一个判断式类是一个仿函数类，它的operator()函数是一个判断式，也就是，它的operator()返回true或 false(或其他可以隐式转换到true或false的东西)

```c++
//若满足上述约束 则会出问题 如下
class BadPredicate: public unary_function<Widget, bool>{
pulic:
    BadPredicate():timesCalled(0){}
    bool operator()(const Widget&){
        return ++timesCalled==3;
    }
private:
    size_t timesCalled;
}

vector<Widget> vw;
vw.erase(remove_if(vw.begin(), vw.end(), BadPredicate()), vw.end());
```

!!不仅会从vw中除去第三个元素，它也会除去第六个!

原因：
remove_if实现如下：

```c++
template <typename FwdIterator, typename Predicate>
FwdIterator remove_if(FwdIterator begin, FwdIterator end, Predicate p) {
	begin = find_if(begin, end, p); 
    if (begin == end) return begin; 
    else {
		FwdIterator next = begin;
		return remove_copy_if(++next, end. begin, p); 
    }
}
```

最初调用remove_if(用户代码中要从vw中除去第三个元素的那次调用)建立一个匿名BadPredicate对象，它把内部的timesCalled成员清零。这个对象(在remove_if内部叫做p)然后被拷贝到find_if，所以find_if也接收了一 个timesCalled等于0的BadPredicate对象。find_if“调用”那个对象直到它返回true，所以调用了三次，find_if然 后返回控制权到remove_if。remove_if继续运行后面的调用remove_copy_if，传p的另一个拷贝作为一个判断 式。但p的timesCalled成员仍然是0!find_if没有调用p，它调用的只是p的拷贝。结果，第三次remove_copy_if 调用它的判断式，它也将会返回true。这就是为什么remove_if最终会从vw中删除两个Widgets而不是一个。



### item 40

#### 使仿函数类可适配

```c++
list<Widget*> widgetPtrs;
bool isInteresting(const Widget *pw);

list<Widget*>::iterator i = 
    find_if(widgetPtrs.begin(), widgetPtrs.end(),
            not1(isInteresting)); //不能编译
	
list<Widget*>::iterator i = 
    find_if(widgetPtrs.begin(), widgetPtrs.end(),
            not1(ptr_func(isInteresting));  //没问题
```

对于仿函数类 需要继承unary_function和binary_function

·unary_function，要指定的是由仿函数类的operator()所带的参数的类型和它的返回类型
·binary_function，要指定三个类型:operator的第 一个和第二个参数的类型，和operator返回类型

```c++
//unary_function例子
template<typename T>
class MeetsThreshold: public std::unary_function<Widget, bool>{ 
private:
	const T threshold;
public:
	MeetsThreshold(const T& threshold); bool operator()(const Widget&) const; 
    ...
};

//binary_function例子
struct WidgetNameCompare:public std::binary_function<Widget, Widget, bool>{
	bool operator()(const Widget& lhs, const Widget& rhs) const; 
};
```



### item 41

#### ptr_fun、mem_fun和mem_fun_ref作用

```c++
f(x); // 语法#1:当f是一个非成员函数
x.f(); // 语法#2
p->f(); // 语法#3

//有如下测试函数
void test(Widget& w); // 测试w，如果没通过 // 就标记为“failed
vector<Widget> vw;
for_each(vw.begin(), vw.end(), test); // 调用#1(可以编译)

class Widget { 
public:
	void test();
};

for_each(vw.begin(), vw.end(), &Widget::test); // 调用#2(不能编译)
list<Widget*> lpw; // lpw容纳Widget的指针 
for_each(lpw.begin(), lpw.end(),&Widget::test); // 调用#3(也不能编译)

```

调用#分别需要用到对应语法# 而for_each不能找到不同对应的语法

```c++
//mem_fun如下
template<typename R, typename C> 
mem_fun_t<R,C>;
// C是类，R是被指向的成员函数的返回类型
mem_fun(R(C::*pmf)());

for_each(lpw.begin(), lpw.end(), mem_fun(&Widget::test)); //可以编译
for_each(vw.begin(), vw.end(), ptr_fun(test)); //可以编译
```



#### item 42

####确定less<T>表示operator<

operator<不仅是实现less的默认方式，它还是程序员希望less做的。让less做除operator<以外的事情是对程序员 预期的无故破坏。它与所被称为“最小惊讶的原则”相反。它是冷淡的。它是低劣的。它是坏的。你不该那 么做。

------

## 使用STL编程

### item 43

#### 尽量用算法调用代替手写循环

```c++
class Widget { 
public:
	...；
	void redraw() const; 
    ...；
};
//你想重画一个list中的所有Widget对象
list<Widget> lw;
...；
for (list<Widget>::iterator i =lw.begin(); i != lw.end(); ++i) { 
    i->redraw();
}

//suggested：
or_each(lw.begin(), lw.end(), mem_fun_ref(&Widget::redraw));
```

原因：效率 正确 可维护性

1 不用每次i != lw.end();
2 库的实现者可以利用他们知道容器的具体实现的优势，用库的使用者无法采用的方式来优化遍历

#### 但是有些条件就用stl算法会更加复杂

假设想要找出vector中第一个比x大又比y小的元素

```c++
vector<int> v;
int x, y;
...
vector<int>::iterator i = v.begin();
for(;i != v.end(); ++i) { 
	if (*i > x && *i < y) break;
}
...;
//用stl算法显得不够直观
vector<int>::iterator i =
find_if(v.begin(), v.end(),
compose2(logical_and<bool>(), bind2nd(greater<int>(), x),bind2nd(less<int>(), y))); 
```



### item 44

#### 尽量用成员函数代替同名的算法

```c++
set<int> s; // 建立set，放入1,000,000个数据 
...；
set<int>::iterator i = s.find(727); // 使用find成员函数
if (i != s.end()) ...
set<int>::iterator i = find(s.begin(), s.end(), 727); 
// 使用find算法 if (i != s.end()) ...
```

find成员:大约40(最坏的情况)至大约20(平均情况) 
find算法:1,000,000(最坏的情况)至500,000(平均情况)  //越小效率越高

//成员函数是为该容器量身定做的



### item 45

图



### item 46

#### 使用函数对象代替函数作算法的参数

```c++
vecotr<double> v;
...;
sort(v.begin(), v.end(), greater<double>());

inline
bool doubleGreater(double d1, double d2) {
	return dl > d2; 
}
...;
sort(v.begin(), v.end(), doubleGreater);
//greater<double>的版本每次都比较快
```

原因：

```c++
void sort(vector<double>::iterator first, 
          vector<double>::iterator last, 
          bool (*comp)(double, double));
```

1 不是真的把doubleGreater传给sort，它传了一个doubleGreater的指针 comp是一个指向函数的指针，每次在sort中用到时，编译器产生一个间接函数调用——通过指针调用

### item 47

#### 避免产生只写代码

即代码要有可读性（别人看得容易）



### item 48 

#### include适当的头文件



### item 49

####stl的 debug信息

string 出错信息：

```c++
example.cpp(20): error C2664:'__thiscall std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> >::std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> >(const class std::allocator<char> &)': cannot convert parameter 1 from 'const int' to 'const class std::allocator<char> &' Reason: cannot convert from 'const int' to 'const class std::allocator<char>
No constructor could take the source type, or constructor overload resolution was ambiguous
```

string 是一个typdedef :

```c++
basic_string<char, char_traits<char>, allocator<char> >；
    //或
std::basic_string<char, std::char_traits<char>, std::allocator<char> >
    //等等
```

将上述错误信息替换得

```
example.cpp(20): error C2664:'__thiscall string::string(const class std::allocator<char> &)': cannot convert parameter 1 from 'const int' to const class std::allocator<char> &'
```

#### 例子二

```c++
truct std::char_traits<char>,class std::allocator<char> >,struct std::less<class std::basic_string<char,structstd::char_traits<char>, class
std::allocator<char> > >,class std::allocator<class std::basic_string<char, struct, std::char_traits<char>,class std::allocator<char> > > >::_Kfn, struct std::less<class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<class std::basic_string<char, struct, std::char_traits<char>,class std::allocator<char> > > >::const_iterator' to 'class std::_Tree<class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> >,struct std::pair<class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> > const .class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> > >,struct std::map<class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> >,class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> >,struct std::less<class std::basic_string<char,structstd::char_traits<char> .class
std::allocator<char> > >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > >::_Kfn, struct std::less<class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char> > > >::iterator'
No constructor could take the source type, or constructor overload resolution was ambiguous
```

替换成basic_string：

```c++
example.cpp(17): error C2440: 'initializing': cannot convert from 'class std::_Tree<class string, struct std::pair<class string const,class string >,struct std::map<class string, class string, struct std::less<class string >,class std::allocator<class string > >::_Kfn, struct std::less<class string >,class std::allocator<class string > >::const_iterator' to 'class std::_Tree<class string, struct std::pair<class string const .class string >,struct std::map<class string, class string, struct std::less<class string >,class std::allocator<class string> >::_Kfn,struct std::less<class string >,class std::allocator<class string> >::iterator'
No constructor could take the source type, or constructor overload resolution was ambiguous
```

将_Tree里面的东西改为something 和 typedef的东西：

```c++
example.cpp(17): error C2440: 'initializing': cannot convert from 'class std::_Tree<SOMETHING>::const_iterator to 'class
std::_Tree<SOMETHING>::iterator'
No constructor could take the source type, or constructor overload resolution was ambiguous
```

