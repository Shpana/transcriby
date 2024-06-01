#pragma once

#include <vector>
#include <filesystem>

namespace transcriby {
	using uint = uint64_t;
	using TrackSource = std::filesystem::path;

	class Playlist {
	public:
		void add(const TrackSource& track);
		void remove(uint id);

		void select(uint id);
		void unselect();
		bool has_selected();

		uint get_selected_id() { return _selected_id; }
		const TrackSource& get_selected() { return _content.at(_selected_id); }
		const std::vector<TrackSource>& get_content() { return _content; }
	private:
		uint _selected_id = -1;
		std::vector<TrackSource> _content;
	};
}

