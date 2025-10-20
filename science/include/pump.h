#ifndef PUMP_H
#define PUMP_H

class Pump
{
public:
    enum class Flow
    {
        Sucking,
        Filling,
    };

    Pump();
    ~Pump();

    bool isEnabled() const;
    void enable();
    void disable();

    void setFlow(Flow flow);
    Flow getFlow() const;

private:
    bool m_enabled;
    Flow m_flow;
};

#endif // PUMP_H
