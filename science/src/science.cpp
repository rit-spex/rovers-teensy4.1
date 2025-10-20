#include "science.h"

#include <Arduino.h>

#include "pinout.h"
#include "constants.h"

Science::Science() {}

void Science::enable() {
    m_enabled = true;
}
void Science::disable() {
    m_enabled = false;
}

bool Science::isEnabled() const {
    return m_enabled;
}

bool Science::isDisabled() const {
    return !m_enabled;
}

void Science::updateStatusLight() {
    unsigned long currentMillis = millis();
    if (isDisabled()) {
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
    } else if (currentMillis - m_prevMillis >= LED_BLINK_INTERVAL) {
        m_prevMillis = currentMillis;
        digitalWrite(STATUS_LIGHT_PIN, !digitalRead(STATUS_LIGHT_PIN));
    }
}
