#include "Header.h"




CURLcode Curl (char cardNumber[17], char month[3], char year[5], char pin[5], double transaction) {
    char *postData = malloc(sizeof(char) * 1024);

    // Initialize curl
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/");

        // Specify the POST data
        sprintf(postData,
            "{\"creditCardNumber\": \"%s\","
            "\"pin\": \"%s\","
            "\"transactionAmount\": %.2f,"
            "\"expirationMonth\": \"%s\","
            "\"expirationYear\": \"%s\""
            "}"
        ,cardNumber, pin, transaction, month, year);

        // Set the POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

        // Set the Content-Type header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);


        // Clean up
        curl_slist_free_all(headers); // free the list of headers
        curl_easy_cleanup(curl);      // clean up curl
        free(postData);

        return res;
    }
    else {
        printf("Failed to initialize curl\n");
        return -1;
    }
}
