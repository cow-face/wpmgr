#include <ncurses.h>
#include <iostream>
#include <nlohmann/json.hpp>

#include "http.h"
#include "chan.h"

int main() {
    Chan fourchan;
    std::vector<int> threads = fourchan.get_threads("w");
    for (int i = 0; i < threads.size(); i++) {
        std::cout << threads[i] << "\n";
    }

    return 0;
}
