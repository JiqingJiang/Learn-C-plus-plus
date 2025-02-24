//
// Created by jiqing on 2025/2/19.
//
#include<iostream>

using namespace std;

/*
 * 函数模板
 * 模板的非类型参数 必须是整数类型（整数或者地址/引用都可以）都是常量，只能使用，不能修改
 * 类模板 => 实例化 => 模版类
 */
// 类模板
template<typename T>
class SeqStack //模板名称+类型参数列表 = 类名称
{
public:
    // 构造和析构函数名不用加<T>，其他出现模板的地方都加上类型参数列表
    // 构造函数
    SeqStack<T>(int size=10)
            : _pstack(new T[size])
            , _top(0)
            , _size(size)
    {}
    // 析构函数
    ~SeqStack<T>()
    {
        delete [] _pstack;
        _pstack = nullptr;
    }

    // 拷贝构造函数
    SeqStack<T>(const SeqStack<T> &stack)
            :_top(stack._top)
            , _size(stack._size)
    {
        _pstack = new T[_size];
        for (int i = 0; i < _top; i++)
        {
            _pstack[i] = stack._pstack[i];
        }
    }

    // 赋值构造函数
    SeqStack<T>& operator=(const SeqStack<T> &stack)
    {
        if (this == &stack)
            return *this;

        delete [] _pstack;
        _top = stack._top;
        _size = stack._size;
        _pstack = new T[_size];
        // 不要用memcopy进行拷贝
        for (int i = 0; i < _top; i++)
        {
            _pstack[i] = stack._pstack[i];
        }
        return *this;
    }

    void push(const T &val);
//    void push(const T &val)
//    {
//        if (full())
//        {
//            expand();
//        }
//        _pstack[_top++] = val;
//    }

    void pop()
    {
        if (empty())
            return;
        --_top;

    }

    T top() const
    {
        if (empty())
            throw "stack is empty!"; // 抛出异常也代表函数逻辑结束
        return _pstack[_top - 1];
    }
    bool full() const { return _top == _size; } // 栈满
    bool empty() const { return _top == 0; } // 栈空
private:
    T *_pstack;
    int _top;
    int _size;
    // 顺序栈底层数组按2倍的方式扩容
    void expand()
    {
        T *ptmp = new T[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }
        delete []_pstack;
        _pstack = ptmp;
        _size *= 2;
    }
};

template<typename T>
void SeqStack<T>::push(const T &val) // 入栈操作
{
    if (full())
        expand();

    _pstack[_top++] = val;
}

int main()
{
    //  类模板的选择性实例化
    //  模板类 class SeqStack<int>{};
    SeqStack<int> stack;
    stack.push(10);
    stack.push(78);
    stack.push(90);
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    return 0;
}





//template<typename T, int SIZE>
//void sort(T *arr)
//{
//    for (int i = 0; i < SIZE; i++)
//    {
//        for (int j = 0; j < SIZE - 1 - i; j++)
//        {
//            if (arr[j] > arr[j + 1])
//            {
//                T temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp;
//            }
//        }
//    }
//}


//int main()
//{
//    int arr[] = { 10, 3, 95, 17, 69, 2, 40, 16, 8, 0 };
//    const int size = sizeof (arr) / sizeof (arr[0]);
//    sort<int, size>(arr);
//    for (int i = 0; i < size; i++)
//    {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//    return 0;
//}