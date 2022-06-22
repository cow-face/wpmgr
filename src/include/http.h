#ifndef HTTP_H
#define HTTP_H

#include <string>

#include <curl/curl.h>

class HTTP {
private:
    std::string base_url;
    CURL* curl;
public:
    HTTP(std::string base_url);
    get_path(std::string path);
};

#endif
