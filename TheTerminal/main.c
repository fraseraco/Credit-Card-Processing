#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <lcd1602.h>

#define TESTING true
#ifndef TESTING
#define READMODE ReadMode = getReadMode()
#else
#define TESTMODE LCD		// Allows testing of LCD
#define READMODE 9
#define DisplayMenu printf
#define CCDump CCDump_DEBUG
#endif
#define printerr printf
#define log printf
#define display printf 

int main(){

	int ReadMode, pin = 0000;
	Card CC_test = {"1234555566667788", "2000", "01", "Bob", "L", "Oblaw"};
	CardInfo ccInfo;

	if (lcd1602Init(1, 0x27)) { printf("Error Initializing LCD\n\n"); return 0; }
	DisplayMenu("0. Swipe Card \t1. Tap to pay \t2. Test \t9. Dev\n");
	
	printf("Testing LCD Display.\nPress Enter to continue: ");
	getchar();
	
	switch ( READMODE ) {
		case -1: 
			printerr("Error");
			return 1;
		case 0: // Swipe option
			ccInfo = getMagData();
			break;
		case 1: // Tap option
			ccInfo = getRFIDData();
			break;
		case 9: // Test/Dev option
			ccInfo = &CC_test;
			pin = 1234;
			break;
		default:
		printf("Something has gone horribly wrong");
	}

	// Get pin
	// Perform local validations - expiration, checksum
	

	// dump CC info to LCD
	CCDump(ccInfo);

	// Parse to JSON - Connor's Function
	// SERVER_API();
	// Process response
	

	if(1/*send stuff to server and is valid data*/){
		printf("Payment Accepted\n");        
	}
	else if(0/*send stuff to server and has insufficient funds*/){
		printf("Transaction Declined...\nInsufficient Funds\n");

	}
	else if(0/*send stuff to server and card info is incorrect*/){
		printf("Transaction Declined...\n");

	}

	DisplayGoodbye();
	Cleanup();
	return 0;
}