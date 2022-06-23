#include <ncurses.h>
#include <iostream>
#include <nlohmann/json.hpp>

#include "http.h"
#include "chan.h"

int main() {
    Chan fourchan;
    
    std::vector<int> threads = fourchan.get_threads("w");

    std::vector<Chan::Reply> replies = fourchan.get_replies("w", threads[20]);

    for (Chan::Reply reply : replies) {
        std::cout << reply.no << "\n";
        std::cout << reply.tim << "\n";
    }

    return 0;
}
