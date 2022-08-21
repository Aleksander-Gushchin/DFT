#include <gtest/gtest.h>
#include "lib.h"

const size_t n = 2000;
const size_t k = 1000;

TEST(DFT_OpenMP, Correctness_test_1_thread) {

  omp_set_num_threads(1);
  std::vector<double> signal(n, 0);
  size_t ic = 0;
  for (auto& item : signal) item = (double)ic++ / n;

  auto sin5 = math::get_sin(5);
  auto sin2 = math::get_sin(2);
  auto sin7 = math::get_sin(7);
  for (auto& item : signal) item = sin5(item) + sin2(item) + sin7(item);

  auto ca = ComplexArray(k);
  DiscreteFourierTransform(signal.data(), &ca, n, k);


  auto list = ca.get_freq(n);
  auto res = testing::found_all(list, 2, 5, 7);

  EXPECT_EQ(res, true);
  
}

TEST(DFT_OpenMP, Correctness_test_8_thread) {

  omp_set_num_threads(8);
  std::vector<double> signal(n, 0);
  size_t ic = 0;
  for (auto& item : signal) item = (double)ic++ / n;

  auto sin5 = math::get_sin(5);
  auto sin2 = math::get_sin(2);
  auto sin7 = math::get_sin(7);
  for (auto& item : signal) item = sin5(item) + sin2(item) + sin7(item);

  auto ca = ComplexArray(k);
  DiscreteFourierTransform(signal.data(), &ca, n, k);


  auto list = ca.get_freq(n);
  auto res = testing::found_all(list, 2, 5, 7);

  EXPECT_EQ(res, true);
}