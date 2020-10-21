## io库

io对象无拷贝或赋值

```c++
ofstream out1, out2;
out1 = out2;                //错：不能对流对象赋值
ofstream print(ofstream);   //错：不能初始化ofstream参数
out2 = print(out2);         //错：不能拷贝流对象
```

管理条件状态：

```c++
auto old_state = cin.rdstate(); //记住cin当前状态
cin.clear();			       //使cin有效
process_input(cin);			   //使用cin
cin.setstate(old_state);	    //将cin置为原来的状态
//有参数的clear
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);//复位failbit和badbit
```

刷新缓冲区

```c++
cout<<"hi"<<endl; //输出hi和换行，刷新缓冲区
cout<<"hi"<<flush; //输出hi， 刷新缓冲区
cout<<"hi"<<ends; //输出hi和一个空格， 刷新缓冲区
//unitbuf
cout<< unitbuf;  //只有所有输出都立即刷新缓冲区
cout << nounitbuf; // 回道正常
```

关联输入输出

```c++
cin.tie(&cout) //cin和cout关联（仅做展示，本来就是关联）
ostream *old_tie = cin.tie(nullptr) ; // cin不和任何关联
cin.tie(&cerr); //关联cerr和cin
cin.tie(old_tie); //恢复默认：cin和cout关联
```

自动构造和析构

```c++
for(auto p = argv + 1; p != argv + argc; ++p){
    ifstream input(*p);  //创建输入流并打开文件
    if(input){ //打开文件成功
        //处理此文件
    }else
        cerrr<< "couldn't open:" + string(*p);
}//每个循环开头自动构造，离开作用域自动销毁
```

文件模式

```c++
//ofstream隐含输出模式，会截断文件
ofstream out1("f1");//三者等价
ofstream out2("f1", ofstream::out);
ofstream out3("f1", ofstream::out | ofstream::trunc);
//保留文件内容如下：
ofstream app("f1", ofstream::app);//两者等价
ofstream app2("f1", ofstream::out | ofstream::app);
```

string

istringstream

```c++
//输入格式如： drew 190234 10-08593475 1239
//人名+多个电话号码  希望输入到以下结构存储
struct PersonInfo{
    string name;
    vector<string> phones;
};
string line, word;
vector<PersonInfo> people;
while(getline(cin, line)){ //从输入的每行->line
    PersonInfo info;
    istringstream record(line); //将record绑定到刚读的line
    record >> info.name; //输出名字到name
    while(record >> word){ //输出电话到word
        info.phones.push_back(word);
    }
    people.push_back(info);
}
```

ostringstream

```c++
for(auto &entry : people){
    ostringstream formatted, badNums; //用ostringstream先处理
    for(auto &nums : entry.phones){ //对每个电话号码
        if(!valid(nums)){
            badNums << " " << nums; //不是正确号码 输入到badNums
        }else
            formatted << " " << format(nums); //格式化电话号码 然后输入到formatted对象
    }
    if(badNums.str().empty()) //没有错误的电话号码
        os << entry.name << " " <<formatted.str() <<endl;
    else
        cerr << "input error: " << entry.name
        	 << " invalid number(s)" << badNums.str() << endl;
}
```

### 容器

```c++
vector<noDefault> v1(10, init); 
//noDefault没有默认构造函数，则必须提供元素初始化器
```

迭代器：左闭右开 ：[begin, end)

```c++
auto it = a.begin(); //仅当a是const，it是const_iterator
auto it = a.cbegin(); //it是const_iterator
```

容器初始化另一个容器

```c++
//容器的列表初始化
list<string> authors = {"Milton", "Shakespeare", "Austen"};
vector<const char*> articles = {"a", "an", "the"};

list<string> list2(authors); //正确，类型匹配
deque<string> authList(authors); //错误容器类型不匹配
vector<string> words(articles); //错误 容器的元素类型不匹配
forward_list<string> words(articles.begin(), articles.end());
//正确，只要能将拷贝的元素转换，新旧容器的元素类型也可以不同（可以将const char* 转为string)
```

标准库array

```c++
//array必须指定类型和大小,如
array<int, 42> ...;
array<int, 10>::size_type i;//ok
array<int>::size_type j; //no array<int>不是一个类型

array<int, 10> ia1;
array<int, 10> ia2 = {0,1,2,3,4,5,6,7,8,9}; //列表初始化
array<int, 10> ia3 = {41}; //ia3[0] 为42 其他都是0

int digs[10] = {0,1,2,3,4,5,6,7,8,9};
int cpy[10] = digs; //no. 不支持拷贝和赋值
array<int, 10> digs = {0,1,2,3,4,5,6,7,8,9};
array<int, 10> cpy = digs;  //yes 支持

array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
array<int, 10> a2 = {0}; //所有元素为0；
//所有容器：
c1 = c2;
c1 = {a, b, c}; //赋值后，c1大小为3
//内置数据不同
a1 = a2; //替换a1元素
a2 = {0}; //no:不能花括号赋值数组
```

assign

```c++
list<string> names;
vector<const char*> oldstyle;
names = oldestyle; //错：容器类型不匹配
names.assign(oldestyle.cbegin(), oldestyle.cend());
//正确，const char*可以转为string

list<string> slist(1); //1个元素，空的string
slist.assign(10, "hi"); //10个元素，都是hi
//等价于下面
slist1.clear();
slist1.insert(slist1.begin(), 10, "hi");
```

除 arrray外，swap不对任何元素进行拷贝、删除或插入操作，故可常数时间完成

关系运算符

