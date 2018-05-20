#define LED0_TRIGGER "/sys/class/leds/beaglebone:green:usr0/trigger"
#define LED1_TRIGGER "/sys/class/leds/beaglebone:green:usr1/trigger"
#define LED2_TRIGGER "/sys/class/leds/beaglebone:green:usr2/trigger"
#define LED3_TRIGGER "/sys/class/leds/beaglebone:green:usr3/trigger"

// openLEDFiles and turn off all LEDs
void openLEDFiles();

// turn off i_th LED on beaglebone
void turnOffLED(int i);

// turn on i_th LED on beaglebone
void turnOnLED(int i);
