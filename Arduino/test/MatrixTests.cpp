#include <Arduino.h> // Essential for setup() and loop() and Serial
#include <cassert>   // We'll replace assert with custom checks, but keeping for reference if you want to fall back
#include <cmath>     // For std::fabs
#include <Matrix.h>  // Assuming this is now located in lib/MatrixLib/include/

// --- Test Reporting Global Variables ---
int totalTestsRun = 0;
int totalTestsPassed = 0;

// --- Helper Functions (same as yours) ---
// Helper: compare floats
bool almost_equal(float a, float b, float eps = 1e-6f) {
    return std::fabs(a - b) < eps;
}

// Helper: compare Vectors
bool vectors_equal(const Vector& a, const Vector& b, float eps = 1e-6f) {
    return almost_equal(a.x, b.x, eps)
        && almost_equal(a.y, b.y, eps)
        && almost_equal(a.z, b.z, eps);
}

// --- Custom Assertion Macro ---
// This macro will print PASS/FAIL messages and update test counters
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


// --- Test Functions ---

void TestDefaultConstructor() {
    Serial.println("Running TestDefaultConstructor...");
    Matrix I;

    // Identity matrix: diagonal 1s, rest 0s
    CUSTOM_ASSERT(almost_equal(I[{0,0}], 1.0f), "TestDefaultConstructor", "I[0,0] is 1.0");
    CUSTOM_ASSERT(almost_equal(I[{1,1}], 1.0f), "TestDefaultConstructor", "I[1,1] is 1.0");
    CUSTOM_ASSERT(almost_equal(I[{2,2}], 1.0f), "TestDefaultConstructor", "I[2,2] is 1.0");

    CUSTOM_ASSERT(almost_equal(I[{0,1}], 0.0f), "TestDefaultConstructor", "I[0,1] is 0.0");
    CUSTOM_ASSERT(almost_equal(I[{0,2}], 0.0f), "TestDefaultConstructor", "I[0,2] is 0.0");
    CUSTOM_ASSERT(almost_equal(I[{1,0}], 0.0f), "TestDefaultConstructor", "I[1,0] is 0.0");
    CUSTOM_ASSERT(almost_equal(I[{1,2}], 0.0f), "TestDefaultConstructor", "I[1,2] is 0.0");
    CUSTOM_ASSERT(almost_equal(I[{2,0}], 0.0f), "TestDefaultConstructor", "I[2,0] is 0.0");
    CUSTOM_ASSERT(almost_equal(I[{2,1}], 0.0f), "TestDefaultConstructor", "I[2,1] is 0.0");
}

void TestInitConstructor() {
    Serial.println("Running TestInitConstructor...");
    MatrixStruct m = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    Matrix M(m);
    CUSTOM_ASSERT(almost_equal(M[{0,0}], 1.0f), "TestInitConstructor", "M[0,0] is 1.0");
    CUSTOM_ASSERT(almost_equal(M[{0,1}], 2.0f), "TestInitConstructor", "M[0,1] is 2.0");
    CUSTOM_ASSERT(almost_equal(M[{0,2}], 3.0f), "TestInitConstructor", "M[0,2] is 3.0");
    CUSTOM_ASSERT(almost_equal(M[{1,0}], 4.0f), "TestInitConstructor", "M[1,0] is 4.0");
    CUSTOM_ASSERT(almost_equal(M[{1,1}], 5.0f), "TestInitConstructor", "M[1,1] is 5.0");
    CUSTOM_ASSERT(almost_equal(M[{1,2}], 6.0f), "TestInitConstructor", "M[1,2] is 6.0");
    CUSTOM_ASSERT(almost_equal(M[{2,0}], 7.0f), "TestInitConstructor", "M[2,0] is 7.0");
    CUSTOM_ASSERT(almost_equal(M[{2,1}], 8.0f), "TestInitConstructor", "M[2,1] is 8.0");
    CUSTOM_ASSERT(almost_equal(M[{2,2}], 9.0f), "TestInitConstructor", "M[2,2] is 9.0");
}

void TestScalarMult() {
    Serial.println("Running TestScalarMult...");
    MatrixStruct m = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    Matrix M(m);
    Matrix R = M * 2.0f;

    CUSTOM_ASSERT(almost_equal(R[{0,0}], 2.0f), "TestScalarMult", "R[0,0] is 2.0");
    CUSTOM_ASSERT(almost_equal(R[{0,1}], 4.0f), "TestScalarMult", "R[0,1] is 4.0");
    CUSTOM_ASSERT(almost_equal(R[{0,2}], 6.0f), "TestScalarMult", "R[0,2] is 6.0");
    CUSTOM_ASSERT(almost_equal(R[{1,0}], 8.0f), "TestScalarMult", "R[1,0] is 8.0");
    CUSTOM_ASSERT(almost_equal(R[{1,1}], 10.0f), "TestScalarMult", "R[1,1] is 10.0");
    CUSTOM_ASSERT(almost_equal(R[{1,2}], 12.0f), "TestScalarMult", "R[1,2] is 12.0");
    CUSTOM_ASSERT(almost_equal(R[{2,0}], 14.0f), "TestScalarMult", "R[2,0] is 14.0");
    CUSTOM_ASSERT(almost_equal(R[{2,1}], 16.0f), "TestScalarMult", "R[2,1] is 16.0");
    CUSTOM_ASSERT(almost_equal(R[{2,2}], 18.0f), "TestScalarMult", "R[2,2] is 18.0");
}

