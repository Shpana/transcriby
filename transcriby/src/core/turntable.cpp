#include "turntable.h"

namespace transcriby {
	Turntable::Turntable() {
		_engine = irrklang::createIrrKlangDevice();
	}

	Turntable::~Turntable() {
		_engine->drop();
	}

	void Turntable::put(const TrackSource& source) {
		if (has_putted())
			extract();
		_putted = source;
		_sound = _engine->play2D(_putted.string().c_str(), true, true);
		set_volume(_info.volume);
		set_playback_speed(_info.playback_speed);

		_info.is_paused = _sound->getIsPaused();
		_info.length = _sound->getPlayLength();
		_info.position = _sound->getPlayPosition();
	}

	void Turntable::extract() {
		_sound->drop();
		_engine->removeSoundSource(_putted.string().c_str());
		_putted = TrackSource();
	}

	void Turntable::play() {
		if (has_putted()) {
			_sound->setIsPaused(false);
			_info.is_paused = false;
		}
	}

	void Turntable::pause() {
		if (has_putted()) {
			_sound->setIsPaused(true);
			_info.is_paused = true;
		}
	}

	void Turntable::set_volume(float volume) {
		if (has_putted()) {
			_sound->setVolume(volume);
			_info.volume = volume;
		}
	}

	void Turntable::set_playback_speed(float speed) {
		if (has_putted()) {
			_sound->setPlaybackSpeed(speed);
			_info.playback_speed = speed;
		}
	}

	void Turntable::set_position(float position) {
		auto& info = get_info();
		if (has_putted()) {
			_sound->setPlayPosition((int)(position * info.length));
			_info.position = _sound->getPlayPosition();
		}
	}

	const TrackExecutionInfo& Turntable::get_info() {
		_info.position = _sound->getPlayPosition();
		return _info;
	}
}

