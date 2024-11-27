#include <lcd1602.h>
#include <unistd.h>     // posix standards
#include <stdint.h>
#include "Header.h"


// Display menu uses the lcd1602.h driver library
// Below shows basic functions to write to the LCD display
// dimensions: 2 rows of 16 characters
void DisplayMenu(char * str) {
		lcd1602Clear();
		lcd1602WriteString("Select Mode");
		lcd1602SetCursor(0,1); // (ch pos, row pos) starting at 0,0 for first printable space
		lcd1602WriteString("0 Swipe | 1 Tap");
		lcd1602Control(1,0,1);  // (backlight, underline, blink block)
}

void CCDump_Name(Card CC){
		char buff[17];
		strcpy(buff, "F:");
		strcat(buff, CC.firstName);
		lcd1602Clear();
		lcd1602WriteString(buff);
		strcpy(buff, "L:");
		strcat(buff, CC.lastName);
		lcd1602SetCursor(0,1); // (ch pos, row pos) starting at 0,0 for first printable space
		lcd1602WriteString(buff);
		sleep(1.5);
		return;
}

void CCDump(Card CC){
		char buff[17];
		strcpy(buff, "F:");
		strcat(buff, CC.firstName);
		lcd1602Clear();
		lcd1602WriteString(buff);	// writes "F:<firstName>" to LCD
		strcpy(buff, "L:");
		strcat(buff, CC.lastName);
		lcd1602SetCursor(0,1); // (ch pos, row pos) // switch to bottom row // starting at 0,0 for first printable space
		lcd1602WriteString(buff);
		printf("Press Enter to continue:\n");
		getchar();
		lcd1602Clear();
		lcd1602SetCursor(0,0);
		lcd1602WriteString("Card Number");
		lcd1602SetCursor(0,1);
		lcd1602WriteString(CC.cardNumber);
		printf("Press Enter to continue:\n");
		getchar();
		return;
}