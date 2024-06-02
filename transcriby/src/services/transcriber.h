#pragma once

#include <string>

#include "core/playlist.h"

namespace transcriby {
	class TranscriberService {
	public:
		TranscriberService();
		std::string translate_track(const TrackSource& track);
	private:
		std::string _service_url = "http://127.0.0.1:5000";
	};
}

