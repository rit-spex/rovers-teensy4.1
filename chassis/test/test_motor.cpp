#ifndef generic_hw
#include <Arduino.h>
#else
#include <cstring>
#endif

#include <unity.h>
#include "../include/drivebase/motor.h"

void setUp() {}
void tearDown() {}

void test_initialize() {
    // Before initialization values...
    Motor testMotor(1);

    // After initialization values...
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, testMotor.getPercent());
}

void test_limitPercent() {
    Motor testMotor = Motor(1);
    testMotor.setPercent(150.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, testMotor.getPercent());
    testMotor.setPercent(-150.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -100.0f, testMotor.getPercent());
}

void test_setPercent() {
    Motor testMotor = Motor(1);
    testMotor.setPercent(50.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 50.0f, testMotor.getPercent());
    testMotor.setPercent(-30.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -30.0f, testMotor.getPercent());
}

void test_forceStop() {
    Motor testMotor = Motor(1);
    testMotor.setPercent(50.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 50.0f, testMotor.getPercent());
    testMotor.forceStop();
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, testMotor.getPercent());
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    RUN_TEST(test_limitPercent);
    RUN_TEST(test_setPercent);
    RUN_TEST(test_forceStop);
    UNITY_END();
}