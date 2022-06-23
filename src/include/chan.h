#ifndef CHAN_H
#define CHAN_H

#include "http.h"

#include <vector>
#include <string>

class Chan {
private:
    HTTP http;
public:
    Chan();

    /**
     * @breif Gets the current threads from a given board
     *
     * @param board The board to get threads from
     *
     * @return A vector containing the thread numbers from the given board
     */
    std::vector<int> get_threads(std::string board);
};

#endif
