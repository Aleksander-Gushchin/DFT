#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "lib.h"


int main() {
  const size_t n = 1000;
  const size_t k = 10;
  std::vector<double> signal(n, 0);
  size_t ic = 0;
  for(auto & item : signal) item = (double)ic++ / n;

  auto sin5 = math::get_sin(5);
  auto sin2 = math::get_sin(2);
  auto sin7 = math::get_sin(7);

  for(auto & item : signal) item = sin5(item) + sin2(item) + sin7(item);
  auto ca = ComplexArray(k);
  DiscreteFourierTransform(signal.data(), &ca, n, k);


  auto res = ca.get_freq(n);
  for(size_t i = 0; i < k; ++i){
    std::cout << i << " Hz: " << ca.get(i) << std::endl;
  }

  std::cout << "Found\n";
  for (auto c : res) {
    std::cout << c << "Hz ";
  }
  std::cout << std::endl;

  return 0;
}