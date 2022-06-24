#ifndef CHAN_H
#define CHAN_H

#include "http.h"

#include <vector>
#include <string>

#include <cstdint>

/**
 * @brief A class describing a reply to a thread
 */
class Reply {
private:
    int no;
    uint64_t tim;
    int w;
    int h;
    std::string filename;
    std::string ext;
    int fsize;
public:
    Reply(int no, uint64_t tim, int w, int h, std::string filename, 
          std::string ext, int fsize);
    /**
     * @brief Checks if the given reply contains an image
     *
     * @return True if the reply contains an image, false if it does not
     */
    bool has_image();

    /**
     * @brief Checks if the resolution of the image attached
     * to the given reply is greater than a given minumum
     *
     * @param min_width The minimum width of the image
     * @param min_height The minimum height of the image
     *
     * @return True if both the image width and height
     * are greater than the minimums, false otherwise
     */
    bool check_resolution(int min_width, int min_height);

    /**
     * @brief Checks if the image attached to the given
     * reply conforms to a given aspect ratio
     *
     * @param aspect_ratio The aspect ratio to check against
     * @param tolerance Determines how strict aspect ratio
     * comparisons should be. Given as a percentage of the
     * given aspect ratio (e.g. 0.1)
     *
     * @return True if the difference between the given aspect 
     * ratio and the aspect ratio of the image is less than the
     * absolute value of tolerance*aspect_ratio, false otherwise
     */
    bool check_aspect_ratio(double aspect_ratio, double tolerance);

    /**
     * @brief Checks the file extension of the image
     * attached to the given reply
     *
     * @param extension The file extension to be check against (e.g ".jpg")
     *
     * @return True if the given file extension matches the
     * file extension of the attached image, false otherwise
     */
    bool check_file_ext(std::string extension);

};

class Chan {
private:
    HTTP http;
public:
    Chan();

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
