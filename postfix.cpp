#include<iostream>
#include<stack>
#include<math.h>
using namespace std;

int priority (char alpha){
    if(alpha == '+' || alpha =='-')
        return 1;

    if(alpha == '*' || alpha =='/')
        return 2;

    return 0;
}

string convert(string infix)
{
    int i = 0;
    string postfix = "";
    stack <double>stack;

    while(infix[i]!='\0')
    {
        if(infix[i]>='0' && infix[i]<='9')
        {
            postfix += infix[i];
            i++;
        }
        else
        {
            while (!stack.empty() && priority(infix[i]) <= priority(stack.top())){
                postfix += stack.top();
                stack.pop();
            }
            stack.push(infix[i]);
            i++;
        }
    }
    while(!stack.empty()){
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

double calculate_Postfix(string  post_exp)
{
    stack <double> stack;
    int len = post_exp.length();
    for (int i = 0; i < len; i++)
    {
        if ( post_exp[i] >= '0' &&  post_exp[i] <= '9')
        {
            stack.push( post_exp[i] - '0');
        }
        else
        {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            switch (post_exp[i])
            {
                case '+': stack.push(b + a);
                          break;
                case '-': stack.push(b - a);
                          break;
                case '*': stack.push(b * a);
                          break;
                case '/': stack.push(b / a);
                          break;
                case '^': stack.push(pow(b,a));
                          break;
            }
        }
    }
    return stack.top();
}
