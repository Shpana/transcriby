#include "track.h"

namespace transcriby {
	Track::Track(const TrackSource& source)
		: _source(source) {
	}
	
	bool Track::has_transcription() {
		return _state == TranscribtionState::Ready;
	}

	void Track::set_transcription(const std::string& transcription) {
		_transcription = transcription;
	}

	void Track::set_state(const TranscribtionState& state) {
		_state = state;
	}
}

