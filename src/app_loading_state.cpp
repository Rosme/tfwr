/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "app_loading_state.hpp"

#include "message_dispatcher.hpp"

#include <iostream>

AppLoadingState::AppLoadingState(StateStack& stateStack, Context context)
	: State(stateStack, context), m_progressBarUnder(sf::Vector2f(300, 40)), m_progressBarOver(sf::Vector2f(300, 40)) {

	m_progressBarUnder.setPosition(50, 50);
	m_progressBarUnder.setFillColor(sf::Color::Red);
	m_progressBarUnder.setOutlineColor(sf::Color::White);
	m_progressBarUnder.setOutlineThickness(1.5f);

	m_progressBarOver.setPosition(50, 50);
	m_progressBarOver.setFillColor(sf::Color::Black);
	m_progressBarOver.setOutlineColor(sf::Color::White);
	/*m_progressBarOver.setOutlineThickness(1.5f);*/
	context.dispatcher.pushMessage("stated.loaded", "App Loading State loaded");
}

void AppLoadingState::onMessage(const Core::Message& message, const std::string& key) {
	if(key == "state.loaded") {
		auto c = message.getContent().get<std::string>();
		std::cout << c;
		auto size = m_progressBarOver.getSize();
		m_progressBarOver.setSize(sf::Vector2f(size.x - 1, size.y));
	}
}

void AppLoadingState::draw() {
	m_context.window.draw(m_progressBarUnder);
	m_context.window.draw(m_progressBarOver);
}

bool AppLoadingState::update(sf::Time delta) {
	return true;
}

bool AppLoadingState::handleEvent(const sf::Event& event) {
	throw std::logic_error("The method or operation is not implemented.");
}
