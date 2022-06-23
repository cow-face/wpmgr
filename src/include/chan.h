#ifndef CHAN_H
#define CHAN_H

#include "http.h"

#include <vector>
#include <string>

#include <cstdint>

class Chan {
private:
    HTTP http;
public:
    Chan();

    /**
     * @brief A data structure describing a reply to a thread
     */
    struct Reply {
        int no;
        uint64_t tim;
        int w;
        int h;
        std::string filename;
        std::string ext;
        int fsize;
    };

    /**
     * @brief Gets the current threads from a given board
     *
     * @param board The board to get threads from
     *
     * @return A vector containing the thread numbers from the given board
     */
    std::vector<int> get_threads(std::string board);
    /**
     * @brief Gets the replies to a given thread on a given board
     *
     * @param board The board the thread is on
     * @param thread_id The ID of the thread to get replies from
     *
     * @return A vector containing the replies to the thread
     */
    std::vector<Reply> get_replies(std::string board, int thread_id);
};

#endif
