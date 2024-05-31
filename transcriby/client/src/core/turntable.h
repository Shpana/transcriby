#pragma once

#include <memory>

#include <irrKlang.h>

#include "core/playlist.h"

namespace transcriby {
	class Turntable {
	public:
		Turntable();
		~Turntable();

		bool try_put_track(const TrackSource& source);
		void play();
		void pause();

		bool has_track() { return _source != TrackSource(); }
		const TrackSource& get_source() { return _source; }
	private:
		TrackSource _source;
		irrklang::ISound* _sound = nullptr;
		irrklang::ISoundEngine* _engine;
	};
}

