/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>

#include "message_dispatcher.hpp"

#include "app_loading_state.hpp"
#include "main_menu_state.hpp"
#include "state_stack.hpp"

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(840, 680, 32), "The Followers: Rebooted");
	window.setFramerateLimit(60);
	
	Core::MessageDispatcher dispatcher;
	State::Context context(window, dispatcher);

	StateStack stateStack(context);

	AppLoadingState appLoadingState(stateStack, context);

	dispatcher.registerHandler("state.loaded", appLoadingState);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) {
				window.close();
			}

			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Escape) {
					window.close();
				}

				if(event.key.code == sf::Keyboard::L) {
					dispatcher.pushMessage("state.loaded", "KeyLoaded");
				}

			}
		}

		dispatcher.dispatch();

		window.clear();

		appLoadingState.draw();

		window.display();
	}

	return 0;
}
