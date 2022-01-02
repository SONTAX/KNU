#pragma once

#include <cmath>
#include <vector>
#include <map>

#include "LongNumber.hpp"

namespace GeneralAlgebra {
  template<typename T>
  T gcd (T a, T b) {
    if (b == 0)
      return a;
    else
      return gcd (b, a % b);
  }

  template<typename T>
  T pollardFactoring(T n) {
    T a = T(2), b = T(2);
    for (int i = 0;; ++i) {
      a = (a * a + T(1)) % n;
      b = (b * b + T(1)) % n;
      b = (b * b + T(1)) % n;

      T d = gcd(a-b, n);

      if (T(1) < d && d < n)
        return d;
      else if (d == n)
        return T(-1);
    }
  }

  template<typename T>
  T sqrt(T n) {
    return std::sqrt(n);
  }

  template <int CellLength>
  LongNumber<CellLength> sqrt(LongNumber<CellLength> n) {
    using LN = LongNumber<CellLength>;

    if (n == LN(0) || n == LN(1))
      return n;

    LongNumber<CellLength> i = LN(1), result = LN(1);
    while (result <= n) {
      ++i;
      result = i * i;
    }
    return i - LN(1);
  }

  template<typename T>
  std::vector<T> naiveFactoring(T n) {
    std::vector<T> factors;

    for (T i = T(2); i <= sqrt(n); ++i) {
      while (n % i == T(0)) {
        factors.push_back(i);
        n = n / i;
      }
    }

    if (n != T(1)) {
      factors.push_back(n);
    }

    return factors;
  }

  template<typename T>
  std::map<T, T> naiveFactoringWithPowers(T n) {
    std::map<T, T> factors;

    for (T i = T(2); i <= sqrt(n); ++i) {
      while (n % i == T(0)) {
        factors[i]++;
        n = n / i;
      }
    }

    if (n != T(1)) {
      factors[n]++;
    }

    return factors;
  }
}