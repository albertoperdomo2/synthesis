#include <iostream>
#include "program_synthesis/synthesizer.h"

int main() {
 // example 1: f(x) = 2x + 1
 std::vector<Example> examples1 = {
  {0, 1},  // f(0) = 1
  {1, 3},  // f(1) = 3
  {2, 5},  // f(2) = 5
  {3, 7}   // f(3) = 7
 };

 Synthesizer synth1(examples1, 3);
 ExprPtr result1 = synth1.synthesize();

 if (result1) {
  std::cout << "Synthesized expression: " << result1->toString() << std::endl;
  std::cout << "Validation:" << std::endl;

  for (const auto& example : examples1) {
   std::cout << "f(" << example.input << ") = " << result1->evaluate(example.input)
    << " (expected: " << example.output << ")" << std::endl;
  }
 }

 // example 2: f(x) = x^2 (approximated as x*x)
 std::vector<Example> examples2 = {
  {0, 0},  // f(0) = 0
  {1, 1},  // f(1) = 1
  {2, 4},  // f(2) = 4
  {3, 9}   // f(3) = 9
 };


 Synthesizer synth2(examples2, 3);
 ExprPtr result2 = synth2.synthesize();

 if (result2) {
  std::cout << "Synthesized expression: " << result2->toString() << std::endl;
  std::cout << "Validation:" << std::endl;

  for (const auto& example : examples2) {
   std::cout << "f(" << example.input << ") = " << result2->evaluate(example.input)
    << " (expected: " << example.output << ")" << std::endl;
  }
 }

 return 0;
}
