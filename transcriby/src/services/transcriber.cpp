#include "transcriber.h"

#include <iostream>

#include "cpr/cpr.h"

namespace transcriby {
	TranscriberService::TranscriberService() {
		cpr::Response response = 
			cpr::Post(cpr::Url{_service_url}, 
				cpr::Multipart{{ "passage", cpr::File("C:\\Dev\\transcriby\\transcriby\\assets\\audio\\1.mp3")}});
		std::cout << response.status_code << std::endl;
	}
}
