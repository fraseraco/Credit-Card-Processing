#include "Header.h"
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