#pragma once

#include <vector>
#include <filesystem>

namespace transcriby {
	using TrackSource = std::filesystem::path;

	using Playlist = std::vector<TrackSource>;
}

