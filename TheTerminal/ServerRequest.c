#include "Header.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}


char* Curl (char cardNumber[17], char month[3], char year[5], char pin[5], double transaction) {
    char *postData = malloc(sizeof(char) * 1024);
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  /* grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */
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

        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_slist_free_all(headers); // free the list of headers
        curl_easy_cleanup(curl);      // clean up curl
        free(postData);

        return chunk.memory;
    }
    else {
        printf("Failed to initialize curl\n");
        return NULL;
    }
}
