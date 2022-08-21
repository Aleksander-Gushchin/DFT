#include <iostream>
#include <complex>
#include <list>
#include <functional>
#include <unordered_map>
#include <omp.h>

namespace math {
  const double pi = acos(-1);

  std::function<double(double)> get_sin(double Hz) {
    return [=](double t) { return sin(2 * pi * Hz * t); };
  }
}

namespace testing {
  template<typename Container,typename... Ts>
  bool found_all(Container cont, Ts&&... args) {
    using c_type = std::common_type_t<Ts...>;
    std::unordered_map<c_type, int> hash_count;
    for (const auto& item : cont)
      ++hash_count[item];

    (--hash_count[args], ...);

    for (auto [key, c] : hash_count)
      if (c != 0) return false;

    return true;
  }

}


struct ComplexArray{
private: 
  size_t k;

public:
  double* realP;
  double* imagP;

  

  ComplexArray(size_t size){
    realP = new double[size];
    imagP = new double[size];
    k = size;
  }

  double get(size_t i){
    return sqrt(realP[i] * realP[i] + imagP[i]*imagP[i]);
  }

  std::list<size_t> get_freq(size_t n) {
    std::list<size_t> res;
    for (int i = 0; i < k; ++i) {
      if (this->get(i) / n > 0.45)
        res.push_back(i);
    }


    return res;
  }

  ~ComplexArray(){
    delete[] realP;
    delete[] imagP;
  }
};

void DiscreteFourierTransform(double* data, ComplexArray* output, size_t end_n, size_t end_k){
  
  std::complex<double> i = {0, 1};
  const size_t N = end_n - 1;

  #pragma omp parallel for schedule(static)
  for(int k = 0; k < end_k; ++k)
  {
    std::complex<double> sum = {0, 0};
    for(size_t n = 0; n < end_n; ++n)
    {
      auto expon =  (((double)k / N * n) * -2 * math::pi * i);
      sum += data[n] * exp(expon);
    }
    output->realP[k] = sum.real();
    output->imagP[k] = sum.imag();
  }
}

template<typename Container>
void print(Container c) {
  for (auto item : c)
    std::cout << item << " ";
  std::cout << std::endl;
}

