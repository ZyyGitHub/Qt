#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);    //创建一个QApplication对象，QApplication底层是一个类 创建对象并初始化,管理应用程序的资源
    QLabel *label = new QLabel("hello QT");   //创建一个Qlable对象  小控件可以显示一行文本
    label->show();        //显示创建的控件
    return app.exec();    //让程序进入消息循环，等待菜单、工具条、鼠标等输入，然后进行相应
}
