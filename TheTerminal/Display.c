// For LCD Display output [2 rows of 16 characters]

#include <lcd1602.h>
#include <unistd.h>     // posix standards
#include <stdint.h>


// int rc;
// 	rc = lcd1602Init(1, 0x27); // init LCD display
// 	if (rc)
// 	{
// 		printf("Initialization failed; aborting...\n");
// 		return 0;
//	}
// lcd1602WriteString("String to LCD");
// lcd1602SetCursor(0,1);
// lcd1602WriteString("Write 2nd Line");
// lcd1602Control(1,0,1); // backlight on, underline off, blink block on 
// getchar(); // wait for character input to continue
// lcd1602Shutdown(); 


void DisplayMenu(char * str) {
    lcd1602WriteString("Select Mode");
    lcd1602SetCursor(0,1);
    lcd1602WriteString("0 Swipe | 1 Tap");
    lcd1602Control(1,1,1);
}