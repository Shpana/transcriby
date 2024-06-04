#pragma once

#include <vector>
#include <filesystem>

#include "core/track.h"
#include "utils/event.h"

namespace transcriby {
	using uint = uint64_t;

	class Playlist {
	public:
		void add(const Track& track);
		void remove(uint id);

		void select(uint id);
		void unselect();
		bool has_selected();
		void change_state(uint id, TranscribtionState state);
		void change_transcription(uint id, const std::string& transcription);

		Event<Track> on_removing_event;
		uint get_selected_id() { return _selected_id; }
		const Track& get_selected() { return _content.at(_selected_id); }
		const std::vector<Track>& get_content() { return _content; }
	private:
		uint _selected_id = -1;
		std::vector<Track> _content;
	};
}

