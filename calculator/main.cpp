#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);    //实例化一个应用
    Calculator calc;                 //实例化计算器应用
    calc.show();                     //显示图形界面
    return app.exec();               //等待退出应用
}
/*
信号：信号被一个对象发射，对客户或者所有者的内部进行改变，信号有moc自动产生，不应该在.cpp文件中实现
信号没有范围属性限制
信号的声明类似函数 void signal();
槽：普通的C++成员函数，槽可以有参数但是不能是缺省值
槽函数有三种类型：
private slots:只有自己的类可以将信号与之相连接
protected slots:类及其子类可以何其相连接
public slots:任何对象将其信号可以与之相连接

信号与槽的关联：
通过connect函数
通过disconnect断开连接

元对象工具moc对类声明进行分析并产生初始化元对象的C++代码
元对象包含全部信号和槽的名字以及指向这些函数的指针
Q_OBJECT宏定义告诉编译器先应用moc工具进行扩展


信号和槽一般在头文件中
头文件中开始位置必须加上Q_OBJECT


宏定义不能用在signal和slot的参数中
函数指针不能用于信号和槽的参数
信号和槽不能有缺省参数
嵌套的类不能位于信号或者槽区域内，也不能有信号或者槽
友元不能声明信号或者槽声明区内
*/
