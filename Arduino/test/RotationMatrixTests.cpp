#include <Arduino.h>    
#include <BarbellExercise.h>  
#include <test_util.h>

namespace RotationMatrixTests{

bool vectors_equal(const Vector& a, const Vector& b, float eps = 1e-6f) {
    return almost_equal(a.x, b.x, eps)
        && almost_equal(a.y, b.y, eps)
        && almost_equal(a.z, b.z, eps);
}



// --- Test Functions ---

void TestRotationMatrix1(){
    BarbellExercise obj = BarbellExercise();
    Vector gravity = {1.3, 9.0, 7.2};
    Matrix m = obj.CreateRotationMatrix({1.3, 9.0, 7.2});
    CUSTOM_ASSERT(almost_equal(dot({0,0,-1}, m*gravity), magnitude(gravity)),"TestRotatonMatrix1 ", "Vectors point in the same direction");
}

void setup() {
    Serial.begin(115200); 
    delay(2000);         

    Serial.println("\n--- Starting Custom Matrix Tests ---");

    TestRotationMatrix1();

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

void loop() {}

} //namespace RotationMatrixTests