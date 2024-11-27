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

CardInfo getMagData()
{
    CardInfo CC = NULL;
    return CC;
}

CardInfo getRFIDData()
{
    CardInfo CC = NULL;
    return CC;
}