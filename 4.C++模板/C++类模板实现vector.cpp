//
// Created by jiqing on 2025/2/20.
//
#include <iostream>

/*
 类模板 => 实现一个C++ STL里面的顺序容器 vector 向量容器

 * */

template<typename T>
class vector
{
public:
    vector(int size = 10)
            : _first(new T[size])
            , _last(_first)
            , _end(_first + size)
    {}

    ~vector()
    {
        delete []_first;
        _first = _last = _end = nullptr;
    }
    //拷贝构造
    vector(const vector<T> &rhs)
    {
        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; i++)
        {
            _first[i] = rhs._first[i];
        }
        _last = _first + len;
        _end = _first + size;
    }
    //赋值构造
    vector<T>& operator=(const vector<T> &rhs)
    {
        if (this == &rhs)
            return *this;
        delete []_first;
        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; i++)
        {
            _first[i] = rhs._first[i];
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
        *_last++ = val;
    }
    // pop_back
    void pop_back() // 删除最后一个元素
    {
        if (empty())
            return;
        --_last;
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
    void expand() // 容器的二倍扩容接口
    {
        int size = _end - _first;
        T *ptmp = new T[size * 2];
        for (int i = 0; i < size; i++)
        {
            ptmp[i] = _first[i];
        }
        delete []_first;
        _first = ptmp;
        _last = _first + size;
        _end = _first + size * 2;
    }
};

int main()
{
    vector<int> vec;
    for (int i=0; i<=10; i++)
    {
        vec.push_back(i);
    }
    for (int i=0; i<vec.size(); i++)
    {
        std::cout << vec.back() << " ";
        vec.pop_back();
    }
    return 0;
}