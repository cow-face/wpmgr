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

std::vector<Chan::Reply> Chan::get_replies(std::string board, int thread_id) {
    std::string reply_list_json = 
                http.fetch_path(board + "/thread/" +
                std::to_string(thread_id) + ".json");

    std::vector<Chan::Reply> replies;

    auto json_response = nlohmann::json::parse(reply_list_json);
    
    for (auto reply : json_response["posts"]) {
        Reply reply_struct = { 0 };
        reply_struct.no = reply["no"];
        reply_struct.tim = reply.value("tim", 0);
        reply_struct.w = reply.value("w", 0);
        reply_struct.h = reply.value("h", 0);
        reply_struct.ext = reply.value("ext", "");
        reply_struct.fsize = reply.value("fsize", 0);

        replies.push_back(reply_struct);
    }

    return replies;
}
