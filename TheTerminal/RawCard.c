#include "Header.h"
// Get read mode (using stdin)
// 0 - Magstripe
// 1 - Tap to Pay
// 9 - Test or Dev Mode
int getReadMode(){
    int in;
    printf("Enter reader mode: ");
    scanf("%d", &in);
    return in;
}

CardInfo getMagData() {
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
    //print for debuggingCardInfo cardInfo;
    //printf("%s", asctime(ptr));

    currentYear = ptr->tm_year + 1900;
    currentMonth = ptr->tm_mon + 1;
    
    //printf("Please swipe your card:\n");

    
    if (fgets(card, sizeof(card), stdin) != NULL) {
      //printf("Card data: %s\n", card);
      
        token = strtok_r(card, "^",&saveptr);
        
        while( token != NULL ){
           
            
          if ( flag == 0 ) {
            char *tempNum = token;
        
             //token is currently 5B/%b/%B + card number 
            for ( int i = 2; i < strlen(tempNum); i ++ ){
               
               cardNumber[i-2] = tempNum[i];
                 }
              cardNumber[strlen(tempNum) - 2] = '\0';
              //printf("Card Number: %s\n", cardNumber);
              
            }
            
          else if ( flag == 1 ){

            char temp[100];
            strcpy(temp, token);
         
             strncpy(temp, token, sizeof(temp) - 1);
                temp[sizeof(temp) - 1] = '\0';
                nameString = strtok(temp, "/");  
            
            
             
              lastName = nameString; 
                //print for debugging
               
                //printf("Last Name: %s\n", lastName);
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
                //printf("First Name: %s\n", firstName);
                //printf("Middle Name: %s\n", middle);
                  
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
          
          //printf("Month: %d\n", cardMonth);
          //printf("Year: %d\n", cardYear);

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
  return CreateCardInfo(cardNumber, cardYear, cardMonth, firstName, middle, lastName);

}

CardInfo CreateCardInfo(char* number, char* year, char* month, char* fName, char* mid, char* lName) {
    CardInfo cardInfo = malloc(sizeof(Card));
    cardInfo->cardNumber = malloc(sizeof(char) * ( strlen(number) + 1));
    cardInfo->cardYear = malloc(sizeof(char) * 5);
    cardInfo->cardMonth = malloc(sizeof(char) * 3);
    cardInfo->firstName = malloc(sizeof(char) * (strlen(fName) +1));
    cardInfo->middle = malloc(sizeof(char) * (strlen(mid)+1));
    cardInfo->lastName = malloc(sizeof(char) * (strlen(lName)+1));
    
    return cardInfo;
}

void FreeCard(CardInfo cc) {
	free(cc->cardNumber);
	free(cc->cardYear);
	free(cc->cardMonth);
	free(cc->firstName);
	free(cc->middle);
	free(cc->lastName);
	free(cc);
}

CardInfo getRFIDData()
{
    CardInfo CC = NULL;
    return CC;
}