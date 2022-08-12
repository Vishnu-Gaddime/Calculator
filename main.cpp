#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "calculator.h"
#include <QApplication>
#define UNIT_TEST_ENABLED

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    Catch::Session().run(argc,argv);
    return a.exec();
}
