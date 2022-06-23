#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "http.h"

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

    for (unsigned int i = 0; i < bytes; i++) {
        HTTP::dl_buffer[HTTP::dl_buffer_size + i] = ptr[i];
    }
    
    HTTP::dl_buffer_size += bytes;
    
    return bytes;
}

void HTTP::initialize_cache() {
    struct stat st = { 0 };
    if (stat(cache_dir.c_str(), &st) == -1) {
        mkdir(cache_dir.c_str(), 0755);
    }

    cache_initialized = true;
}

std::time_t HTTP::check_cache(std::string path) {
    struct stat st = { 0 };
    const std::string cache_file_path = cache_dir + "/" + path; 
    std::cout << cache_file_path << "\n";
    if (stat(cache_file_path.c_str(), &st) == -1) {
        return 0; 
    }
    
    return (std::time_t) st.st_mtim.tv_sec;
}

bool HTTP::is_stale(std::string path, const std::time_t cache_timestamp) {
    // TODO: check via http if cache timestamp is stale
    return true;
}

std::string HTTP::fetch_cache(std::string path) {
    // TODO: fetch cache off disk
    return "";
}

void HTTP::save_cache(std::string path, std::string contents) {
    // TODO: save response to disk
    return;
}

std::string HTTP::fetch_http(std::string path) {
    CURLcode res;
    if (curl) {
        const std::string full_path = base_url + path;
        curl_easy_setopt(curl, CURLOPT_URL, full_path.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTP::write_callback);
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        /* always cleanup */
        // TODO: figure out why this segfaults
        //curl_easy_cleanup(curl);
    }
    std::string result((char*) HTTP::dl_buffer, HTTP::dl_buffer_size);
    free(HTTP::dl_buffer); // free on nullptr is nop
    
    HTTP::dl_buffer = nullptr;
    HTTP::dl_buffer_size = 0;
 
    return result;
}

std::string HTTP::fetch_path(std::string path) {
    if (!cache_initialized)
        initialize_cache();

    const std::time_t cache_timestamp = check_cache(path);
   
    std::cout << cache_timestamp << "\n";

    if (is_stale(path, cache_timestamp)) {
        std::string result = fetch_http(path);
        save_cache(path, result);
        return result;
    }
    
    return fetch_cache(path);
}
