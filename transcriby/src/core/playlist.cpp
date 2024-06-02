#include "playlist.h"

namespace transcriby {
	void Playlist::add(const TrackSource& track) {
		if (std::find(_content.begin(), _content.end(), track) == _content.end())
			_content.push_back(track);
	}

	void Playlist::remove(uint id) {
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
}