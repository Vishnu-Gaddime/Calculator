#include "calculator.h"
#include "./ui_calculator.h"

double firstValue;
bool secondNumberFlag = false;

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
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clearInput()));
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
    if ((ui->ButtonAdd->isChecked() || ui->ButtonSubstract->isChecked()
            || ui->ButtonMultiply->isChecked() || ui->ButtonDivision->isChecked()
            || ui->ButtonPercentage->isChecked()) && (!secondNumberFlag))
    {
        numbers = button->text().toDouble();
        secondNumberFlag = true;
        numberTODisplay = QString::number(numbers, 'g', 10);
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

void Calculator::clearInput()
{
    ui->ButtonAdd->setChecked(false);
    ui->ButtonSubstract->setChecked(false);
    ui->ButtonMultiply->setChecked(false);
    ui->ButtonDivision->setChecked(false);

    secondNumberFlag = false;
    ui->Display->setText("0");
}
