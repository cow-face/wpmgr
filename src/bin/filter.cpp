#include "filter.h"

#include <cstdlib>

bool has_image(Chan::Reply reply) {
	return (reply.tim != 0);
}

bool check_resolution(Chan::Reply reply, int min_width, int min_height) {
	return (reply.w >= min_width && reply.h >= min_height);
}

bool check_aspect_ratio(Chan::Reply reply, double aspect_ratio, double tolerance) {
	double epsilon = aspect_ratio * tolerance;
	double reply_aspect_ratio = (double)reply.w/(double)reply.h;
	return (std::abs(reply_aspect_ratio - aspect_ratio) < epsilon);
}

bool check_file_ext(Chan::Reply reply, std::string extension) {
	return reply.ext == extension;
}