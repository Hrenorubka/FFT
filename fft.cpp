#include "fft.h"
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <stack>
#include <numeric>

using std::size_t;

const double kPi = acos(-1);
const long long kMod = 1'000'000'000 + 7;

template<typename T>
std::vector<std::complex<double>>
FFT(const std::vector<T> &coeffs, std::complex<double> first_point, size_t start_ind, size_t step) {
    if (coeffs.size() <= start_ind + step) {
        return {static_cast<std::complex<double>>(coeffs[start_ind])};
    }
    std::vector<std::complex<double>> out(coeffs.size() / step);
    std::complex<double> complex_step = 1;
    auto even_result_coeffs = FFT(coeffs, first_point * first_point, start_ind, step * 2);
    auto odd_result_coeffs = FFT(coeffs, first_point * first_point, start_ind + step, step * 2);
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = even_result_coeffs[i % even_result_coeffs.size()] +
                 odd_result_coeffs[i % even_result_coeffs.size()] * complex_step;
        complex_step *= first_point;
    }
    return out;
}

template<typename T>
std::vector<std::complex<double>>
FFT(const std::vector<T> &coeffs, std::complex<double> first_point) {
    return FFT(coeffs, first_point, 0, 1);
}

std::vector<std::complex<double>> GetPointValue(const std::vector<int> &coeffs) {
    return FFT(coeffs, std::polar(1., 2 * M_PI / static_cast<double>(coeffs.size())));
}

std::vector<int> Interpolate(const std::vector<std::complex<double>> &values) {
    auto inv = FFT(values, std::polar(1., -2 * M_PI / static_cast<int>(values.size())));
    std::vector<int> out(values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        out[i] = static_cast<int>(
                static_cast<long long>(std::round(std::real(inv[i])) / values.size()) % kMod);
    }
    return out;
}

std::vector<int> Conv(const std::vector<int> &first, const std::vector<int> &second) {
    auto first_points = GetPointValue(first);
    auto second_points = GetPointValue(second);
    std::vector<std::complex<double>> result_coeffs(first_points.size());
    for (size_t i = 0; i < first_points.size(); ++i) {
//        std::complex<double> complex_size = static_cast<double>(first_points.size());
        result_coeffs[i] = (first_points[i] * second_points[i]
//                / complex_size)
        );
    }
    return Interpolate(result_coeffs);
}
