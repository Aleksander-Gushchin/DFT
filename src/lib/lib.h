#include <iostream>
#include <complex>

const double pi = acos(-1);

struct ComplexArray{
  double* realP;
  double* imagP;

  ComplexArray(size_t size){
    realP = new double[size];
    imagP = new double[size];
  }

  double get(size_t i){
    return sqrt(realP[i] * realP[i] + imagP[i]*imagP[i]);
  }

  ~ComplexArray(){
    delete[] realP;
    delete[] imagP;
  }
};

void DiscreteFourierTransform(double* data, ComplexArray* output, size_t end_n, size_t end_k){
  
  std::complex<double> i = {0, 1};
  const size_t N = end_n - 1;
  for(size_t k = 0; k < end_k; ++k)
  {
    std::complex<double> sum = {0, 0};
    for(size_t n = 0; n < end_n; ++n)
    {
      auto expon =  (((double)k / N * n) * -2 * pi * i);
      sum += data[n] * exp(expon);
    }
    output->realP[k] = sum.real();
    output->imagP[k] = sum.imag();
  }
}

template<typename Collection>
void print(Collection c) {
  for (auto item : c)
    std::cout << item << " ";
  std::cout << std::endl;
}