```c++
vector<int> v1 = {1,3,5,7,9,12};
vector<int> v2 = {1,3,9};
vector<int> v3 = {1,3,5,7};
vector<int> v4 = {1,3,5,7,9,12};
v1 < v2;//true v1[2] <= v2[2]
v1 < v3; //false v3元素更少 
v1 == v4 //true
v1 == v2 //false
```

insert

```c++
svec.insert(svec.end(), 10, "hi") //末尾添加10个hi
slist.insert(slist.end(), v.end() - 2, v.end()) //末尾添加v的后两个元素
slist.insert(slist.end(), {"a", "b", "c"}) //末尾添加 括号里面的元素
    
//insert 的返回值
auto iter = lst.begin();
while(cin >> word)
    iter = lst.insert(iter, word);//等于调用push_front;
```

emplace

```c++
//emplace等于push_back等函数+对象的构造函数
//容器c装有Sales_data 
vector<Sales_data> c;
//iter 为c的一个iter
c.emplace_back(); //使用默认构造函数
c.emplace(iter, "id") //使用Sales_data(string)的构造函数
c.emplace_back("id", 25, 15); //使用Sales_data的三个参数的构造函数并添加
//上一条等价于：
c.push_back(Sales_data("id", 25, 15));



```

容器的访问

```c++
//访问元素的成员函数返回的是引用
c.front() = 42; //首元素赋值42
auto &v = c.back();
v = 1024;   //改变c中的元素
auto v2 = c.back();
v2 = 0;     //没有改变c的元素

//安全得访问函数
vector<string> svec;
cout << svec[0]; //运行错误：svec没有元素
cout << svec.at(10);  //抛出 out_of_range异常
```

改变容器大小

```c++
list<int> ilist(10, 42);
ilist.resize(15);  //末尾添加5个0
ilist.resize(25, -1); //末尾添加10个-1
ilist.resize(5); //删除末尾20个元素
```

迭代器失效：

```c++
//vector string deque 添加元素 空间可能会被重新分配 迭代器指针引用失效
//注意返回迭代器的函数来更新迭代器 避免迭代器失效
//如果在一个循环中插入/删除deque\string\vector中的元素，不要缓存end返回的迭代器，因为他不指向任何元素
```

string的操作

```c++
const char *cp = "hello world!!!";
string s1(cp);  //s1 = hello world!!!
string s2(s1, 6); //从s1的6开始到结尾 s2 = world!!!
string s4(cp + 6, 5) //同上
string s3(s1, 6, 5); //从s1的6开始拷贝5个字符
string s5(s1, 6, 20); //正确 也是到结尾
string s6(s1, 20); //抛出out of range异常 （没有position其实位置）

s.insert(s.ize(), 5, "!") //末尾添加5个！
s.erase(s.size() - 5, 5) //删除末尾5个
    
const char *cp = "hello world!!!";
s.assign(cp, 7); //s=cp开头7个字符
s.insert(s.size(), cp + 7);//s末尾添加cp的第七个字符到最后的字符

string s = "bbbababa", st = "adgfadg";
s.insert(0, s2); // s在0处插入s2的拷贝
s.insert(0, s2, 0, s2.size()) //在s的0处 插入 s2的0处开始的s2.size()个字符
s.append("lakjdf"); //末尾添加
s.erase(11, 3); //s删除11处开始的3个字符
s.insert(11, "5th") //11处插入5th
s2.replace(11, 3, "5th") //11处的3个字符替换为5th
//搜索
...
    
```

### 关联容器

关联容器不支持位置相关的操作，例如push_front/push_back. 因为它们的元素是根据关键字存储的

```c++
//自定义排序方式：必须是严格弱序
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
    return lhs.isbn() < rhs.isbn();
}
//利用decltype 注意*
multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn); 
```

关联容器的操作

```c++
set<string>::value_type v1; //v1是string
set<string>::key_type v2;   //v2是string
map<string, int>::value_type v3;  //v3是pair<const string, int>
map<string, int>::key_type v4; //v4是string
map<string, int>::mapped_type v5 //v5是int
```

set迭代器是const的

添加元素

```c++
word_count.insert({word, 1});
word_count.insert(make_pair(word, 1));
word_count.insert(pair<string, size_t>(word, 1));
word_count.insert(map<string, size_t>::value_tpye(word, 1));

//若word_count原本没有{word, 1} 调用insert返回true
//word_count原本有{word, 1}, 则返回false
```

对multiset和multimap添加元素，总能插入，因此这里insert无返回

删除元素

```c++
c.erase(k); //删除关键字为k的元素，返回删除的元素数量
c.erase(p); //删除迭代器p指定的元素，返回p的下一个元素的迭代器
c.erase(b, e); // 删除迭代器p到e范围的元素，返回e
```

map下标

```c++
c[k] //若k不在c中，添加关键字为k的元素，并初始化
c.at(k) //若k不在c中，抛出out_of_range异常
```

在multimap或multiset查找

```c++
//例如查找某作者的所有书
string search_item("Shakespeara");
auto entries = authors.count(search_item); //书的数量
auto iter = authors.find(search_item); //指向第一本书
while(entries){
    cout << iter->second << endl;
    ++iter;
    --entries;
}

//或者用lower_bound /upper_bound
for(auto beg = authors.lower_bound(search_item), end = authors.upper_bound(search_item); beg != end; ++beg)
    cout << beg->second <<endl;

//用equal range
for(auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first)
    cout << pos.first->second << endl;
```

### 动态内存

使用动态内存的一个常见原因是：允许多个对象共享相同的状态

![image-20201017153145234](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201017153145234.png)

![image-20201017153157730](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201017153157730.png)

make_shared

```c++
shared_ptr<int> p3 = make_shared<int>(42);//p3指向值为42的int的shared_ptr
shared_ptr<string> p4 = make_shared<string>(10, '9');
shared_ptr<int> p5 = make_shared<int>(); //值为0的int
auto q(p3); //p3和q指向相同对象
```

