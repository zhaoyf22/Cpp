#include "SmartPointerTest.h"
#include <string>
#include <vector>
#include <initializer_list>
#include <iostream>

namespace SmartPointer {
// shared_ptr
// 动态内存实现多个对象共享相同的底层数据，使用shared_ptr实现
class StrBlobPtr;
class StrBlob {    
public:
    friend class StrBlobPtr;
    // 返回指向首元素和尾后元素的 StrBlobPtr
    StrBlobPtr begin();
    StrBlobPtr end();

    using size_type = vector<string>::size_type;

    StrBlob():data(make_shared<vector<string>>()){}
    StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)) {}
    // 类属性
    size_type size() const {
        return data->size();
    }
    bool empty() const {
        return data->empty();
    }
    // 添加和删除元素
    void push_back(const string& str) {
        data->push_back(str);
    }
    void pop_back() {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }

    // 访问元素,非常量版本
    string& front() {
        check(0, "front on empty StrBlob");
        return data->front();
    }
    string& back() {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    // 访问元素,const版本
    const string& front() const {
        check(0, "front on empty StrBlob");
        return data->front();
    }
    const string& back() const {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    // print
    void print(const string& msg) const {
        cout << msg << "[ ";
        for(size_type i=0; i<size(); i++) {
            cout << data->at(i) << " ";
        }
        cout << "]";
        cout << endl;
    }
private:
    shared_ptr<vector<string>> data;
    // 核查索引是否在有效范围内
    void check(size_type i, const string& msg) const {
        if( i >= size() ) {
            throw out_of_range(msg);
        }
    }
};
void SharedPtrTest2() {
    StrBlob b1;
    b1.print("b1"); // b1[ ]
    {
        StrBlob b2{"a", "an", "the"};
        b1 = b2; // 赋值，采用默认赋值版本，即shared_ptr的赋值操作
        b1.print("b1"); // b1[ a an the ]
        b2.push_back("about");

        b1.print("b1"); // b1[ a an the about ]
        b2.print("b2"); // b2[ a an the about ]
    }

    b1.print("b1");  // b1[ a an the about ]

    // const版本的front/back测试
    string strCp = b1.front(); // 调用非const版本
    strCp.push_back('a'); // "aa"

    const string& strRef = b1.front();  // "a"，调用非const版本

    const StrBlob b3 = b1;
    string strCp1 = b3.front(); // 调用const版本
    const string& strRef1 = b3.front(); // 调用const版本

    int temp = 0;
    return;
}

void SharedPtrTest1()
{
    // shared_ptr的几种初始化方式
    shared_ptr<int> p1; // null
    shared_ptr<string> p2 = make_shared<string>(); // 非null, 调用string默认构造函数
    if(p2 && p2->empty()) {
        *p2 = "hello world";
    }
    shared_ptr<string> p4 = make_shared<string>("hello world"); // 非null

    // shared_ptr引用计数调试
    shared_ptr<int> p3 = make_shared<int>(100); // 非null,值初始化对象int(100)
    int p3count = p3.use_count();   // 1，初始化，引用计数为1

    shared_ptr<int> p5 = p3;
    p3count = p3.use_count();       // 2，被拷贝，引用计数+1
    int p5count = p5.use_count();   // 2,请思考

    shared_ptr<int> p6(p3);
    p3count = p3.use_count();       // 3，被拷贝，引用计数+1
    p5count = p5.use_count();       // 3,请思考
    int p6count = p6.use_count();   // 3,请思考

    p5 = make_shared<int>(10);
    p3count = p3.use_count();       // 2,请思考
    p5count = p5.use_count();       // 1,被赋予新的shared_ptr,引用计数为1
    p6count = p6.use_count();       // 2,请思考

    p6 = make_shared<int>(20);
    p3count = p3.use_count();       // 1,请注意
    p5count = p5.use_count();       // 1,请注意
    p6count = p6.use_count();       // 1,被赋予新的shared_ptr,引用计数为1

    p3 = make_shared<int>(30);      // 此时，引用计数递减为0，对象int(100)被释放
    p3count = p3.use_count();       // 1,请注意
    p5count = p5.use_count();       // 1,请注意
    p6count = p6.use_count();       // 1,被赋予新的shared_ptr,引用计数为1

    int temp = 0;
    return;
}


// shared_ptr 和内置指针结合使用，慎重
void process(shared_ptr<int> ptr) {
    cout << *ptr << endl;
}

void SharedPtrTest3() {
//    shared_ptr<int> p1 = new int(1024);   // 错误，explicit构造函数
    shared_ptr<int> p2(new int(1024));      // 通过指针初始化shared_ptr

    process(p2);
    int value = *p2;                // 有效
    p2.reset(new int(100));         // p2释放指向的1024，重新指向100

    shared_ptr<int> pCp = p2;
    if( !p2.unique() ) {
        // p2不是所知对象的仅有用户，改变之前制作一份新的拷贝
        p2.reset(new int(*p2));
    }
    *p2 = 200;                      // 可以放心的修改p2指向的内容了

    // 临时shared_ptr会释放
    int *x = new int(2048);
    process(shared_ptr<int>(x));    // 临时shared_ptr，该条语句结束后被释放，即x指向内存被释放
    value = *x;                     // x指向内存已经被释放，悬空指针，未定义行为

    // 绝对不要使用get初始化另一个智能指针或为内置指针赋值
    shared_ptr<int> p(new int(1024));
    int *q = p.get();
    {
        value = *p;
        shared_ptr<int> p3(q);  // p3遇到 "}" 会释放指向的内存空间，即p,q指向内存已经被释放
    }
    value = *p;                 // 错误

    return;
}



// unique_ptr
// 不能拷贝unique_ptr有一个例外，我们可以拷贝或者赋值一个将要被销毁的unique_ptr
unique_ptr<int> clone1(int n) {
    return unique_ptr<int>(new int(n));
}

unique_ptr<int> clone2(int n) {
    unique_ptr<int> ret(new int(n));
    cout << *ret << endl;
    return ret;
}

void UniquePtrTest1() {
    // unique_ptr完全拥有它所指向的对象，因此不支持普通的拷贝或赋值操作
    unique_ptr<int> up1;
    unique_ptr<int> up2(new int(1024));

    // 不能拷贝unique_ptr有一个例外，我们可以拷贝或者赋值一个将要被销毁的unique_ptr
    auto ret1 = clone1(1024);
    *ret1 = 2048;
    auto ret2 = clone2(100);
    ret1.reset(ret2.release());

    // unique_ptr的所有权转移
    unique_ptr<string> p1(new string("tegpsaurus")); // p1指向"tegpsaurus"
    unique_ptr<string> p2(p1.release());             // p1放弃对"tegpsaurus"的指针，并且置为nullptr,p2指向p1返回的指针
    unique_ptr<string> p3(new string("trex"));       // p3指向"trex"
    p2.reset(p3.release());                          // p2释放原来指向的对象，重新指向p3返回的指针

    return;
}

void UniquePtrTest2() {
    using intup = unique_ptr<int>;

    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
//    intup p0(ix);       // 错误，尝试将栈上的变量赋值给unique_ptr
    {
//        intup p1(pi);   // 错误，会尝试delete pi指向的栈上的变量ix
    }
    int value = ix;

    intup p2(pi2);
    {
//        intup p3(&ix);          // 错误，ix为栈上的变量，同p1
    }
    intup p4( new int(2048));   // 正确
    value = *p2;
    {
//        intup p5(p2.get());     // 禁止，尝试将智能指针通过get返回的原始指针赋给另一个智能指针
    }
    value = *p2;                // 错误, p2指向的内存已经被p5释放掉

    return;
}


// weak_ptr
class StrBlobPtr {
public:
    StrBlobPtr():curr(0) {}
    StrBlobPtr(StrBlob& b, size_t cur=0):wptr(b.data),curr(cur) {}

    // 解引用
    string& deref() const {
        auto ret = check(curr, "dereference past end");
        return (*ret)[curr];
    }
    // 自增
    StrBlobPtr& incr() {
        check(curr, "increase past end of StrBlobPtr");
        ++curr;
        return *this;
    }
private:
    // 核查，若成功，返回一个指向vector的shared_ptr
    shared_ptr<vector<string>> check(size_t i, const string& msg) const {
        auto ret = wptr.lock();
        if( !ret ) {
            throw runtime_error("unbound StrBlobPtr");
        }
        if( i >= ret->size() ) {
            throw out_of_range("msg");
        }
        return ret;
    }

    weak_ptr<vector<string>> wptr;  // 指向vector
    size_t curr;                    // 在数组中的位置
};

StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

void WeakPtrTest1() {
    StrBlob sb1({"apple", "banalan", "juce"});
    {
        StrBlob sb2 = sb1;
    }

    auto iter = sb1.begin();
    auto itere = sb1.end();

    string str = iter.deref();
    iter.incr();
    str = iter.deref();
    iter.incr();
    str = iter.deref();
    iter.incr();
    str = iter.deref();

    return;
}

void test() {
    // weak_ptr
    WeakPtrTest1();

    // unique_ptr
    UniquePtrTest2();
    UniquePtrTest1();

    // shared_ptr
    SharedPtrTest3();
    SharedPtrTest2();
    SharedPtrTest1();
}
};
