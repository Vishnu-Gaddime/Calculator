#include "calculator.h"
#include "./ui_calculator.h"

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

    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonSubstract, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonDivision, SIGNAL(released()), this, SLOT(symbolPressed()));
    connect(ui->ButtonPercentage, SIGNAL(released()), this, SLOT(symbolPressed()));

    connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(equalPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numberPressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();
    QString newValue = displayValue + buttonValue;
     ui->Display->setText(QString::number(newValue.toDouble(),'g', 11));
}

double firstValue = 0.0;
bool addFlag = false;
bool substractFlag = false;
bool multipleFlag = false;
bool divisionFlag = false;
bool percentageFlag = false;


void Calculator::symbolPressed()
{
    bool addFlag = false;
    bool substractFlag = false;
    bool multipleFlag = false;
    bool divisionFlag = false;
    bool percentageFlag = false;

    QString displayValue = ui->Display->text();
    firstValue = displayValue.toDouble();
    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();
    if (QString::compare(buttonValue, "+") == 0)
    {
        addFlag = true;
    }
    else if (QString::compare(buttonValue, "-") == 0)
    {
        substractFlag = true;
    }
    else if (QString::compare(buttonValue, "*") == 0)
    {
        multipleFlag = true;
    }
    else if (QString::compare(buttonValue, "/") == 0)
    {
        divisionFlag = true;
    }
    else
    {
        percentageFlag = true;
    }
    ui->Display->setText("");
}

void Calculator::equalPressed()
{
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    double result =  0.0;
    if (addFlag)
    {
        result =  firstValue + dblDisplayValue;
    }
    else if (substractFlag)
    {
        result = firstValue - dblDisplayValue;
    }
    else if (multipleFlag)
    {
        result = firstValue * dblDisplayValue;
    }
    else if (divisionFlag)
    {
        result = firstValue / dblDisplayValue;
    }
    else
    {
        result = (firstValue * dblDisplayValue) / 100;
    }
    ui->Display->setText(QString::number(result));
}