如果将shared_ptr存放于一个容器中，而后不再需要全部元素，而只用其中一部分，记得erase删除不用的那些元素，这样才能正确释放shared_ptr

应用：

```c++
//为了实现以下：
Blob<string> b1;
{
    Blob<string> b2 = {"a", "an"}; //临时变量
    b1 = b2;
}
//目标：拷贝一个blob时，原blob对象及其拷贝应该引用相同的底层元素
//实现strblob类
class StrBlob{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const {return data->size();}
    bool empty() const{return data->empty();}
    ...
private:
    std::shared_ptr<std::vector<std::string>> data;//使用这个实现
}
```

内置类型中，值初始化的内置类型对象有着良好的定义的值
			          默认初始化对象的值则是未定义的

多次释放相同指针值，未定义错误

shared_ptr和new结合使用:

不能将一个内置指针隐式转换为一个智能指针，必须使用直接初始化

```c++
shared_ptr<int> p1 = new int(1024); //错误
shared_ptr<int> p2(new int(1024)); //正确

//错误:
shared_ptr<int> clone(int p){
    return new int(p);
}

//正确：
shared_ptr<int> clone(int p){
    return shared_ptr<int>(new int(p));
}
```

不能混用智能指针和普通指针

```c++
int *x(new int(1024));
process(x); //错误 不能将int* 转为之智能指针
process(shared_ptr<int>(x)); //正确，但内存会被释放
int j = *x; //未定义，x是一个悬空指针
```

不能使用get用到另一个智能指针初始化或赋值

```c++
shared_ptr<int> p(new int(42)); 
int *q = p.get();
{
    shared_ptr<int>(q);
}//块结束，q被销毁 ，同样的p也会被销毁
int foo = *p;//未定义：p内容已经被释放了
//当p离开作用域会再次释放，这样就被释放了两次p，错误
```

缩放动态数组

```c++
delete p;  //p必须指向动态分配的对象或空
delete [] pa;  //pa必须指向动态分配的数组或空
```

allocator：

```c++
allocator<string> alloc;
auto const p = alloc.allocate(n);//分配n个未初始化的string
```

![image-20201017162343309](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201017162343309.png)

![image-20201017162526618](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201017162526618.png)

```c++
auto p = alloc.allocate(vi.size()*2);//分配比vi空间大一倍的动态内存
auto q = uninitialize_copy(vi.begin(), vi.end(), p);//拷贝vi来构造从p开始的元素
uninitialized_fill_n(q, vi.size(), 42);//剩余的元素都初始化为42
```

### 文本查询程序设计：

![image-20201017213633437](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201017213633437.png)

共享数据：在查询数据的时候，拷贝行号会引起很多文件的拷贝，应避免，用shared_ptr来应用这种共享关系

实现：

```c++
void runQueries(ifsteam &infile){
    TextQuery tq(infile);
    while(true){
        cout << "enter word to look for, or q to quit: ";
        string s;
        //遇到文件尾或用户输入‘q’终止
        if(!(cin >> s) || s == "q") break;
        //指向查询并打印结果
        print(cout, tq.query(s)) << endl;
    }
}

class QueryResult;
class TextQuery{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    //每个单词-行号集合的map
    std::map<std::string, 
             std::shared_ptr<std::set<line_no>>> wm;
}

TextQuery::TextQuery(ifstream &is):file(new vector<string){
    string text;
    while(getline(is, text)){  //从流读入一行
        file->push_back(text); //保存到file
        int n = file->size() - 1; //当前行号
        istringstream line(text);  //对text创建到流格式，后面进行分词处理
        string word;
        while(line >> word){ // 自动对空格分词
            auto &lines = wm[word];  //lines是一个shared_ptr
            if(!lines){ //第一次遇到这个单词时，此指针为空
                lines.reset(new set<line_no>); //分配一个新的set
            }
            lines.insert(n); //插入行号
        }
    }
}

class QueryResult{
friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string> f):
    	sought(s), lines(p), file(f){}
private:
    string sought; //查询单词
    shared_ptr<set<line_no>> lines;  //出现的行号
    shared_ptr<vector<string> file;  //输入文件
}

QueryResult TextQuery::query(const string &sought) const{
    //没找到 返回该指针
    static shared_ptr<set<line>> nodata(new set<line>);
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

ostream &print(ostream &os, const QueryResult &qr){
    os << qr.sought << "occurs" << qr.lines->size() <<" " << make_plural(qr.lines->size(), "time", "s") << endl;
    for(auto num : *qr.lines)
        os <<"\t(line" << num + 1 << ")" <<*(qr.file->begin() + num) <<endl;
    return os;
}
```

### 泛型算法

```c++
//删除重复的元素
void elimDups(vector<strring> &words){
    //按字典顺序排序
    sort(words.begin(), words.end());
    //unique 重排，返回指向不重复区域后一个迭代器
    auto end_unique = unique(words.begin(), words.end());
    //删除重复的单词
    words.erase(end_unique, words.end());
}
```

lamda函数

