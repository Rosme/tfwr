/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "text.hpp"

namespace Gui {

	Text::Text(const sf::Font& font, const std::string& text)
		: m_text(text, font) {}

	Text::Text(const sf::Font& font, const std::string& text, unsigned int characterSize) 
		: m_text(text, font, characterSize) {}

	void Text::setFont(const sf::Font& font) {
		m_text.setFont(font);
	}

	void Text::setString(const std::string& text) {
		m_text.setString(text);
	}

	void Text::setCharacterSize(unsigned int size) {
		m_text.setCharacterSize(size);
	}

	sf::FloatRect Text::getGlobalBounds() const {
		return m_text.getGlobalBounds();
	}

	sf::FloatRect Text::getLocalBounds() const {
		return m_text.getLocalBounds();
	}

}
