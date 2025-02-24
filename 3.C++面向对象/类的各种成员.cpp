//
// Created by jiqing on 2025/2/21.
//
#include <iostream>

/*
 * 类的各种成员 - 成员方法/变量
 * 普通的成员方法  => 编译器会添加一个this形参
 * 1.属于类的作用域
 * 2.调用该方法时，需要依赖一个对象（常对象是无法调用的）
 * 3.可以访问对象的私有成员变量  protected继承 public private
 *
 * static静态成员方法 => 不会生成this形参
 * 1.属于类的作用域
 * 2.用类名作用域来调用方法
 * 3.可以任意访问对象的私有成员，仅限于不依赖对象的成员（只能调用其他的static静态成员）
 *
 * const常成员方法 => const CGoods *this
 * 1.属于类的作用域
 * 2.调用依赖一个对象，普通对象或者常对象都可以
 * 3.可以任意访问对象的私有成员，但是只能读，不能写
 *
 */
class CDate
{
public:
    CDate(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    // 常成员方法  只要是只读操作的成员方法，一律实现成const常成员方法
    void show() const
    {
        std::cout << _year << "年" << _month << "月" << _day << "日" << std::endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

class CGoods
{
public:
    CGoods(char *name, double price, int amount, int y, int m, int d)
            :_date(y, m, d) //构造函数的初始化列表
    {
        _price = price;
        _amount = amount;
        strcpy(_name, name);
        _count++; //记录商品对象的总数量
    }
    void show()
    {
        std::cout << "商品名称：" << _name << std::endl;
        std::cout << "商品价格：" << _price << std::endl;
        std::cout << "商品数量：" << _amount << std::endl;
        _date.show();
    }
    void show() const
    {
        std::cout << "商品名称：" << _name << std::endl;
        std::cout << "商品价格：" << _price << std::endl;
        std::cout << "商品数量：" << _amount << std::endl;
        _date.show();
    }
    // 静态成员方法 没有this指针的
    static void showCGoodsCount()
    {
        std::cout << "商品对象的总数量：" << _count << std::endl;
    }
private:
    char _name[20];
    double _price;
    int _amount;
    CDate _date; // 成员对象
    static int _count; // 静态成员变量  不属于对象，而是属于类级别的   声明  用来记录商品对象的总数量
};
// static成员变量一定要在类外进行定义并且初始化
int CGoods::_count = 0; // 静态成员变量的初始化

int main()
{
    CGoods good1("商品1", 10.5, 100, 2025, 2, 21);
    good1.show();
    CGoods good2("商品2", 20.5, 200, 2025, 2, 22);
    good2.show();
    CGoods good3("商品3", 30.5, 300, 2025, 2, 23);
    good3.show();
    CGoods good4("商品4", 40.5, 400, 2025, 2, 24);
    good4.show();

    // 统计所有商品的总数量
//    good4.showCGoodsCount();
    CGoods::showCGoodsCount();

    const CGoods good5("商品5", 50.5, 500, 2025, 2, 25);
    good5.show();
    return 0;
}