#include "main.h"

void setup() {
    // Serial.begin(9600);
    arm = Arm();
    arm.startUp();
    can = CAN(&currentRunCycle);
}

void loop() {
    if(can.isNewMessage(CAN::E_STOP)){
        arm.disable();
    }
    for(int i = 10; i < 16; ++i){
        if(can.isNewMessage((CAN::Message_ID)i)){
            switch(i){
                case 10:
                    break;
                case 11:
                    break;
                case 12:
                    break;
                case 13:
                    break;
                case 14:
                    break;
                case 15:
                    break;
            }
        }
    }
}
