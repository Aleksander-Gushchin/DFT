#include <gtest/gtest.h>

#include <random>

#include "lib.h"

const size_t n = 2000;
const size_t k = 1000;
std::mt19937 rg(time(0)); 


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

TEST(DFT_OpenMP, Correctness_test_8_thread_random) {

  omp_set_num_threads(8);
  std::vector<double> signal(n, 0);
  size_t ic = 0;
  for (auto& item : signal) item = (double)ic++ / n;

  auto f = rg() % 100;
  auto s = rg() % 100;
  auto t = rg() % 100;

  auto sin1 = math::get_sin(f);
  auto sin2 = math::get_sin(s);
  auto sin3 = math::get_sin(t);
  for (auto& item : signal) item = sin1(item) + sin2(item) + sin3(item);

  auto ca = ComplexArray(k);
  DiscreteFourierTransform(signal.data(), &ca, n, k);


  auto list = ca.get_freq(n);
  auto res = testing::found_all(list, f, s, t);

  EXPECT_EQ(res, true);
}