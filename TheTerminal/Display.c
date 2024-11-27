// For LCD Display output [2 rows of 16 characters]

#include <lcd1602.h>
#include <unistd.h>     // posix standards
#include <stdint.h>


void DisplayMenu(char * str) {
    lcd1602WriteString("Select Mode");
    lcd1602SetCursor(0,1);
    lcd1602WriteString("0 Swipe | 1 Tap");
    lcd1602Control(1,1,1);
}