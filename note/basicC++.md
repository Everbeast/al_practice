### class之间的关系（面向对象）

·继承
·复合
·委托

### c和c++的区别:

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105140645750.png" alt="image-20201105140645750"  style="zoom:50%;" />

·object beasted ：面对单一的class的设计
·object oriented ：面对多重classes的设计

·class分类：有指针成员/无指针成员
以下用complex类代表无指针成员
       用string 类代表有指针成员

#### 代码形式：

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105142232636.png" alt="image-20201105142232636" style="zoom:67%;"/>

#### 头文件的布局

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105142342804.png" alt="image-20201105142342804" style="zoom:50%;" />

其他：

·相同class的各个objects互为friends

·设计一个class要考虑：
	数据是否为private
	参数尽量为reference
	返回值尽量是reference

·该种情况不能return by reference，因为是local object

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105142838348.png" alt="image-20201105142838348" style="zoom:45%;"/>

·对<<只能是非成员重载（因为只能对cout作用）

```c++
ostream&
operator << (ostream& os, const complex& x){
    return os << "(" << real(x)<<","
        	  << imag(x) <<")";
}
{
    complex c1(2,1);
    cout<<conj(cj); //(2,-1)
    cout<< c1 << conj(c1); //(2,1)(2,-1)
}
//返回值为ostream&使得能够使用cout<<c1<<conj(c1)
//改成返回值为void就不能使用连续使用
```

·若类是含有指针 这拷贝构造就需要自己写，如string类

#### 实现complex

```c++
//in complex.h
#ifndef __COMPLEX__
#define __COMPLEX__

class complex {
public:
    complex (double r = 0, double i = 0):
    	re (r), im (i){}
    complex& operator += (const complex&);
    double real () const {return re;}
    double imag () const {return im;}
private:
    double re, im;
    
    friend complex& __doapl (complex*, const complex&);
};

#endif
//函数定义
inline complex&
__doapl(complex* ths, const complex& r){
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex&
complex::operator += (const complex& r){
    return __doapl(this, r);
}

inline complex
operator + (const complex& x, const complex& y){
    return complex( real(x) + real(y),
                    imag(x) + imag(y));
}

inline complex
operator + (const complex& x, double y){
    return complex (real(x) + y, imag(x));
}

inline complex
operator + (double x, const complex& y){
    return complex(x + real(y), image(y));
}
```

#### 实现string类

```c++
class String{
public:
    String(const char* cstr = 0);
    String(const String& str);
    String& operator=(const String& str);
    ~String();
    char* get_c_str() const {return m_data;}
private:
    char* m_data;
};

//ctor
inline
String::String(const char* cstr = 0){
    if(cstr){
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }else{
        m_data = new char[1];
        *m_data = "\0";
    }
}

//dtor
inline
String::~String(){
    deletep[] m_data;
}

//copy ctor
inline
String::String(const String& str){
    //直接取另一个object的private data 因为兄弟之间互为friend
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data)
}

//copy op=
inline
String& String::operator=(const String& str){
    if(this == &str){//自我检测很重要
        return *this;
    }
    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}
```

copy op=中不自我检测会造成指向空：

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105150459887.png" alt="image-20201105150459887" style="zoom: 33%;" />

#####Stack

存在于某个作用域的一块内存空间。当调用函数，函数本身会形成一个stack用来放置它所接受的函数以及返回地址。函数本体内生命的任何变量其所用的内存块都取自stack
（如一个命名空间中的变量，离开这个空间生命结束）

#####Heap

指由操作系统提供的一块global内存空间，程序可动态分配从中获得若干blocks
（如一个程序的全局变量，直到程序结束或者delete之际结束）



### 类间关系

**composition**：复合，表示 has-a

如下：queue(container)里有一个deque(component)

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105152503019.png" alt="image-20201105152503019" style="zoom:35%;" />



**delegation**：委托

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105152726898.png" alt="image-20201105152726898" style="zoom:335%;" />



**inheritance:** 继承， 表示 is-a

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105152945934.png" alt="image-20201105152945934" style="zoom:35%;"/>

虚函数：
no-virtual：不希望被继承和overried它
virtual: 希望子类override它，并已经提供了默认定义
pure virtual：希望子类一定要overried它，因为没有默认定义



#### template method

子类继承父类的函数使用virtual关键字，改变该函数的行为，其他行为不变。
如下：执行流程如灰色线

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105153349881.png" alt="image-20201105153349881" style="zoom:40%;" />

#### 转换函数

```c++
//例子1
class Fraction{
public:
    Fraction(int num, int den = 1)
        : m_num(num), m_denom(den){}
    operator double() const{
        return (double)(m_num / m_denom);
    }
private:
    int m_num;
    int m_denom;
}

//调用
Fraction f(3, 5);
double d = 4 + f; //调用opeartor double 将f转为0.6

//例子2---------------
class Fraction{
public:
    Fraction(int num, int den = 1)
        : m_num(num), m_denom(den){}
    Fraction operator+(const Fraction& f){
        return Fraction(...);
    }
private:
    int m_num;
    int m_denom;
}
//调用
Fraction f(3,5);
Fraction df = f + 4; //调用非explicit的ctor将4转为F(4,1)，在调用op+

//例子3---------------
class Fraction{
public:
    Fraction(int num, int den = 1)
        : m_num(num), m_denom(den){}
    operator double() const{
        return ...;
    }
    Fraction operator+(const Fraction& f){
        return Fraction(...);
    }
private:
    int m_num;
    int m_denom;
}
//调用
Fraction f(3,5);
Fraction df = f + 4; //歧义

//例子2---------------
class Fraction{
public:
    explict Fraction(int num, int den = 1)
        : m_num(num), m_denom(den){}
   
    operator double() const{
        return ...;
    }
    Fraction operator+(const Fraction& f){
        return Fraction(...);
    }
private:
    int m_num;
    int m_denom;
}
//调用
Fraction f(3,5);
Fraction df = f + 4; //是explicit 无法转换
```



#### 模板模板参数：

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105161116706.png" alt="image-20201105161116706" style="zoom:35%;" />

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105161155584.png" alt="image-20201105161155584" style="zoom:35%;"  />

这不是模版模版参数：

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105161257354.png" alt="image-20201105161257354" style="zoom:35%;"  />

#### 虚函数的实现：

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105161439120.png" alt="image-20201105161439120" style="zoom:50%;" />



#### const

const object只会只能调用const版本
non-const object只会只能调用non-const版本

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20201105161756608.png" alt="image-20201105161756608" style="zoom:50%;"  />