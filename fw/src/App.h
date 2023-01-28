#pragma once

#include <Arduino.h>

class App
{
public:
    /**
     * @brief Construct a new App object
     * 
     * @param ledPin Output pin driving LED PWM
     * @param modePin Input pin, driven by push button or cap touch IC
     * @param modeInterruptFunc Callback to be called when interrupt fires
     */
    App(pin_size_t ledPin, pin_size_t modePin, void (*modeInterruptFunc)());
    
    /**
     * @brief Main loop
     * 
     */
    void loop();

    /**
     * @brief Interrupt service routine for mode pin
     * 
     */
    void modePin_isr();
    
private:
    pin_size_t m_ledPin;
    pin_size_t m_modePin;


    const uint8_t m_brightnessSettings[7] = {0, 10, 50, 100, 150, 200, 254};
    uint8_t m_brightnessIndex = 0;

    uint32_t m_timestamp_ms = 0;
    uint32_t m_brightnessLastUpdated = 0;
    const uint32_t BRIGHTNESS_UPDATE_PERIOD_MS = 100;
    volatile bool m_modePressed;

};
