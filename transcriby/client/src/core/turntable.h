#pragma once

#include <memory>

#include <irrKlang.h>

#include "core/playlist.h"

namespace transcriby {
	struct TrackExecutionInfo {
		bool is_paused;
		int length;
		int position;
		float volume = 1.0f;
		float playback_speed = 1.0f;
	};

	class Turntable {
	public:
		Turntable();
		~Turntable();

		void put(const TrackSource& source);
		void extract();
		bool has_putted() { return _putted != TrackSource(); }

		void play();
		void pause();
		void set_volume(float volume);
		void set_playback_speed(float speed);
		void set_position(float position);

		const TrackExecutionInfo& get_info();
		const TrackSource& get_putted() { return _putted; }
	private:
		TrackSource _putted;
		TrackExecutionInfo _info;
		irrklang::ISound* _sound = nullptr;
		irrklang::ISoundEngine* _engine;
	};
}

