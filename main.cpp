#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>



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





class customer{
    public:
        int chance[10];
        char* message[10];
        bool active;
};

int main(void){
    init_serial();
    HD44780 lcd;

    lcd.Initialize(); // Initialize the LCD
    lcd.Clear();      // Clear the LCD
    //lcd.WriteText((char *)"Hej hej");

    customer Harry = {.chance = {1,2,3,4,5}, .message ={"Buy cars at Harrys","A good purchase (for Harry!)","Honest Harrys Cars" }, .active = false};

    customer IoT = {.chance = {6}, .message = "IoT Advertisements", .active = false};

    customer Pete = {.chance = {7,8}, .message = {"Pete will build it for you", "Unauthorised constduction? Call Pete!"}, .active = false};

    customer Duck = {.chance = {9,10,11}, .message = {"Buy pies from Grandma Duck", "Hurry up while pies remain"}, .active = false};
    
    customer Goofy = {.chance = {12,13,14,15}, .message = {"mysteries? call goofy", "Goofy finds it"}, .active = false};
    
    int random_number = rand() % 15 + 1; // 1 to 15

    while(1){
        lcd.Clear();
        
        if (Harry.active == true){
            random_number = rand() % 15 + 6; // 6 to 15
            Harry.active = (false);
        }
        if (IoT.active == true){
            do{
                random_number = rand() % 15 + 1; // 7 to 15
            } while (random_number == 6);
            IoT.active = (false);
        }
        if (Pete.active == true){
            do{
                random_number = rand() % 15 + 1; // 9 to 15
            } while (random_number == 7 || random_number == 8);
            Pete.active = (false);
        }
        if (Duck.active == true){
            do{
                random_number = rand() % 15 + 1; // 12 to 15
            } while (random_number >= 9 && random_number <=11);
            Duck.active = (false);
        }
        if (Goofy.active == true){
            random_number = rand() % 11 + 1; // 1 to 11
            Goofy.active = (false);
        }
        
        
        if (random_number >= 1 && random_number <= 5) {
            Harry.active = (true);
        } else if (random_number == 6) {
            IoT.active = (true);
        } else if (random_number >= 7 && random_number <= 8) {
            Pete.active = (true);
        } else if (random_number >= 9 && random_number <= 11) {
            Duck.active = (true);
        } else if (random_number >= 12 && random_number <= 15) {
            Goofy.active = (true);
        }

        if (Harry.active = (true)) {
            int temp = rand() % 3;
            if (temp == 0){
                scroll(Harry.message[0]);
            }
            else if (temp == 1){
                print(Harry.message[1]);
            }
            else if (temp == 2){
                blink(Harry.message[2]);
            }
            Harry.active = (false);
        }

        if (Duck.active = (true)) {
            int temp = rand() % 2;
            if (temp == 0){
                scroll(Duck.message[0]);
            }
            else if (temp == 1){
                print(Duck.message[1]);
            }
            Duck.active = (false);
        }

        if (Goofy.active = (true)) {
            int temp = rand() % 2;
            if (temp == 0){
                scroll(Goofy.message[0]);
            }
            else if (temp == 1){
                blink(Goofy.message[1]);
            }
            Goofy.active = (false);
        }

        if (IoT.active = (true)) {
            print(IoT.message[0]);
            IoT.active = (false);
        }

        if (Pete.active = (true)) {
            time_t t = time(0);

            tm *ltm = localtime(&t);
            if (ltm->tm_min % 2 == 0){
                scroll(Pete.message[0]);
            }
            else{ 
                print(Pete.message[1]);
            }
            Pete.active = (false);
        }
    }
    return 0;
}



