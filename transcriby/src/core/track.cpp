#include "track.h"

namespace transcriby {
	Track::Track(const TrackSource& source)
		: _source(source) {
	}
	
	bool Track::has_transcription() {
		return _state == TranscribtionState::Ready;
	}

	void Track::clear_transcribtion() {
		_transcribtion.clear();
	}

	void Track::set_state(const TranscribtionState& state) {
		_state = state;
	}

	void Track::add_passage_transcribtion(const Passage& passage) {
		_transcribtion.push_back(passage);
	}
}

