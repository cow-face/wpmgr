#ifndef CHAN_H
#define CHAN_H

#include <vector>

class Chan {
private:

public:
    Chan();
    std::vector<int> get_threads(std::string board);
}

#endif
