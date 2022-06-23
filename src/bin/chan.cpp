#include "chan.h"

#include <nlohmann/json.hpp>

Chan::Chan() 
    : http("https://a.4cdn.org/") {
}

/**
 * @brief Gets the current threads from a given board
 *
 * @param board The board to get threads from
 *
 * @return A vector containing the thread numbers from the given board
 */
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
