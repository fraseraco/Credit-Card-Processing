#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <lcd1602.h>

#define TESTING true
#ifndef TESTING
#define READMODE ReadMode = getReadMode()
#else
#define READMODE 9
#endif
#define printerr printf
#define log printf
#define display printf 

int main(){

    int ReadMode;
    CardInfo CC;

    if (lcd1602Init(1, 0x27)) { printf("Error Initializing LCD\n\n"); return 0; }
    DisplayMenu("0. Swipe Card \t1. Tap to pay \t2. Test \t9. Dev\n");
    return 0;
    
    switch ( READMODE ) {
        case -1: 
            printerr("Error");
            return 1;
        case 0: // Swipe option
            CC = getMagData();
            break;
        case 1: // Tap option
            CC = getRFIDData();
            break;
        case 9: // Test/Dev option
            
            break;
        default:
        printf("Something has gone horribly wrong");
    }

    // Parse to JSON - Connor's Function
    // SERVER_API();
    

    if(1/*send stuff to server and is valid data*/){
        printf("Payment Accepted\n");        
    }
    else if(0/*send stuff to server and has insufficient funds*/){
        printf("Transaction Declined...\nInsufficient Funds\n");

    }
    else if(0/*send stuff to server and card info is incorrect*/){
        printf("Transaction Declined...\n");

    }



    return 0;
}