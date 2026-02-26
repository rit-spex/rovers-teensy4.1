#ifndef SCIENCE_H
#define SCIENCE_H

#include <array>

#include "CAN/messages/science.h"
#include "auger.h"
#include "constants.h"
#include "pinout.h"
#include "pump.h"
#include "sampleSlide.h"

#include "CAN/CAN.h"

class Science
{
public:
    Science();
    ~Science();

    void startUp();
    void updateSubsystems();
    void runBackgroundProcesses();

    void enable();
    void disable();
    bool isEnabled() const;

    void updateStatusLight();

    // CAN Handlers
    void handleEnableScience(const EnableScienceMsg &msg);
    void handleMoveAuger(const MoveAugerMsg &msg);
    void handleEnableDrill(const EnableDrillMsg &msg);
    void handleMoveSlide(const MoveSlideMsg &msg);
    void handleEnablePump(const EnablePumpMsg &msg);
    void handleMoveSpectrometerSlide(const MoveSpectrometerSlideMsg &msg);
    void handleMoveFluorometerSlide(const MoveFluorometerSlideMsg &msg);
    void handleEnableFluorometerMicroPump(const EnableFluorometerMicroPumpMsg &msg);
    void handleEnablePrimer(const EnablePrimerMsg &msg);
    void handleEnableVibration(const EnableVibrationMsg &msg);
private:
    // Subsystems
    SampleSlide m_sampleSlide;
    Auger m_auger;
    std::array<Pump, NUM_PUMPS> m_pumps = {
        Pump(PUMP_0_I2C_ADDR, PUMP_SPEED),
        Pump(PUMP_1_I2C_ADDR, PUMP_SPEED),
        Pump(PUMP_2_I2C_ADDR, PUMP_SPEED),
    };

    bool m_enabled = true;

    unsigned long m_prevMillis = 0; // For status light blinking

    CAN m_can;
};

// #include "TICT249.h"
// #include "SMC.h"

// class Science
// {
// public:
//     enum Direction
//     {
//         FORWARD = 1,
//         REVERSE = 0,
//         OFF = 2
//     };
//     Science();
//     ~Science();
//     void startUp();
//
//     // Sample Collection
//     void moveAuger(float speed);                               // SPARKMAX
//     void extendGroundLevelLinearActuator(Direction direction); // TIC
//     void moveSoilSplitter(Direction direction);                // TIC
//     void controlFloodingPump(Direction direction);             // SMC
//     void controlSolutionPump1(Direction direction);            // SMC
//     void controlSolutionPump2(Direction direction);            // SMC
//     void moveSolutionServo1(float speed);                      // PWM
//     void moveSolutionServo2(float speed);                      // PWM
//
//     // Fluorometer
//     void peristalticPump(Direction direction);               // TIC
//     void microPumpServo(float speed);                        // PWM
//     int readThermister();                                    // 10k Thermisters
//     void turnHeaterStripsOn();                               // 12V heater strips
//     void turnHeaterStripsOff();                              // 12V heater strips
//     void moveFluorometerLinearActuator(Direction direction); // TIC
//     int readADC();                                           // I2C
//
//     // Spectrometer/Ethonol Test
//     void moveSpectrometerLinearActuator(Direction direction); // TIC
//     int readSpectrometerModule();
//
// private:
// };
//

#endif // SCIENCE_H
