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
    Button *createButton(const QString &text, const char *member);
    void abortOperation();
    bool calculate(double rightOperand,const QString &pendingOperator);
    double sumInMemory;
    double sunSoFar;
    double factorSpfar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicateOperator;
    bool waitingForOperand;
    QLineEdit *display;

    enum{NumDigitButtons = 10};
    Button *digitButton[NumDigitButtons];
};

#endif // CALCULATOR_H
