#include <cstdint>
#include <cstdio>
#define CAN_CODEC_TEST
#include "CAN/codec.h"
#include "CAN/message_id.h"
#include "CAN/messages/science.h"
#include <unity.h>

void _memdump(void const* data, size_t size) {
    const uint8_t* ptr = (const uint8_t*)data;
    size_t i;

    for (i = 0; i < size; i++) {
        // Print each byte in hexadecimal format
        printf("%02X ", ptr[i]);
    }
    printf("\n");
}

void test_enable_science_codec() {
    EnableScienceMsg msg = EnableScienceMsg { (uint8_t)1 };
    CANMessage canMsg = encode(msg, MessageID::ENABLE_SCIENCE);

    TEST_ASSERT_EQUAL(canMsg.id, (uint32_t)MessageID::ENABLE_SCIENCE);
    TEST_ASSERT_EQUAL(canMsg.len, sizeof(EnableScienceMsg));

    EnableScienceMsg decoded = decode<EnableScienceMsg>(canMsg);

    TEST_ASSERT_EQUAL(decoded.enable, 1);
}

void test_move_auger_codec() {
    MoveAugerMsg msg = MoveAugerMsg {
        ScienceState::Active,
        ScienceDir::Reverse,
    };
    CANMessage canMsg = encode(msg, MessageID::MOVE_AUGER);
    _memdump(&canMsg, sizeof(typeof(canMsg)));

    TEST_ASSERT_EQUAL(canMsg.id, (uint32_t)MessageID::MOVE_AUGER);
    TEST_ASSERT_EQUAL(canMsg.len, sizeof(MoveAugerMsg));

    MoveAugerMsg decoded = decode<MoveAugerMsg>(canMsg);

    TEST_ASSERT_EQUAL(decoded.state, ScienceState::Active);
    TEST_ASSERT_EQUAL(decoded.direction, ScienceDir::Reverse);
}



int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_enable_science_codec);
    RUN_TEST(test_move_auger_codec);

    UNITY_END();
}

