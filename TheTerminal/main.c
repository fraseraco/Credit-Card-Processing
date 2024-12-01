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
// #define DisplayMenu printf
#define CCDump CCDump_DEBUG
#endif
#define printerr printf
#define log printf
#define display printf 

int main(){

	int ReadMode, pin = 0000;
	double transactionAmount = 0.0;
	Card CC_test = {"4242424242424242", "2025", "03", "Bob", "L", "Oblaw"};
	CardInfo ccInfo;
	if (lcd1602Init(1, 0x27)) { printf("Error Initializing LCD\n\n"); return 0; }
	
	PromptAmount();
	transactionAmount = getAmount();

	DisplayAmount(transactionAmount);


	
	//DisplayMenu("0. Swipe Card \t1. Tap to pay \t2. Test \t9. Dev\n");
	
	// printf("Press Enter to continue\n");
	// getchar();
	
	switch ( 9 ) {
		case -1: 
			printerr("Error");
			return 1;
		case 0: // Swipe option
			PromptSwipe();
			ccInfo = getMagData();
			break;
		case 1: // Tap option
			ccInfo = getRFIDData();
			break;
		case 9: // Test/Dev option
			ccInfo = &CC_test;
			break;
		default:
		printf("Something has gone horribly wrong");
	}

	// Get pin()
	PromptPin();
	pin = getPin();
	// pin = 756;
	// Perform local validations - expiration, checksum
	

	// dump CC info to LCD
	CCDump(ccInfo);

	// Parse to JSON - Connor's Function
	// SERVER_API();
	// Process response
	char pinString[5];
	sprintf(pinString, "%d", pin);
	char* res = Curl(ccInfo->cardNumber, ccInfo->cardMonth, ccInfo->cardYear, pinString, transactionAmount);

	if (res == NULL) {
		printf("ERROR: server response NULL");
	}

	if (strstr(res, "Approved")) {
		printf("Transaction Approved\n");
		DisplayApproved();
	}
	else {
		printf("Transaction Declined\n");
	}
	

	DisplayGoodbye();
	Cleanup();
	return 0;
}