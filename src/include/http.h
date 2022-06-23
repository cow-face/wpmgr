#ifndef HTTP_H
#define HTTP_H

#include <string>

#include <cstdint>
#include <ctime>

#include <curl/curl.h>

class HTTP {
private:
    std::string base_url;
    CURL* curl;

    // Static functions for cURL
    inline static uint8_t* dl_buffer;
    inline static size_t dl_buffer_size;
    static size_t write_callback(char *ptr, size_t size, 
                          size_t nmemb, void *userdata);

    bool cache_initialized = false;
    void initialize_cache();
    std::time_t check_cache(std::string path);
    bool is_stale(std::string path, const std::time_t cache_timestamp);
    std::string fetch_http(std::string path);
    std::string fetch_cache(std::string path);
    void save_cache(std::string path, std::string contents);

    const std::string cache_dir = "/tmp/wpmgr";

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
