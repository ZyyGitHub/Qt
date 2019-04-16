#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

QT_BEGIN_NAMESPACE class QLineEdit;
QT_END_NAMESPACE class Button;

class Calculator:public QDialog
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = 0);
private slots:      //槽函数
    void digitClicked();                            //按键0~9
    void unaryOperatorClicked();                     //平方，开根号
    void additiveOperatorClicked();                  //"+""-"
    void multiplicativeOperatorClicked();            //"x""/"
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addTomemory();
private:
    Button *createButton(const QString &text, const char *member);          //生成按键函数
    void abortOperation();                                                   //运算错误
    bool calculate(double rightOperand,const QString &pendingOperator);      //运算函数
    double sumInMemory;                                  //Memory相关的值
    double sumSoFar;                                     //加减运算值保存
    double factorSofar;                                  //乘除运算值保存
    QString pendingAdditiveOperator;                     //加减运算符号保存
    QString pendingMultiplicateOperator;                 //乘除运算符号保存
    bool waitingForOperand;                               //表示状态
    QLineEdit *display;                                  //数字显示框

    enum{NumDigitButtons = 10};
    Button *digitButtons[NumDigitButtons];                  //按键0~9
};

#endif // CALCULATOR_H