```c++
//比较大小
[](const string &a, const string &b){
    return a.size() < b.size();
}

//有参数的lamda
[sz](const string &a){
    return a.size() >= sz;
}

//值捕获 
//被捕获变量是在lambda创建时拷贝的
size_t v1 = 42;
auto f = [v1]{return v1;};
v1 = 0;
auto j = f(); //j=42；

//值捕获中改变其值
size_t v1 = 42;
auto f = [v1]() mutable {return ++v1;};
v1 = 0;
auto j = f(); //j=43；

//引用捕获
size_t v1 = 42;
auto f = [&v1]{return v1;};
v1 = 0;
auto j = f(); //j=0；
//引用捕获中改变其值，依赖于是否为const

//隐式捕获：引用捕获 &， 值捕获 =
//隐式捕获引用的os
for_each(word.begin(), word.end(),
        [&, c](const string &s){os << s << c;});
//隐式捕获值的捕获c
for_each(words.begin(), words.end(),
         [=, &os](const string &s){os << s <<c;});

//指定返回类型
transform(vi.begin(), vi.end(), vi.begin(),
         [](int i) -> int {
             if(i < 0) return -i;
             else return i;
         });
```

bind

```c++
bool check_size(const string &s, string::size_type sz){
    return s.size() >= sz;
}
auto check6 = bind(check_size, _1, 6); //_1表示check6的参数绑定在check_size的第一个参数
string s = "hello";
bool b1 = check6(s); //就等于调用 check_size(s, 6);
//因此 可用bind函数替换lambda函数
auto wc = find_if(words.begin(), words.end(),
                 [sz](const string &a){...});
//替换为
auto wc = find_if(words.begin(), words.end(),
                 bind(check_size, _1, sz));

auto g = bind(f, a, b, _2, c, _1);
g(_1, _2);//映射为
f(a, b, _2, c, _1);

//bind中用ref来绑定引用
ostream &print(ostream &s, const string &s, char c){
    return os << s << c;
}
//错误:不能拷贝os
for(words.begin(), words.end(), bind(print, os, _1, ' '));
//正确
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
    
```

#### iostream迭代器

```c++
//istream_iterator操作
ifsteam in("afile");
istream_iterator<string> str_it(in); //从“afile”读字符串
istream_iterator<int> in_iter(cin); //从cin读取int
istream_iterator<int> eof;  //istream尾后迭代器
while(in_iter != eof)
    vec.push_back(*in_iter++);

//或
vector<int> vec(in_iter, eof);
//计算输入流数值的和
istream_iterator<int> in(cin), eof;
cout << accumlate(in, eof, 0) << endl; //输出和
```

#### ostream_iterator

```c++
//打印vector中的元素，空格隔开
ostream_iterator<int> out_iter(cout, " ");
for(auto e : vec)
    *out_iter++ = e;
cout<<endl;

```

### 模板

非类型模板参数的模板实参必须是常量表达式

```c++
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]){
    return strcmp(p1, p2);
}
//调用
compare("hi", "mom");
//实例化了：
int compare(const char (&p1)[3], const char (&p2)[4]);
```

inline模板

```c++
template <typename T> inline T min(const T&, const T&);
```

编译器到模板定义是，不会生成代码。只有当实例化出模板的一个特定版本时，才会生成代码。模板的头文件通常包括声明和定义。函数模板和类模板成员函数的定义通常放在头文件。

如果一个类模板包含一个非模板友元，则友元被授权可以访问所有模板实例。
如果友元自身事模板，类可以授权给所有友元模板实例，也可以只授权给特定实例。

```c++
template<typename T> class Pal;
class C{
    friend class Pal<C>; //用c实例化的Pal是C的友元
    template<typename T> friend class Pal2;//Pal2所有实例化都是c的友元
}

template <typename T> class C2{
    friend class Pal<T>; //Pal用C2相同实例化的 是C2的友元
    template <typename X> friend class Pal2; //pal2的所有实例化都是C2友元
    friend class Pal3; //Pal3是c2所有实例化的友元
}
```

可以将模板类型参数声明为友元

```c++
template<typename Type> class Bar{
friend Type; //作用？
}
```

##### 模板行别名

```c++
template<typename T> using twin = pair<T, T>;
twin<string> authors; // authors为pair<string, string>;

template<typename T> using partNo = pair<T, unsigned>;
partNo<string> books; //books是pair<string, unsigned>
```

类模板的static成员：

```c++
template <typename T> class Foo{
public:
    static std::size_t count() {return ctr;}
private:
    static std::size_t ctr;
}
//所有Foo<X>类型共享相同的ctr和count函数

//初始化静态成员
template<typename T>
size_t Foo<T>::ctr = 0;
```

必须使用typename的情况

```c++
T::size_type *p;
//产生歧义：不知道是T的成员变量和p相乘 
//             还是定义一个类型的指针
//故
typename T::size_type *p;
```

模板默认参数

```c++
template<class T = int> class Numbers;

Numbers<long double> lots_of_precision;
Numbers<>average_precision;//若希望使用默认参数，必须跟空尖括号
```

##### 成员模板：

普通类的成员模板

```c++
class DebugDelete{
public:
    DebugDelete(ostream &s = cerr) : os(s){}
    template <typename T> void operator()(T *p) const{
        os << "deleting unique_ptr" << endl;
        delete p;
    }
private:
    ostream &os;
};

double *p = new double;
DebugDelete d;
d(p); //调用DebugDelete::operator()(double*)释放p;

int *p = new int;
DebugDelete()(p); //调用DebugDelete::operator()(int*)释放p;

//若用DebugDelete作为unique_ptr的删除器
unique_ptr<int, DebugDelete> p(new int, DebugDelete()); //销毁类型int

unique_ptr<int, DebugDelete> p(new string, DebugDelete());//string
```

模板类模板成员

```c++
//模板类的构造函数接受两个迭代器
template<typename T> class Blob{
    template <typename It> Blob(It b, It e);
    ...;
};
//类外定义：必须两个模板参数列表在前(类的，然后是成员的)
template<typename T>
template<typename It>
	Blob<T>::Blob(It b, It e):
		data(make_shared<vector<T>>(b, e)){};

//实例化
int a[] = {........};
vector<long> vi = {........};
list<const char*> w = {......};
Blob<int> a1(begin(ia), end(ia)); //T为int  It为begin和end获取数组的迭代器
//T为int, It为vector<long>::iterator
Blob<int> a2(vi.begin(), vi.end());
//。。。
Blob<string> a3(w.begin(), w.end());
```

