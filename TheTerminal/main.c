// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <Header.h>



// int main(){

//     int cardOption;
//     CardInfo CC;
//     printf("0. Swipe Card \t1. Tap to pay \t2. Test \t9. Dev\n");

//     cardOption = getReadMode();
    
//     switch (cardOption) {
//         case 0: // Swipe option
//             CC = getMagData();
//             break;
//         case 1: // Tap option
//             CC = getRFIDData();
//             break;
//         case 9: // Test/Dev option
            
//             break;
//         default:
//         printf("Something has gone horribly wrong");
//     }


    

//     if(/*send stuff to server and is valid data*/){
//         printf("Payment Accepted\n");        
//     }
//     else if(/*send stuff to server and has insufficient funds*/){
//         printf("Transaction Declined...\nInsufficient Funds\n");

//     }
//     else if(/*send stuff to server and card info is incorrect*/){
//         printf("Transaction Declined...\n");

//     }



//     return 0;
// }