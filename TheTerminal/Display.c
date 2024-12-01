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
		lcd1602Control(1,0,0);  // (backlight, underline, blink block)
}

void PromptAmount() {
		lcd1602Clear();
		lcd1602WriteString("Enter");
		lcd1602SetCursor(0,1); // (ch pos, row pos) starting at 0,0 for first printable space
		lcd1602WriteString("amount: ");
		lcd1602Control(1,0,0);  // (backlight, underline, blink block)
}

void DisplayAmount(double amt) {
	char buff[17];
	sprintf(buff, "$%.2lf", amt);
	lcd1602Clear();
	lcd1602SetCursor(0,0);
	lcd1602WriteString("Amount: ");
	lcd1602SetCursor(0,1); // (ch pos, row pos) starting at 0,0 for first printable space
	lcd1602WriteString(buff);
	sleep(2);
	lcd1602Control(1,0,0);  // (backlight, underline, blink block)
}

void PromptSwipe(){
	lcd1602Clear();
	lcd1602WriteString("Swipe now");
	lcd1602SetCursor(0,1); // (ch pos, row pos) starting at 0,0 for first printable space
	lcd1602WriteString(">>> >>> >>>");
	lcd1602Control(1,0,0);  // (backlight, underline, blink block)
}

void PromptPin(){
	lcd1602Clear();
	lcd1602WriteString("Enter PIN:");
}

void DisplayGoodbye(){
	lcd1602Clear();
	lcd1602SetCursor(0,0);
	lcd1602WriteString("Goodbye...");
	sleep(2);
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

void CCDump(CardInfo CC){
		char buff[17];
		strcpy(buff, "F:");
		strcat(buff, CC->firstName);
		lcd1602Clear();
		lcd1602WriteString(buff);	// writes "F:<firstName>" to LCD
		strcpy(buff, "L:");
		strcat(buff, CC->lastName);
		lcd1602SetCursor(0,1); // (ch pos, row pos) // switch to bottom row // starting at 0,0 for first printable space
		lcd1602WriteString(buff);
		printf("Press Enter to continue:\n");
		getchar();
		lcd1602Clear();
		lcd1602SetCursor(0,0);
		lcd1602WriteString("Card Number");
		lcd1602SetCursor(0,1);
		lcd1602WriteString(CC->cardNumber);
		sleep(1);
		return;
}

void CCDump_DEBUG(CardInfo CC){
		char buff[17];
		strcpy(buff, "F:");
		strcat(buff, CC->firstName);
		printf("%s\n", buff);	// writes "F:<firstName>" to LCD
		strcpy(buff, "L:");
		strcat(buff, CC->lastName);
		printf("%s\n", buff);
		sleep(2);
		printf("Card Number\n");
		printf("%s\n", CC->cardNumber);
		sleep(2);
		return;
}