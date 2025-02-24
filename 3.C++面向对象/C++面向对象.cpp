//
// Created by jiqing on 2025/2/21.
//

#include <iostream>
using namespace std;
/*
 C++ OOP面向对象    OOP编程    this指针
 C：各种各样的函数的定义 Struct
 C++: 类 => 实体的抽象类型
 实体（属性、行为）  ->    ADT(Abstract data type)
 对象               <-(实例化)            类（属性->成员变量  行为->成员方法）

 OOP语言的四大特征是什么？
 抽象  封装/隐藏  继承  多态

 类  ->   商品实体
 访问限定符：public公有的 private私有的 protected保护的

 */
const int NAME_LEN = 20;
class CGoods{   // 商品的抽象数据类型
private: //属性一般都是私有的
    char _name[NAME_LEN];
    double _price;
    int _amount;
public: //给外部提供公有的方法，来访问私有的属性
    // 做商品数据初始化用
    void init(char *name, double price, int amount);
    // 打印商品信息
    void show();
    // 给成员变量提供一个getXXX或setXXX的方法 类体内实现的方法，自动实现成inline方法
    void setName(char *name) { strcpy(_name, name); }
    void setPrice(double price) { _price = price; }
    void setAmount(int amount) { _amount = amount; }
    const char* getName() { return _name; }
    double getPrice() { return _price; }
    int getAmount() { return _amount; }
};
 void CGoods::init(char *name, double price, int amount)
 {
     strcpy(_name, name);
     _price = price;
     _amount = amount;
 }
 void CGoods::show() {
     cout << "商品名称：" << _name << endl;
     cout << "商品价格：" << _price << endl;
     cout << "商品数量：" << _amount << endl;
 }
int main()
{
     /*
      * CGoods可以定义无数的对象，每一个对象都有自己的成员变量
      * 但是它们共享一套成员方法
      *
      * show  =>  怎么知道处理哪个对象的信息？
      * init(name, price, amount) =>  初始化哪个对象的信息？
      *
      * 类的成员方法一经编译，所有的方法参数，都会加一个this指针，接收
      */

    CGoods good; //类实例化了一个对象
    // init(&good, "面包", 5.6, 100);
    good.init("面包", 5.6, 100);
    good.show();
    return 0;
}
