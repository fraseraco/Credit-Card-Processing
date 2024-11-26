#include "headers.h"

int main(int argc, char **argv) {
    sqlite3 *db;
    int rc = sqlite3_open("creditCardAccount.db", &db);
    const char *cardNumberD = "4011 5401 0501 9941";
    int accountId = 1;
    const char *pin = "655";
    const char *expYear = "2025";
    const char *expMonth = "07";
    int testPurchaseTotal = 15;

    char card[256] = ""; 
    char *token;
    char cardNumber[16];
    char month[3] = "";
    char year[5] = "";
    char *firstName = NULL;
    char *lastName = NULL;
    char *middle = NULL;
    int flag = 0;
    char *saveptr;
    char *nameString;
    char *nameToken;

    printf("Please swipe your card:\n");

    
    if (fgets(card, sizeof(card), stdin) != NULL) {
      //  printf("Card data: %s\n", card);
      
        token = strtok_r(card, "^",&saveptr);
        
        while( token != NULL ){
           // printf("%s\n", token);
            
          if ( flag == 0 ) {
            char *tempNum = token;
        
             //token is currently 5B/%b/%B + card number 
            for ( int i = 2; i < strlen(tempNum); i ++ ){
               
               cardNumber[i-2] = tempNum[i];
                 }
              cardNumber[strlen(tempNum) - 2] = '\0';
              printf("Card Number: %s\n", cardNumber);
            }     
          else if ( flag == 1 ){
                char temp[100];
                strcpy(temp, token);
                strncpy(temp, token, sizeof(temp) - 1);
                temp[sizeof(temp) - 1] = '\0';
                nameString = strtok(temp, "/");  
                lastName = nameString; 
                printf("Last Name: %s\n", lastName);
                nameString = strtok(NULL, "/");
                nameToken = trim_whitespace(nameString);
           
            for ( int i = 0; i < strlen(nameToken) - 1; i ++){
              
                if( isspace( nameToken[i] ) ){
                    char *firstToken = strtok( nameToken, " " );
                
                    while ( firstToken != NULL ) {
                        firstName = firstToken;
                        firstToken = strtok(NULL, " ");
                        middle = firstToken;
                        firstToken = strtok( NULL, " " );
                    }
                  
                }
                else {
                  firstName = nameToken;
                  middle = "";
                }
            }
            printf("First Name: %s\n", firstName);
            printf("Middle Name: %s\n", middle);
            }

       else if ( flag == 2 ){
            year[0] = '2';
            year[1] = '0';
            year[2] = token[0];
            year[3] = token[1];
            year[4] = '\0';

            month[0] = token[2];
            month[1] = token[3];
            month[2] = '\0';
            
            printf("Month: %s\n", month);
            printf("Year: %s\n", year);
        }
        
         token = strtok_r(NULL, "^", &saveptr);
         flag++;
          
        }
        returnCode(db, rc);
    
        createTables(db);  
        validateCard(db, testPurchaseTotal, (const char *) cardNumber, (const char *) pin, accountId, (const char *) year, (const char *) month);
        // validateCard(db, testPurchaseTotal, cardNumberD, pin, accountId, expYear, expMonth);
        }  
    
    else {
        printf("Failed to read card data.\n");
    }

    return 0;
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