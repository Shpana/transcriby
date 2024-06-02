#pragma once

#include <string>

namespace transcriby {
	class TranscriberService {
	public:
		TranscriberService();
	private:
		std::string _service_url = "http://127.0.0.1:5000";
	};
}

