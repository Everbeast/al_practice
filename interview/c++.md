### deque的实现原理 

    deque由一个“控制中心”(map)和多端连续空间(buffer)构成的。 
    
    其中map是一段连续的空间，每个节点是指向每段buffer开头的指针，deque的数据存储在buffer中。
    
    由迭代器的复杂实现来使得deque体现出整体是连续的
    
    维持有start和finish迭代器，迭代器有四个指针分别有指向：数据在buffer的位置，buffer的开头，buffer结尾，该buffer对应的控制中心的位置
    
    当扩充时，若迭代器中cur等于first(push_front时)或者等于last(push_back时)，则会申请新的一段buffer，设置新的迭代器中对应指针的值，然后存去数据。当map需要扩充时，将原来的指针拷贝到新的空间里面的中间位置(map_size是原来的两倍?)

### vector和deque的优劣

```
两者都是连续存储结构

vector支持高校的随机访问和*尾部*插入/删除操作,其他位置插入/删除操作效率低(O(n))
deque提供两级数组结构, 支持高效的*头尾*插入/删除,同时支持随机访问 但占用内存比vector高

高效随机存取,不在乎插入删除效率,或者只在尾部插入删除,用vector
需要随机存取,在乎首位插入删除效率,用deque
大量插入删除,不需要随机存储,用list
```

### vector的扩容实现

```
vector维持有capacity变量表示空间容量大小,若vector的size增长至满容量,则开辟新的空间(或是1.5倍或是2倍,取决于编译器),将原来的空间的数据复制到新的空间中,删除释放原来空间,并调整迭代器指向新的空间
```

### 说说C++的内存分区

```
程序分为:
-高地址
| [栈区]       :存储局部变量,当这些变量超出作用域时自动弹出释放,效率很高但分配内存容量有限
| [堆区]       :由程序员分配的空间(即new分配的)和释放,编译器不管,当程序结束,内存没有被释放,系统自动收回
| [全局存储区] :存放全局变量和静态变量,若未初始化的会被自动初始化
| [常量存储区] :存放常量,不允许被修改
| [代码区]     : 存放函数体的二进制代码
-低地址

```

### 讲讲移动构造函数

```
当我们用对象a来初始化对象b后,对象a就不再用了. 
拷贝构造函数就是就是分配新的空间,将对象a的内容复制到对象b,然后再释放a的空间(不用的话,调用析构)而使用移动构造函数就能避免新的空间分配,降低构造成本

对于指针: 拷贝构造采用深层赋值, 移动构造函数采用浅层赋值(两个指针指向同一片内存空间,避免被两次释放,就将原来的指针置为NULL)

移动构造和拷贝构造的参数不同:拷贝-> 左值引用, 移动->右值引用
即用一个右值或者是将亡值去初始化另一个对象时,才会调用移动构造函数,而move作用是将一个左值变成一个将亡值
```

### 常量指针和指针常量

```c++
常量指针: const int* cp
	     int const* cp //两个等价 不能通过该指针改变指向的变量, 无论指向的变量是否为常量
    //若指向的是非常量,可以通过其他方式改变
    //理解:常量的指针(cp是指针,*cp表指向的变量,const表示该指针指向的变量不能改变)
    //可以改变指向哪个变量 因为指针本身是个变量
int a, b;
int const * cp = &a;
*cp = 2; //错误 
a = 2;//正确
cp = &b //正确
    
指针常量: int *const cp
    //理解: cp是指针 const表示指针本身是个常量,不能改变指向. 可以通过该指针改变指向的变量
int a ;
int *const cp = &a;
a = 1;
*cp = 2;
```

### 讲讲顶层const、底层const，引用更接近哪个

```c++
顶层const: 指const修饰指针本身 int *const p       ---->指针常量
底层const: 指const修饰指针指向的对象 const int * p --->常量指针
int a = 10;
int* const b1 = &a;        //顶层const，b1本身是一个常量
const int* b2 = &a;        //底层const，b2本身可变，所指的对象是常量
const int b3 = 20; 		   //顶层const，b3是常量不可变
const int* const b4 = &a;  //前一个const为底层，后一个为顶层，b4不可变
const int& b5 = a;		   //用于声明引用变量，都是底层const

const int a = 1;  //a是顶层const  
//int * pi = &a;  //错误，&a是底层const，不能赋值给非底层const   
const int * pi = &a; //正确，&a是底层const，可以赋值给底层const  
const int *const *const ppi = &pi  //即是底层const，也是顶层const  
const int  *const *const *pppi = &ppi; //底层const  

引用更加接近顶层const,都必须定义时初始化,且不能改变指向
————————————————拓展————————————————
重载:
void test(char *p); (1)
void test(char *const p); (2)
void test(const char *p); (3)
//底层指针需要实参是常量,其他没有这个限制,因此 (1)(3)或 (2)(3)组成重载函数
————————————————
作用:
对象拷贝时,常量底层const不能赋值给非常量的底层const
int num = 0;
const int * p1 = &num;
//int *p2 = p1 //错误
const int *p3 = p1;//正确
---
const_cast只能给变对象的底层const
int num = 4;  
const int *p = &num;  
//*p = 5;  //错误，不能改变底层const指针指向的内容  
int *p_f = const_cast<int *>(p_e);  //正确，const_cast可以改变运算对象的底层const
//但是使用时一定要知道num_e不是const的类型。  
*p_f = 5;  //正确，非顶层const指针可以改变指向的内容  
cout << num;  //输出5  (把底层const去掉了,能通过*p_f改变num
---
//顶层const是指针本身常量,和指向的变量没关系
int num = 4;
int *const p = &num;
int *pf = p;
*pf = 5;
cout<<num<<endl;//输出5
    



```

