#include "headers.h"

int createTables(sqlite3 *db) {
    char *err_msg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS CUSTOMER("
	"Account_id	INTEGER UNIQUE,"
	"First_name	TEXT,"
	"Last_name	TEXT,"
	"PRIMARY KEY(Account_id AUTOINCREMENT)"
    ");";
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    returnCode(db, rc);

    char *sql2 = "CREATE TABLE IF NOT EXISTS CARDS("
	"Account_id	INTEGER,"
	"Card_num	TEXT,"
	"Pin	TEXT,"
	"Balance	INTEGER DEFAULT 0,"
	"Exp_month	TEXT,"
	"Exp_year	TEXT,"
	"PRIMARY KEY(Card_num),"
	"FOREIGN KEY(Account_id) REFERENCES CUSTOMER(Account_id)"
    ");";

    rc = sqlite3_exec(db, sql2, 0, 0, &err_msg);

    returnCode(db, rc);

    sqlite3_close(db);

    return 0;
}

int validateCard(sqlite3 *db, int purchaseTotal, const char *cardNumber, const char *pin, int accountId, const char *expYear, const char *expMonth) {
    char *err_msg = 0;
    char parsedNum[17];
    int validCardFlag = 0;
    int validTransactionFlag = 0;
    int currentBalance = 0;
    int j = 0;
    const char *balanceUpdateSql = "UPDATE CARDS SET Balance = ? WHERE Card_num = ?";
    char *sql = "SELECT * FROM CARDS WHERE Card_num = ? AND Account_id = ? AND Pin = ? AND Exp_month = ? AND Exp_year = ?";   


    int rc = sqlite3_open("creditCardAccount.db", &db);

    returnCode(db, rc);

    sqlite3_stmt *stmt;

    //Honestly we probably don't need this but if we need to convert the card to an int
    //to make comparisons easier/ harder (lol) I have this here.
    for(int i = 0; i < strlen(cardNumber); i++) {
        if(cardNumber[i] != ' '){
            parsedNum[j++] = cardNumber[i]; //only appending if the space is not a space
        }
    }
    parsedNum[j] = '\0'; //null terminating manually 

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_bind_text(stmt, 1, cardNumber, -1, SQLITE_STATIC);
    returnCode(db, rc);
    rc = sqlite3_bind_int(stmt, 2, accountId);
    returnCode(db, rc);
    rc = sqlite3_bind_text(stmt, 3, pin, -1, SQLITE_STATIC);
    returnCode(db, rc);
    rc = sqlite3_bind_text(stmt, 4, expMonth, -1, SQLITE_STATIC);
    returnCode(db, rc);
    rc = sqlite3_bind_text(stmt, 5, expYear, -1, SQLITE_STATIC);
    returnCode(db, rc);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        currentBalance = sqlite3_column_int(stmt,3);
        if(currentBalance < purchaseTotal){
            printf("Error: Cannot overdraft/ Balance is too low for the purchase\n");    
        } else {
            validTransactionFlag += 1;
        }
        const char *cardNum = (const char *) sqlite3_column_text(stmt,1);
        if(!strcmp(cardNum, cardNumber)) { //Checking if the cardNum queried and cardNumber provided match
            printf("%s is a valid card number \n", cardNumber);
            validCardFlag += 1;
        } 
    }

    //Check flag state
    if(validCardFlag > 0 && validTransactionFlag > 0) {
        printf("Successful validation\n");
        sqlite3_stmt *localStmt;
        int updatedBalance = 0;
        updatedBalance = currentBalance - purchaseTotal;
        rc = sqlite3_prepare_v2(db, balanceUpdateSql, -1, &stmt, 0);
        returnCode(db, rc);
        rc = sqlite3_bind_int(stmt, 1, updatedBalance);
        returnCode(db, rc);
        rc = sqlite3_bind_text(stmt, 2, cardNumber, -1, SQLITE_STATIC);
        returnCode(db, rc);
        rc = sqlite3_step(stmt);
        printf("Success: Account balance was successfully updated from %d to %d\n", currentBalance, updatedBalance);
    }

    return 0;
}

int returnCode(sqlite3 *db, int rc) {
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }
    return 0;
}