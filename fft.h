#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

std::vector<int> ScalarProd(const std::vector<int> &first, const std::vector<int> &second);

std::vector<std::complex<double>> GetPointValue(const std::vector<int> &coeffs);

std::vector<int> Interpolate(const std::vector<std::complex<double>> &values);

std::vector<int> Conv(const std::vector<int> &first, const std::vector<int> &second);

#endif //FFT_H
