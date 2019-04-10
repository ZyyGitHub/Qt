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
private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
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

};

#endif // CALCULATOR_H
