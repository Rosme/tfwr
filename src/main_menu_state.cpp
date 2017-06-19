/*
Copyright (C) - Jean-S�bastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "main_menu_state.hpp"
#include "message_dispatcher.hpp"
#include "message.hpp"
#include "resourceids.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <rsm/unused.hpp>

MainMenuState::MainMenuState(StateStack& stateStack, Context context)
	: State(stateStack, context) {
	const auto& windowSize = m_context.window.getSize();

	for(int i = 0; i < 5; ++i) {
		m_menuTexts.push_back(Gui::AnimatedText(m_context.fontHolder[Resources::FontIds::GameFont]));
	}

	m_menuTexts[0].setString("The Followers: Rebooted");
	m_menuTexts[0].setCharacterSize(80);
	m_menuTexts[0].setPosition(sf::Vector2f(windowSize.x/2.f, 100.f));
	m_menuTexts[0].setAnimationType(Gui::AnimatedText::AnimationType::Rotating);
	m_menuTexts[0].setAnimationDelay(sf::milliseconds(75));
	const auto& titleBounds = m_menuTexts[0].getGlobalBounds();
	m_menuTexts[0].setOrigin(sf::Vector2f(titleBounds.width/2, titleBounds.height/2));
	m_menuTexts[0].setRotatingAngleLimit(8.5f);
	m_menuTexts[0].setRotatingAngleStep(180.f);

	m_menuTexts[1].setString("New Game");
	m_menuTexts[1].setCharacterSize(35);
	m_menuTexts[1].setPosition(sf::Vector2f(25.f, 200.f));
	m_menuTexts[1].setAnimationType(Gui::AnimatedText::AnimationType::None);

	m_menuTexts[2].setString("Options");
	m_menuTexts[2].setCharacterSize(35);
	m_menuTexts[2].setPosition(sf::Vector2f(25.f, 250.f));

	m_menuTexts[3].setString("Credits");
	m_menuTexts[3].setCharacterSize(35);
	m_menuTexts[3].setPosition(sf::Vector2f(25.f, 300.f));

	m_menuTexts[4].setString("Exit");
	m_menuTexts[4].setCharacterSize(35);
	m_menuTexts[4].setPosition(sf::Vector2f(25.f, 350.f));

	context.dispatcher.pushMessage("state.loaded", Core::Message("main_menu_state"));
}

void MainMenuState::onMessage(const Core::Message& message, const std::string& key) {
	RSM_UNUSED(message);
	RSM_UNUSED(key);
}

void MainMenuState::draw() {
	for(auto& text : m_menuTexts) {
		m_context.window.draw(text);
	}
}

bool MainMenuState::update(const sf::Time& delta) {
	m_menuTexts[0].animate(delta);
	m_menuTexts[1].animate(delta);
	return true;
}

bool MainMenuState::handleEvent(const sf::Event& event) {
	RSM_UNUSED(event);
	return true;
}
