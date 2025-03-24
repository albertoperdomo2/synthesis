#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

class Expression;
using ExprPtr = std::shared_ptr<Expression>;

struct Example {
 int input;
 int output;
};

// base expression class
class Expression {
 public:
  virtual ~Expression() = default;
  virtual int evaluate(int input) const = 0;
  virtual std::string toString() const = 0;
  virtual int complexity() const = 0;
};

// input variable X
class Variable : public Expression {
 public:
  int evaluate(int input) const override { return input; }
  std::string toString() const override { return "x"; } 
  int complexity() const override { return 1; }
};

// constant value
class Constant : public Expression {
 int value;
 
 public:
  explicit Constant(int val) : value(val) {}
  int evaluate(int input) const override { return value; }
  std::string toString() const override { return std::to_string(value); } 
  int complexity() const override { return 1; }
};

// binary operation: Add, Subtract, Multiply
class BinaryOp : public Expression {
 protected:
  ExprPtr left;
  ExprPtr right;
  std::string op_symbol;
  std::function<int(int, int)> operation;

 public:
  BinaryOp(ExprPtr l, ExprPtr r, std::string symbol, std::function<int(int, int)> op)
   : left(l), right(r), op_symbol(symbol), operation(op) {}

  int evaluate(int input) const override {
   return operation(left->evaluate(input), right->evaluate(input));
  }

  std::string toString() const override {
   return "(" + left->toString() + " " + op_symbol + " " + right->toString() + ")";
  }

  int complexity() const override {
   return left->complexity() + right->complexity() + 1;
  }
};

class Add : public BinaryOp {
 public:
  Add(ExprPtr l, ExprPtr r) : BinaryOp(l,r, "+", [](int a, int b) { return a + b; }) {}
};

class Subtract : public BinaryOp {
 public:
  Subtract(ExprPtr l, ExprPtr r) : BinaryOp(l,r, "-", [](int a, int b) { return a - b; }) {}
};

class Multiply : public BinaryOp {
 public:
  Multiply(ExprPtr l, ExprPtr r) : BinaryOp(l,r, "*", [](int a, int b) { return a * b; }) {}
};

#endif