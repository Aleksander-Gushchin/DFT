#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <random>
#include <algorithm>
#include <chrono>
#include "lib.h"


int main() {
  const size_t n = 8000;
  const size_t k = 4000;
  std::mt19937 rg(time(0));

  std::vector<double> signal(n, 0);
  size_t ic = 0;
  for(auto & item : signal) item = (double)ic++ / n;

  auto sin1 = math::get_sin(rg() % 50);
  auto sin2 = math::get_sin(rg() % 50);
  auto sin3 = math::get_sin(rg() % 50);

  for(auto & item : signal) item = sin1(item) + sin2(item) + sin3(item);
  auto ca = ComplexArray(k);

  auto start = std::chrono::high_resolution_clock::now();
  DiscreteFourierTransform(signal.data(), &ca, n, k);
  auto end = std::chrono::high_resolution_clock::now();

  std::cout <<  std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

  auto res = ca.get_freq(n);
  std::cout << "Found\n";
  for (auto c : res) {
    std::cout << c << "Hz ";
  }
  std::cout << std::endl;

  return 0;
}