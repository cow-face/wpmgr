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
    /**
     * @brief Callback for cURL to provided downloaded data
     * 
     * @param ptr Pointer to buffer containing data
     * @param size Size of data buffer elements
     * @param nmemb Number of elements in data buffer
     * @param userdata Unused
     * @return size_t Number of bytes read
     */
    static size_t write_callback(char *ptr, size_t size, 
                          size_t nmemb, void *userdata);

    
    bool cache_initialized = false;

    /**
     * @brief Create cache directories if needed
     */
    void initialize_cache();
    /**
     * @brief Check to see if the cache contains a file
     * 
     * @param path Path relative to the base URL
     * @return std::time_t Last modified timestamp if cache file exists,
     * otherwise 0
     */
    std::time_t check_cache(std::string path);
    /**
     * @brief Check if on-disk cache is stale via HTTP request
     * 
     * @param path Path relative to the base URL
     * @param cache_timestamp Timestamp of on-disk cache
     * @return true if cache is stale and must be updated,
     * otherwise false
     */
    bool is_stale(std::string path, const std::time_t cache_timestamp);
    /**
     * @brief Perform the actual HTTP request to get data
     * 
     * @param path Path relative to the base URL
     * @return std::string Data received from HTTP request
     */
    std::string fetch_http(std::string path);
    /**
     * @brief Fetch cached data from disk
     * 
     * @param path Path relative to the base URL
     * @return std::string Data read from cache
     */
    std::string fetch_cache(std::string path);
    /**
     * @brief Cache requested data to disk
     * 
     * @param path Path relative to the base URL
     * @param contents Dataq to store in cache
     */
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