void TestVectorMult() {
    Serial.println("Running TestVectorMult...");
    MatrixStruct m = {
        1,0,0,
        0,1,0,
        0,0,1
    };
    Matrix I(m);
    Vector v{1, 2, 3};

    Vector result = I * v;

    CUSTOM_ASSERT(vectors_equal(result, v), "TestVectorMult", "Result vector equals original");
}

void TestMatrixMult() {
    Serial.println("Running TestMatrixMult...");
    MatrixStruct A_s = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    Matrix A(A_s);

    MatrixStruct B_s = {
        9,8,7,
        6,5,4,
        3,2,1
    };
    Matrix B(B_s);

    Matrix C = A * B;

    CUSTOM_ASSERT(almost_equal(C[{0,0}], 30.0f), "TestMatrixMult", "C[0,0] is 30.0");
    CUSTOM_ASSERT(almost_equal(C[{0,1}], 24.0f), "TestMatrixMult", "C[0,1] is 24.0");
    CUSTOM_ASSERT(almost_equal(C[{0,2}], 18.0f), "TestMatrixMult", "C[0,2] is 18.0");

    CUSTOM_ASSERT(almost_equal(C[{1,0}], 84.0f), "TestMatrixMult", "C[1,0] is 84.0");
    CUSTOM_ASSERT(almost_equal(C[{1,1}], 69.0f), "TestMatrixMult", "C[1,1] is 69.0");
    CUSTOM_ASSERT(almost_equal(C[{1,2}], 54.0f), "TestMatrixMult", "C[1,2] is 54.0");

    CUSTOM_ASSERT(almost_equal(C[{2,0}], 138.0f), "TestMatrixMult", "C[2,0] is 138.0");
    CUSTOM_ASSERT(almost_equal(C[{2,1}], 114.0f), "TestMatrixMult", "C[2,1] is 114.0");
    CUSTOM_ASSERT(almost_equal(C[{2,2}], 90.0f), "TestMatrixMult", "C[2,2] is 90.0");
}

void TestAddition() {
    Serial.println("Running TestAddition...");
    MatrixStruct A_s = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    Matrix A(A_s);

    MatrixStruct B_s = {
        9,8,7,
        6,5,4,
        3,2,1
    };
    Matrix B(B_s);

    Matrix C = A + B;

    CUSTOM_ASSERT(almost_equal(C[{0,0}], 10.0f), "TestAddition", "C[0,0] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{0,1}], 10.0f), "TestAddition", "C[0,1] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{0,2}], 10.0f), "TestAddition", "C[0,2] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{1,0}], 10.0f), "TestAddition", "C[1,0] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{1,1}], 10.0f), "TestAddition", "C[1,1] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{1,2}], 10.0f), "TestAddition", "C[1,2] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{2,0}], 10.0f), "TestAddition", "C[2,0] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{2,1}], 10.0f), "TestAddition", "C[2,1] is 10.0");
    CUSTOM_ASSERT(almost_equal(C[{2,2}], 10.0f), "TestAddition", "C[2,2] is 10.0");
}


// --- Arduino setup() function ---
void setup() {
    Serial.begin(115200); // Initialize serial communication at a common baud rate
    delay(2000);          // Give some time for the serial monitor to connect

    Serial.println("\n--- Starting Custom Matrix Tests ---");

    // Call all your test functions
    TestDefaultConstructor();
    TestInitConstructor();
    TestScalarMult();
    TestVectorMult();
    TestMatrixMult();
    TestAddition();

    Serial.println("\n--- Test Summary ---");
    Serial.print("Total Tests Run: ");
    Serial.println(totalTestsRun);
    Serial.print("Tests Passed: ");
    Serial.println(totalTestsPassed);
    Serial.print("Tests Failed: ");
    Serial.println(totalTestsRun - totalTestsPassed);

    if (totalTestsPassed == totalTestsRun) {
        Serial.println("--- All Tests PASSED! ✅ ---");
    } else {
        Serial.println("--- Some Tests FAILED! ❌ ---");
    }
}

// --- Arduino loop() function ---
void loop() {
    // For unit tests that run once in setup(), the loop() function can remain empty.
    // The board will typically stay in this empty loop after tests complete.
}