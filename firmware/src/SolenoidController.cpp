#include "SolenoidController.h"
#include "Config.h"

// Note: Pulse duration adjusted based on provided configuration for safety.
#define PULSE_DURATION_MS 150 

void SolenoidController::init() {
    pinMode(PIN_DRV1_AIN1, OUTPUT); pinMode(PIN_DRV1_AIN2, OUTPUT);
    pinMode(PIN_DRV1_BIN1, OUTPUT); pinMode(PIN_DRV1_BIN2, OUTPUT);
    
    pinMode(PIN_DRV2_AIN1, OUTPUT); pinMode(PIN_DRV2_AIN2, OUTPUT);
    pinMode(PIN_DRV2_BIN1, OUTPUT); pinMode(PIN_DRV2_BIN2, OUTPUT);
    
    pinMode(PIN_DRV3_AIN1, OUTPUT); pinMode(PIN_DRV3_AIN2, OUTPUT);
    pinMode(PIN_DRV3_BIN1, OUTPUT); pinMode(PIN_DRV3_BIN2, OUTPUT);
}

void SolenoidController::raiseDot(int dotNumber) {
    int p1 = -1, p2 = -1;
    switch(dotNumber) {
        case 1: p1 = PIN_DRV1_AIN1; p2 = PIN_DRV1_AIN2; break;
        case 2: p1 = PIN_DRV1_BIN1; p2 = PIN_DRV1_BIN2; break;
        case 3: p1 = PIN_DRV2_AIN1; p2 = PIN_DRV2_AIN2; break;
        case 4: p1 = PIN_DRV2_BIN2; p2 = PIN_DRV2_BIN1; break; // SWAPPED polarity!
        case 5: p1 = PIN_DRV3_AIN1; p2 = PIN_DRV3_AIN2; break;
        case 6: p1 = PIN_DRV3_BIN1; p2 = PIN_DRV3_BIN2; break;
    }
    if (p1 != -1) {
        digitalWrite(p1, HIGH);
        digitalWrite(p2, LOW);
    }
}

void SolenoidController::lowerDot(int dotNumber) {
    int p1 = -1, p2 = -1;
    switch(dotNumber) {
        case 1: p1 = PIN_DRV1_AIN1; p2 = PIN_DRV1_AIN2; break;
        case 2: p1 = PIN_DRV1_BIN1; p2 = PIN_DRV1_BIN2; break;
        case 3: p1 = PIN_DRV2_AIN1; p2 = PIN_DRV2_AIN2; break;
        case 4: p1 = PIN_DRV2_BIN1; p2 = PIN_DRV2_BIN2; break;
        case 5: p1 = PIN_DRV3_AIN1; p2 = PIN_DRV3_AIN2; break;
        case 6: p1 = PIN_DRV3_BIN1; p2 = PIN_DRV3_BIN2; break;
    }
    if (p1 != -1) {
        digitalWrite(p1, LOW);
        digitalWrite(p2, HIGH);
    }
}

void SolenoidController::displayBrailleCell(int pattern[6]) {
    // We MUST fire them sequentially to prevent the motor drivers from crashing,
    // but we can do it extremely fast so it feels like "all at once" to your finger.
    for (int i = 0; i < 6; i++) {
        if (pattern[i] == 1) {
            // 1. Turn on the solenoid
            raiseDot(i + 1);
            
            // 2. Wait just 40ms for the pin to pop up (much faster than 150ms)
            delay(40);
            
            // 3. Turn it off to free up power for the next pin
            int p1 = -1, p2 = -1;
            switch(i + 1) {
                case 1: p1 = PIN_DRV1_AIN1; p2 = PIN_DRV1_AIN2; break;
                case 2: p1 = PIN_DRV1_BIN1; p2 = PIN_DRV1_BIN2; break;
                case 3: p1 = PIN_DRV2_AIN1; p2 = PIN_DRV2_AIN2; break;
                case 4: p1 = PIN_DRV2_BIN1; p2 = PIN_DRV2_BIN2; break;
                case 5: p1 = PIN_DRV3_AIN1; p2 = PIN_DRV3_AIN2; break;
                case 6: p1 = PIN_DRV3_BIN1; p2 = PIN_DRV3_BIN2; break;
            }
            if (p1 != -1) {
                digitalWrite(p1, LOW);
                digitalWrite(p2, LOW);
            }
        }
    }
}
