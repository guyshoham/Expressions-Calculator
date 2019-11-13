//
// Created by Guy on 04/11/2019.
//

#include "ex1.h"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;

/**BinaryOperator**/
BinaryOperator::BinaryOperator(Expression* left, Expression* right) : left(left), right(right) {}
BinaryOperator::~BinaryOperator() {
  delete left;
  delete right;
}

/**UnaryOperator**/
UnaryOperator::UnaryOperator(Expression* expression) : expression(expression) {}
UnaryOperator::~UnaryOperator() { delete expression; }

/**Plus**/
Plus::Plus(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Plus::~Plus() = default;
double Plus::calculate() {

  return left->calculate() + right->calculate();

}
string Plus::getType() {
  return "plus";
}

/**Minus**/
Minus::Minus(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Minus::~Minus() = default;
double Minus::calculate() {

  return left->calculate() - right->calculate();

}
string Minus::getType() {
  return "minus";
}

/**Mul**/
Mul::Mul(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Mul::~Mul() = default;
double Mul::calculate() {

  return left->calculate() * right->calculate();

}
string Mul::getType() {
  return "mul";
}

/**Div**/
Div::Div(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Div::~Div() = default;
double Div::calculate() {
  try {
    if (right->calculate() == 0) {
      throw "division by zero";
    }
    return left->calculate() / right->calculate();
  } catch (const char* e) {
    throw e;
  }
}
string Div::getType() {
  return "div";
}

/**UPlus**/
UPlus::UPlus(Expression* expression) : UnaryOperator(expression) {}
UPlus::~UPlus() = default;
double UPlus::calculate() {

  return expression->calculate();

}
string UPlus::getType() {
  return "uplus";
}

/**UMinus**/
UMinus::UMinus(Expression* expression) : UnaryOperator(expression) {}
UMinus::~UMinus() = default;
double UMinus::calculate() {

  return expression->calculate() * -1;

}
string UMinus::getType() {
  return "uminus";
}

/**Value**/
Value::Value(double value) {

  this->value = value;

}

double Value::calculate() {

  return value;

}
string Value::getType() {
  return "value";
}

/**Variable**/
Variable::Variable(string name, double value) {
  this->name = name;
  this->value = value;
}

double Variable::calculate() {

  return value;

}
string Variable::getType() {
  return "variable";
}

Variable& Variable::operator++() {
  value++;
  return *this;
}

Variable& Variable::operator--() {
  value--;
  return *this;
}

Variable& Variable::operator+=(double num) {
  value = value + num;
  return *this;
}

Variable& Variable::operator-=(double num) {
  value = value - num;
  return *this;
}
Variable& Variable::operator++(int) {
  value++;
  return *this;
}
Variable& Variable::operator--(int) {
  value--;
  return *this;
}
void Variable::setValue(double value) {
  this->value = value;
}
string Variable::getName() {
  return this->name;
}
double Variable::getValue() {
  return this->value;
}

/**Interpreter**/
Interpreter::Interpreter() = default;
Interpreter::~Interpreter() = default;
void Interpreter::setVariables(string input) {
  string delimiter = ";", token, name, value;
  size_t pos = 0;
  while ((pos = input.find(delimiter)) != string::npos) {
    token = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
    name = token.substr(0, token.find('='));
    value = token.substr(token.find('=') + 1);
    Variable* variable = nullptr;
    try {
      variable = new Variable(name, (stod(value)));
      addToArr(variable);
    } catch (...) {
      if (variable != nullptr) {
        delete variable;
      }
      throw "illegal variable assignment!";
    }
  }
  token = input.substr(0, pos);
  input.erase(0, pos + delimiter.length());
  name = token.substr(0, token.find('='));
  value = token.substr(token.find('=') + 1);
  Variable* variable = new Variable(name, (stod(value)));
  addToArr(variable);
}
Expression* Interpreter::interpret(string input) {
  try {

    stack<char> operators;
    queue<Expression*> output;
    stack<Expression*> expressions;
    int pos = 0, posAfter = 0;

    //replace variables with values
    for (Variable* ptr : this->variables) {
      if (ptr == nullptr) { break; }
      replaceAll(input, ptr->getName(), to_string(ptr->getValue()));
    }

    //for every char in input string
    for (char c : input) {

      if (pos < posAfter) {
        pos++;
        continue;
      }

      if (isOperand(c)) {
        Value* v = getWholeValue(input, pos, &posAfter);
        output.push(v);
      } else if (isOperator(c)) {
        while (!operators.empty()
            && !isOpeningParentheses(operators.top())
            && hasHigherPrec(operators.top(), c)) {
          //push top of operators stack into output queue
          Expression* e = createExpressionFromStack(&operators);
          if (e != nullptr) {
            output.push(e);
          }
          operators.pop();
        }
        if (c == '+' || c == '-') {
          if (pos == 0 || input[pos - 1] == '(') {
            operators.push('$');
          }
        }
        operators.push(c);
      } else if (isOpeningParentheses(c)) {
        // c = '('
        operators.push(c);
      } else if (isClosingParentheses(c)) {
        // c = ')'
        while (!operators.empty()
            && !isOpeningParentheses(operators.top())) {
          Expression* e = createExpressionFromStack(&operators);
          if (e != nullptr) {
            output.push(e);
          }
          operators.pop();
        }
        operators.pop();
      }
      pos++;
    }// end of for loop. end of input

    //empty operators stack and push to output
    while (!operators.empty()) {
      Expression* e = createExpressionFromStack(&operators);
      if (e != nullptr) {
        output.push(e);
      }
      operators.pop();
    }

    //starting second task, calculating postfix
    while (!output.empty()) {
      Expression* e = output.front();
      Expression* eLeft;
      Expression* eRight;

      if (e->getType() == "value") {
        expressions.push(output.front());
      } else if (e->getType() == "mul") {
        eRight = expressions.top();
        expressions.pop();
        eLeft = expressions.top();
        expressions.pop();
        Mul* mul = new Mul(eLeft, eRight);
        expressions.push(mul);
      } else if (e->getType() == "div") {
        eRight = expressions.top();
        expressions.pop();
        eLeft = expressions.top();
        expressions.pop();
        Div* div = new Div(eLeft, eRight);
        expressions.push(div);
      } else if (e->getType() == "plus") {
        eRight = expressions.top();
        expressions.pop();
        eLeft = expressions.top();
        expressions.pop();
        Plus* plus = new Plus(eLeft, eRight);
        expressions.push(plus);
      } else if (e->getType() == "minus") {
        eRight = expressions.top();
        expressions.pop();
        eLeft = expressions.top();
        expressions.pop();
        Minus* minus = new Minus(eLeft, eRight);
        expressions.push(minus);
      } else if (e->getType() == "uplus") {
        eRight = expressions.top();
        expressions.pop();
        UPlus* uPlus = new UPlus(eRight);
        expressions.push(uPlus);
      } else if (e->getType() == "uminus") {
        eRight = expressions.top();
        expressions.pop();
        UMinus* uMinus = new UMinus(eRight);
        expressions.push(uMinus);
      }
      output.pop();
    }
    return expressions.top();
  } catch (const char* e) {
    cout << e << std::endl;
  }
}
bool Interpreter::isOperand(char& c) {

  return c >= 48 && c <= 57;
}
bool Interpreter::isOperator(char& c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
bool Interpreter::hasHigherPrec(char& top, char& c) {
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
void Interpreter::addToArr(Variable* variable) {
  int pos = 0;
  for (Variable* ptr : this->variables) {
    if (ptr == nullptr) { break; }
    if (ptr->getName() == variable->getName()) {
      ptr->setValue(variable->getValue());
      return;
    }
    pos++;
  }
  variables[pos] = variable;
}
void Interpreter::replaceAll(string& str, const string& from, const string& to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}
Value* Interpreter::getWholeValue(string input, int pos, int* posAfter) {
  int originalPos = pos;
  while (isOperand(input.at(pos)) || input.at(pos) == '.') {
    pos++;
  }
  string str = input.substr(originalPos, pos);
  Value* v = new Value(stod(str));
  *posAfter = pos;
  return v;
}
Expression* Interpreter::createExpressionFromStack(stack<char>* stack) {
  Expression* e = nullptr;

  //temporary pop top element
  char top = stack->top();
  stack->pop();
  char prevTop = ' ';
  if (!stack->empty()) {
    prevTop = stack->top();
  }

  switch (top) {
    case '*':e = new Mul(nullptr, nullptr);
      break;
    case '/':e = new Div(nullptr, nullptr);
      break;
    case '+':
      if (prevTop == '$') {
        e = new UPlus(nullptr);
      } else {
        e = new Plus(nullptr, nullptr);
      }
      break;
    case '-':
      if (prevTop == '$') {
        e = new UMinus(nullptr);
      } else {
        e = new Minus(nullptr, nullptr);
      }
      break;
    default:break;
  }

  //return top element
  stack->push(top);
  return e;
}
