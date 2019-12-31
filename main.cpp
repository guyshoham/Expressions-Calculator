#include <iostream>

#include "ex1.h"

int main() {
  // 4
  Interpreter* i1 = new Interpreter();
  Expression* e4 = nullptr;
  try {
    e4 = i1->interpret("-(2*(3+4))");
    std::cout << "4: " << e4->calculate() << std::endl;//-14
    delete e4;
    delete i1;
  } catch (const char* e) {
    if (e4 != nullptr) {
      delete e4;
    }
    if (i1 != nullptr) {
      delete i1;
    }
    std::cout << e << std::endl;
  }

  // 5
  Interpreter* i2 = new Interpreter();
  Expression* e5 = nullptr;
  try {
    i2->setVariables("x=2;y=4");
    i2->setVariables("x=3");
    e5 = i2->interpret("2*(-(x+y))");
    std::cout << "5: " << e5->calculate() << std::endl;//-14
    delete e5;
  } catch (const char* e) {
    if (e5 != nullptr) {
      delete e5;
    } //deleting i2 in the next example
    std::cout << e << std::endl;
  }

  // 6
  Interpreter* i3 = new Interpreter();
  Expression* e6 = nullptr;
  try {
    i3->setVariables("x=1.5;y=8.5");
    i2->setVariables("x=3");
    e6 = i3->interpret("-(-(-((x+0.5)*(y+(-3.5)))))");
    std::cout << "6: " << e6->calculate() << std::endl;//-10
    delete e6;
    delete i2;
    delete i3;
  } catch (const char* e) {
    if (e6 != nullptr) {
      delete e6;
    }
    if (i2 != nullptr) {
      delete i2;
    }
    if (i3 != nullptr) {
      delete i3;
    }
    std::cout << e << std::endl;
  }

  Interpreter* i4 = new Interpreter();
  Expression* e7 = nullptr;
  try {
    // 7
    i4->setVariables("x2=@;y=8.5");//error
    e7 = i4->interpret("-(-(-((x+0.5)*(y+(-3.5)))))");
    std::cout << "7: " << e7->calculate() << std::endl;
    delete e7;
    delete i4;
  } catch (const char* e) {
    if (e7 != nullptr) {
      delete e7;
    }
    if (i4 != nullptr) {
      delete i4;
    }
    std::cout << e << std::endl;
  }

  // 8
  Expression* e8 = nullptr;
  try {
    e8 = new Div(new Value(1.0), new Value(0.0));// 1.0/0.0
    std::cout << "8: " << e8->calculate() << std::endl;// error
    delete e8;
  } catch (const char* e) {
    if (e8 != nullptr) {
      delete e8;
    }
    std::cout << e << std::endl;
  }

  // 9
  Interpreter* i6 = new Interpreter();
  Expression* e9 = nullptr;
  try {
    e9 = i6->interpret("1.0-(-(-16.0))");
    std::cout << "9: " << e9->calculate() << std::endl;// -15
    delete e9;
    delete i6;
  } catch (const char* e) {
    if (e9 != nullptr) {
      delete e9;
    }
    if (i6 != nullptr) {
      delete i6;
    }
    std::cout << e << std::endl;
  }

  // 10
  Interpreter* i7 = new Interpreter();
  Expression* e10 = nullptr;
  try {
    i7->setVariables("x=1;y=2;z=3");
    e10 = i7->interpret("-(-(-((z+0.5)*(y+(-3.5)))))");
    std::cout << "10: " << e10->calculate() << std::endl;// 5.25
    delete e10;
    delete i7;
  } catch (const char* e) {
    if (e10 != nullptr) {
      delete e10;
    }
    if (i7 != nullptr) {
      delete i7;
    }
    std::cout << e << std::endl;
  }

  Interpreter* i8 = new Interpreter();
  Expression* e11 = nullptr;
  try {
    // 11
    i8->setVariables("x2=14;y=8.5");
    e11 = i8->interpret("-(-(-((x+0.5)**(y+(-3.5)))))"); //error
    std::cout << "11: " << e11->calculate() << std::endl;
    delete e11;
    delete i8;
  } catch (const char* e) {
    if (e11 != nullptr) {
      delete e11;
    }
    if (i8 != nullptr) {
      delete i8;
    }
    std::cout << e << std::endl;
  }

  Interpreter* i9 = new Interpreter();
  Expression* e12 = nullptr;
  try {
    // 12
    i9->setVariables("x=1;y=-5");
    e12 = i9->interpret("- ( + ( - ( x) )  ) ");
    std::cout << "12: " << e12->calculate() << std::endl;
    delete e12;
    delete i9;
  } catch (const char* e) {
    if (e12 != nullptr) {
      delete e12;
    }
    if (i9 != nullptr) {
      delete i9;
    }
    std::cout << e << std::endl;
  }
  return 0;
}


/*
1: -37.5
2: 2
3: -10.5
4: -14
5: -14
6: -10
illegal variable assignment!
8: division by zero
9: -15
10: 5.25
illegal math expression
*/