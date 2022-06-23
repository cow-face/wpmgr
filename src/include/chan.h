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

    struct Reply {
        int no;
        unsigned int tim;
        int w;
        int h;
        std::string ext;
        int fsize;
    };

    std::vector<int> get_threads(std::string board);
    std::vector<Reply> get_replies(std::string board, int thread_id);
};

#endif
