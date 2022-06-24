#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

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

    // TODO: The cache functions use the relative path which includes the board
    // needs its own subdir in the cache directory... for now everything is
    // hardcoded to /w/ so we will hardcode it here too, but that needs to
    // change in the near future

    const std::string board_cache_dir = cache_dir + "/w";
    if (stat(board_cache_dir.c_str(), &st) == -1) {
        mkdir(board_cache_dir.c_str(), 0755);
    }

    const std::string thread_cache_dir = board_cache_dir + "/thread";
    if (stat(thread_cache_dir.c_str(), &st) == -1) {
        mkdir(thread_cache_dir.c_str(), 0755);
    }

    cache_initialized = true;
}

std::time_t HTTP::check_cache(std::string path) {
    struct stat st = { 0 };
    const std::string cache_file_path = cache_dir + "/" + path; 
    if (stat(cache_file_path.c_str(), &st) == -1) {
        return 0; 
    }
    
    return (std::time_t) st.st_mtim.tv_sec;
}

bool HTTP::fetch_if_stale(std::string path, const std::time_t cache_timestamp) {
    const std::string http_header = "If-Modified-Since: " +
                                    unix_time_to_http(cache_timestamp);
    const std::string full_path = base_url + path;

    CURLcode res;
    long response_code;

    if(curl) {
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, http_header.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_URL, full_path.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTP::write_callback);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            // cURL error...
            response_code = 0;
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        }

        /* always cleanup */
        // TODO: fix segfault
        //curl_easy_cleanup(curl);
 
        /* free the custom headers */
        curl_slist_free_all(chunk);
    }

    std::string result((char*) HTTP::dl_buffer, HTTP::dl_buffer_size);
    free(HTTP::dl_buffer); // free on nullptr is nop
    
    HTTP::dl_buffer = nullptr;
    HTTP::dl_buffer_size = 0;

    if (response_code == 200) {
        save_cache(path, result);
        return true;
    }

    return false;
}

std::string HTTP::fetch_cache(std::string path) {
    std::string full_path = cache_dir + "/" + path;
    std::cout << "Reading cache from " << full_path << "\n";
    std::ifstream t(full_path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    return buffer.str();
}

void HTTP::save_cache(std::string path, std::string contents) {
    const std::string full_path = cache_dir + "/" + path;
    std::cout << "Writing cache to " << full_path << "\n";
    std::ofstream out(full_path);
    out << contents;
    out.close();
}

std::string HTTP::unix_time_to_http(const std::time_t time) {
    std::tm* broken_time = gmtime(&time);
    std::string formatted_time = "";

    char str_buffer[250];
    strftime(str_buffer, 250, "%a, %d %b %Y %T %Z", broken_time);
    std::string cpp_str = str_buffer;

    return cpp_str;
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

    fetch_if_stale(path, cache_timestamp);
    return fetch_cache(path);
}
