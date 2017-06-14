/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "main_menu_state.hpp"

#include "message_dispatcher.hpp"
#include "message.hpp"

MainMenuState::MainMenuState(StateStack& stateStack, Context context)
	: State(stateStack, context) {

	context.dispatcher.pushMessage("state.loaded", Core::Message("main_menu_state"));
}

void MainMenuState::onMessage(const Core::Message& message, const std::string& key) {
	
}

void MainMenuState::draw() {

}

bool MainMenuState::update(sf::Time delta) {
	return true;
}

bool MainMenuState::handleEvent(const sf::Event& event) {
	throw std::logic_error("The method or operation is not implemented.");
}
