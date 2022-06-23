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
    std::vector<int> get_threads(std::string board);
};

#endif
