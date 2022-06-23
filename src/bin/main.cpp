#include <ncurses.h>
#include <iostream>

#include "http.h"
#include "chan.h"

int main() {
    Chan fourchan;
    
    std::vector<int> threads = fourchan.get_threads("w");

    std::vector<Chan::Reply> replies = fourchan.get_replies("w", threads[20]);

    for (Chan::Reply reply : replies) {
        std::cout << reply.no << "\n";
        std::cout << reply.tim << reply.ext << "\n";
        std::cout << reply.w << "x" << reply.h << "\n";
    }

    return 0;
}
