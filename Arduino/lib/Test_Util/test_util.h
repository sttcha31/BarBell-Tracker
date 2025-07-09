#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <cmath>     

extern int totalTestsRun = 0;
extern int totalTestsPassed = 0;

bool almost_equal(float a, float b, float eps = 1e-6f);


#define CUSTOM_ASSERT(condition, test_name, message) \
    totalTestsRun++; \
    if (condition) { \
        Serial.print("  [PASS] "); \
        Serial.print(test_name); \
        Serial.print(": "); \
        Serial.println(message); \
        totalTestsPassed++; \
    } else { \
        Serial.print("  [FAIL] "); \
        Serial.print(test_name); \
        Serial.print(": "); \
        Serial.println(message); \
    }

#endif