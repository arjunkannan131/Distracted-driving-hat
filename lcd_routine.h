#ifndef LCD_ROUTINE_H_
#define LCD_ROUTINE_H_

#include <msp430.h>
#include <stdint.h>

void delay_ms(unsigned int ms); // function for delaying
void delay_us(unsigned int us); // function for delaying micro seconds
void data_write(void); // writing data to LCD
void send_data(unsigned char data); // sending data to LCD
void send_string(char *s); // sending string to LCD
void send_command(unsigned char cmd); // sending command
void lcd_init(void); // initializing LCD
void display_time_distracted(int time); // displaying distracted time
void display_starting_message(void); // displaying starting message
void display_calibration_message(void); // displaying calibration message
void display_end_message(int time); // displaying end message



#endif /* LCD_ROUTINE_H_ */

