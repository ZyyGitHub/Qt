#include <QtGui>
#include <math.h>
#include <QLineEdit>
#include <QGridLayout>

#include "button.h"
#include "calculator.h"

Calculator::Calculator(QWidget *parent):QDialog (parent)
{
    //初始化变量
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSofar = 0.0;
    waitingForOperand = true;

    //初始化Qt窗口部件的初始状态
    display = new QLineEdit("0");    //The QLineEdit widget is a one-line text editor.
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize()+8);
    display->setFont(font);

    //Qt部件信号与槽的关联
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i),SLOT(digitClicked()));
    }
    Button *pointButton = createButton(tr("."),SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("+-"),SLOT(changeSignClicked()));
    Button *backspaceButton = createButton(tr("Backspace"),SLOT(backspaceClicked()));
    Button *clearButton = createButton(tr("clear"),SLOT(clear()));
    Button *clearAllButton = createButton(tr("Clear All"),SLOT(clearAll()));
    Button *clearMemoryButton = createButton(tr("MC"),SLOT(clearMemory()));
    Button *readMemoryButton = createButton(tr("MR"),SLOT(readMemory()));
    Button *setMemoryButton = createButton(tr("MS"),SLOT(setMemory()));
    Button *addToMemoryButton = createButton(tr("M+"),SLOT(addtoMemory()));
    Button *divisionButton = createButton(tr("/"),SLOT(multiplicateOperatorClicked()));
    Button *timesButton = createButton(tr("x"),SLOT(multiplicateOperatorClicked()));
    Button *minusButton = createButton(tr("-"),SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"),SLOT(additiveOperatorClicked()));
    Button *squareRootButton = createButton(tr("Sqrt"),SLOT(unaryOperatorClicked()));
    Button *powerButton = createButton(tr("x^2"),SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("1/x"),SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="),SLOT(equalClicked()));

    QGridLayout *mainLayout = new QGridLayout;    //The QGridLayout class lays out widgets in a grid
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(display,0,0,1,6);
    mainLayout->addWidget(backspaceButton,1,0,1,2);
    mainLayout->addWidget(clearButton,1,2,1,2);
    mainLayout->addWidget(clearAllButton,1,4,1,2);

    mainLayout->addWidget(clearMemoryButton,2,0);
    mainLayout->addWidget(readMemoryButton,3,0);
    mainLayout->addWidget(setMemoryButton,4,0);
    mainLayout->addWidget(addToMemoryButton,5,0);

    for(int i = 1; i < NumDigitButtons; ++i)
    {
        int row = ((9-i)/3)+2;
        int column = ((i -1)%3) + 1;

        mainLayout -> addWidget(digitButtons[i],row, column);
    }

    mainLayout -> addWidget(digitButtons[0],5,1);
    mainLayout -> addWidget(pointButton,5,2);
    mainLayout -> addWidget(changeSignButton,5,3);

    mainLayout -> addWidget(divisionButton,2,4);
    mainLayout -> addWidget(timesButton,3,4);
    mainLayout -> addWidget(minusButton,4,4);
    mainLayout -> addWidget(plusButton,5,4);

    mainLayout -> addWidget(squareRootButton,2,5);
    mainLayout -> addWidget(powerButton,3,5);
    mainLayout -> addWidget(reciprocalButton,4,5);
    mainLayout -> addWidget(equalButton,5,5);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}

//创建一个按钮，并将部件的信号关联到相应的槽
Button *Calculator::createButton(const QString &text, const char *member)
{
    Button  *button = new Button(text);
    connect(button,SIGNAL(clicked()),this,member);  //实现部件的信号与槽的关联
    return button;
}
void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}
void Calculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}
void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}
void Calculator::addTomemory()
{
    equalClicked();
    sumInMemory +=display->text().toDouble();
}
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if(display->text() == "0" && digitValue == 0.0){
        return;
    }
    if (waitingForOperand){
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}
void Calculator::pointClicked()
{
    if(waitingForOperand){
        display->setText("0");
    }
    if(!display->text().contains(".")){
        display->setText(display->text() + tr("."));
    }
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if(value > 0.0){
        text.prepend(tr("-"));
    }else if(value < 0.0){
        text.remove(0,1);
    }
    display->setText(text);
}
void Calculator::backspaceClicked()
{
    if(waitingForOperand)
        return;
    QString text = display->text();
    text.chop(1);
    if(text.isEmpty()){
        text = "0";
        waitingForOperand = true;
    }
    display -> setText(text);
}
void Calculator::clear()
{
    if(waitingForOperand)
        return;
    display->setText("0");
    waitingForOperand = true;
}
void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSofar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicateOperator.clear();
    display ->setText("0");
    waitingForOperand = true;
}
void Calculator::abortOperation()
{
    clearAll();
    display -> setText(tr("####"));
}
bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if(pendingOperator == tr("+")){
        sumSoFar += rightOperand;
    }else if(pendingOperator == tr("-")){
        sumSoFar -= rightOperand;
    }else if(pendingOperator == tr("\327")){
        factorSofar *= rightOperand;
    }else if(pendingOperator == tr("\367")){
        if(rightOperand == 0.0){
            return  false;
        }
        factorSofar /= rightOperand;
    }
    return true;
}
void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if(!pendingMultiplicateOperator.isEmpty()){
        if(!calculate(operand, pendingMultiplicateOperator)){
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSofar));
        operand = factorSofar;
        factorSofar = 0.0;
        pendingMultiplicateOperator.clear();
    }
    if(!pendingAdditiveOperator.isEmpty()){
        if(calculate(operand,pendingAdditiveOperator)){
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    }else{
        sumSoFar = operand;
    }
    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}
void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if(!pendingMultiplicateOperator.isEmpty()){
        if(!calculate(operand, pendingMultiplicateOperator)){
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSofar));
    }else{
        factorSofar = operand;
    }
    pendingMultiplicateOperator = clickedOperator;
    waitingForOperand = true;
}
void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if(clickedOperator == tr("Sqrt")){
        if(operand < 0.0){
            abortOperation();
            return;
        }
        result = sqrt(operand);
    }else if(clickedOperator == tr("x\262")){
        result = pow(operand,2.0);
    }else if(clickedOperator == tr("1/x")){
        if(operand == 0.0){
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}
void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    if(!pendingMultiplicateOperator.isEmpty()){
        if(calculate(operand,pendingMultiplicateOperator)){
            abortOperation();
            return;
        }
        operand = factorSofar;
        factorSofar = 0.0;
        pendingMultiplicateOperator.clear();
    }
    operand = display->text().toDouble();
    if(!pendingAdditiveOperator.isEmpty()){
        if(calculate(operand,pendingAdditiveOperator)){
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    }else{
        sumSoFar = operand;
    }
    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}
