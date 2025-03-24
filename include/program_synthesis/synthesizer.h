#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <vector>
#include "expression.h"

class Synthesizer {
 private:
  std::vector<Example> examples;
  int max_depth;
  std::vector<ExprPtr> generateExpressions(int depth);
  bool satisfiesExamples(const ExprPtr& expr) const;

 public:
  Synthesizer(const std::vector<Example>& examples, int max_depth = 3);
  ExprPtr synthesize();
};

#endif
