/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(840, 680, 32), "TFW2");

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
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}
