#pragma once

#include <string>
#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

#include "core/playlist.h"
#include "services/transcriber.h"
#include "ui/panels.h"

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

		ImFont* _font;
		std::unique_ptr<sf::RenderWindow> _window;

		Playlist _playlist;
		std::vector<ui::IPanel*> _panels;
	};
}

