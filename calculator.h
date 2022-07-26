#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void numberPressed();
    void symbolPressed();
    void changeSignPressed();
    void equalPressed();
    void on_ButtonComma_released();
    void unaryOperatorPressed();
    void backspaceClicked();
    void clearInput();

};
#endif // CALCULATOR_H
