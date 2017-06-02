/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "message_dispatcher.hpp"
#include "message_handler.hpp"

#include <iostream>

class KeyPressedHandler : public Core::MessageHandler {
	void onMessage(const Core::Message& message, const std::string& key) override {
		std::cout << "Key: " << key << " - Message Content: " << message.getContent().get<const char*>() << std::endl;
	}
};

class KeyReleasedHandler : public Core::MessageHandler {
	void onMessage(const Core::Message& message, const std::string& key) override {
		std::cout << "Key: " << key << " - Message Content: " << message.getContent().get<const char*>() << std::endl;
	}
};

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(840, 680, 32), "The Followers: Rebooted");
	window.setFramerateLimit(60);
	
	Core::MessageDispatcher dispatcher;
	KeyPressedHandler keyPressedHandler;
	KeyReleasedHandler keyReleasedHandler;
	dispatcher.registerHandler("keypressed", keyPressedHandler);
	dispatcher.registerHandler("keyreleased", keyReleasedHandler);
	bool isPressed = false;

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
				if(event.key.code == sf::Keyboard::K && isPressed) {
					isPressed = false;
					dispatcher.pushMessage("keyreleased", Core::Message("key is released"));
				}
			}

			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::K && !isPressed) {
					isPressed = true;
					dispatcher.pushMessage("keypressed", Core::Message("Key is pressed"));
				}
			}
		}

		dispatcher.dispatch();

		window.clear();
		window.display();
	}

	return 0;
}
