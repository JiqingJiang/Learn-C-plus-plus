//
// Created by jiqing on 2025/2/19.
//
#include <iostream>
using namespace std;
/* C++函数模板
 * 模板的意义：对函数类型也可以参数化了
 * 函数模板 => 是不进行编译的，因为类型还不知道
 * 模板的实例化 => 函数调用点进行实例化
 * 模板函数 => 才是要被编译器来编译的
 *
 * 模板类型参数：typename/class
 * 模板非类型参数
 *
 * 模版的实参推演 => 可以根据用户传入的实参的类型，推导出模版类型参数
 * 模板的特例化（专用化） 特殊的
 *
 * 函数模版，模版的特例化，非模版函数的重载关系
 *
 * 模板代码是不能一个文件中定义，在另一个文件中使用的
 *
 * 模版在调用之前，一定要看到模版的定义，这样才能正常的被实例化，产生能够被编译器编译的代码
 *
 * 所以模板代码都是放在头文件中的，然后在源文件中直接include包含
*/

// 模板的声明
template <typename T>
bool compare(T a, T b);

template <typename T>        //定义一个模板参数列表
bool compare(T a, T b){      //compare是一个函数模板
    cout << "template compare" << endl;
    return a > b;
}

/*
在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
bool compare<int>(int a, int b);
{
     return a > b;
 }
 */

// 针对compare函数模板，提供const char*类型的特例化版本
template <>
bool compare<const char*>(const char* a, const char* b){
    cout << "compare<const char*>" << endl;
    return strcmp(a, b) > 0;
}

// 非模板函数 - 普通函数
bool compare(const char* a, const char* b){
    cout << "normal compare" << endl;
    return strcmp(a, b) > 0;
}

int main(){
    // 函数的调用点
    compare<int>(10, 20);
    compare<double>(10.5, 2.4);
    // 函数模板实参的推演
    compare(20, 20);
    compare<int>(30, 40.5);

    // 函数模板实参的推演 T const char*
    // 对于某些类型来说，依赖编译器默认实例化的模板代码，代码处理逻辑是
    // 编译器优先把compare处理成函数名字，没有的话，才去找compare模板
    compare("aaa", "bbb");
    compare<const char *>("aaa", "bbb");
    return 0;
}