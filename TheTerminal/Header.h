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
void DisplayMenu(char*);
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
char *trim_whitespace(char *str);
int Cleanup();

/* Server request */
CURLcode Curl (char cardNumber[17], char month[3], char year[5], char pin[5], double transaction);