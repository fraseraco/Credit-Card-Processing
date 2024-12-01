#include "Header.h"

int getAmount() {
    int amt;
    printf("Enter transaction amount: ");
    scanf("%d", &amt);
    return amt;
}

int getPin() {
    int pin;
    printf("Enter pin: ");
    scanf("%d", &pin);
    return pin;
}

char *trim_whitespace(char *str) {
    char *end;

   
    while(isspace((unsigned char)*str)) str++;

  
    if(*str == 0) return str;

     end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    
    *(end+1) = '\0';
    return str;
}
int Cleanup()
{
    // Properly Shutdown LCD Display
    lcd1602Shutdown();
    return 0;
}