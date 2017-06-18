/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <SFML/Window/Event.hpp>

#include "application.hpp"
#include "app_loading_state.hpp"
#include "main_menu_state.hpp"

const sf::Time Application::MaximumTimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: m_window(sf::VideoMode(840, 680, 32), "The Followers: Rebooted")
	, m_stateStack(State::Context(m_window, m_dispatcher)) {
	registerStates();

	m_stateStack.pushState(States::ID::AppLoadingState);
}

void Application::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(m_window.isOpen()) {
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while(timeSinceLastUpdate > MaximumTimePerFrame) {
			timeSinceLastUpdate -= MaximumTimePerFrame;

			handleEvents();
			m_stateStack.update(MaximumTimePerFrame);
			m_dispatcher.dispatch();

			if(m_stateStack.isEmpty()) {
				m_window.close();
			}
		}

		draw();
	}
}

void Application::registerStates() {
	m_stateStack.registerState<AppLoadingState>(States::ID::AppLoadingState);
	m_stateStack.registerState<MainMenuState>(States::ID::MainMenuState);
}

void Application::draw() {
	m_window.clear();
	m_stateStack.draw();
	m_window.display();
}

void Application::handleEvents() {
	sf::Event event;
	while(m_window.pollEvent(event)) {
		m_stateStack.handleEvents(event);

		if(event.type == sf::Event::Closed) {
			m_window.close();
		}

		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			m_window.close();
		}
	}
}
