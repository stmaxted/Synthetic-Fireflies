#include "App.h"

App::App(pin_size_t ledPin, pin_size_t modePin, void (*modeInterruptFunc)()):
    m_ledPin(ledPin),
    m_modePin(modePin)
{
    m_modePressed = false;
    pinMode(m_ledPin, OUTPUT);
    pinMode(m_modePin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt((int)m_modePin), 
                    modeInterruptFunc, 
                    FALLING);
    analogWrite(m_ledPin, m_brightnessSettings[m_brightnessIndex]);
}

void App::loop()
{
    m_timestamp_ms = millis();
    
    if(m_modePressed)
    {
        m_modePressed = false;
        if((m_timestamp_ms - m_brightnessLastUpdated) >= BRIGHTNESS_UPDATE_PERIOD_MS)
        {
            m_brightnessIndex++;
            if (m_brightnessIndex >= sizeof(m_brightnessSettings)) m_brightnessIndex = 0;
            Serial.println(m_brightnessSettings[m_brightnessIndex]);
            analogWrite(m_ledPin, m_brightnessSettings[m_brightnessIndex]);
            m_brightnessLastUpdated = m_timestamp_ms;
        }
    }
}

void App::modePin_isr()
{
    m_modePressed = true;
}