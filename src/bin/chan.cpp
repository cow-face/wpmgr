#include "chan.h"

#include <nlohmann/json.hpp>

Chan::Chan() 
    : http("https://a.4cdn.org/") {
}

std::vector<int> Chan::get_threads(std::string board) {
    std::string threadlist_json = http.fetch_path(board + "/threads.json");
       
    std::vector<int> threads;

    auto json_response = nlohmann::json::parse(threadlist_json);

    for (int page = 0; page < json_response.size(); page++) {
        auto cur_page = json_response[page];
        for (int thread = 0; thread < cur_page["threads"].size(); thread++) {
            auto cur_thread = cur_page["threads"][thread];
            threads.push_back(cur_thread["no"]);
        }
    }

    return threads;
}
