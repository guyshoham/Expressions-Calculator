
#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

/**
 * Expression Interface
 */
class Expression {

 public:
  Expression();
  virtual double calculate() = 0;
  virtual ~Expression();
};

#endif //PROJECT_EXPRESSION_H