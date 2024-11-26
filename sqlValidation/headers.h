#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <ctype.h>

int createTables(sqlite3 *db);
int validateCard(sqlite3 *db, int purchaseTotal, const char *cardNumber, const char *pin, int accountId, const char *expYear, const char *expMonth);
int returnCode(sqlite3 *db, int rc);
char *trim_whitespace(char *str);

