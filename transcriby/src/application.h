#pragma once

#include <string>
#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

#include "core/playlist.h"
#include "ui/panels/playlist_panel.h"
#include "ui/panels/player_panel.h"
#include "ui/panels/transcribe_panel.h"

namespace transcriby {
	class Application {
	public:
		Application(const std::string& title);
		~Application();
		void run();
	private:
		void _on_update(sf::Clock& clock);
		void _handle_events();
		void _handle_dockspace(std::function<void()> hook);
	private:
		int _frame_rate = 60;
		sf::Vector2u _resolution = { 800, 600 };
		std::unique_ptr<sf::RenderWindow> _window;

		Playlist _playlist;
		std::unique_ptr<ui::PlaylistPanel> _playlist_panel;
		std::unique_ptr<ui::PlayerPanel> _player_panel;
		std::unique_ptr<ui::TranscribePanel> _transcribe_panel;
	};
}

