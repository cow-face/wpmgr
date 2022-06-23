#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "http.h"

/**
 * @brief Constructor for the HTTP class
 * 
 * @details Initializes the download buffer and cURL
 *
 * @param base_url The base url to which
 * requests will be made
 */
HTTP::HTTP(std::string base_url) 
    : base_url(base_url) {
    HTTP::dl_buffer = nullptr;
    HTTP::dl_buffer_size = 0;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();    
}

size_t HTTP::write_callback(char* ptr, size_t size,
                            size_t nmemb, void* userdata) {
    size_t bytes = size * nmemb;
    
    if (!HTTP::dl_buffer)
        HTTP::dl_buffer = (uint8_t*) malloc(bytes);
    else
        HTTP::dl_buffer = (uint8_t*) realloc(HTTP::dl_buffer,
                                  HTTP::dl_buffer_size + bytes);

    for (int i = 0; i < bytes; i++) {
        HTTP::dl_buffer[HTTP::dl_buffer_size + i] = ptr[i];
    }
    
    HTTP::dl_buffer_size += bytes;
    
    return bytes;
}

/**
 * @brief Fetches data from a given path
 * 
 * @details Also empties the download buffer to be used again
 *
 * @param path The url the data is to be 
 * fetched from relative to the base path
 *
 * @return The data from the url
 */
std::string HTTP::fetch_path(std::string path) {
    CURLcode res;
    if (curl) {
        std::string full_path = base_url + path;
        curl_easy_setopt(curl, CURLOPT_URL, full_path.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTP::write_callback);
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        /* always cleanup */
        //curl_easy_cleanup(curl);
    }
    std::string result((char*) HTTP::dl_buffer, HTTP::dl_buffer_size);
    free(HTTP::dl_buffer); // free on nullptr is nop
    
    HTTP::dl_buffer = nullptr;
    HTTP::dl_buffer_size = 0;
    
    return result;
}
