#include "calculator.h"
#include "./ui_calculator.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "postfix.h"

bool waitingForOperand = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->Button0, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button1, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button2, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button3, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button4, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button5, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button6, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button7, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button8, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->Button9, SIGNAL(released()), this, SLOT(numberPressed()));

    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->ButtonSubstract, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(numberPressed()));
    connect(ui->ButtonDivision, SIGNAL(released()), this, SLOT(numberPressed()));

    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(changeSignPressed()));
    connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(equalPressed()));
    connect(ui->BackSpace, SIGNAL(released()), this, SLOT(backspaceClicked()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clearInput()));

    connect(ui->ButtonSqrt, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonInverse, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonSquare, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonCube, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonPercentage, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numberPressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString text = ui->Display->text() + button->text();
    text.remove("=");
    ui->Display->setText(text);
    ui->Display2->setText("");
}

void Calculator::changeSignPressed()
{
    QPushButton *button = (QPushButton*)sender();
    double newNumber;
    if (button->text() == "+/-")
    {
        if (ui->Display2->text() != "")
        {
            newNumber = ui->Display2->text().toDouble();
        }
        else
        {
            newNumber = ui->Display->text().toDouble();
        }
        newNumber = newNumber * -1;
        ui->Display->setText(QString::number(newNumber, 'g', 10));
    }
}

void Calculator::equalPressed()
{
    numberPressed();
    std::string stackString = ui->Display->text().toStdString();
    double result = EvaluateExpression(stackString);
    ui->Display2->setText(QString::number(result,'g',15));
}

void Calculator::on_ButtonComma_released()
{
    ui->Display->setText(ui->Display->text()+'.');
}

void Calculator::unaryOperatorPressed()
{
    QPushButton *button = (QPushButton*)sender();
    double result = 0.0;
    double operand;
    if (ui->Display2->text() != "")
    {
        operand = ui->Display2->text().toDouble();
    }
    else
    {
        operand = ui->Display->text().toDouble();
    }

    if (button->text() == "√")
    {
        if (operand < 0.0 || operand < 0)
        {
            clearInput();
            return;
        }
        result = std::sqrt(operand);
    }
    else if (button->text() == "1/x")
    {
        if (operand == 0.0)
        {
            clearInput();
            return;
        }
        result = 1.0 / operand;
    }
    else if (button->text() == "x² ")
    {
            result = std::pow(operand, 2.0);
    }
    else if (button->text() == "x³")
    {
            result = std::pow(operand, 3.0);
    }
    else if (button->text() == "%")
    {
        result = operand * 0.01;
    }

    ui->Display2->setText(QString::number(result, 'g', 10));
    waitingForOperand = true;
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;
    QString number = ui->Display->text();
    number.chop(1);
    if (number.isEmpty()) {
        number = "";
        waitingForOperand = true;
    }
    ui->Display->setText(number);
}

void Calculator::clearInput()
{
    waitingForOperand = false;
    ui->Display->setText("");
    ui->Display2->setText("");
}
