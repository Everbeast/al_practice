### deque的实现原理 

> deque由一个“控制中心”(map)和多端连续空间(buffer)构成的。 
>
> 其中map是一段连续的空间，每个节点是指向每段buffer开头的指针，deque的数据存储在buffer中。
>
> 由迭代器的复杂实现来使得deque体现出整体是连续的
>
> 维持有start和finish迭代器，迭代器有四个指针分别有指向：数据在buffer的位置，buffer的开头，buffer结尾，该buffer对应的控制中心的位置
>
> 当扩充时，若迭代器中cur等于first(push_front时)或者等于last(push_back时)，则会申请新的一段buffer，设置新的迭代器中对应指针的值，然后存去数据。当map需要扩充时，将原来的指针拷贝到新的空间里面的中间位置(map_size是原来的两倍?)

### vector和deque的优劣

> 两者都是连续存储结构
>
> vector支持高校的随机访问和**尾部**插入/删除操作,其他位置插入/删除操作效率低(O(n))
> deque提供两级数组结构, 支持高效的**头尾**插入/删除,同时支持随机访问 但占用内存比vector高
>
> 高效随机存取,不在乎插入删除效率,或者只在尾部插入删除,用vector
> 需要随机存取,在乎首位插入删除效率,用deque
> 大量插入删除,不需要随机存储,用list

### vector的扩容实现

```
vector维持有capacity变量表示空间容量大小,若vector的size增长至满容量,则开辟新的空间(或是1.5倍或是2倍,取决于编译器),将原来的空间的数据复制到新的空间中,删除释放原来空间,并调整迭代器指向新的空间
```

### hashtable的实现

> stl中的hashtable使用的是开链法. 他维护一个buckets vector,其中存放指针指向自定义链表,链表的node存放实际的数据. 其中内置有一堆质数,创建哈希表时,根据存入元素个数来选择大于等于元素个数的质数作为哈希表的容量,即buckets vector的长度.当元素个数达到该容量,会选择下一个质数,重建新的bucket vector,再计算所有元素在新的哈希表的位置

### 哈希表为什么要用质数

> 因为计算key的时候需要用到模运算,若不选用质数,那么具有相同公共因数的数据就会发生冲突,哈希表需要避免这种冲突

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

### 堆和栈的区别

> **栈**是由系统自动分配的,是一块连续的内存空间,且大小固定,若申请空间超过栈剩余空间,会有栈溢出错误.
>
> **堆**是由程序员申请的,因为系统用链表来存储空闲内存地址,因此堆是不连续的内存区域.申请的内存应由程序员释放,若不释放在程序结束后系统收回.
>
> 效率比较:
>
> - 栈由系统分配,速度快,但程序员无法控制
> - 堆由new分配,速度较慢,容易产生内部碎片.

### 讲讲移动构造函数

```
某情况:当我们用对象a来初始化对象b后,对象a就不再用了. 
拷贝构造函数(深拷贝的情况下)就是就是分配新的空间,将对象a的内容复制到对象b,然后再释放a的空间(不用的话,调用析构)而使用移动构造函数就能避免新的空间分配,降低构造成本

对于指针: 拷贝构造采用深层赋值, 移动构造函数采用浅层赋值(两个指针指向同一片内存空间,避免被两次释放,就将原来的指针置为NULL)

移动构造和拷贝构造的参数不同:拷贝-> 左值引用, 移动->右值引用
即用一个右值或者是将亡值去初始化另一个对象时,才会调用移动构造函数,而move作用是将一个左值变成一个将亡值
```

### 常量指针和指针常量

