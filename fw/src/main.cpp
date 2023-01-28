// #define ARDUINO_MAIN
#include <Arduino.h>
#include <USB/PluggableUSBSerial.h>

#include "pins.h"
#include "App.h"


// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

App* app;

//Push button interrupt callback for C compatability
void staticButtonInterrupt()
{
  app->modePin_isr();
}

int main(void)
{
	init();
	initVariant();

#if defined(SERIAL_CDC)
  PluggableUSBD().begin();
  _SerialUSB.begin(115200);
#endif

    //dirty hack to get a convenient place for a pullup
    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);

    SerialUSB.begin(115200);
    // Sleep to allow for USB to enumerate
    sleep_ms(2000);

    app = new App(pins::ledPin, pins::modeButton, &staticButtonInterrupt);


	for (;;) {
    app->loop();
        // Process Serial comms
		if (arduino::serialEventRun) arduino::serialEventRun();
	}

	return 0;
}