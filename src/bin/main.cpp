#include <ncurses.h>
#include <iostream>
#include <nlohmann/json.hpp>

#include "http.h"

int main() {
    HTTP http("https://a.4cdn.org/w/");
    std::string threadlist_json = http.fetch_path("threads.json");
    
    auto json_response = nlohmann::json::parse(threadlist_json);

    for (int page = 0; page < json_response.size(); page++) {
        std::cout << "Page " << page << "\n";
        auto cur_page = json_response[page];
        for (int thread = 0; thread < cur_page["threads"].size(); thread++) {
            auto cur_thread = cur_page["threads"][thread];
            std::cout << cur_thread["no"] << "\n";
        }
    }

    return 0;
}
