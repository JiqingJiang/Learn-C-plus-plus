//
// Created by jiqing on 2025/2/21.
//
#include <iostream>

/*
 * 日期类
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
    void show()
    {
        std::cout << _year << "年" << _month << "月" << _day << "日" << std::endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

/*
 * 构造函数的初始化列表
 * CDate信息    CGoods商品信息的一部分      a part of  组合关系
 */
class CGoods
{
public:
    CGoods(char *name, double price, int amount, int y, int m, int d)
        :_date(y, m, d) //构造函数的初始化列表
    {
        _price = price;
        _amount = amount;
        strcpy(_name, name);
    }
    void show()
    {
        std::cout << "商品名称：" << _name << std::endl;
        std::cout << "商品价格：" << _price << std::endl;
        std::cout << "商品数量：" << _amount << std::endl;
    }
private:
    char _name[20];
    double _price;
    int _amount;
    CDate _date; // 成员对象
};

int main()
{

    return 0;
}