定于与声明

```c++
extern template class Blob<string>; //声明
template int compare(const int&, const int&); //定义
//声明表承诺在程序的其他位置有该实例化的一个定义，可多个声明，但只有一个定义
extern template class Blob<string>;
Blob<string> sa1, sa2; //实例化出现在其他位置
Blob<string> a2(sa1); //拷贝构造在本文件中实例化
```

实例化定义会实例化所有成员，即使不用，包括内敛成员函数

算术转换，派生类向基类转换，用户自定义转换都不能用于函数模板
能自动转换的只有**const的转换**或者函数到指针的转换

```c++
template <typename T> T fobj(T, T);
template<typename T> T fref(const T&, const T&);
string s1("aaa");
const string s2("bbb");
fobj(s1,s2); //ok  忽略const
fref(s1, s2); //ok 都是const
int a[10], b[42];
fobj(a, b); //f(int*, int*);
fref(a, b); // not ok

```

指定显式模板实参

```c++
template<typename T1, typename T2, tpyename T3>
T1 sum(T2, T3);

auto val = sum<long long>(i, lng);//<>指定返回类型， i，lng是参数，推断T2 T3 故调用long long sum(int, long);

template<typename T1, typename T2, tpyename T3>
T3 sum(T1, T2);//若这样定义 就必须显式定义三个模板参数
auto val2 = sum<long long, int, long>(i, lng); //按顺序显示定义

//显式指定的类型转换
long lng;
compare<long>(lng, 1024); //compare(long, long);
compare<int>(lng, 1024);//compare(int, int)
```

位置返回推断返回类型

```c++
template<typename It>
auto fcn(It beg, It end) -> decltype(*beg){
    ...;
    return *beg; //返回序列一个元素的引用
}

template<typename It>
auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type{
    ...;
    return *beg; //返回序列一个元素的拷贝
}
```

函数指针与模板

```c++
template <typename T> int compare(const T&, const T&);
int (*pf1)(const int&, const int&) = compare;
//pf1指向了int compare(const int&, const int&)

//遇到函数重载要要明确版本
void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));
func(compare)//which one？
func(compare<int>)//good
```

推断

```c++
template<typename T> void f1(T&);
f1(i); f1(ci); //若i是int ci是const int；都正常推断
f1(5); //not good
template<typename T> void f2(const T&);
f1(i); //T为int
f2(ci); //T为int
f2(5); //T为int
template<typename T> void f3(const T&&);
f3(5);//T为int
f3(i); //T为int&
f3(ci); //T 是const int&
```

折叠:
x& &, x& &&, x&& &  ->  x&
x&& && -> x&&

如果模板参数是T&&（右值引用）可以传任意类型的实参。
若传一个左值，他会被实例T为 普通引用

```c++
//右值引用模板的使用情况：模板重载
template <typename T> void f(T&&); //绑定非const右值
template <typename T> void f(const T&); //左值和const 右值
```

传播

```c++
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2){
	f(t2, t1);
}
void f(int v11, int &v2){
	cout << v1 << " " << ++v2 <<endl;
}

f(42, i); // f改变了i
flip1(f, j, 42); //f不会改变j 
//因为j被拷贝到t1中，而没有绑定 故不会改变

template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2){
	f(t2, t1);
} //这个f就能改变j

```

模板重载：
两个模板可行，选最特例化的（即使用范围少）
模板和非模板都可行，选非模板

##### 可变参数模板

```c++
template <typename T, typename... Args?
void foo(const T& t, const Args& ... rest);
foo(i, s, 42, d)//包中有三个参数 //自动推断参数类型
foo(i); //空包

template<typename T>
ostream& print(ostream& os, const T& t){
    return os << t;
}

template<typename T, typename... Args>
ostream& print(ostream &os, const T& t, const Args&... rest){
    os << t<<", "; //打印第一个实参
    return print(os, rest...); //递归打印其他实参
}
```

模板特例化

```c++
template<typename T> int compare(const T&, const T&);
//特例化
template<> int compare(const char* const& p1, const char* const& p2){
    ...;
}
//偏特化
template<typename T> int compare(const T&, const T&)<需要偏特化的类型>{
}
```



## 拷贝控制

### 拷贝构造函数

参数的第一个参数必须是一个引用类型，因此非引用类类型参数是调用拷贝构造函数来初始化的，因此不是引用类型就是无限循环。

![image-20201020204749787](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020204749787.png)

![image-20201020204801024](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020204801024.png)

发生拷贝初始化的情况：

![image-20201020204728465](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020204728465.png)

### 拷贝赋值运算符

```c++
class Foo{
public:
	Foo& operator=(const Foo&);
}
```

返回一个指向其左侧运算对象的引用

![image-20201020205414861](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020205414861.png)

### 析构函数

![image-20201020205516738](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020205516738.png)

当指向一个对象的引用或指针离开作用域时，析构函数不会执行

·需要自定义析构函数-->几乎肯定也需要自定义**拷贝赋值运算符**和**拷贝构造函数**
例子：![image-20201020210227563](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020210227563.png)

当有一个函数如下：![image-20201020210342605](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020210342605.png)

f返回时，hp和ret都被销毁，而这两者都是指向相同的指针，而该指针被delete了两次，发生错误

![image-20201020210506859](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020210506859.png)

f(p)之后，p指向的内存被释放了，最后p q都指向无效内存

·需要拷贝构造函数-->也需要拷贝赋值运算符

