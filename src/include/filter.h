#ifndef FILTER_H
#define FILTER_H

#include "chan.h"

#include <string>

/**
 * @brief A class for filtering 4chan replies by criteria
 */
class filter {
private:

public:
	/**
	 * @brief Checks if the given reply contains an image
	 *
	 * @param reply The reply to be checked
	 *
	 * @return True if the reply contains an image, false if it does not
	 */
	bool check_if_image(Chan::Reply reply);

	/**
	 * @brief Checks if the resolution of the image attached
	 * to the given reply is greater than a given minumum
	 *
	 * @param reply The reply to be checked
	 * @param min_width The minimum width of the image
	 * @param min_height The minimum height of the image
	 *
	 * @return True if both the image width and height
	 * are greater than the minimums, false otherwise
	 */
	bool check_resolution(Chan::Reply reply, int min_width, int min_height);

	/**
	 * @brief Checks if the image attached to the given
	 * reply conforms to a given aspect ratio
	 *
	 * @param reply The reply to be checked
	 * @param aspect_ratio The aspect ratio to check against
	 * @param epsilon Determines how strict aspect ratio comparisons should be
	 *
	 * @return True if the difference between the given aspect ratio and
	 * the aspect ratio of the image are less than epsilon, false otherwise
	 */
	bool check_aspect_r(Chan::Reply reply, float aspect_ratio, float epsilon);

	/**
	 * @brief Checks the file extension of the image
	 * attached to the given reply
	 *
	 * @param reply The reply to be checked
	 * @param extension The file extension to be check against (e.g ".jpg")
	 *
	 * @return True if the given file extension matches the
	 * file extension of the attached image, false otherwise
	 */
	bool check_file_ext(Chan::Reply reply, std::string extension);
}