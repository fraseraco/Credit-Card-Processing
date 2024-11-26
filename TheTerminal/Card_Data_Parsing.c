#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

char *trim_whitespace(char *str) {
    char *end;

   
    while(isspace((unsigned char)*str)) str++;

  
    if(*str == 0) return str;

     end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    
    *(end+1) = '\0';
    return str;
}


int main() {
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
    
    int cardYear = 0;
    int cardMonth = 0;
    int currentYear; 
    int currentMonth;
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    //print for debugging
    printf("%s", asctime(ptr));

    currentYear = ptr->tm_year + 1900;
    currentMonth = ptr->tm_mon + 1;
    
    printf("Please swipe your card:\n");

    
    if (fgets(card, sizeof(card), stdin) != NULL) {
      //  printf("Card data: %s\n", card);
      
        token = strtok_r(card, "^",&saveptr);
        
        while( token != NULL ){
           
            
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
                //print for debugging
                printf("Last Name: %s\n", lastName);
               nameString = strtok(NULL, "/");
                   nameToken = trim_whitespace(nameString);
           
            for ( int i = 0; i < strlen(nameToken) - 1; i ++){
              
                if( isspace( nameToken[i] ) ){
                    char *firstToken = strtok( nameToken, " " );
                
                    while ( firstToken != NULL ){
                       firstName = firstToken;
                        firstToken = strtok(NULL, " ");
                        
                       middle = firstToken;

                    firstToken = strtok( NULL, " " );
                  
                      }
                  
                }
                else{
                  firstName = nameToken;
                  middle = "";
                }
               
                
               }
                //print for debugging
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
            
            cardYear = atoi(year);
            cardMonth = atoi(month);

            
            printf("Month: %d\n", cardMonth);
            printf("Year: %d\n", cardYear);

            }
        
         token = strtok_r(NULL, "^", &saveptr);
         flag++;
          
        }
        }  
    
    else {
        printf("Failed to read card data.\n");
    }

    if ( cardYear < currentYear ){

      printf("Card is expired, please present different form of payment\n");
    }
    else if( cardYear == currentYear && cardMonth < currentMonth ){
      printf("Card is expired, please present different form of payment\n");
     }
    else{
      printf("Processing...\n");
    }
    

    return 0;

}