#pragma once

#include <filesystem>
#include <chrono>
#include <vector>

namespace transcriby {
	using TrackSource = std::filesystem::path;

	enum TranscribtionState {
		None = 0,
		InQueue, InProgress, Ready
	};

	struct Passage {
		std::string transcribtion;
		// time in seconds
		int start;
		int end;
	};

	class Track {
	public:
		Track(const TrackSource& source);

		bool operator==(const Track& other) {
			return other._source == _source;
		}

		void clear_transcribtion();
		void set_state(const TranscribtionState& state);
		void add_passage_transcribtion(const Passage& passage);

		bool has_transcription();
		const TrackSource& get_source() const { return _source; }
		const TranscribtionState& get_state() const { return _state; }
		const std::vector<Passage>& get_transcribtion() const { return _transcribtion; }
	private:
		TrackSource _source;
		TranscribtionState _state = TranscribtionState::None;
		std::vector<Passage> _transcribtion;
	};
}

