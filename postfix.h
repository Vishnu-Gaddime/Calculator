#ifndef POSTFIX_H
#define POSTFIX_H

#include <iostream>
#include <string>

int priority (char alpha);
std::string convert(std::string infix);
double calculate_Postfix(std::string  post_exp);

#endif // POSTFIX_H
