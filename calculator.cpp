#include "calculator.h"
#include "./ui_calculator.h"
#include <algorithm>

double firstValue;
bool secondNumberFlag = false;
bool waitingForOperand = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->ButtonAdd->setCheckable(true);
    ui->ButtonSubstract->setCheckable(true);
    ui->ButtonMultiply->setCheckable(true);
    ui->ButtonDivision->setCheckable(true);
    ui->ButtonPercentage->setCheckable(true);

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

    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonSubstract, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonDivision, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonPercentage, SIGNAL(released()), this, SLOT(symbolPressed()));

    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(changeSignPressed()));
    connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(equalPressed()));
    connect(ui->BackSpace, SIGNAL(released()), this, SLOT(backspaceClicked()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clearInput()));

    connect(ui->ButtonSqrt, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonInverse, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonSquare, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
    connect(ui->ButtonCube, SIGNAL(released()), this, SLOT(unaryOperatorPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numberPressed()
{
    QPushButton *button = (QPushButton*)sender();
    double numbers;
    QString numberTODisplay;
    if (ui->Display->text() == "0" && button->text().toInt() == 0.0)
    {
            return;
    }
    else if ((ui->ButtonAdd->isChecked() || ui->ButtonSubstract->isChecked()
            || ui->ButtonMultiply->isChecked() || ui->ButtonDivision->isChecked()
            || ui->ButtonPercentage->isChecked()) && (!secondNumberFlag))
    {
        numbers = button->text().toDouble();
        secondNumberFlag = true;
        numberTODisplay = QString::number(numbers, 'g', 10);
    }
    else if (waitingForOperand)
    {
        numbers = button->text().toDouble();
        ui->Display->setText(QString::number(numbers, 'g', 10));
        waitingForOperand = false;
    }
    else
    {
        if (ui->Display->text().contains('.') && button->text() == "0")
        {
            numberTODisplay = ui->Display->text() + button->text();
        }
        else
        {
            numbers = (ui->Display->text() + button->text()).toDouble();
            numberTODisplay = QString::number(numbers, 'g', 10);
        }
    }
    ui->Display->setText(numberTODisplay);
}

void Calculator::symbolPressed()
{
    QPushButton *button = (QPushButton*)sender();
    firstValue = ui->Display->text().toDouble();
    button->setChecked(true);
}

void Calculator::changeSignPressed()
{
    QPushButton *button = (QPushButton*)sender();
    double newNumber;
    if (button->text() == "+/-")
    {
        newNumber = ui->Display->text().toDouble();
        newNumber = newNumber * -1;
        ui->Display->setText(QString::number(newNumber, 'g', 10));
    }
}

void Calculator::equalPressed()
{
    double result;
    double displayValue = ui->Display->text().toDouble();

    if (ui->ButtonAdd->isChecked())
    {
        result = firstValue + displayValue;
        ui->ButtonAdd->setChecked(false);
    }
    else if (ui->ButtonSubstract->isChecked())
    {
        result = firstValue - displayValue;
        ui->ButtonSubstract->setChecked(false);
    }
    else if (ui->ButtonMultiply->isChecked())
    {
        result = firstValue * displayValue;
        ui->ButtonMultiply->setChecked(false);
    }
    else if (ui->ButtonDivision->isChecked())
    {
        result = firstValue / displayValue;
        ui->ButtonDivision->setChecked(false);
    }
    else if (ui->ButtonPercentage->isChecked())
    {
        result = (firstValue * displayValue) / 100;
        ui->ButtonPercentage->setChecked(false);
    }
    else
    {
        result = displayValue;
    }
    secondNumberFlag = false;
    ui->Display->setText(QString::number(result,'g', 10));
}

void Calculator::on_ButtonComma_released()
{
    if (ui->Display->text().contains('.'))
    {
        ui->Display->setText(ui->Display->text());
    }
    else
    {
        ui->Display->setText(ui->Display->text() + ".");
    }
}

void Calculator::unaryOperatorPressed()
{
    QPushButton *button = (QPushButton*)sender();
    double result = 0.0;
    double operand = ui->Display->text().toDouble();
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
    ui->Display->setText(QString::number(result, 'g', 10));
    waitingForOperand = true;
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString number = ui->Display->text();
    number.chop(1);
    if (number.isEmpty()) {
        number = "0";
        waitingForOperand = true;
    }
    ui->Display->setText(number);
}

void Calculator::clearInput()
{
    ui->ButtonAdd->setChecked(false);
    ui->ButtonSubstract->setChecked(false);
    ui->ButtonMultiply->setChecked(false);
    ui->ButtonDivision->setChecked(false);

    secondNumberFlag = false;
    ui->Display->setText("0");
}
