#include "chan.h"
#include "ui.h"

#include <iostream>

int main() {
    Chan fourchan;
    
    std::vector<int> threads = fourchan.get_threads("w");

    std::vector<std::string> thread_strs;
    for (int thread : threads) {
        thread_strs.push_back(std::to_string(thread));
    }

    UI::setup_ui();
    UI::setup_menu(thread_strs);
    UI::draw_menu();
    UI::destroy_menu();
    UI::destroy_ui();

    return 0;
}