·需要拷贝赋值运算符-->也需要拷贝构造函数

##### 阻止拷贝：

如iostream阻止了拷贝，避免多个对象写入或读取相同的io缓冲

```c++
struct NoCopy{
    NoCopy() = default; //使用合成默认构造函数
    NoCopy(const NoCopy&) = delete; //阻止拷贝
    NoCopy &operator=(const NoCopy&) = delete; //阻止赋值
    ~NoCopy() = default; //使用合成的析构函数
};
```

##### 析构函数不能是删除的

否则无法销毁此类型![image-20201020222706715](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020222706715.png)

不能初始化该对象，但是能够定义一个指向该类型的指针，但是不能删除该指针

##### 如果一个类有数据成员不能默认构造、拷贝、复制或销毁，则对应的成员函数将被定义为删除的。即，当不能拷贝、赋值或销毁类的成员时，类的合成拷贝控制成员就被定义为删除的

##### private拷贝控制：（effective c++条款6）

将拷贝构造和赋值运算符设置为private且不定义，能阻止拷贝，但是友元和成员函数仍然能够访问该函数，会导致连接错误。因此 应该是用=delete或者参考effective c++条款6

##### 类的行为像一个值：有自己的状态，拷贝则副本和原对象完全独立。

例子：定义一个HasPtr，对象都必须有自己的拷贝![image-20201020224105451](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020224105451.png)

实现类似：![image-20201020224122342](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020224122342.png)

```c++
//赋值运算符定义
HasPtr& HasPtr::operator=(const HasPtr &rhs){
    autu newp = new string(*rhs.ps); //拷贝底层string
    delete ps;
    ps = newp; //从右侧运算对象拷贝数据到本对象
    i = rhs.i;
    return *this;
}

//如下定义是错误的
HasPtr& HasPtr::operator=(const HasPtr &rhs){
    delete ps;
    ps = new string(*(rhs.ps));
    i = rhs.i;
    return *this;
}//rhs和本对象都是统一对象，delete ps会释放*this和rhs指向的string
//new的时候就会访问一个指向无效内存的指针
```

如果将一个对象赋予自己，赋值运算必须能正常工作
大多数赋值运算符组合了析构函数和拷贝构造函数的工作

##### 类的行为像一个指针：状态共享，拷贝则副本和原对象共享底层数据。

例子：![image-20201020224748638](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020224748638.png)

引用计数：

![image-20201020224733309](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020224733309.png)

![image-20201020225003958](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020225003958.png)

![image-20201020225132832](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020225132832.png)

赋值运算符：

```c++
HasPtr& HasPtr::operator=(const HasPtr &rhs){
    ++*rhs.use; //递增右侧运算对象的引用计数
    if(--*use == 0){ //递减本对象的引用计数
        delete ps;  //如果没有其他用户，这释放本对象分配的成员
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
```

#### 交换操作：

传统的赋值交换 进行了一次拷贝，两次赋值，我们更希望交换指针即可![image-20201020225510284](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020225510284.png)

声明swap为friend使其能够访问私有成员

```c++
//using std::swap使得存在类型特定的swap版本，swap会调用与之匹配，没有的话这调用std的版本
//如下则会一直调用std的版本，性能没有提高
void swap(Foo &lhs, Foo &rhs){
    std::swap(lhs.h, rhs.h) //即使特定版本的swap也不会被匹配调用
}
```

##### 赋值运算符中使用swap

![image-20201020230220410](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020230220410.png)

好处：自动是异常安全的，且正确处理自赋值

##### 移动

右值引用：只能绑定到一个将要销毁的对象
·所引用的对象将要销毁
·该对象没有其他用户

左值表达值表对象身份   右值表达值表对象的值

![image-20201020233337587](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020233337587.png)

左值持久；右值短暂；

变量 左值，不能将右值引用**直接**绑定到一个变量，即使这个变量是右值引用类型也不行

```c++
int &&rr1 = 42; //ok
int &&rr2 = rr1; // not ok
```

通过**move**来获取绑定到左值的右值引用

```c++
int &&rr3 = std::move(rr1); //ok
```

move：调用move意味着，除了对rrr1赋值或者销毁它外，不会再使用他。（rr1为移后源）

移动构造函数：![image-20201020234032078](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020234032078.png)

承诺对s赋值或销毁外部再使用，因此用s的成员赋值给本对象成员后，都对s的成员=nullptr，即对移后源销毁。

#### noexcept：

```c++
class StrVec{
public:
	StrVec(StrVec&&) noexcept; //移动构造函数
};
StrVec::StrVec(StrVec &&s) noexcept:/成员初始化列表/{定义};
```

不抛出异常的移动构造函数和移动赋值运算符必须标记为noexcept

#### 移动赋值运算符

```c++
StrVec &StrVec::operator=(StrrVec &&rhs) noexcept{
    //检测自赋值
    if(this != &rhs){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.element = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
```

在移动操作之后，移后源对象必须保持有效的、可析构的状态，但是用户不能对其值进行任何假设

#### 合成的移动操作

只有当一个类没有定义任何自己版本拷贝控制成员，且类的每个非static数据成员都可以移动式，编译器才会为它合成移动构造函数和移动赋值操作运算符

![image-20201020234931471](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020234931471.png)

移动操作永远不会隐式定义为删除的函数

如果显式让移动操作=default，则有可能定义为删除的![image-20201020235139570](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020235139570.png)

![image-20201020235215442](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020235215442.png)

#### 拷贝构造和移动构造：

移动构造函数值能用于实参是右值的时候
拷贝构造适用于任何能够转换为目标类型的时候![image-20201020235422956](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020235422956.png)

如果没有移动构造函数 右值也被拷贝：![image-20201020235454705](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020235454705.png)

