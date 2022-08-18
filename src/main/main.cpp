#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "lib.h"


int main() {
  const size_t n = 100;
  const size_t k = 20;
  std::vector<double> signal(n, 0);
  size_t ic = 0;
  for(auto & item : signal) item = (double)ic++ / n * 2 * pi;
  print(signal);
  for(auto & item : signal) item = (sin(5 * item + pi/2) + sin(2*item  + pi / 2));
  print(signal);
  auto ca = ComplexArray(100);
  DiscreteFourierTransform(signal.data(), &ca, n, k);

  for(size_t i = 0; i < k; ++i){
    std::cout << i << " Hz: " << ca.get(i) << std::endl;
  }

  return 0;
}