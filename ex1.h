//
// Created by Guy on 04/11/2019.
//

#ifndef EX1__EX1_H_
#include <string>
#include "Expression.h"
using namespace std;
#define EX1__EX1_H_

class Value : public Expression {

  double value;

 public:
  Value(double value);
  double calculate();
};

class Variable : public Expression {
  string name;

  double value;

 public:
  Variable(string name, double value);
  double calculate();
  Variable &operator++();
  Variable &operator--();
  Variable &operator+=(double num);
  Variable &operator-=(double num);
  Variable &operator++(int);
  Variable &operator--(int);
};

class BinaryOperator : public Expression {
 protected:
  Expression *left, *right;

 public:
  BinaryOperator(Expression *left, Expression *right);
  virtual ~BinaryOperator();
};

class UnaryOperator : public Expression {
 protected:
  Expression *expression;

 public:
  UnaryOperator(Expression *expression);
  virtual ~UnaryOperator();
};

class Plus : public BinaryOperator {

 public:
  Plus(Expression *left, Expression *right);
  double calculate();
  virtual ~Plus();
};

class Minus : public BinaryOperator {

 public:
  Minus(Expression *left, Expression *right);
  double calculate();
  virtual ~Minus();
};

class Mul : public BinaryOperator {

 public:
  Mul(Expression *left, Expression *right);
  double calculate();
  virtual ~Mul();
};

class Div : public BinaryOperator {

 public:
  Div(Expression *left, Expression *right);
  double calculate();
  virtual ~Div();
};

class UPlus : public UnaryOperator {

 public:
  UPlus(Expression *expression);
  double calculate();
  virtual ~UPlus();
};

class UMinus : public UnaryOperator {

 public:
  UMinus(Expression *expression);
  double calculate();
  virtual ~UMinus();
};

class Interpreter {
 public:
  Interpreter();
  Expression *interpret(string expression);
  void setVariables(string expression);
  virtual ~Interpreter();
  bool isOperand(char &c);
  bool isOperator(char &c);
  bool hasHigherPrec(char &top, char &c);
  bool isOpeningParentheses(char c);
  bool isClosingParentheses(char c);
};

#endif //EX1__EX1_H_
