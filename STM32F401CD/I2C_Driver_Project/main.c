#include "GPIO.h"
#include "I2C.h"

int main() {
    GPIO_InitPin(PORT_A, 1, OUTPUT);

    I2C1_init_begin();  // Initialize I2C as a slave

    while (1) {

        if (available()) {
            uint8_t receivedData = I2C1_Read();

            // Check if the received data is 0x01
            if (receivedData == 0x01) {
                    GPIO_DigitalWrite(PORT_A ,0, HIGH);
                    Delay_us(3000);
                    GPIO_DigitalWrite(PORT_A ,0, HIGH);
                    Delay_us(3000);
            }
        }
    }

    return 0;
}
