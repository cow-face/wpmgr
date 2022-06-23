#include <ncurses.h>
#include <iostream>

#include "http.h"
#include "chan.h"

int main() {
    Chan fourchan;
    
    std::vector<int> threads = fourchan.get_threads("w");

    std::vector<std::string> thread_strs;
    for (int thread : threads) {
        thread_strs.push_back(std::to_string(thread));
    }

    return 0;
}
