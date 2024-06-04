#pragma once

#include <filesystem>

namespace transcriby {
	using TrackSource = std::filesystem::path;

	enum TranscribtionState {
		None = 0,
		InQueue,
		InProgress,
		Ready,
	};

	class Track {
	public:
		Track(const TrackSource& source);


		void set_transcription(const std::string& transcription);
		void set_state(const TranscribtionState& state);

		bool has_transcription();
		const std::string& get_transcribtion() const { return _transcription; }
		const TrackSource& get_source() const { return _source; }
		const TranscribtionState& get_state() const { return _state; }
	private:
		std::string _transcription = "";
		TrackSource _source;
		TranscribtionState _state = TranscribtionState::None;
	};
}