```c++
常量指针: const int* cp
	     int const* cp //两个等价 
    //不能通过该指针改变所指变量, 无论所指变量是否为常量
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
const int b3 = 20; 		   //顶层const，b3是常量不可变!
const int* const b4 = &a;  //前一个const为底层，后一个为顶层，b4不可变
const int& b5 = a;		   //用于声明引用变量，都是底层const!

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
--------------------------
const_cast只能改变对象的底层const
int num = 4;  
const int *p = &num;  
//*p = 5;  //错误，不能改变底层const指针指向的内容  
int *p_f = const_cast<int *>(p_e);  //正确，const_cast可以改变运算对象的底层const
                                   //但是使用时一定要知道num不是const的类型。  
*p_f = 5;  //正确，非顶层const指针可以改变指向的内容  
cout << num;  //输出5  (把底层const去掉了,能通过*p_f改变num)
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

指针作为参数传递时,将实参拷贝传递给形参,两者指向同一地址,但是两个变量.引用会改变(引用永远就是同一个东西)
(传递指针,形参能改变所指的变量,和实参所指的是同一变量,但不能改变实参指针自己本身)
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

## 拷贝构造

### 什么时候会调用拷贝构造函数

> - 一个对象以值传递的方式传入函数体: 根据实参用拷贝构造去初始化这个临时对象(1)
> - 一个对象以值传递的方式从函数返回: 先产生临时对象,拷贝构造将函数里面局部变量给临时对象,函数结束先析构局部变量,在析构临时变量. 若有接受对象,则如case3那样同样调用拷贝构造初始化a3(2)
> - 一个对象需要通过另外一个对象进行初始化。(3)
>
> ```c++
> class A{...};
> void useA(A a){}
> A getA(){
>     A a;
>     return a;
> }
> int main(){
>     A a1;
>     A a2 = a1;//case 3
>     useA(a1) //case 1
>     A a3 = getA(); //case2
> }
> ```

### 什么时候调用赋值运算符

> - 一个对象以值传递方式从函数体返回,且接受返回值的对象已经过初始化(1)
> - 一个对象直接复赋值给另一个对象,且接受的对象已经初始化(2)
>
> ```c++
> //接上面的另一个作用域
> A a1;
> A a2;
> a2 = a1 //case 2
> a1 = getA(); //case1
> ```

### 拷贝构造函数和赋值运算符重载的区别

> - 拷贝构造函数是函数，赋值运算符是运算符重载。
>
> - 拷贝构造函数会生成新的类对象，赋值运算符不能。
>
> - 赋值运算符需要检查原对象和新对象(=号左边的对象)是否相同, 需要避免自赋值),拷贝构造不用(3)
>
> - 赋值运算符中如果原来的对象有内存分配则需要先把内存释放掉。(4)
>
>   ```c++
>   class A{
>   	char* ptr;
>   	...
>   public:
>       A& operator=(A& a){
>           if(this != &a){ //避免自赋值(3)
>               //避免内存泄漏(4)
>               if(ptr != NULL){
>                   delete ptr;
>                   ptr = NULL;
>               }
>               ptr = new char[strlen(a.ptr) + 1];
>               strncpy(ptr, a.ptr, strlen(a.ptr) + 1);
>           }
>       }
>       return *this;
>   }
>   ```
>
>   补:形参传递是调用拷贝构造函数（调用被赋值对象的拷贝构造函数），但并不是所有出现"="的地方都是使用赋值运算符
>
>   ```
>    Student s;
>   Student s1 = s;    // 调用拷贝构造函数
>   Student s2;
>   s2 = s;    // 赋值运算符操作c++
>   ```
>
>   注：类中有指针变量时要重写析构函数、拷贝构造函数和赋值运算符
>

### 深拷贝除了改写拷贝构造函数以外还要做什么操作

> 还需要重载赋值运算符

补:

- 默认拷贝构造是浅拷贝
- 需要自定义析构函数-->几乎肯定也需要自定义**拷贝赋值运算符**和**拷贝构造函数**
- 需要拷贝构造函数-->也需要赋值运算符
- 需要赋值运算符-->也需要拷贝构造函数

### 深浅拷贝的区别

> 浅拷贝只拷贝一个指针,和原来指针指向同一个地址,若原指针所指资源被释放,再释放浅拷贝指针所指资源会出错
>
> 深拷贝开辟新的空间,将被拷贝的对象拷贝过来,深拷贝指针指向新的空间,原对象被析构不影响深拷贝的对象
>
> ```c++
> //理解程序
> class Student{
> 	int num;
> 	char *name;
> public:
> 	Student(){
>         name = new char(20);
> 		cout << "Student" << endl;
>     };
> 	~Student(){
>         cout << "~Student " << &name << endl;
>         delete name;
>         name = NULL;
>     };
> 	Student(const Student &s){//拷贝构造函数
>         //浅拷贝，当对象的name和传入对象的name指向相同的地址
>         name = s.name;
>         //深拷贝
>         //name = new char(20);
>         //memcpy(name, s.name, strlen(s.name));
>         cout << "copy Student" << endl;
>     };
> };
>  
> int main()
> {
> 	{// 花括号让s1和s2变成局部对象，方便测试
> 		Student s1;
> 		Student s2(s1);// 复制对象
> 	}
> 	return 0;
> }
> //浅拷贝执行结果：
> //Student
> //copy Student
> //~Student 0x7fffed0c3ec0
> //~Student 0x7fffed0c3ed0
> //*** Error in `/tmp/815453382/a.out': double free or corruption (fasttop): 0x0000000001c82c20 ***
> 
> //深拷贝执行结果：
> //Student
> //copy Student
> //~Student 0x7fffebca9fb0
> //~Student 0x7fffebca9fc0
> ```

## 虚函数

### 虚函数的机制:

```c++
当我们将函数声明为virtual时，编译器不会在编译时就确定对象要调用的函数的地址，而是在运行时再去确定要调用的函数的地址，这就是晚绑定，也叫做动态绑定

