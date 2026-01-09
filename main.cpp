#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
#include <string.h>





// https://wokwi.com/projects/416241646559459329

// PORTB B (digital pin 8 to 13)
// C (analog input pins)
// PORTD D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)



typedef struct{
    int chance[10];
    char* message[10];
    bool active;
} customer;

int main(void){
    init_serial();
    HD44780 lcd;

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD
    //lcd.WriteText((char *)"Hej hej");

    customer Harry = {.chance = {1,2,3,4,5}, .message ={"Honest Harrys Cars", "A good purchase (for Harry!)", "Buy cars at Harrys"}, .active = false};

    customer IoT = {.chance = {6}, .message = "IoT Advertisements", .active = false};

    customer Pete = {.chance = {7,8}, .message = {"Pete will build it for you", "Unauthorised constduction? Call Pete!"}, .active = false};

    customer Anka = {.chance = {9,10,11}, .message = {"Hurry up while stores last", "yummy!"}, .active = false};
    
    customer goofy = {.chance = {12,13,14,15}, .message = {"mysteries? call goofy", "Goofy finds it"}, .active = false};
    

    //blink(Harry.message);
    //blink(IoT.message);



    //lcd.WriteText((char *)"Hej hej");
    //printf("Hej hej\n");

  
    
    //int r = 12;
    //printf("Hej 2 %d\n",r);
    // // //Sätt till INPUT_PULLUP
    // BIT_CLEAR(DDRB,BUTTON_PIN); // INPUT MODE
    // BIT_SET(PORTB,BUTTON_PIN); 

    // DATA DIRECTION = avgör mode
    // om output så skickar vi  1 eller 0 på motsvarande pinne på PORT
    // om input så läser vi  1 eller 0 på motsvarande pinne på PIN
    //bool blinking = false;
    while(1){
        
        //blink(Harry.message[0]);

        //lcd.WriteText((char *)Harry.message[1]);
        //_delay_ms(20000);
        
        scroll(IoT.message[0]);
        
    }
    return 0;
}



