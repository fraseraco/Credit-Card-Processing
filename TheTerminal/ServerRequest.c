#include "Header.h"
#include <curl/curl.h>



void Curl (char cardNumber[17], char month[3], char year[5], char pin[5], double transaction) {
    CURL *curl;
    CURLcode res;
    char *postData = malloc(sizeof(char) * 1024);

    // Initialize curl
    curl = curl_easy_init();
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
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_slist_free_all(headers); // free the list of headers
        curl_easy_cleanup(curl);      // clean up curl
    }
    else {
        printf("Failed to initialize curl\n");
    }
}
