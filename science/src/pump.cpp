#include "pump.h"

Pump::Pump()
{
    m_flow = Flow::Sucking;
}

Pump::~Pump()
{
}

bool Pump::isEnabled() const
{
    return m_enabled;
}

void Pump::enable()
{
    m_enabled = true;
}

void Pump::disable()
{
    m_enabled = false;
}

Pump::Flow Pump::getFlow() const
{
    return m_flow;
}

void Pump::setFlow(Flow flow)
{
    m_flow = flow;
}
