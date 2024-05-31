#pragma once

#include <string>
#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

#include "core/playlist.h"
#include "ui/panels/playlist.h"

namespace transcriby {
	class Application {
	public:
		void run();
		Application(const std::string& title);
		~Application();
	private:
		void _on_update(sf::Clock& clock);
		void _handle_events();
		void _handle_dockspace(std::function<void()> hook);
	private:
		int _frame_rate = 60;
		sf::Vector2u _resolution = { 800, 600 };
		std::unique_ptr<sf::RenderWindow> _window;
	private:
		std::unique_ptr<ui::PlaylistPanel> _playlist_panel;
	};
}

