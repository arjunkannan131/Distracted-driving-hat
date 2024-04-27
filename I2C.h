
#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include <stdint.h>

typedef enum {
    false,
    true
}bool;

void msp430_init(); // Initializing msp
void i2c_init(); // Initializing I2C communication
bool i2c_write_byte(uint8_t byte); // writting byte function
bool i2c_read_addr8_data8(uint8_t addr, uint8_t *data); // reading register data
bool i2c_write_addr8_data8(uint8_t addr, uint8_t data); // writing register function



#endif /* I2C_H_ */
