//
// Created by jiqing on 2025/2/20.
//
#include <iostream>

/*
 * 容器的空间配置器allocator
 */
// 定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
struct Allocator
{
    T* allocate(size_t size) //负责内存开辟
    {
        return (T*)malloc(sizeof(T) * size);
    }

    void deallocate(T *p) //负责内存释放
    {
        free(p);
    }

    void construct(T *p, const T &val) //负责对象构造
    {
        new(p) T(val); // 定位new表达式
    }

    void destroy(T *p) //负责对象析构
    {
        p->~T(); // ~T()代表了T类型的析构函数
    }
};

// 容器底层内存开辟，内存释放，对象构造，对象析构都通过allocator空间配置器来实现
template<typename T, typename Alloc=Allocator<T> >
class vector
{
public:
    vector(int size = 10)
    {
        // 需要把内存开辟和对象构造分开处理
        // _first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    ~vector()
    {
        // 析构容器有效的元素，然后释放_first指针指向的堆内存
        // delete []_first;
        for (T *p = _first; p != _last; ++p)
        {
            _allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构处理
        }
        _allocator.deallocate(_first); // 释放_first指针指向的堆上的数组内存
        _first = _last = _end = nullptr;
    }
    //拷贝构造
    vector(const vector<T> &rhs)
    {
        int size = rhs._end - rhs._first;
        // _first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; i++)
        {
            // _first[i] = rhs._first[i];
            _allocator.construct(_first + i, rhs._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
    }
    //赋值构造
    vector<T>& operator=(const vector<T> &rhs)
    {
        if (this == &rhs)
            return *this;
        // delete []_first;
        for (T *p = _first; p != _last; ++p)
        {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);
        int size = rhs._end - rhs._first;
//        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; i++)
        {
//            _first[i] = rhs._first[i];
            _allocator.construct(_first + i, rhs._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }
    // pushback
    void push_back(const T &val) // 尾插
    {
        if (full())
            expand();
//        *_last++ = val; _last指针指向的内存构造一个值为val的对象
        _allocator.construct(_last, val);
        _last++;
    }
    // pop_back
    void pop_back() // 删除最后一个元素
    {
        if (empty())
            return;
//        --_last; //不仅要把_last指针--，还需要析构删除的元素
        --_last;
        _allocator.destroy(_last);
    }
    // back
    T back() const
    {
        return *(_last - 1);
    }
    bool full() const { return _last == _end; } // 判断是否满了
    bool empty() const { return _last == _first; } // 判断是否空了
    int size() const { return _last - _first; } // 返回有效元素的个数
private:
    T *_first; // 指向数组起始的位置
    T *_last;  // 指向数组中有效元素的后继位置
    T *_end;   // 指向数组空间的后继位置
    Alloc _allocator; // 容器的空间配置器对象
    void expand() // 容器的二倍扩容接口
    {
        int size = _end - _first;
//        T *ptmp = new T[size * 2];
        T *ptmp = _allocator.allocate(size * 2);
        for (int i = 0; i < size; i++)
        {
            _allocator.construct(ptmp + i, _first[i]);
//            ptmp[i] = _first[i];
        }
//        delete []_first;
        for (T *p = _first; p != _last; ++p)
        {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);
        _first = ptmp;
        _last = _first + size;
        _end = _first + size * 2;
    }
};


class Test
{
public:
    Test(){ std::cout << "Test()" << std::endl; }
    ~Test(){ std::cout << "~Test()" << std::endl; }
    Test(const Test&) { std::cout << "Test(const Test&)" << std::endl; }
};
int main()
{
    Test t1, t2, t3;
    std::cout << "----------------" << std::endl;
    vector<Test> vec;
    vec.push_back(t1);
    vec.push_back(t2);
    vec.push_back(t3);
    std::cout << "----------------" << std::endl;
    vec.pop_back();  // 只需要析构对象，要把对象的析构和内存释放分开
    std::cout << "----------------" << std::endl;
    return 0;
}