过程(看下图):
(1)编译器在发现基类中有虚函数时，会自动为*每个含有虚函数的类*(继承多少个基类时)生成一份虚表，该表是一个一维数组，虚表里保存了虚函数的入口地址

(2)编译器会在每个对象的前四个字节中保存一个虚表指针，即vptr，指向对象所属类的虚表。在构造时，根据对象的类型去初始化虚指针vptr，从而让vptr指向正确的虚表，从而在调用虚函数时，能找到正确的函数

(3)在派生类定义对象时，程序运行会自动调用构造函数，在构造函数中创建虚表并对虚表初始化。在构造子类对象时，会先调用父类的构造函数，此时，编译器只“看到了”父类，并为父类对象初始化虚表指针，令它指向父类的虚表；当调用子类的构造函数时，为子类对象初始化虚表指针，令它指向子类的虚表

(4)当派生类对基类的虚函数没有重写时，派生类的虚表指针指向的是基类的虚表；当派生类对基类的虚函数重写时，派生类的虚表指针指向的是自身的虚表；当派生类中有自己的虚函数时，在自己的虚表中将此虚函数地址添加在后面

重写的虚函数在虚表中的slot和基类对应的虚函数的slot一样
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
派生对象 |  ---------  |
         |  son成员    |
          --------------
