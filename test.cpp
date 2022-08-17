#include "catch.hpp"
#include "postfix.h"
#include <cmath>
#include <QString>

TEST_CASE("precendence","[char]"){
    REQUIRE(precedence('+') == 2);
    REQUIRE(precedence('-') == 2);
    REQUIRE(precedence('*') == 3);
    REQUIRE(precedence('/') == 3);
    REQUIRE(precedence('a') == -1);
    REQUIRE(precedence('s') == -1);
}

TEST_CASE("associativity", "[char]"){
    REQUIRE(associativity('+') == 'L');
    REQUIRE(associativity('-') == 'L');
    REQUIRE(associativity('*') == 'L');
    REQUIRE(associativity('/') == 'L');
    REQUIRE(associativity('#') == '.');
    REQUIRE(associativity('$') == '.');
}

TEST_CASE("isoperator", "[char]"){
    REQUIRE(isoperator('+') == 1);
    REQUIRE(isoperator('-') == 1);
    REQUIRE(isoperator('*') == 1);
    REQUIRE(isoperator('/') == 1);
    REQUIRE(isoperator('&') == 0);
    REQUIRE(isoperator('@') == 0);
}

TEST_CASE("modify", "[string]"){
    REQUIRE(modify("12+3 4 - 8") == "12+34-8");
    REQUIRE(modify(" 1 2 + 3 4 - 8") == "12+34-8");
}

TEST_CASE("postfix_exp", "[string]"){
    REQUIRE(to_postfix("12") == "12 ");
    REQUIRE(to_postfix(" 1 2 + 3 4 - 8") == "12 34 + 8 - ");
    REQUIRE(to_postfix("12+") == "12 + ");
}

TEST_CASE("evaluate", "[string]"){
    REQUIRE(EvaluateExpression(" 1 2 + 3 4 - 8") == 38);
}