拷贝构造代替移动构造几乎肯定是安全的

##### 拷贝交换和移动操作

此时赋值运算符即使移动赋值也是拷贝赋值

![image-20201020235800957](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020235800957.png)

![image-20201020235820819](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201020235820819.png)

#### 移动迭代器

移动迭代器解引用生成一个右值引用

make_move_iterator将迭代器转换为移动迭代器

```c++
void StrVec::reallocate(){
    auto newcapacity = size() ? size() * 2 : 1;
    auto fisrt = alloc.allocate(newcapacity);
    //移动元素
    auto last = uninitialized_copy(make_move_iterator(begin()),
                                   make_move_iterator(end()),
                                   first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
```

·当确定需要移动操作以及移动操作是安全的，才可以使用std::move

#### 移动和拷贝的重载：

![image-20201021000511937](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021000511937.png)

![image-20201021000526392](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021000526392.png)

```c++
StrVec vec; //空的
string s = "something";
vec.push_back(s); //调用拷贝的版本
vec.push_back("done") //调用移动版本 因为done是临时的，右值
```

#### 引用限定符：

![image-20201021000818614](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021000818614.png)

![image-20201021000826979](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021000826979.png)

#### 重载 引用：

![image-20201021001228616](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021001228616.png)

对象是一个右值表示没有其他用户，因此可以改变它，故可以原地排序
左值相反

·如果一个成员函数有引用限定符，这具有相同参数列表的所有版本都必须有引用限定符![image-20201021001430145](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021001430145.png)

### 面向对象程序设计

使用基类引用（或指针）调用一个虚函数将发生动态绑定![image-20201021105614237](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021105614237.png)![image-20201021105619704](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021105619704.png)

基类通常应该定义个一个虚析构函数，即使该函数不执行任何实际操作

成员函数不是虚函数其解析过程发生在编译时，不是运行时。

派生类到基类的类型转换：
如果表达式即不是引用类型也不是指针，这他的动态类型永远和静态类型一致

![image-20201021111421848](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021111421848.png)

不存在基类向派生类的转换
即，派生类向基类自动类型转换至对指针和引用类型有效，派生类和基类之间不存在转换，但是可以用派生类构造基类：![image-20201021113448855](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021113448855.png)

每个类控制自己的初始化：![image-20201021111733245](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021111733245.png)

派生类的声明不包含继承列表。

要继承某个类，则这个类必须定义，而不仅仅是声明

防止继承：class NoDerived final {...}; //添加final关键字

动态绑定只有通过指针或引用调用虚函数才会发生，才会运行时才解析。否则：![image-20201021114011774](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021114011774.png)

**override：**

![image-20201021114533469](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021114533469.png)

**final：**![image-20201021114605552](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021114605552.png)

如果虚函数使用了默认实参，这基类和派生类中定义的默认实参最好一致

回避虚函数机制：

```c++
//强行调用基类中定义的函数，不管baseP的动态类型是什么：
double undiscounted = baseP->Quote::net_price(42);
```

使用情况：当一个派生类的虚函数调用它覆盖的基类的虚函数的版本。
因为，若一个派生类虚函数需要调用它的基类版本，而没有指定是基类的版本，在运行时会被解析为对派生类版本的自身调用，从而导致无限递归。

抽象基类负责定义借口，后续的其他类可以覆盖接口，即派生类给出纯虚函数的定义，否则派生类仍然是抽象类。不能创建抽象基类的对象

#### 友元![image-20201021194916523](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021194916523.png)

clobber只是Sneaky的友元，不是base的友元

private 继承：![image-20201021195013156](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021195013156.png)

私有继承后，类的用户不能调用基类的成员，但是类内能用：![image-20201021195208840](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021195208840.png)

派生说明符还可以控制继承自派生类的新类的访问权限：![image-20201021195321237](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021195321237.png)

派生类向基类的访问行：（假设D继承自B）![image-20201021195538359](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021195538359.png)

友元和继承：![image-20201021200215176](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021200215176.png)

![image-20201021200256308](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021200256308.png)

改变访问性：

```c++
class Base{
public:
    size_t size() const{return n;}
protected:
    size_t n;
};

class Derived: private Base{
public:
    using Base::size;
protected:
    using Base::n;
}
//private继承本来size()和n都是派生类的private，用using就能改变为对应的访问
```

class 默认private继承； struct默认public继承 （应该保持显示声明）

同名情况：![image-20201021201315429](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021201315429.png)

基类的析构函数：如如果要删除一个指向派生类对象的基类指针，就需要虚析构函数。此时，无论其派生类使用合成的析构函数还是自己定义的，都是虚析构函数（继承了基类的虚属性）![image-20201021202024446](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021202024446.png)

虚析构函数将阻止合成移动操作

派生类的析构函数即销毁自己还负责销毁派生类的直接基类；

删除和继承：![image-20201021202400424](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021202400424.png)

移动操作与继承：派生类要有移动操作，其基类必须有移动操作的定义

**派生类和拷贝控制值**：通常使用对应的基类构造函数来初始化对象的基类部分：![image-20201021202554822](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021202554822.png)

派生类和赋值运算符：需要显示调用：

```c++
//Base::operator=(const Base&) //不会被自动调用
D &D::operator=(const D &rhs){
    Base::operator=(rhs); //显式调用
    //return *this
}
```

派生类析构函数：![image-20201021202809190](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021202809190.png)

如果构造函数或析构函数调用了某个虚函数，则应该执行与构造函数或析构函数所属类型相对应的虚函数版本。

**继承构造函数**：
默认情况下，类不能继承默认、拷贝、移动构造函数，若派生类没有指定，这会被合成

