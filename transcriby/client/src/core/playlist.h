#pragma once

#include <vector>
#include <filesystem>

namespace transcriby {
	struct Track {
		std::filesystem::path source;
	};

	using Playlist = std::vector<Track>;
}

