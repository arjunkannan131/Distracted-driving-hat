
// Author: Arjun K. and Liam W.

#include <msp430g2553.h>

#include <stdio.h>

// define RS high
#define DR P2OUT = P2OUT | BIT0

// define RS low
#define CR P2OUT = P2OUT & (~BIT0)

// define Read signal R/W = 1 for reading
#define READ P2OUT = P2OUT | BIT1

// define Write signal R/W = 0 for writing
#define WRITE P2OUT = P2OUT & (~BIT1)

// define Enable high signal
#define ENABLE_HIGH P2OUT = P2OUT | BIT2

// define Enable Low signal
#define ENABLE_LOW P2OUT = P2OUT & (~BIT2)

void delay_us(unsigned int us)

{

  while (us)

  {

    // 1 for 1 Mhz set 16 for 16 MHz

    __delay_cycles(1);

    us--;

  }

}


void delay_ms(unsigned int ms)

{

  while (ms)

  {

    // 1000 for 1MHz and 16000 for 16MHz

    __delay_cycles(1000);

    ms--;

  }

}



void data_write(void)

{

  ENABLE_HIGH;

  delay_ms(5);

  ENABLE_LOW;

}



void send_data(unsigned char data)

{

  unsigned char higher_nibble = 0xF0 & (data);

  unsigned char lower_nibble = 0xF0 & (data << 4);



  delay_us(200);



  WRITE;

  DR;



  // send higher nibble

  P2OUT = (P2OUT & 0x0F) | (higher_nibble);

  data_write();



  // send lower nibble

  P2OUT = (P2OUT & 0x0F) | (lower_nibble);

  data_write();

}



void send_string(char *s)

{

  while(*s)

  {

    send_data(*s);

    s++;

  }

}



void send_command(unsigned char cmd)

{

  unsigned char higher_nibble = 0xF0 & (cmd);

  unsigned char lower_nibble = 0xF0 & (cmd << 4);



  WRITE;

  CR;



  // send higher nibble

  P2OUT = (P2OUT & 0x0F) | (higher_nibble);

  data_write();



  // send lower nibble

  P2OUT = (P2OUT & 0x0F) | (lower_nibble);

  data_write();

}





void lcd_init(void)

{

  P2DIR |= 0xF7;

  P2OUT &= 0x00;



  delay_ms(15);

  send_command(0x33);



  delay_us(200);

  send_command(0x32);



  delay_us(40);

  send_command(0x28); // 4 bit mode



  delay_us(40);

  send_command(0x0E); // clear the screen



  delay_us(40);

  send_command(0x01); // display on cursor on



  delay_us(40);

  send_command(0x06); // increment cursor



  delay_us(40);

  send_command(0x80); // row 1 column 1



}


void display_time_distracted(int time) {

    char buffer[6]; // Buffer to hold the string representation of the integer

    int minutes = time / 60;

    int seconds = time % 60;



    // Format the time as "MM:SS"

    buffer[0] = '0' + (minutes / 10); // Tens digit of minutes

    buffer[1] = '0' + (minutes % 10); // Ones digit of minutes

    buffer[2] = ':';

    buffer[3] = '0' + (seconds / 10); // Tens digit of seconds

    buffer[4] = '0' + (seconds % 10); // Ones digit of seconds

    buffer[5] = '\0'; // Null terminator



    send_string("Time Distracted:");

    send_command(0xC0); // Move cursor to the second line

    send_string(buffer); // Display the time
}

void display_starting_message(){
    send_string("Press Button");
}

void display_calibration_message(){
    send_string("Please calibrate");
}

void display_end_message(int time){

    char buffer[6]; // Buffer to hold the string representation of the integer

    int minutes = time / 60;

    int seconds = time % 60;



    // Format the time as "MM:SS"

    buffer[0] = '0' + (minutes / 10); // Tens digit of minutes

    buffer[1] = '0' + (minutes % 10); // Ones digit of minutes

    buffer[2] = ':';

    buffer[3] = '0' + (seconds / 10); // Tens digit of seconds

    buffer[4] = '0' + (seconds % 10); // Ones digit of seconds

    buffer[5] = '\0'; // Null terminator



    send_string("Total Time:");

    send_command(0xC0); // Move cursor to the second line

    send_string(buffer); // Display the time
}
