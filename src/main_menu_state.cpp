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
#include "animatedtext.hpp"
#include "selectabletext.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <rsm/unused.hpp>

MainMenuState::MainMenuState(StateStack& stateStack, Context context)
	: State(stateStack, context) {
	const auto& windowSize = m_context.window.getSize();

	//auto title = std::make_unique<Gui::AnimatedText>(m_context.fontHolder[Resources::FontIds::GameFont], "The Followers: Rebooted", 80);
	m_title.setFont(m_context.fontHolder[Resources::FontIds::GameFont]);
	m_title.setString("The Followers: Rebooted");
	m_title.setCharacterSize(80);
	m_title.setPosition(sf::Vector2f(windowSize.x/2.f, 100.f));
	m_title.setAnimationType(Gui::AnimatedText::AnimationType::Rotating);
	m_title.setAnimationDelay(sf::milliseconds(75));
	const auto& titleBounds = m_title.getGlobalBounds();
	m_title.setOrigin(sf::Vector2f(titleBounds.width/2, titleBounds.height/2));
	m_title.setRotatingAngleLimit(8.5f);
	m_title.setRotatingAngleStep(180.f);

	auto newGame = std::make_unique<Gui::SelectableText>(m_context.fontHolder[Resources::FontIds::GameFont], "New Game", 35);
	newGame->setPosition(sf::Vector2f(25.f, 200.f));
	newGame->select();
	m_menuTexts.emplace_back(std::move(newGame));

	auto options = std::make_unique<Gui::SelectableText>(m_context.fontHolder[Resources::FontIds::GameFont], "Options", 35);
	options->setPosition(sf::Vector2f(25.f, 250.f));
	m_menuTexts.emplace_back(std::move(options));

	auto credits = std::make_unique<Gui::SelectableText>(m_context.fontHolder[Resources::FontIds::GameFont], "Credits", 35);
	credits->setPosition(sf::Vector2f(25.f, 300.f));
	m_menuTexts.emplace_back(std::move(credits));

	auto exit = std::make_unique<Gui::SelectableText>(m_context.fontHolder[Resources::FontIds::GameFont], "Exit", 35);
	exit->setPosition(sf::Vector2f(25.f, 350.f));
	exit->setCallback([this]() {
		m_context.dispatcher.pushMessage("game.close");
	});
	m_menuTexts.emplace_back(std::move(exit));

	context.dispatcher.pushMessage("state.loaded", Core::Message("main_menu_state"));
}

void MainMenuState::onMessage(const Core::Message& message, const std::string& key) {
	RSM_UNUSED(message);
	RSM_UNUSED(key);
}

void MainMenuState::draw() {
	m_context.window.draw(m_title);
	for(auto& text : m_menuTexts) {
		m_context.window.draw(*text);
	}
}

bool MainMenuState::update(const sf::Time& delta) {
	m_title.animate(delta);
	return true;
}

bool MainMenuState::handleEvent(const sf::Event& event) {
	if(event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::Up) {
			m_menuTexts[m_currentIndex]->unselect();
			if(m_currentIndex == 0) {
				m_currentIndex = m_menuTexts.size()-1;
			} else {
				--m_currentIndex;
			}
			m_menuTexts[m_currentIndex]->select();
		}
		if(event.key.code == sf::Keyboard::Down) {
			m_menuTexts[m_currentIndex]->unselect();
			++m_currentIndex;
			if(m_currentIndex >= m_menuTexts.size()) {
				m_currentIndex = 0;
			}
			m_menuTexts[m_currentIndex]->select();
		}
		if(event.key.code == sf::Keyboard::Return) {
			m_menuTexts[m_currentIndex]->activate();
		}
	}
	
	return true;
}
