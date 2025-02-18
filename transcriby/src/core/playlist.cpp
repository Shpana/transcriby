#include "playlist.h"

namespace transcriby {
	void Playlist::add(const Track& track) {
		_content.push_back(track);
	}

	void Playlist::remove(uint id) {
		on_removing_event.notify(_content[id]);
		if (_selected_id > id)
			_selected_id--;
		if (_selected_id == id)
			unselect();
		_content.erase(_content.begin() + id);
	}

	void Playlist::select(uint id) {
		_selected_id = id;
	}

	void Playlist::unselect() {
		_selected_id = -1;
	}

	bool Playlist::has_selected() {
		return _selected_id != -1;
	}

	void Playlist::change_state(uint id, TranscribtionState state) {
		_content[id].set_state(state);
		if (state == TranscribtionState::None)
			_content[id].clear_transcribtion();
	}

	void Playlist::add_passage_transcribtion(uint id, const Passage& transcribtion) {
		_content[id].add_passage_transcribtion(transcribtion);
	}

	uint Playlist::get_track_id(const Track& track) {
		auto it = std::find(_content.begin(), _content.end(), track);
		return static_cast<uint>(it - _content.begin());
	}
}