用using来继承构造函数：![image-20201021203132950](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021203132950.png)

等价于：![image-20201021203203876](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021203203876.png)

若派生类有自己的数据成员，这会被默认初始化

对构造函数的继承（用using）不会改变访问级别：在基类是私有的，在子类也是，即使using声明在public中

若基类构造函数有默认实参，这些实参不会被继承

如果派生类定义的构造函数和基类的构造函数具有相同的参数列表，这该构造函数不会被继承。

默认的、拷贝、移动构造函数不会被继承

#### 容器与继承

不能把有继承关系的多种类型对象直接存在容器中，否则派生类部分会被切掉![image-20201021203706145](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021203706145.png)

解决方法：在容器中放入指针：

![image-20201021203741249](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021203741249.png)



## 文本查询程序设计：

![image-20201017213633437](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201017213633437.png)

共享数据：在查询数据的时候，拷贝行号会引起很多文件的拷贝，应避免，用shared_ptr来应用这种共享关系

实现：

```c++
void runQueries(ifsteam &infile){
    TextQuery tq(infile);
    while(true){
        cout << "enter word to look for, or q to quit: ";
        string s;
        //遇到文件尾或用户输入‘q’终止
        if(!(cin >> s) || s == "q") break;
        //指向查询并打印结果
        print(cout, tq.query(s)) << endl;
    }
}

class QueryResult;
class TextQuery{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    //每个单词-行号集合的map
    std::map<std::string, 
             std::shared_ptr<std::set<line_no>>> wm;
}

TextQuery::TextQuery(ifstream &is):file(new vector<string){
    string text;
    while(getline(is, text)){  //从流读入一行
        file->push_back(text); //保存到file
        int n = file->size() - 1; //当前行号
        istringstream line(text);  //对text创建到流格式，后面进行分词处理
        string word;
        while(line >> word){ // 自动对空格分词
            auto &lines = wm[word];  //lines是一个shared_ptr
            if(!lines){ //第一次遇到这个单词时，此指针为空
                lines.reset(new set<line_no>); //分配一个新的set
            }
            lines.insert(n); //插入行号
        }
    }
}

class QueryResult{
friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string> f):
    	sought(s), lines(p), file(f){}
private:
    string sought; //查询单词
    shared_ptr<set<line_no>> lines;  //出现的行号
    shared_ptr<vector<string> file;  //输入文件
}

QueryResult TextQuery::query(const string &sought) const{
    //没找到 返回该指针
    static shared_ptr<set<line>> nodata(new set<line>);
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

ostream &print(ostream &os, const QueryResult &qr){
    os << qr.sought << "occurs" << qr.lines->size() <<" " << make_plural(qr.lines->size(), "time", "s") << endl;
    for(auto num : *qr.lines)
        os <<"\t(line" << num + 1 << ")" <<*(qr.file->begin() + num) <<endl;
    return os;
}
```

#改进：<img src="C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021222420414.png" alt="image-20201021222420414" style="zoom:70%;" />

设计：<img src="C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021222547630.png" alt="image-20201021222547630" style="zoom:40%;" /><img src="C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20201021222605648.png" alt="image-20201021222605648" style="zoom:45%;" />

实现：

```c++
//抽象类，具体查询类型从中派生，所有成员都是private
class Query_base{
    friend class Query;
protected:
    using line_no = TextQuery::line_no; // 用于eval函数
    virtual ~Query_base() = default;
private:
    //返回于当前Query匹配的QueryReuslt
    virtual QueryResult eval(const TextQuery&) const = 0;
    //rep表示查询的一个string
    virtual std::string rep() const = 0;
}

//管理Query_base的继承体系的接口类
class Query{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&); //构建一个wordQuery
    //接口函数
    QueryResult eval(const TextQuery &t) const {return q->eval(t);}
    std::string rep() const {return q->rep();}
private:
    Query(std::shared_ptr<Query_base> query) : q(query){}
    std::shared_ptr<Query_base> q;
};

//Query的输出运算符
std::ostream& operator<<(std::ostream &os, const Query &query){
    //Query::rep通过他的Query_base指针对rep进行虚调用
    return os << query.rep();
}

//调用如下 Query andq = Query(s1) & Query(s2); cout << andq <<endl;

//派生类

class WordQuery: public Query_base{
    friend class Query;  //Query使用wordQuery构造函数
    WordQuery(const std::string &s) : query_word(s){}
    //具体的类，故它要定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t) const{
        return t.query(query_word);
    }
    std::string rep() const {return query_word;}
    std::string query_word; //要查找的单词
}
//定义Query的构造函数
//因为它要用到wordQuery的构造函数，故定义在类wordQuery的后面
inline
Query::Query(const std::string &s): q(new WordQuery(s)) {}

class NotQuery: public Query_base{
    friend Query operator(const Query&);
    NotQuery(const Query &q): query(q){}
    
    std::string rep() const {return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};
inline Query operator~(const Query &operand){
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery: public Query_base{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
    	lhs(l), rhs(r), opSym(s){}
    //本类是抽象类，不定义eval
    std::string rep() const {return "(" + lhs.rep() + " "
                            		   + opySym + " "
                              		   + rhs.rep() + ")";}
    Query lhs, rhs;
    std::string opSym;
};

class AndQuery: public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
    		BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs){
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResutl
AndQuery::eval(const TextQuery &text) const{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(left.begin(), left.end(),
                    right.begin(), right.end(),
                    inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}


class OrQuery: public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right):
    		BinaryQuery(left, right, "|"){}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs, const Query &rhs){
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResutl
OrQuery::eval(const TextQuery &text) const{
    //通过query成员lhs和rhs的虚调用
    //调用eval返回每个运算对象的QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}
```

