#include "drill.h"

Drill::Drill() {
    m_enabled = false;
    m_dir = Direction::FORWARD;
}

bool Drill::isEnabled() const {
    return m_enabled;
}

void Drill::enable() {
    m_enabled = true;
}

void Drill::disable() {
    m_enabled = false;
}

Drill::Direction Drill::getDir() const {
    return m_dir;
}

void Drill::setDir(Drill::Direction dir) {
    m_dir = dir;
}

void Drill::reverseDir() {
    if (m_dir == Direction::FORWARD) {
        m_dir = Direction::BACKWARD;
    } else if (m_dir == Direction::BACKWARD) {
        m_dir = Direction::FORWARD;
    }
}
