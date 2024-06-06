#include "convert_seconds_to_time_string.h"

std::string _with_leading_zeros(int x, int zeros) {
	std::string sx = std::to_string(x);
	if (sx.size() >= zeros)
		return sx;
	else
		return std::string(zeros - sx.size(), '0') + sx;
}

std::string convert_seconds_to_time_string(int total_seconds) {
	int hs = total_seconds / (60 * 60);
	total_seconds -= hs * 60 * 60;
	int ms = total_seconds / 60;
	total_seconds -= ms * 60;
	int ss = total_seconds;
	return
		_with_leading_zeros(hs, 2) + ":" + _with_leading_zeros(ms, 2) + ":" + _with_leading_zeros(ss, 2);
}
