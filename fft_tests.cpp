#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"
#include "fft.h"
#include <random>
#include <ctime>

using namespace std;

std::vector<int> NativeConv(std::vector<int> &first, std::vector<int> &second) {
    std::vector<int> out(first.size());
    for (size_t i = 0; i < first.size(); ++i) {
        for (size_t j = 0; j < second.size(); ++j) {
            out[i + j] += first[i] * second[j];
        }
    }
    return out;
}

void ConvCheck(vector<int> actual, const std::vector<int>& expected) {
    EXPECT_THAT(actual, testing::ContainerEq(expected));
    EXPECT_THAT(actual, testing::ContainerEq(expected));
}

TEST(VectorsConv, Dummy) {
   std::vector<int> first = {1, 1, 0, 0};
   std::vector<int> second = {0, 0, 0, 0};
   std::vector<int> expected = {0, 0, 0, 0};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_1) {
   std::vector<int> first = {1, 1, 0, 0};
   std::vector<int> second = {-1, 1, 0, 0};
   std::vector<int> expected = {-1, 0, 1, 0};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_2) {
   std::vector<int> first = {1, 0, 0, 0};
   std::vector<int> second = {1, 1, 1, 0};
   std::vector<int> expected = {1, 1, 1, 0};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_3) {
   std::vector<int> first = {0, 1, 0 ,0};
   std::vector<int> second = {0, 0, 1, 0};
   std::vector<int> expected = {0, 0, 0, 1};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_4) {
   std::vector<int> first = {-3, -4, 6, 2, 0, 0, 0, 0};
   std::vector<int> second = {-2, 1, 0, 4, 0, 0, 0, 0};
   std::vector<int> expected = {6, 5, -16, -10, -14, 24, 8, 0};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_5) {
   std::vector<int> first = {-1, 0, 1, 0, 0, 0, 0, 0};
   std::vector<int> second = {-1, 0, 1, 0, -3, 0, 0, 0};
   std::vector<int> expected = {1, 0, -2, 0, 4, 0, -3, 0};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_6) {
   std::vector<int> first = {-1, -1, -1, -1, 0, 0, 0, 0};
   std::vector<int> second = {1, 1, 1, 1, 0, 0, 0, 0};
   std::vector<int> expected = {-1, -2, -3, -4, -3, -2, -1, 0};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_7) {
   std::vector<int> first = {2};
   std::vector<int> second = {3};
   std::vector<int> expected = {6};
   ConvCheck(Conv(first, second), expected);
}

TEST(VectorsConv, Correctness_Random) {
   size_t vect_size = 16;
   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_int_distribution<std::mt19937::result_type> dist6(0,25);
   for (size_t i = 0; i < 25; ++i) {
       std::vector<int> first(vect_size * 2);
       std::vector<int> second(vect_size * 2);
       for (size_t j = 0; j < vect_size; ++j) {
           first[j] = dist6(rng);
           second[j] = dist6(rng);
       }
       auto expected = NativeConv(first, second);
       auto actual = Conv(first, second);
       ConvCheck(actual, expected);
   }
}

TEST(VectorsConv, TimeLimit) {
   size_t vect_size = 2;
   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_int_distribution<std::mt19937::result_type> dist6(0,25);
   for (size_t i = 0; i < 5; ++i) {
       std::vector<int> first(vect_size * 2);
       std::vector<int> second(vect_size * 2);
       for (size_t j = 0; j < vect_size; ++j) {
           first[j] = dist6(rng);
           second[j] = dist6(rng);
       }
       time_t start = clock();
       Conv(first, second);
       time_t end = clock();
       EXPECT_LE(end - start, 1 * CLOCKS_PER_SEC);
   }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
