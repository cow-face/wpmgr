#include "http.h"

HTTP::HTTP(std::string base_url) 
    : base_url(base_url) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HTTP::get_path(std::string path) {
    
}
