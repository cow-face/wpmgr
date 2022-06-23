#ifndef HTTP_H
#define HTTP_H

#include <string>

#include <cstdint>

#include <curl/curl.h>

class HTTP {
private:
    std::string base_url;
    CURL* curl;

    inline static uint8_t* dl_buffer;
    inline static size_t dl_buffer_size;
    static size_t write_callback(char *ptr, size_t size, 
                          size_t nmemb, void *userdata);
public:
    /**
    * @brief Constructor for the HTTP class
    * 
    * @details Initializes the download buffer and cURL
    *
    * @param base_url The base url to which
    * requests will be made
    */ 
    HTTP(std::string base_url);
    
    /**
     * @brief Fetches data from a given path
     *
     * @details Also empties the download buffer to be used again
     *
     * @param path The URL of the data to be fetched from,
     * relative to the base path
     *
     * @return The data from the URL
     */
    std::string fetch_path(std::string path);
};

#endif
