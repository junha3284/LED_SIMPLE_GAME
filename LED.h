#define LED0_TRIGGER "/sys/class/leds/beaglebone:green:usr0/trigger"
#define LED1_TRIGGER "/sys/class/leds/beaglebone:green:usr1/trigger"
#define LED2_TRIGGER "/sys/class/leds/beaglebone:green:usr2/trigger"
#define LED3_TRIGGER "/sys/class/leds/beaglebone:green:usr3/trigger"

// change all LEDs Trigger to none 
void LED_init();

// turn on i_th LED on beaglebone
void LED_turn_on(int i);

// turn off i_th LED on beaglebone
void LED_turn_off(int i);


