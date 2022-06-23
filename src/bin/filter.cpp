#include "filter.h"

#include <cstdlib>

bool has_image(Chan::Reply reply) {
	if (reply.tim != 0) {
		return true;
	}
	return false;
}

bool check_resolution(Chan::Reply reply, int min_width, int min_height) {
	if (reply.w >= min_width && reply.h >= min_height) {
		return true;
	}
	return false;
}

bool check_aspect_ratio(Chan::Reply reply, double aspect_ratio, double tolerance) {
	double epsilon = aspect_ratio * tolerance;
	double reply_aspect_ratio = static_cast<double>(reply.w)/reply.h;
	if (std::abs(reply_aspect_ratio - aspect_ratio) < epsilon) {
		return true;
	}
	return false;
}

bool check_file_ext(Chan::Reply reply, std::string extension) {
	if (reply.ext == extension) {
		return true;
	}
	return false;
}