### 讲讲指针和引用

```c++
指针是一个变量,存储的是一个地址 | 引用跟原来的变量本质上是同一个东西,只是原变量的别名

指针可以多级                   | 引用只有一级

指针可以为空                   | 引用不能为NULL
指针可以先声明不初始化         | 引用定义是必须初始化

指针初始化后可以改变指向	   | 引用在初始化后不可改变
						    | 变量可以被引用多次,但引用只能作为一个变量的引用

sizeof指针是指针本身大小       | sizeof引用得到引用所指变量的大小

指针作为参数传递时,将实参拷贝传递给形参,两者指向同一地址,但是两个变量,在函数中改变形参指针指向,不影响实参,而引用会改变(引用永远就是同一个东西)
void test(int *p)
{
　　int a=1;
　　p=&a;
　　cout<<p<<" "<<*p<<endl;
}

int main(void)
{
    int *p=NULL;
    test(p);
    if(p==NULL)
    	cout<<"指针p为NULL"<<endl;
    return 0;
}
//运行结果为：
//0x22ff44 1
//指针p为NUL
```

### 虚函数的机制:

```c++
当我们将函数声明为virtual时，编译器不会在编译时就确定对象要调用的函数的地址，而是在运行时再去确定要调用的函数的地址，这就是晚绑定，也叫做动态绑定

过程(看下图):
(1)编译器在发现基类中有虚函数时，会自动为*每个含有虚函数的类*(继承多少个基类时)生成一份虚表，该表是一个一维数组，虚表里保存了虚函数的入口地址

(2)编译器会在每个对象的前四个字节中保存一个虚表指针，即vptr，指向对象所属类的虚表。在构造时，根据对象的类型去初始化虚指针vptr，从而让vptr指向正确的虚表，从而在调用虚函数时，能找到正确的函数

(3)在派生类定义对象时，程序运行会自动调用构造函数，在构造函数中创建虚表并对虚表初始化。在构造子类对象时，会先调用父类的构造函数，此时，编译器只“看到了”父类，并为父类对象初始化虚表指针，令它指向父类的虚表；当调用子类的构造函数时，为子类对象初始化虚表指针，令它指向子类的虚表

(4)当派生类对基类的虚函数没有重写时，派生类的虚表指针指向的是基类的虚表；当派生类对基类的虚函数重写时，派生类的虚表指针指向的是自身的虚表；当派生类中有自己的虚函数时，在自己的虚表中将此虚函数地址添加在后面

(5)重写的虚函数在虚表中的slot和基类对应的虚函数的slot一样
 理解:如一个ptr调用一个虚函数z(),转化成:(*ptr->vptr[4])(ptr);

这样指向派生类的基类指针在运行时，就可以根据派生类对虚函数重写情况动态的进行调用，从而实现多态性。
————————————————

class Father{
public:
	virtual void fun()
	{cout << "I am father!" << endl;}
};
class Son:public Father{
public:
	void fun()
	{cout << "I am son!" << endl;}
};
int main()
{
	Son son;
	Father *Pfather= &son;
	Father& father = son;
	Pfather->fun(); //output "I am son!"
	father.fun();//output "I am son!"
 
	Father fath;
	Father* Pfath = &fath;
	Pfath->fun();//output "I am father!"
 
	system("pause");
	return 0;
}
```

<img src="https://gitee.com/chillchan/images/raw/master/test/image-20210227232931539.png" alt="image-20210227232931539" style="zoom: 80%;" />

```c++
补充:————————————————————————————————
与普通继承的对比
class Father{
public:
	void fun()
	{cout << "I am father!" << endl;}
 
};
class Son:public Father{
public:
	void fun()
	{cout << "I am son!" << endl;}
};
 
int main()
{
	Son son;
	Father *Pfather= &son;
	Pfather->fun(); //output "I am father!"
	return 0;
}
         --------------
         |  father成员 |
派生对象 |	---------  |
         |  son成员    |
          --------------
定义对象时先构造父类,为父类成员变量初始化, 再构造子类,当将子类转化为父类,该对象被认为是派生类对象模型的上半部分(此阶段,是在编译时,会确定每个对象调用函数(非虚函数的地址),即静态绑定),即访问的就是基类的成员
```

