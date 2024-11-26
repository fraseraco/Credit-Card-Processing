#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* * * * Card Data * * * */

typedef struct Card {
    char *cardNumber;
    int *cardYear;
    int *cardMonth;
    char *firstName;
    char *middle;
    char *lastName;
} Card;

typedef Card* CardInfo;

/* * * * Card_Data_Parsing.c * * * */

CardInfo Card_Data_Parsing();

/* * * * RawCard.c * * * */
int getReadMode();

/* * * * ParseCard.c * * * */
CardInfo getMagData();

/* * * * Utility.c * * * */
char *trim_whitespace(char *str);
