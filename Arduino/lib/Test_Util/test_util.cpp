#include <test_util.h>

bool almost_equal(float a, float b, float eps = 1e-6f) {
    return std::fabs(a - b) < eps;
}