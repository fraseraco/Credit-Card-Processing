#include "headers.h"

int main(int argc, char **argv) {
    sqlite3 *db;
    int rc = sqlite3_open("creditCardAccount.db", &db);
    const char *cardNumber = "6011 0009 9803 4767";
    int accountId = 1;
    const char *pin = "657";
    const char *expYear = "2024";
    const char *expMonth = "12";
    int testPurchaseTotal = 15;

    returnCode(db, rc);
    
    createTables(db);  
    validateCard(db, testPurchaseTotal, cardNumber, pin, accountId, expYear, expMonth);
    return 0;
}