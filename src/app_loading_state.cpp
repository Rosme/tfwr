/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "app_loading_state.hpp"
#include "message_dispatcher.hpp"
#include "stateids.hpp"
#include "state_stack.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <rsm/logger.hpp>

AppLoadingState::AppLoadingState(StateStack& stateStack, Context context)
	: State(stateStack, context), m_stateLoadedCount(0), STATE_COUNT(static_cast<unsigned int>(States::ID::MainMenuState)) {

	context.dispatcher.pushMessage("state.loaded", "App Loading State loaded");

	loadResources();
}

void AppLoadingState::onMessage(const Core::Message& message, const std::string& key) {
	if(key == "state.loaded") {
		RSM_LOG_DEBUG(message.getContent().get<std::string>());
		++m_stateLoadedCount;
	}
}

void AppLoadingState::draw() {
	m_context.window.draw(m_loadingText);
}

bool AppLoadingState::update(const sf::Time& delta) {
	if(m_stateLoadedCount >= STATE_COUNT) {
		m_stateStack.pop();
		m_stateStack.pushState(States::ID::MainMenuState);
	}

	return true;
}

bool AppLoadingState::handleEvent(const sf::Event& event) {
	if(event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::L) {
			m_context.dispatcher.pushMessage("state.loaded", "KeyLoaded");
		}
	}

	return true;
}

void AppLoadingState::loadResources() {
	try {
		const sf::Font& gameFont = m_context.fontHolder.acquire(Resources::FontIds::GameFont, thor::Resources::fromFile<sf::Font>("fonts/TheNightCreatures.ttf"));

		m_loadingText.setFont(gameFont);
	} catch(const aurora::Exception& exception) {
		m_context.dispatcher.pushMessage("error.critical", exception.what());
	}

	m_loadingText.setString("Loading...");
	m_loadingText.setCharacterSize(52);
	const auto& windowSize = m_context.window.getSize();
	const auto& textBounds = m_loadingText.getGlobalBounds();
	m_loadingText.setPosition(sf::Vector2f(windowSize.x/2.f - textBounds.width/2.f, windowSize.y/2.f - textBounds.height/2.f));
}
