#include "program_synthesis/synthesizer.h"
#include <algorithm>
#include <iostream>
#include <spdlog/spdlog.h>

Synthesizer::Synthesizer(const std::vector<Example>& examples, int max_depth)
 : examples(examples), max_depth(max_depth) {}

std::vector<ExprPtr> Synthesizer::generateExpressions(int depth) {
 std::vector<ExprPtr> expressions;

 // base case: depth 0
 if (depth == 0) {
  // add variable x
  expressions.push_back(std::make_shared<Variable>());

  // add constants 0, 1, 2
  for (int i = 0; i <= 2; i++) {
   expressions.push_back(std::make_shared<Constant>(i));
  }

  return expressions;
 }

 // recursive case: generate expressions with binary operations
 auto subexprs = generateExpressions(depth - 1);

 for (const auto& left : subexprs) {
  for (const auto& right : subexprs) {
   
   // skip if combined complexity is too high
   if (left->complexity() + right->complexity() > depth * 2) {
    continue;
   }

   // add binary operations
   expressions.push_back(std::make_shared<Add>(left, right));
   expressions.push_back(std::make_shared<Subtract>(left, right));
   expressions.push_back(std::make_shared<Multiply>(left, right));
  }
 }

 return expressions;
}

bool Synthesizer::satisfiesExamples(const ExprPtr& expr) const {
 for (const auto& example : examples) {
  try {
   if (expr->evaluate(example.input) != example.output) {
    return false;
   }
  } catch (...) {
   spdlog::warn("Potential runtime error");
   return false;
  }
 }

 return true;
}

ExprPtr Synthesizer::synthesize() {
 spdlog::info("Synthesizing program from {} examples...", examples.size());

 // start from depth 1 and increase if needed
 for (int depth = 1; depth <= max_depth; depth++) {
  spdlog::info("Searching at depth {}...", depth);

  auto expressions = generateExpressions(depth);
  spdlog::info("Generated {} candidate expressions", expressions.size());

  // sort by complexity
  std::sort(expressions.begin(), expressions.end(),
    [](const ExprPtr& a, const ExprPtr& b) {
    return a->complexity()< b->complexity();
  });

  // find the first expression that satisfies all the examples
  for (const auto& expr : expressions) {
   if (satisfiesExamples(expr)) {
    spdlog::info("Found solution: {}", expr->toString());
    return expr;
   }
  }
 }

 spdlog::warn("No solution found within depth limit");
 return nullptr;
}
