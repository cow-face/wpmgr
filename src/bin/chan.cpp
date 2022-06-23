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

std::vector<Reply> Chan::get_replies(std::string board, int thread_id) {
    std::string reply_list_json = 
                http.fetch_path(board + "/thread/" +
                std::to_string(thread_id) + ".json");

    std::vector<Reply> replies;

    auto json_response = nlohmann::json::parse(reply_list_json);
    
    for (auto reply : json_response["posts"]) {
        // Parsing for the value 'tim' is weird for some reason
        // It needs to be coerced into a uint64_t
        uint64_t tim;
        if (reply["tim"] != nullptr)
            tim = reply["tim"].get<uint64_t>();

        Reply reply_struct(reply["no"],
                           tim,
                           reply.value("w", 0), 
                           reply.value("h", 0), 
                           reply.value("filename", ""), 
                           reply.value("ext", ""), 
                           reply.value("fsize", 0));

        replies.push_back(reply_struct);
    }

    return replies;
}

Reply::Reply(int no, uint64_t tim, int w, int h, std::string filename, std::string ext, int fsize)
    : no(no),
    tim(tim),
    w(w),
    h(h), 
    filename(filename), 
    ext(ext), 
    fsize(fsize) {

}

bool Reply::has_image() {
    return (tim != 0);
}

bool Reply::check_resolution(int min_width, int min_height) {
    return (w >= min_width && h >= min_height);
}

bool Reply::check_aspect_ratio(double aspect_ratio, double tolerance) {
    double epsilon = aspect_ratio * tolerance;
    double reply_aspect_ratio = (double)w/(double)h;
    return (std::abs(reply_aspect_ratio - aspect_ratio) < epsilon);
}

bool Reply::check_file_ext(std::string extension) {
    return ext == extension;
}
