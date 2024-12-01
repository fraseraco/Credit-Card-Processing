#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>     // posix standards
#include <stdint.h>
#include <lcd1602.h>
#include <curl/curl.h>

/* * * * Card Data * * * */

typedef struct Card {
    char *cardNumber;
    char *cardYear;
    char *cardMonth;
    char *firstName;
    char *middle;
    char *lastName;
} Card;

typedef Card* CardInfo;

/* * * * Card_Data_Parsing.c * * * */
CardInfo Card_Data_Parsing();

/* * * * Display.c * * * */
void DisplayWelcome();
void DisplayMenu(char*);
void PromptAmount();
void DisplayAmount(double);
void PromptSwipe();
void PromptPin();
void DisplayProcessing();
void DisplayApproved();
void DisplayDeclined();
void DisplayInvalidPin();
void DisplayGoodbye();
void CCDump_Name(Card);
void CCDump(CardInfo);
void CCDump_DEBUG(CardInfo);

/* * * * RawCard.c * * * */
int getReadMode();
CardInfo getMagData();
CardInfo getRFIDData();

/* * * * ParseCard.c * * * */


/* * * * Utility.c * * * */
int getAmount();
int getPin();
char *trim_whitespace(char *str);
int Cleanup();

/* Server request */
char* Curl (char cardNumber[17], char month[3], char year[5], char pin[5], double transaction);