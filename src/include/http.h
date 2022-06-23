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
    HTTP(std::string base_url);
    std::string fetch_path(std::string path);
};

#endif
