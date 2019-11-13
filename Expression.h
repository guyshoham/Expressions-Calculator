
#ifndef PROJECT_EXPRESSION_H
#include <string>
using namespace std;
#define PROJECT_EXPRESSION_H

/**
 * Expression Interface
 */
class Expression {

 public:
  Expression();
  virtual double calculate() = 0;
  virtual ~Expression();
  virtual string getType();
};

#endif //PROJECT_EXPRESSION_H
