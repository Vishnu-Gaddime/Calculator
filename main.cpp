#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    Catch::Session().run(argc,argv);
    return a.exec();
}
