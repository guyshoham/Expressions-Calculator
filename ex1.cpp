//
// Created by Guy on 04/11/2019.
//

#include "ex1.h"
#include <stack>
#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

/**BinaryOperator**/
BinaryOperator::BinaryOperator(Expression *left, Expression *right) : left(left), right(right) {}
BinaryOperator::~BinaryOperator() {
  delete left;
  delete right;
}

/**UnaryOperator**/
UnaryOperator::UnaryOperator(Expression *expression) : expression(expression) {}
UnaryOperator::~UnaryOperator() { delete expression; }

/**Plus**/
Plus::Plus(Expression *left, Expression *right) : BinaryOperator(left, right) {}
Plus::~Plus() {

}
double Plus::calculate() {

  return left->calculate() + right->calculate();

}

/**Minus**/
Minus::Minus(Expression *left, Expression *right) : BinaryOperator(left, right) {}
Minus::~Minus() {}
double Minus::calculate() {

  return left->calculate() - right->calculate();

}

/**Mul**/
Mul::Mul(Expression *left, Expression *right) : BinaryOperator(left, right) {}
Mul::~Mul() {}
double Mul::calculate() {

  return left->calculate() * right->calculate();

}

/**Div**/
Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {}
Div::~Div() {}
double Div::calculate() {

  return left->calculate() / right->calculate();

}

/**UPlus**/
UPlus::UPlus(Expression *expression) : UnaryOperator(expression) {}
UPlus::~UPlus() {

}
double UPlus::calculate() {

  return expression->calculate();

}

/**UMinus**/
UMinus::UMinus(Expression *expression) : UnaryOperator(expression) {}
UMinus::~UMinus() {

}
double UMinus::calculate() {

  return expression->calculate() * -1;

}

/**Value**/
Value::Value(double value) {

  this->value = value;

}

double Value::calculate() {

  return value;

}

/**Variable**/
Variable::Variable(string name, double value) {
  this->name = name;
  this->value = value;
}

double Variable::calculate() {

  return value;

}

Variable &Variable::operator++() {
  value++;
  return *this;
}

Variable &Variable::operator--() {
  value--;
  return *this;
}

Variable &Variable::operator+=(double num) {
  value = value + num;
  return *this;
}

Variable &Variable::operator-=(double num) {
  value = value - num;
  return *this;
}
Variable &Variable::operator++(int) {
  value++;
  return *this;
}
Variable &Variable::operator--(int) {
  value--;
  return *this;
}

/**Interpreter**/
Interpreter::Interpreter() {}
Interpreter::~Interpreter() {}
void Interpreter::setVariables(string expression) {

}
Expression *Interpreter::interpret(string expression) {
  stack<char> operators;
  queue<char> output;
  stack<Expression *> expressions;

  for (char &i : expression) {
    cout << i;
  }
  cout << endl;

  for (char c : expression) {
    if (isOperand(c)) {
      output.push(c);
    } else if (isOperator(c)) {
      while (!operators.empty()
          && !isOpeningParentheses(operators.top())
          && hasHigherPrec(operators.top(), c)) {
        output.push(operators.top());
        operators.pop();
      }
      operators.push(c);
    } else if (isOpeningParentheses(c)) {
      operators.push(c);
    } else if (isClosingParentheses(c)) {
      while (!operators.empty()
          && !isOpeningParentheses(operators.top())) {
        output.push(operators.top());
        operators.pop();
      }
      operators.pop();
    }
  }// end of for loop

  //todo: implement

  while (!operators.empty()) {
    output.push(operators.top());
    operators.pop();
  }

  while (!output.empty()) {
    char c = output.front();

    if (isOperand(c)) {
      double value = c - 48;
      Value *v = new Value(value);
      expressions.push(v);
    } else {
      Expression *e1, *e2;
      switch (c) {
        case '*': {
          e1 = expressions.top();
          expressions.pop();
          e2 = expressions.top();
          expressions.pop();
          Mul *mul = new Mul(e1, e2);
          expressions.push(mul);
        }
          break;
        case '/': {
          e1 = expressions.top();
          expressions.pop();
          e2 = expressions.top();
          expressions.pop();
          Div *div = new Div(e1, e2);
          expressions.push(div);
        }
          break;
        case '+':
          if (expressions.size() > 1) {
            e1 = expressions.top();
            expressions.pop();
            e2 = expressions.top();
            expressions.pop();
            Plus *plus = new Plus(e1, e2);
            expressions.push(plus);
          } else {
            e1 = expressions.top();
            expressions.pop();
            UPlus *uPlus = new UPlus(e1);
            expressions.push(uPlus);
          }
          break;
        case '-':
          if (expressions.size() > 1) {
            e1 = expressions.top();
            expressions.pop();
            e2 = expressions.top();
            expressions.pop();
            Minus *minus = new Minus(e1, e2);
            expressions.push(minus);
          } else {
            e1 = expressions.top();
            expressions.pop();
            UMinus *uMinus = new UMinus(e1);
            expressions.push(uMinus);
          }
          break;
        default:break;
      }//end of switch
    }
    output.pop();

  }

  return expressions.top();
}
bool Interpreter::isOperand(char &c) {
  if (c == '+') {
    return false;
  }
  if (c == '-') {
    return false;
  }
  if (c == '*') {
    return false;
  }
  if (c == '/') {
    return false;
  }
  if (c == '(') {
    return false;
  }
  if (c == ')') {
    return false;
  }
  return true;
}
bool Interpreter::isOperator(char &c) {
  if (c == '+') {
    return true;
  }
  if (c == '-') {
    return true;
  }
  if (c == '*') {
    return true;
  }
  if (c == '/') {
    return true;
  }
  return false;
}
bool Interpreter::hasHigherPrec(char &top, char &c) {

  if (c == '*' || c == '/') {
    return false;
  }

  if (c == '+' || c == '-') {
    if (top == '*' || top == '/')
      return true;
  }

  return false;
}
bool Interpreter::isOpeningParentheses(char c) {
  return c == '(';
}
bool Interpreter::isClosingParentheses(char c) {
  return c == ')';
}
