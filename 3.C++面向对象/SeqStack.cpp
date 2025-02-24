//
// Created by jiqing on 2025/2/21.
//
#include <iostream>
/*
 * this 指针 => 类 => 很多对象共用一套成员方法
 * 成员方法，方法的参数都会添加一个this指针
 *
 * 构造函数：
 *     定义对象时，自动调用的；可以重载的；构造完成，对象产生了
 * 析构函数：
 *     不带参数，不能重载，只有一个析构函数；析构完成，对象就不存在了
 *
 * 对象的深拷贝和浅拷贝
 *
 */
class SeqStack
{
public:
    // 构造函数
    SeqStack(int size = 10)
            : _pstack(new int[size])
            , _top(0)
            , _size(size)
    {}
    ~SeqStack()
    {
        std::cout << "~SeqStack()" << std::endl;
        delete []_pstack;
        _pstack = nullptr;
    }
    SeqStack(const SeqStack &stack)
    {
        _top = stack._top;
        _size = stack._size;
        _pstack = new int[_size];
        for (int i = 0; i < _top; i++)
        {
            _pstack[i] = stack._pstack[i];
        }
    }
    SeqStack& operator=(const SeqStack &stack)
    {
        if (this == &stack)
            return *this;
        delete []_pstack;
        _top = stack._top;
        _size = stack._size;
        _pstack = new int[_size];
        for (int i = 0; i < _top; i++)
        {
            _pstack[i] = stack._pstack[i];
        }
        return *this;
    }
    void push(int val)
    {
        if (full())
            resize();
        _pstack[_top++] = val;
    }
    void pop()
    {
        if (empty())
            return;
        --_top;
    }
    int top()
    {
        return _pstack[_top];
    }
    bool empty(){ return _top == -1; }
    bool full(){ return _top == _size-1; }
private:
    int *_pstack;
    int _top;
    int _size;
    void resize()
    {
        int *ptmp = new int[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }
        delete []_pstack;
        _pstack = ptmp;
        _size *= 2;
    }
};

int main()
{
    SeqStack s1(10);
    SeqStack s2=s1;  //默认的拷贝构造是浅拷贝，做直接的内存拷贝
    SeqStack s3(s2);
    return 0;
}