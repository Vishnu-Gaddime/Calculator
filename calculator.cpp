#include "calculator.h"
#include "./ui_calculator.h"

double firstValue;

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

    ui->ButtonAdd->setCheckable(true);
    ui->ButtonSubstract->setCheckable(true);
    ui->ButtonMultiply->setCheckable(true);
    ui->ButtonDivision->setCheckable(true);

    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clearInput()));
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
    QString valueToDisplay;
    double newValue;
    if (ui->ButtonAdd->isChecked() || ui->ButtonSubstract->isChecked()
            || ui->ButtonMultiply->isChecked() || ui->ButtonDivision->isChecked())
    {
        newValue = buttonValue.toDouble();
    }
    else
    {
        newValue = (displayValue + buttonValue).toDouble();
    }
    valueToDisplay = QString::number(newValue, 'g', 10);
    ui->Display->setText(valueToDisplay);
}

void Calculator::symbolPressed()
{
    QPushButton *button = (QPushButton*)sender();
    firstValue = ui->Display->text().toDouble();
    button->setChecked(true);

}

void Calculator::on_ButtonComma_released()
{
    ui->Display->setText(ui->Display->text() + ".");
}

void Calculator::equalPressed()
{
    double result;
    QString newValue;
    double displayValue = ui->Display->text().toDouble();

    if (ui->ButtonAdd->isChecked())
    {
        result = firstValue + displayValue;
        newValue = QString::number(result,'g', 10);
        ui->Display->setText(newValue);
        ui->ButtonAdd->setChecked(false);
    }
    else if (ui->ButtonSubstract->isChecked())
    {
        result = firstValue - displayValue;
        newValue = QString::number(result,'g', 10);
        ui->Display->setText(newValue);
        ui->ButtonSubstract->setChecked(false);
    }
    else if (ui->ButtonMultiply->isChecked())
    {
        result = firstValue * displayValue;
        newValue = QString::number(result,'g', 10);
        ui->Display->setText(newValue);
        ui->ButtonMultiply->setChecked(false);
    }
    else if (ui->ButtonDivision->isChecked())
    {
        result = firstValue / displayValue;
        newValue = QString::number(result,'g', 10);
        ui->Display->setText(newValue);
        ui->ButtonDivision->setChecked(false);
    }
}

void Calculator::clearInput()
{
    ui->Display->clear();
    double firstValue = 0;
    ui->Display->setText(QString::number(firstValue));
}