定义对象时先构造父类,为父类成员变量初始化, 再构造子类,当将子类转化为父类,该对象被认为是派生类对象模型的上半部分(此阶段,是在编译时,会确定每个对象调用函数(非虚函数的地址),即静态绑定),即访问的就是基类的成员
```

### 析构函数设为虚函数可不可以？为什么

> 析构函数可以为虚函数，并且一般情况下基类析构函数要定义为虚函数。
>
> 由于类的多态性，基类指针可以指向派生类的对象，如果删除该基类的指针，就会调用该指针指向的派生类析构函数，而派生类的析构函数又自动调用基类的析构函数，这样整个派生类的对象完全被释放。
> 如果析构函数不被声明成虚函数，则编译器实施静态绑定，在删除基类指针时，只会调用基类的析构函数而不调用派生类析构函数，这样就会造成派生类对象析构不完全，造成内存泄漏。
>
> **析构函数可以是纯虚函数**，含有纯虚函数的类是抽象类，此时不能被实例化。但派生类中可以根据自身需求重新改写基类中的纯虚函数

### 构造函数能不能设为虚函数?为什么

> 含有虚函数的类的对象的内存空间都会有vptr,指向vtable. 若是构造函数是虚函数,那么就需要在vtable中找到该函数,但对象没有实例化就没有内存空间,找不到vtable. 即vtbl是调用构造函数后才建立的
>
> 虚函数的作用在于通过父类的指针或引用来调用这个虚函数时,可以变成调用子类的那个成员函数.而构造函数是在创建对象时自己主动调用的,不可能通过父类指针或引用去调用,因此构造函数不能是虚函数也没有意义.

### public protected private 继承

> public继承: 基类公有/保护成员作为子类成员保留原有状态, 基类私有作为子类成员任然是私有(即子类不能访问基类的私有)
>
> protected继承: 基类公有/保护成为子类的保护成员,基类私有仍然私有
>
> private继承: 基类公有/保护成员为子类的私有成员,即不能被改子类的子类可见
>
> ![68747470733a2f2f63646e2e6a7364656c6976722e6e65742f67682f666f7274686573706164612f6d65646961496d6167653140312e362e332e342f3230323130322f313536343133323235353034302e706e67](https://gitee.com/chillchan/images/raw/master/test/68747470733a2f2f63646e2e6a7364656c6976722e6e65742f67682f666f7274686573706164612f6d65646961496d6167653140312e362e332e342f3230323130322f313536343133323235353034302e706e67.png)

### STL的内存分配器:

> 分有一级分配器和二级分配器
>
> 一级分配器是以malloc() free()等c函数执行的实际内存分配
>
> 二级分配器维护16条链表,0-15号链表分别对应8到128字节的内存块(8的倍数)(当需要空间<128字节调用二级分配器,反之调用一级)
>
> 步骤:
>
> 其实free_list[16]都为空,例如用户申请32字节(25-32的范围都是申请32字节)
>
> 查看对应free_list(即free_list[3])是否有挂有内存块:
>
> - 有: 就将该块给用户,对应指针下移一位.
>
> - 无: 查看内存池是否为空:
>
>   ​       ->内存池为空: 申请 2 * 32字节 * 20 + 额外空间作为内存池大小, 将内存池中20 * 32字节 挂到对应free_list上(其中第一块分配给用户,free_list剩余19*32)
>   
>   ​       ->内存池不为空: 若内存池够20*32字节的空间, 则将其挂到对应free_list中,then同上(第一块分配给用户...)
>   
>   ​                                  若内存池不够则能分配多少就分配多少块 x*32字节空间,then同上(第一块分配给用户...)	

![image-20210301155713197](https://gitee.com/chillchan/images/raw/master/test/image-20210301155713197.png)

### STL迭代器的实现:

> 迭代器内部必须保存一个与容器相关的指针,通过重载各种运算操作来遍历,其中最重要的是*运算符和->运算符,也可能包括++\ --(自增自减)等运算符.
>
> 作用:通过迭代器可以在不了解容器内部原理的情况下遍历容器
>
> 常用迭代器的里面的性质: iterator_category	value_type	pointer	reference	difference_type

### 简述STL萃取机:

> 一个类模板,里面没有成员,只有类型的重命名,在不再来其他的负担的前提下, 利用模板参数推导功能来向外界提供一些信息 如:
>
> iterator_traits:
>
> - value_type：迭代器所指对象的型别
> - difference_type：两个迭代器之间的距离
> - pointer：迭代器所指向的型别
> - reference：迭代器所引用的型别
> - iterator_category
>
> type_traits:
>
> ```c++
> __type_traits<T>::has_trivial_default_constructor
> __type_traits<T>::has_trivial_copy_constructor
> __type_traits<T>::has_trivial_assignment_operator
> __type_traits<T>::has_trivial_destructor
> __type_traits<T>::is_POD_type
> ```
>
> 补充:
>
> ```c++
> struct __true_type{};
> struct __false_type{};//是类型,在编译期知道
> true false//是值, 运行时知道
> ```
>
> 是一个空的结构体,作为编译器对类对象参数推导结果(自定义类型如下)
>
> ```c++
> template<> struct __type_traits<Shape>{
> 	typedef __true_type has_trivial_default_constructor;
> 	typedef __false_type has_trivial_copy_constructor;
> 	typedef __false_type has_trivial_assignment_operator;
> 	typedef __false_type has_trivial_destructor;
> 	typedef __false_type is_POD_type;
> };
> ```

### new一个数组p, delete p和delete[] p的区别

> ![image-20210301163028461](C:\Users\chill\AppData\Roaming\Typora\typora-user-images\image-20210301163028461.png)

### 为什么malloc时需要指定size，对应的free时不需要指定size？

> 调用malloc(size)时,实际分配的内存大小大于size字节, 多出的内存区域有一个结构记录malloc申请的内存大小以及已使用大小等信息. free的时候根据这个结构里的信息来释放内存

## 智能指针

### 为什么用shared_ptr而不用auto_ptr(为什么摒弃auto_ptr)

> 如果两个auto_ptr指针指向同一个对象时，当该对象的生存周期结束后，系统会调用析构函数，这样导致的结果是程序对同一个对象删除了2次，造成程序出错。
>
> 解决方法之一就是采用引用计数的方法. 当有一个一个指针指向对象时，引用计数加1，当指向该对象的指针销毁时，引用计数减1，当且仅当最后一个指向该对象的指针销毁时，也就是引用计数为0时，对象才能够被删除。智能指针shared-ptr就是采用该机制来实现的。

### 自己写一个memcpy

```c++
void * my_memcpy(void *dst, const void *src, int n){
    if(dst == NULL || src == NULL || n <= 0) return NULL;
    
    char * pdst = (char *) dst;
    char * psrc = (char *) src;
    
    if(pdst > psrc && pdst < psrc + n){
        pdst = pdst + n - 1;
        psrc = psrc + n - 1;
        while(n--){
            *pdst = *psrc;
            src--;
            dst--;
        }
    }else{
        while(n--){
            *pdst = *psrc;
            src++;
            dst++;
        }
    }
    return dst;
}
```

### 前后序递归和迭代实现

```c++
//中序迭代
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> stk;
    TreeNode* node = root;
    while(node || !stk.empty()){
        while(node){
            stk.push(node);
            node = node->left;
        }
        node = stk.top();
        stk.pop();
        res.push_back(node->val);

        node = node->right;
    }
    return res;
}
//前序迭代
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    if(root == nullptr) return res;
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()){
        TreeNode* node = stk.top();
        stk.pop();
        res.push_back(node->val);
        if(node->right){
            stk.push(node->right);
        }
        if(node->left){
            stk.push(node->left);
        }
    }
    return res;
}

```

### 十进制转二进制

```c++
   int n,i,j=0;
   int a[1000];
  // n = "想要转换的数";
   i=n;
   while(i)
   {
    a[j]=i%2;
    i/=2;
    j++;
    
   }
   for(i=j-1;i>=0;i--)
    cout<<a[i];
   cout<<endl;
```

stack的实现

> stl默认是用deque实现, 也可以用vector实现,是一个适配器