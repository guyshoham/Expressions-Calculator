//
// Created by Guy on 04/11/2019.
//

#ifndef EX1__EX1_H_
#include <string>
#include <stack>
#include <queue>
#include "Expression.h"
using namespace std;
#define EX1__EX1_H_

class Value : public Expression {

  double value;

 public:
  Value(double value);
  double calculate();
  string getType();

};

class Variable : public Expression {
  string name;

  double value;

 public:
  Variable(string name, double value);
  double calculate();
  Variable& operator++();
  Variable& operator--();
  Variable& operator+=(double num);
  Variable& operator-=(double num);
  Variable& operator++(int);
  Variable& operator--(int);
  string getType();
  string getName();
  double getValue();
  void setValue(double value);

};

class BinaryOperator : public Expression {
 protected:
  Expression* left, * right;

 public:
  BinaryOperator(Expression* left, Expression* right);
  virtual ~BinaryOperator();
};

class UnaryOperator : public Expression {
 protected:
  Expression* expression;

 public:
  UnaryOperator(Expression* expression);
  virtual ~UnaryOperator();
};

class Plus : public BinaryOperator {

 public:
  Plus(Expression* left, Expression* right);
  double calculate();
  virtual ~Plus();
  string getType();

};

class Minus : public BinaryOperator {

 public:
  Minus(Expression* left, Expression* right);
  double calculate();
  virtual ~Minus();
  string getType();

};

class Mul : public BinaryOperator {

 public:
  Mul(Expression* left, Expression* right);
  double calculate();
  virtual ~Mul();
  string getType();

};

class Div : public BinaryOperator {

 public:
  Div(Expression* left, Expression* right);
  double calculate();
  string getType();
  virtual ~Div();
};

class UPlus : public UnaryOperator {

 public:
  UPlus(Expression* expression);
  double calculate();
  virtual ~UPlus();
  string getType();

};

class UMinus : public UnaryOperator {

 public:
  UMinus(Expression* expression);
  double calculate();
  virtual ~UMinus();
  string getType();

};

class Interpreter {

  Variable* variables[10] = {nullptr};

 public:
  Interpreter();
  Expression* interpret(string input);
  void setVariables(string input);
  virtual ~Interpreter();
  static bool isOperand(char& c);
  static bool isOperator(char& c);
  static bool hasHigherPrec(char& top, char& c);
  static bool isOpeningParentheses(char cstatic);
  static bool isClosingParentheses(char c);
  void addToArr(Variable* variable);
  static void replaceAll(string& str, const string& from, const string& to);
  static Value* getWholeValue(string input, int pos, int* posAfter);
  static Expression* createExpressionFromStack(stack<char>* stack);
  queue<Expression*> infixToPostfix(string input);
  static Expression* integrateExpressions(queue<Expression*> output);
  static bool validateMathExpression(string expression);
  static bool validateVariableExpression(string expression,char symbol);
  static bool validateVariableName(string name);
  static bool validateVariableValue(string value);
};

#endif //EX1__EX1_H_
