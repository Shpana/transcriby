#include "transcriber.h"

#include <assert.h>

#include "cpr/cpr.h"

namespace transcriby {
	TranscriberService::TranscriberService() {}

	std::string TranscriberService::translate_track(const TrackSource& track) {
		cpr::Response response = cpr::Post(
			cpr::Url(_service_url), 
			cpr::Multipart{ {"passage", cpr::File{track.string()}} });

		if (response.status_code == 200)
			return response.text;
		else
			assert(false);
	}
}

