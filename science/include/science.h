#ifndef SCIENCE_H
#define SCIENCE_H

#include "auger.h"
#include "sampleSlide.h"

class Science {
public:
    Science();
    ~Science();

    void startUp();
    void updateSubsystems();
    void runBackgroundProcesses();

    void enable();
    void disable();
    bool isEnabled() const;
    bool isDisabled() const;

    void updateStatusLight();
private:
    SampleSlide m_sampleSlide;
    Auger m_auger;

    bool m_enabled = true;

    unsigned long m_prevMillis = 0; // For status light blinking
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
