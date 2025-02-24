//
// Created by jiqing on 2025/2/21.
//
#include <iostream>
/*
 * 构造函数和析构函数 OOP编程复习一下
 * OOP实现一个顺序栈
 *
 * 构造函数和析构函数
 * 函数的名字和类名一样
 * 没有返回值
 */
class SeqStack
{
public:
    SeqStack(int size = 10) // 构造函数可以有多个，不同参数的构造函数，构造函数的重载
            : _pstack(new int[size])
            , _top(-1)
            , _size(size)
    {
        std::cout << "SeqStack()" << std::endl;
    }
    ~SeqStack()  // 析构函数只能有一个
    {
        delete []_pstack;
        _pstack = nullptr;
        _top = -1;
        _size = 0;
        std::cout << "~SeqStack()" << std::endl;
    }
    void init(int size = 10)
    {
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }
    void release()
    {
        delete []_pstack;
        _pstack = nullptr;
        _top = -1;
        _size = 0;
    }
    void push(int val)
    {
        if (full())
            resize();
        _pstack[++_top] = val;
    }
    void pop()
    {
        if (empty())
            return;
        --_top;
    }
    int top()
    {
        return _pstack[_top - 1];
    }
    bool empty(){ return _top == -1; }
    bool full(){ return _top == _size - 1; }
private:
    int *_pstack; //动态开辟数组，存储顺序栈的元素
    int _top;     //指向栈顶元素的位置
    int _size;    //数组扩容的总大小
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
    SeqStack s1;
//    s1.init(10);
    for (int i = 0; i < 15; i++)
    {
        s1.push(rand() % 100);
    }
    while (!s1.empty())
    {
        std::cout << s1.top() << " ";
        s1.pop();
    }
//    s1.release();
    return 0;
}
